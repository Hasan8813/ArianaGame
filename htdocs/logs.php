<?php
/**
 * تک نقطه‌ی ورودی برای همه‌چیزِ مربوط به لاگ‌ها: /logs
 *
 * هر بار که این فایل اجرا میشه (چه بار اول، چه رفرش، چه جست‌وجو، چه صفحه‌بندی)
 * از اول چک می‌کنه که نشست معتبره یا نه؛ پس هیچ راهی نیست که کسی بعد از تموم
 * شدن زمانش، با رفرش یا جست‌وجوی دوباره، بازم لاگ‌ها رو ببینه.
 */
define('ARIANA_LOGS_APP', true);
require_once __DIR__ . '/includes/bootstrap.php';
require_once __DIR__ . '/includes/views.php';

$ip = client_ip();

// ---------- خروج (فقط از همین مسیر /logs، طبق درخواست) ----------
if (isset($_GET['action']) && $_GET['action'] === 'logout') {
    destroy_session();
    header('Location: logs');
    exit;
}
if (is_session_valid() && $_SERVER['REQUEST_METHOD'] === 'POST' && ($_POST['action'] ?? '') === 'revoke_ip') {
    if (csrf_ok($_POST['csrf'] ?? null)) {
        revoke_current_access();
    }
    header('Location: logs');
    exit;
}
// ============================================================
// مرحله ۱: اگه از قبل لاگین کرده و نشستش هنوز معتبره (زمانش تموم نشده)
// ============================================================
if (is_session_valid()) {
    $view = $_GET['view'] ?? null; // 'money', 'gold' ya 'login'
    if ($view === 'money' || $view === 'gold') {
        require_once __DIR__ . '/includes/render_table.php';
        render_log_page($view);
    } elseif ($view === 'login') {
        require_once __DIR__ . '/includes/render_login_table.php';
        render_login_log_page();
    } else {
        render_choice_page();
    }
    exit;
}

// اگه قبلا لاگین کرده بوده ولی الان دیگه معتبر نیست (زمانش تموم شده/باطل شده)،
// فقط اون‌موقع نشست رو کامل پاک کن. یه نشست معمولیِ هنوز-لاگین-نکرده رو دست
// نزن، چون همین نشست حامل توکن CSRF و شمارنده‌ی تلاش‌های لاگینه که چند خط
// پایین‌تر برای خود همین درخواست بهش نیاز داریم (وگرنه فرم لاگین همیشه با
// خطای «درخواست نامعتبره» رد میشه، حتی با نام/کد درست).
if (session_status() === PHP_SESSION_ACTIVE && !empty($_SESSION['log_access'])) {
    destroy_session();
}

// ============================================================
// مرحله ۲: چک آی‌پی و فرم لاگین
// ============================================================
$ipAllowed = ip_is_authorized($ip);
$error = '';

if ($ipAllowed && $_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!login_throttle_ok($ip)) {
        $error = 'تعداد تلاش‌های ورود بیش از حد مجازه. چند دقیقه دیگه دوباره امتحان کن.';
    } elseif (!csrf_ok($_POST['csrf'] ?? null)) {
        $error = 'درخواست نامعتبره؛ صفحه رو رفرش کن و دوباره تلاش کن.';
    } else {
        $name = trim($_POST['admin_name'] ?? '');
        $code = trim($_POST['code'] ?? '');
        $row  = verify_login($ip, $name, $code);

        if ($row) {
            start_authenticated_session($row, $ip);
            header('Location: logs');
            exit;
        } else {
            login_throttle_hit($ip);
            $error = 'نام یا کد وارد شده اشتباهه یا منقضی شده.';
        }
    }
}

render_login_page($ipAllowed, $error);
