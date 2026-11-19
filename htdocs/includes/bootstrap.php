<?php
defined('ARIANA_LOGS_APP') or die('دسترسی مستقیم مجاز نیست.');

require_once __DIR__ . '/config.php';

error_reporting(E_ALL);
ini_set('display_errors', '0'); // خطاهای فنی هیچ‌وقت نباید به کاربر نمایش داده بشه

// ---------- تنظیم امن کوکی نشست، قبل از session_start ----------
if (session_status() === PHP_SESSION_NONE) {
    $isHttps = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off')
        || (($_SERVER['HTTP_X_FORWARDED_PROTO'] ?? '') === 'https');

    session_set_cookie_params([
        'lifetime' => 0,
        'path'     => '/',
        'domain'   => '',
        'secure'   => $isHttps,
        'httponly' => true,
        'samesite' => 'Lax',
    ]);
    session_name('ariana_logs_sid');
    session_start();
}

// ---------- هدرهای امنیتی + جلوگیری کامل از کش شدن صفحه ----------
// این خیلی مهمه: صفحه لاگ نباید هیچوقت توی کش مرورگر/پراکسی بمونه،
// وگرنه با دکمه Back میشه محتوای قدیمی رو بعد از تموم شدن زمان هم دید.
header('Cache-Control: no-store, no-cache, must-revalidate, max-age=0');
header('Pragma: no-cache');
header('Expires: 0');
header('X-Content-Type-Options: nosniff');
header('X-Frame-Options: DENY');
header('Referrer-Policy: no-referrer');

function db() {
    static $pdo = null;
    if ($pdo === null) {
        try {
            $pdo = new PDO(
                "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME . ";charset=utf8mb4",
                DB_USER,
                DB_PASS,
                [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]
            );
        } catch (PDOException $e) {
            die('خطا در اتصال به دیتابیس. لطفا بعدا امتحان کن.');
        }
    }
    return $pdo;
}

function client_ip() {
    return $_SERVER['REMOTE_ADDR'] ?? '0.0.0.0';
}

/** آیا برای این آی‌پی حداقل یک کد فعال (منقضی‌نشده) توی دیتابیس ثبت شده؟ */
function ip_is_authorized($ip) {
    $stmt = db()->prepare("SELECT COUNT(*) FROM " . TBL_ACCESS . " WHERE IP = :ip AND ExpireAt > NOW()");
    $stmt->execute([':ip' => $ip]);
    return $stmt->fetchColumn() > 0;
}

/** بررسی نام ادمین + کد برای این آی‌پی. اگه درست بود ردیف دیتابیس رو برمی‌گردونه، وگرنه false */
function verify_login($ip, $name, $code) {
    $stmt = db()->prepare(
        "SELECT * FROM " . TBL_ACCESS . "
         WHERE AdminName = :name AND Code = :code AND IP = :ip AND ExpireAt > NOW()
         LIMIT 1"
    );
    $stmt->execute([':name' => $name, ':code' => $code, ':ip' => $ip]);
    $row = $stmt->fetch(PDO::FETCH_ASSOC);
    return $row ?: false;
}

/**
 * چک قطعی معتبر بودن نشست.
 *
 * نکته امنیتی مهم (رفع باگ اصلی): به‌جای اینکه فقط به زمان انقضایی که یک‌بار
 * موقع لاگین توی سشن کپی شده اعتماد کنیم، هر بار مستقیم از روی همون ردیف
 * دیتابیس (منبع اصلی) دوباره چک می‌کنیم که ExpireAt هنوز نگذشته.
 * این‌طوری حتی اگه دسترسی توی دیتابیس زودتر باطل/حذف بشه یا زمانش تموم بشه،
 * همون لحظه (توی همون رفرش/جست‌وجوی بعدی) نشست هم باطل میشه؛ دیگه امکان نداره
 * یه نشست قدیمی با یه زمان کش‌شده بیشتر از حد مجازش زنده بمونه.
 */
function is_session_valid() {
    if (empty($_SESSION['log_access']) || empty($_SESSION['log_access_id']) || empty($_SESSION['log_ip'])) {
        return false;
    }
    if ($_SESSION['log_ip'] !== client_ip()) {
        return false;
    }
    // سقف مطلق نشست (دفاع دوم)
    if (empty($_SESSION['log_started_at']) || (time() - $_SESSION['log_started_at']) > SESSION_HARD_LIMIT) {
        return false;
    }
    // چک زنده روی دیتابیس -> منبع اصلی حقیقت
    $stmt = db()->prepare(
        "SELECT COUNT(*) FROM " . TBL_ACCESS . " WHERE id = :id AND IP = :ip AND ExpireAt > NOW()"
    );
    $stmt->execute([':id' => $_SESSION['log_access_id'], ':ip' => client_ip()]);
    return $stmt->fetchColumn() > 0;
}

function start_authenticated_session($row, $ip) {
    // جلوگیری از Session Fixation
    session_regenerate_id(true);
    $_SESSION['log_access']     = true;
    $_SESSION['log_access_id']  = $row['id'] ?? null;
    $_SESSION['log_admin_name'] = $row['AdminName'] ?? '';
    $_SESSION['log_ip']         = $ip;
    $_SESSION['log_started_at'] = time();
    unset($_SESSION['login_attempts']);
}

function destroy_session() {
    $_SESSION = [];
    if (ini_get('session.use_cookies')) {
        $p = session_get_cookie_params();
        setcookie(session_name(), '', time() - 42000, $p['path'], $p['domain'], $p['secure'], $p['httponly']);
    }
    session_destroy();
}

function csrf_token() {
    if (empty($_SESSION['csrf_token'])) {
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
    }
    return $_SESSION['csrf_token'];
}

function csrf_ok($token) {
    return is_string($token) && !empty($_SESSION['csrf_token']) && hash_equals($_SESSION['csrf_token'], $token);
}

/** محدود کردن تلاش‌های ورود بر اساس IP در دیتابیس، نه سشن — با پاک کردن کوکی دور زده نمیشه */
function ensure_throttle_table() {
    static $done = false;
    if ($done) return;
    $done = true;
    try {
        db()->exec("CREATE TABLE IF NOT EXISTS LoginThrottle (
            id INT AUTO_INCREMENT PRIMARY KEY,
            IP VARCHAR(45) NOT NULL,
            AttemptAt DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
            INDEX(IP, AttemptAt)
        )");
    } catch (PDOException $e) {}
}

function login_throttle_ok($ip) {
    ensure_throttle_table();
    $stmt = db()->prepare("SELECT COUNT(*) FROM LoginThrottle WHERE IP = :ip AND AttemptAt > (NOW() - INTERVAL 300 SECOND)");
    $stmt->execute([':ip' => $ip]);
    return $stmt->fetchColumn() < 5;
}

function login_throttle_hit($ip) {
    ensure_throttle_table();
    $stmt = db()->prepare("INSERT INTO LoginThrottle (IP) VALUES (:ip)");
    $stmt->execute([':ip' => $ip]);
    db()->exec("DELETE FROM LoginThrottle WHERE AttemptAt < (NOW() - INTERVAL 1 HOUR)");
    usleep(400000);
}

/** خروج سخت: هم سشن پاک میشه، هم ردیف کد از AdminLogAccess حذف میشه (باید دوباره /codelog بزنه) */
function revoke_current_access() {
    if (!empty($_SESSION['log_access_id']) && !empty($_SESSION['log_ip'])) {
        $stmt = db()->prepare("DELETE FROM " . TBL_ACCESS . " WHERE id = :id AND IP = :ip");
        $stmt->execute([':id' => $_SESSION['log_access_id'], ':ip' => $_SESSION['log_ip']]);
    }
    destroy_session();
}