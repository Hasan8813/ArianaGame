<?php
if ($_SERVER['REMOTE_ADDR'] !== '127.0.0.1') {
    http_response_code(403);
    die('Access denied');
}
require 'Mailer/src/PHPMailer.php';
require 'Mailer/src/SMTP.php';
require 'Mailer/src/Exception.php';
use PHPMailer\PHPMailer\PHPMailer;

$email = $_POST['email'];
$code  = $_POST['code'];

$mail = new PHPMailer(true);
try {
    $mail->isSMTP();
    $mail->Host = 'smtp.gmail.com';
    $mail->SMTPAuth = true;
    $mail->Username = 'arianagamerpg@gmail.com';
    $mail->Password = 'larvzqylwrwmvdyx';
    $mail->SMTPSecure = 'ssl';
    $mail->Port = 465;

    $mail->CharSet = 'UTF-8';
    $mail->setFrom('arianagamerpg@gmail.com', 'Ariana Game');
    $mail->addAddress($email);
    $mail->isHTML(true);
    $mail->Subject = 'کد تایید ایمیل شما - Ariana Game';

    $mail->Body = "
    <html dir='rtl'>
    <body style='margin:0; padding:0; background-color:#0f0a1e; font-family:Tahoma, Arial, sans-serif;'>
        <table width='100%' cellpadding='0' cellspacing='0' style='background:linear-gradient(135deg,#1a0b2e 0%,#2d1250 50%,#0f0a1e 100%); padding:40px 0;'>
            <tr>
                <td align='center'>
                    <table width='460' cellpadding='0' cellspacing='0' style='background-color:#1c1230; border-radius:18px; overflow:hidden; box-shadow:0 8px 30px rgba(124,58,237,0.35); border:1px solid rgba(168,85,247,0.25);'>
                        <tr>
                            <td style='background:linear-gradient(135deg,#7c3aed 0%,#a855f7 50%,#c084fc 100%); padding:35px; text-align:center;'>
                                <span style='color:#ffffff; font-size:26px; font-weight:bold; letter-spacing:1px; text-shadow:0 2px 8px rgba(0,0,0,0.25);'>✦ Ariana Game ✦</span>
                            </td>
                        </tr>
                        <tr>
                            <td style='padding:40px 32px; text-align:center;'>
                                <p style='font-size:18px; color:#f3e8ff; margin:0 0 12px; font-weight:bold;'>سلام 👋</p>
                                <p style='font-size:14px; color:#c4b5d9; margin:0 0 28px; line-height:1.9;'>
                                 برای تایید ایمیل حساب کاربری‌تان در سرور از کد زیر استفاده کنید
                                </p>
                                <div style='background:linear-gradient(135deg,#2d1250 0%,#3b1a63 100%); border:1px solid rgba(168,85,247,0.5); border-radius:12px; padding:22px; margin-bottom:28px; box-shadow:inset 0 0 20px rgba(168,85,247,0.15);'>
                                    <span style='font-size:34px; letter-spacing:10px; font-weight:bold; color:#c084fc; text-shadow:0 0 20px rgba(192,132,252,0.6);'>$code</span>
                                </div>
                                <p style='font-size:13px; color:#8b7aa0; margin:0; line-height:1.9;'>
                                    این کد تا ۵ دقیقه دیگر معتبر است.<br>
                                    اگر شما این درخواست را نداده‌اید، این ایمیل را نادیده بگیرید.
                                </p>
                            </td>
                        </tr>
                        <tr>
                            <td style='background-color:#150c26; padding:20px; text-align:center; border-top:1px solid rgba(168,85,247,0.15);'>
                                <span style='font-size:11px; color:#6b5b7d;'>&copy; Ariana Game - تمامی حقوق محفوظ است</span>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
        </table>
    </body>
    </html>
    ";

    $mail->AltBody = "کد تایید ایمیل شما: $code (این کد تا ۵ دقیقه معتبر است)";

    $mail->send();
    echo "OK";
} catch (Exception $e) {
    echo "ERROR: {$mail->ErrorInfo}";
}
