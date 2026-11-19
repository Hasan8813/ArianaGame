<?php
defined('ARIANA_LOGS_APP') or die('دسترسی مستقیم مجاز نیست.');

function render_login_page($ipAllowed, $error) {
?>
<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="robots" content="noindex, nofollow">
<title>ورود به پنل لاگ‌ها</title>
<style>
  * { box-sizing: border-box; }
  :root {
      --bg: #16171a; --panel: #1f2126; --panel-2: #24262c;
      --border: #33353c; --text: #e4e4e7; --muted: #9a9ba3;
      --accent: #4f8ef7; --accent-hover: #6ba0ff; --red: #f24b4b;
  }
  body {
      font-family: "Segoe UI", Tahoma, Arial, sans-serif;
      background: var(--bg); color: var(--text);
      margin: 0; min-height: 100vh; display: flex;
      align-items: center; justify-content: center; padding: 16px;
  }
  .card {
      background: var(--panel); border: 1px solid var(--border);
      border-radius: 14px; padding: 28px; width: 100%; max-width: 380px;
      box-shadow: 0 4px 20px rgba(0,0,0,0.35);
  }
  h2 { margin: 0 0 6px; color: #fff; font-size: 19px; text-align: center; }
  p.sub { color: var(--muted); font-size: 13px; text-align: center; margin: 0 0 20px; }
  .field { margin-bottom: 14px; display: flex; flex-direction: column; }
  label { font-size: 12px; color: var(--accent); margin-bottom: 6px; font-weight: 600; }
  input {
      background: var(--panel-2); border: 1px solid var(--border); color: var(--text);
      padding: 10px 12px; border-radius: 8px; font-size: 14px; outline: none;
  }
  input:focus { border-color: var(--accent); }
  button {
      width: 100%; padding: 11px; border: none; border-radius: 8px;
      background: var(--accent); color: #fff; font-size: 14px; font-weight: 700;
      cursor: pointer; margin-top: 6px;
  }
  button:hover { background: var(--accent-hover); }
  .error {
      background: rgba(242,75,75,0.12); border: 1px solid var(--red); color: var(--red);
      padding: 10px 12px; border-radius: 8px; font-size: 13px; margin-bottom: 14px; text-align: center;
  }
  .denied { color: var(--red); text-align: center; font-size: 14px; line-height: 1.8; }
</style>
</head>
<body>
<div class="card">
  <?php if (!$ipAllowed): ?>
    <h2>دسترسی مجاز نیست</h2>
    <p class="denied">
      برای آی‌پی شما هیچ کد فعالی ثبت نشده.<br>
      از داخل بازی دستور <b>/codelog</b> رو بزن تا کد دریافت کنی.
    </p>
  <?php else: ?>
    <h2>ورود به پنل لاگ‌ها</h2>
    <p class="sub">نام ادمین و کدی که در بازی گرفتی رو وارد کن</p>
    <?php if ($error): ?>
      <div class="error"><?= htmlspecialchars($error) ?></div>
    <?php endif; ?>
    <form method="post">
      <input type="hidden" name="csrf" value="<?= htmlspecialchars(csrf_token()) ?>">
      <div class="field">
        <label>نام ادمین</label>
        <input type="text" name="admin_name" required autocomplete="off">
      </div>
      <div class="field">
        <label>کد یک‌بار مصرف</label>
        <input type="text" name="code" required autocomplete="off" maxlength="6" inputmode="numeric">
      </div>
      <button type="submit">ورود</button>
    </form>
  <?php endif; ?>
</div>
</body>
</html>
<?php
}

function render_choice_page() {
    $adminName = htmlspecialchars($_SESSION['log_admin_name'] ?? '');
?>
<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta name="robots" content="noindex, nofollow">
<title>پنل لاگ‌ها</title>
<style>
  * { box-sizing: border-box; }
  body {
    margin: 0; min-height: 100vh; display: flex; flex-direction: column;
    align-items: center; justify-content: center;
    background: radial-gradient(circle at 50% 20%, #1c1f26 0%, #0b0d11 70%);
    font-family: "Segoe UI", Tahoma, sans-serif;
  }
  .topbar {
    position: fixed; top: 0; left: 0; right: 0; display: flex;
    justify-content: space-between; align-items: center; padding: 14px 20px;
    color: #9a9ba3; font-size: 13px;
  }
  .topbar a { color: #f24b4b; text-decoration: none; font-weight: 600; }
  .wrap { text-align: center; }
  .wrap h1 { color: #e7e7e7; font-weight: 600; letter-spacing: 1px; margin-bottom: 40px; font-size: 22px; }
  .buttons { display: flex; gap: 28px; justify-content: center; flex-wrap: wrap; }
  .card {
    width: 210px; padding: 34px 20px; border-radius: 16px; text-decoration: none;
    display: flex; flex-direction: column; align-items: center; gap: 12px;
    font-size: 18px; font-weight: 700; transition: transform .18s ease, box-shadow .18s ease;
    border: 1px solid rgba(255,255,255,0.08);
  }
  .card:hover { transform: translateY(-6px); }
  .card .icon { font-size: 40px; }
  .gold { background: linear-gradient(145deg, #4a3a10, #1c1710); color: #ffd76a; box-shadow: 0 8px 24px rgba(212, 160, 23, 0.15); }
  .gold:hover { box-shadow: 0 12px 30px rgba(212, 175, 55, 0.35); border-color: #d4af37; }
  .money { background: linear-gradient(145deg, #103a1f, #101c14); color: #6dffa0; box-shadow: 0 8px 24px rgba(30, 180, 90, 0.15); }
  .money:hover { box-shadow: 0 12px 30px rgba(30, 200, 100, 0.35); border-color: #2ecc71; }
  .login { background: linear-gradient(145deg, #1a2a3a, #0f1a24); color: #6ab8ff; box-shadow: 0 8px 24px rgba(30, 120, 200, 0.15); }
  .login:hover { box-shadow: 0 12px 30px rgba(30, 140, 220, 0.35); border-color: #4aa8f0; }
</style>
</head>
<body>
  <div class="topbar">
    <span><?= $adminName !== '' ? 'خوش اومدی، ' . $adminName : '' ?></span>
    <a href="?action=logout">خروج</a>
  </div>
  <div class="wrap">
    <h1>پنل مدیریت لاگ‌ها</h1>
    <div class="buttons">
      <a href="?view=gold" class="card gold">
        <span class="icon">🪙</span>
        Gold Logs
      </a>
      <a href="?view=money" class="card money">
        <span class="icon">💵</span>
        Money Logs
      </a>
      <a href="?view=login" class="card login">
        <span class="icon">🛰️</span>
        Login / IP Logs
      </a>
    </div>
  </div>
</body>
</html>
<?php
}
