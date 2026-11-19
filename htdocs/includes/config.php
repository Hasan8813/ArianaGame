<?php
// جلوگیری از اجرای مستقیم این فایل (حتی اگه یه روز تنظیمات وب‌سرور عوض بشه)
defined('ARIANA_LOGS_APP') or die('دسترسی مستقیم مجاز نیست.');

// ================== تنظیمات اتصال به دیتابیس ==================
// این فایل تنها جایی هست که این اطلاعات نوشته شده (قبلا توی ۳ فایل جدا تکرار شده بود)
define('DB_HOST', '127.0.0.1');
define('DB_NAME', 'ariana');
define('DB_USER', 'ArianaGames');
define('DB_PASS', '88Mohamad13@');

define('TBL_MONEY',  'MoneyLog');
define('TBL_GOLD',   'GoldLog');
define('TBL_ACCESS', 'AdminLogAccess');
define('TBL_LOGIN',  'AccountLoginLog');

// سقف مطلق نشست به ثانیه (دفاع دوم، حتی اگه ExpireAt توی دیتابیس یه چیز عجیب باشه)
define('SESSION_HARD_LIMIT', 3600); // ۱ ساعت

/*
  توصیه امنیتی: چون این پسورد قبلا داخل چند فایل جدا و به‌صورت متن ساده
  ذخیره شده بود، بهتره بعد از نصب نسخه جدید، پسورد یوزر ArianaGames رو
  توی MySQL عوض کنی و همینجا آپدیت کنی.
*/
