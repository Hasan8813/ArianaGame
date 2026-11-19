<?php
declare(strict_types=1);

$serverName = 'ARIANA';
$serverTag = 'ROLEPLAY';
$serverIp   = '100.78.167.13:7777';

$features = [
    ['icon' => '⚡', 'title' => 'گیم‌پلی روان', 'text' => 'طراحی شده برای تجربه سریع، تمیز و بدون شلوغی.'],
    ['icon' => '◈', 'title' => 'جامعه فعال', 'text' => 'محیطی برای بازی، تعامل و ساختن تجربه‌های جدید.'],
    ['icon' => '✦', 'title' => 'فضای مدرن', 'text' => 'رابط و هویت بصری متفاوت با تمرکز روی تجربه بازیکن.'],
];

$steps = [
    ['01', 'نصب SA-MP', 'کلاینت SA-MP را روی دستگاهت آماده کن.'],
    ['02', 'افزودن IP', 'آدرس سرور را در بخش Favorites وارد کن.'],
    ['03', 'ورود به بازی', 'سرور را انتخاب کن و وارد دنیای ARIANA شو.'],
];
?>
<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover">
    <meta name="theme-color" content="#08070d">
    <meta name="description" content="معرفی سرور ARIANA Roleplay | SA-MP">
    <title><?= htmlspecialchars($serverName) ?> • <?= htmlspecialchars($serverTag) ?></title>

    <style>
        :root{
            --bg:#07060b;
            --panel:rgba(255,255,255,.055);
            --panel-strong:rgba(255,255,255,.085);
            --border:rgba(255,255,255,.10);
            --text:#f7f4ff;
            --muted:#aaa4b9;
            --purple:#9b4dff;
            --purple-2:#6c25d9;
            --purple-soft:#c78cff;
            --shadow:0 25px 80px rgba(0,0,0,.45);
            --radius:26px;
        }

        *{box-sizing:border-box}
        html{scroll-behavior:smooth}
        body{
            margin:0;
            color:var(--text);
            background:
                radial-gradient(circle at 15% 8%, rgba(142,64,255,.18), transparent 30%),
                radial-gradient(circle at 90% 16%, rgba(115,36,230,.14), transparent 28%),
                radial-gradient(circle at 50% 100%, rgba(86,27,181,.12), transparent 34%),
                var(--bg);
            font-family:Tahoma, Arial, sans-serif;
            line-height:1.8;
            overflow-x:hidden;
        }

        a{color:inherit;text-decoration:none}
        button{font:inherit}

        .shell{
            width:min(1180px, calc(100% - 32px));
            margin:auto;
        }

        .topbar{
            position:sticky;
            top:14px;
            z-index:20;
            margin:14px auto 0;
            width:min(1180px, calc(100% - 32px));
            padding:10px;
            border:1px solid var(--border);
            border-radius:20px;
            background:rgba(12,10,18,.72);
            backdrop-filter:blur(16px);
            -webkit-backdrop-filter:blur(16px);
            box-shadow:0 14px 50px rgba(0,0,0,.26);
        }

        .nav{
            display:flex;
            align-items:center;
            justify-content:space-between;
            gap:16px;
        }

        .brand{
            display:flex;
            align-items:center;
            gap:10px;
            min-width:0;
        }

        .brand-mark{
            width:40px;
            height:40px;
            display:grid;
            place-items:center;
            border-radius:13px;
            background:linear-gradient(145deg,var(--purple-soft),var(--purple-2));
            box-shadow:0 12px 28px rgba(127,46,227,.35);
            font-size:19px;
            font-weight:900;
        }

        .brand-copy{display:flex;flex-direction:column;line-height:1.2}
        .brand-name{font-size:14px;font-weight:900;letter-spacing:.12em}
        .brand-tag{font-size:10px;color:var(--muted);margin-top:3px;letter-spacing:.16em}

        .nav-links{display:flex;gap:6px}
        .nav-links a{
            padding:8px 12px;
            color:#d2cedb;
            border-radius:12px;
            font-size:12px;
            transition:.2s ease;
        }
        .nav-links a:hover{background:rgba(255,255,255,.06);color:#fff}

        .hero{
            min-height:calc(100vh - 90px);
            display:grid;
            place-items:center;
            padding:58px 0 70px;
        }

        .hero-grid{
            display:grid;
            grid-template-columns:1.18fr .82fr;
            gap:22px;
            align-items:stretch;
            width:100%;
        }

        .glass{
            background:linear-gradient(180deg, rgba(255,255,255,.075), rgba(255,255,255,.035));
            border:1px solid var(--border);
            box-shadow:var(--shadow);
            border-radius:var(--radius);
            backdrop-filter:blur(14px);
            -webkit-backdrop-filter:blur(14px);
        }

        .hero-card{
            position:relative;
            overflow:hidden;
            padding:clamp(26px,5vw,58px);
            isolation:isolate;
        }

        .hero-card::before{
            content:"";
            position:absolute;
            width:330px;
            height:330px;
            top:-170px;
            left:-130px;
            background:radial-gradient(circle, rgba(167,91,255,.25), transparent 65%);
            pointer-events:none;
            z-index:-1;
        }

        .eyebrow{
            display:inline-flex;
            align-items:center;
            gap:8px;
            padding:7px 12px;
            border:1px solid rgba(199,140,255,.22);
            border-radius:999px;
            background:rgba(155,77,255,.08);
            color:#d9bbff;
            font-size:11px;
            font-weight:700;
        }

        .dot{
            width:7px;height:7px;border-radius:50%;
            background:#c987ff;
            box-shadow:0 0 18px rgba(201,135,255,.9);
        }

        h1{
            margin:20px 0 10px;
            font-size:clamp(42px, 7vw, 82px);
            line-height:.98;
            letter-spacing:-.055em;
        }

        .gradient-text{
            background:linear-gradient(90deg,#fff 10%,#d9b8ff 52%,#9250ff 100%);
            -webkit-background-clip:text;
            background-clip:text;
            color:transparent;
        }

        .hero-sub{
            max-width:700px;
            margin:0 0 28px;
            color:#b6b0c0;
            font-size:clamp(14px,1.6vw,17px);
        }

        .actions{
            display:flex;
            flex-wrap:wrap;
            gap:10px;
        }

        .btn{
            border:0;
            border-radius:15px;
            padding:13px 18px;
            cursor:pointer;
            transition:transform .18s ease, box-shadow .18s ease, background .18s ease;
        }

        .btn:hover{transform:translateY(-2px)}
        .btn-primary{
            color:#fff;
            background:linear-gradient(135deg,#b56cff,#7327e2);
            box-shadow:0 16px 34px rgba(121,39,226,.28);
        }

        .btn-secondary{
            color:#ece8f2;
            background:rgba(255,255,255,.055);
            border:1px solid var(--border);
        }

        .ip-card{
            display:flex;
            flex-direction:column;
            justify-content:space-between;
            padding:24px;
        }

        .ip-top{
            display:flex;
            justify-content:space-between;
            align-items:center;
            gap:12px;
        }

        .label{font-size:11px;color:var(--muted)}
        .status{
            display:inline-flex;
            align-items:center;
            gap:7px;
            font-size:11px;
            color:#d9c5ff;
            padding:7px 10px;
            border-radius:999px;
            border:1px solid rgba(199,140,255,.17);
            background:rgba(155,77,255,.07);
        }

        .status i{
            display:block;
            width:7px;height:7px;border-radius:50%;
            background:#c987ff;
            box-shadow:0 0 12px rgba(201,135,255,.8);
        }

        .ip-box{
            margin-top:26px;
            padding:18px;
            border-radius:20px;
            background:rgba(0,0,0,.20);
            border:1px solid rgba(255,255,255,.07);
        }

        .ip{
            font-family:Consolas, monospace;
            font-size:clamp(20px,4vw,34px);
            letter-spacing:.02em;
            direction:ltr;
            text-align:center;
            white-space:nowrap;
        }

        .copy-btn{
            width:100%;
            margin-top:14px;
            padding:12px;
            background:rgba(155,77,255,.11);
            border:1px solid rgba(155,77,255,.23);
            color:#e5d4ff;
            border-radius:13px;
            cursor:pointer;
            transition:.2s ease;
        }
        .copy-btn:hover{background:rgba(155,77,255,.18)}

        .mini{
            margin-top:22px;
            display:grid;
            grid-template-columns:repeat(2,1fr);
            gap:10px;
        }

        .mini > div{
            padding:14px;
            border-radius:18px;
            background:rgba(255,255,255,.035);
            border:1px solid rgba(255,255,255,.06);
        }

        .mini b{display:block;font-size:15px}
        .mini span{display:block;margin-top:2px;color:var(--muted);font-size:10px}

        section{padding:18px 0 80px}
        .section-head{
            display:flex;
            align-items:end;
            justify-content:space-between;
            gap:18px;
            margin-bottom:18px;
        }

        .section-head h2{
            margin:0;
            font-size:clamp(24px,4vw,38px);
            letter-spacing:-.03em;
        }

        .section-head p{
            margin:0;
            color:var(--muted);
            font-size:13px;
            max-width:520px;
        }

        .cards{
            display:grid;
            grid-template-columns:repeat(3,1fr);
            gap:14px;
        }

        .card{
            padding:22px;
            border-radius:22px;
            background:linear-gradient(180deg,rgba(255,255,255,.055),rgba(255,255,255,.025));
            border:1px solid rgba(255,255,255,.075);
            transition:transform .2s ease, border-color .2s ease, background .2s ease;
        }

        .card:hover{
            transform:translateY(-4px);
            border-color:rgba(183,120,255,.23);
            background:linear-gradient(180deg,rgba(166,88,255,.09),rgba(255,255,255,.025));
        }

        .icon{
            width:45px;height:45px;
            display:grid;place-items:center;
            border-radius:15px;
            background:rgba(155,77,255,.11);
            border:1px solid rgba(155,77,255,.18);
            font-size:18px;
            margin-bottom:16px;
        }

        .card h3{margin:0 0 4px;font-size:16px}
        .card p{margin:0;color:var(--muted);font-size:12px;line-height:1.9}

        .steps{
            display:grid;
            grid-template-columns:repeat(3,1fr);
            gap:14px;
        }

        .step{
            display:flex;
            align-items:flex-start;
            gap:14px;
            padding:20px;
        }

        .num{
            flex:0 0 42px;
            width:42px;height:42px;
            display:grid;place-items:center;
            border-radius:14px;
            background:linear-gradient(145deg,rgba(193,133,255,.25),rgba(106,32,211,.18));
            border:1px solid rgba(199,140,255,.18);
            color:#d9b7ff;
            font-family:Consolas,monospace;
            font-weight:700;
        }

        .step h3{margin:0 0 3px;font-size:14px}
        .step p{margin:0;color:var(--muted);font-size:11px;line-height:1.85}

        .footer{
            padding:28px 0 36px;
            color:#8f899a;
            font-size:11px;
            text-align:center;
        }

        .toast{
            position:fixed;
            left:50%;
            bottom:22px;
            transform:translate(-50%,20px);
            opacity:0;
            pointer-events:none;
            z-index:40;
            padding:11px 15px;
            border-radius:13px;
            background:rgba(18,14,26,.93);
            border:1px solid rgba(199,140,255,.18);
            color:#efe9f6;
            font-size:11px;
            box-shadow:0 16px 40px rgba(0,0,0,.35);
            transition:.22s ease;
        }

        .toast.show{
            opacity:1;
            transform:translate(-50%,0);
        }

        @media (max-width: 900px){
            .hero{padding-top:36px}
            .hero-grid{grid-template-columns:1fr}
            .cards,.steps{grid-template-columns:1fr}
            .ip-card{min-height:unset}
        }

        @media (max-width: 620px){
            .shell,.topbar{width:min(100% - 20px,1180px)}
            .topbar{top:8px;margin-top:8px}
            .nav-links{display:none}
            .hero{min-height:auto;padding:38px 0 42px}
            .hero-card{padding:24px 20px}
            .ip-card{padding:19px}
            h1{font-size:50px}
            .hero-sub{font-size:13px;line-height:2}
            .actions{display:grid}
            .btn{width:100%}
            section{padding-bottom:56px}
            .section-head{display:block}
            .section-head p{margin-top:8px}
            .mini{grid-template-columns:1fr 1fr}
        }

        @media (prefers-reduced-motion: reduce){
            html{scroll-behavior:auto}
            *{transition:none!important}
        }
    </style>
</head>
<body>

<header class="topbar">
    <nav class="nav">
        <a href="#" class="brand" aria-label="ARIANA">
            <span class="brand-mark">A</span>
            <span class="brand-copy">
                <span class="brand-name"><?= htmlspecialchars($serverName) ?></span>
                <span class="brand-tag"><?= htmlspecialchars($serverTag) ?> SERVER</span>
            </span>
        </a>

        <div class="nav-links">
            <a href="#features">ویژگی‌ها</a>
            <a href="#join">نحوه ورود</a>
            <a href="#server">سرور</a>
        </div>
    </nav>
</header>

<main>
    <section class="hero" id="server">
        <div class="shell hero-grid">

            <div class="glass hero-card">
                <span class="eyebrow"><span class="dot"></span> SA-MP ROLEPLAY • NEXT ERA</span>

                <h1>
                    دنیای <span class="gradient-text">ARIANA</span><br>
                    برای بازی کردن ساخته شده.
                </h1>

                <p class="hero-sub">
                    یک معرفی ساده اما حرفه‌ای برای سرور شما؛
                    سریع، سبک، مناسب موبایل و دسکتاپ و بدون وابستگی به کتابخانه‌های سنگین.
                </p>

                <div class="actions">
                    <button class="btn btn-primary" type="button" onclick="copyIP()">
                        کپی IP سرور
                    </button>
                    <a class="btn btn-secondary" href="#join">
                        راهنمای ورود
                    </a>
                </div>
            </div>

            <aside class="glass ip-card">
                <div>
                    <div class="ip-top">
                        <span class="label">آدرس اتصال</span>
                        <span class="status"><i></i> ARIANA ONLINE</span>
                    </div>

                    <div class="ip-box">
                        <div class="ip" id="serverIp"><?= htmlspecialchars($serverIp) ?></div>
                        <button class="copy-btn" type="button" onclick="copyIP()">
                            کپی آدرس
                        </button>
                    </div>
                </div>

                <div class="mini">
                    <div>
                        <b>SA-MP</b>
                        <span>GTA Multiplayer</span>
                    </div>
                    <div>
                        <b>ROLEPLAY</b>
                        <span>Immersive World</span>
                    </div>
                </div>
            </aside>

        </div>
    </section>

    <section id="features">
        <div class="shell">
            <div class="section-head">
                <div>
                    <div class="label">WHY ARIANA</div>
                    <h2>ساده، سریع، متفاوت.</h2>
                </div>
                <p>ساختار صفحه عمداً سبک نگه داشته شده تا روی گوشی‌های معمولی هم سریع باز شود.</p>
            </div>

            <div class="cards">
                <?php foreach ($features as $feature): ?>
                    <article class="card">
                        <div class="icon"><?= $feature['icon'] ?></div>
                        <h3><?= htmlspecialchars($feature['title']) ?></h3>
                        <p><?= htmlspecialchars($feature['text']) ?></p>
                    </article>
                <?php endforeach; ?>
            </div>
        </div>
    </section>

    <section id="join">
        <div class="shell">
            <div class="section-head">
                <div>
                    <div class="label">GET IN</div>
                    <h2>ورود به سرور</h2>
                </div>
                <p>سه مرحله ساده تا ورود به ARIANA.</p>
            </div>

            <div class="glass steps">
                <?php foreach ($steps as $step): ?>
                    <div class="step">
                        <div class="num"><?= htmlspecialchars($step[0]) ?></div>
                        <div>
                            <h3><?= htmlspecialchars($step[1]) ?></h3>
                            <p><?= htmlspecialchars($step[2]) ?></p>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
    </section>
</main>

<footer class="footer">
    <?= htmlspecialchars($serverName) ?> • <?= htmlspecialchars($serverTag) ?> • <?= date('Y') ?>
</footer>

<div class="toast" id="toast">IP سرور کپی شد ✓</div>

<script>
function copyIP(){
    const ip = document.getElementById('serverIp').textContent.trim();
    const done = () => {
        const toast = document.getElementById('toast');
        toast.classList.add('show');
        clearTimeout(window.__toastTimer);
        window.__toastTimer = setTimeout(() => toast.classList.remove('show'), 1600);
    };

    if (navigator.clipboard && window.isSecureContext) {
        navigator.clipboard.writeText(ip).then(done).catch(() => fallbackCopy(ip));
    } else {
        fallbackCopy(ip);
    }
}

function fallbackCopy(text){
    const el = document.createElement('textarea');
    el.value = text;
    el.style.position = 'fixed';
    el.style.opacity = '0';
    document.body.appendChild(el);
    el.select();
    try { document.execCommand('copy'); } catch(e) {}
    el.remove();

    const toast = document.getElementById('toast');
    toast.classList.add('show');
    clearTimeout(window.__toastTimer);
    window.__toastTimer = setTimeout(() => toast.classList.remove('show'), 1600);
}
</script>

</body>
</html>
