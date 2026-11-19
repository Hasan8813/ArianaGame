<?php
defined('ARIANA_LOGS_APP') or die('دسترسی مستقیم مجاز نیست.');

function render_login_log_page() {
    $pdo = db();
    $TABLE = TBL_LOGIN;

    $ALLOWED_PER_PAGE = [20, 40, 50, 100];
    $PER_PAGE = isset($_GET['perPage']) && in_array((int)$_GET['perPage'], $ALLOWED_PER_PAGE)
        ? (int)$_GET['perPage'] : 20;

    function lg($key) {
        return isset($_GET[$key]) && trim($_GET[$key]) !== '' ? trim($_GET[$key]) : null;
    }

    $f_name     = lg('playerName');
    $f_pid      = lg('playerPID');
    $f_ip       = lg('ip');
    $f_gpci     = lg('gpci');
    $f_dateFrom = lg('dateFrom');
    $f_dateTo   = lg('dateTo');

    $where = []; $params = [];
    if ($f_name !== null) { $where[] = "AccountName LIKE :name"; $params[':name'] = "%$f_name%"; }
    if ($f_pid !== null && is_numeric($f_pid)) { $where[] = "AccountPID = :pid"; $params[':pid'] = (int)$f_pid; }
    if ($f_ip !== null) { $where[] = "IP LIKE :ip"; $params[':ip'] = "%$f_ip%"; }
    if ($f_gpci !== null) { $where[] = "GPCI LIKE :gpci"; $params[':gpci'] = "%$f_gpci%"; }
    if ($f_dateFrom !== null) { $where[] = "LoginTime >= :dateFrom"; $params[':dateFrom'] = $f_dateFrom . " 00:00:00"; }
    if ($f_dateTo !== null) { $where[] = "LoginTime <= :dateTo"; $params[':dateTo'] = $f_dateTo . " 23:59:59"; }

    $whereSql = $where ? ("WHERE " . implode(" AND ", $where)) : "";

    $countStmt = $pdo->prepare("SELECT COUNT(*) FROM `$TABLE` $whereSql");
    $countStmt->execute($params);
    $totalRows  = (int)$countStmt->fetchColumn();
    $totalPages = max(1, (int)ceil($totalRows / $PER_PAGE));

    $page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
    if ($page < 1) $page = 1;
    if ($page > $totalPages) $page = $totalPages;
    $offset = ($page - 1) * $PER_PAGE;

    $sql = "SELECT id, AccountName, AccountPID, IP, GPCI, LoginTime FROM `$TABLE` $whereSql ORDER BY id DESC LIMIT :limit OFFSET :offset";
    $stmt = $pdo->prepare($sql);
    foreach ($params as $k => $v) { $stmt->bindValue($k, $v); }
    $stmt->bindValue(':limit', $PER_PAGE, PDO::PARAM_INT);
    $stmt->bindValue(':offset', $offset, PDO::PARAM_INT);
    $stmt->execute();
    $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

    // چک اینکه کدوم IP/GPCI های همین صفحه، روی چند اکانت مختلف دیده شدن (برای هشدار سواستفاده)
    $sharedIp = []; $sharedGpci = [];
    $ips = array_values(array_unique(array_column($rows, 'IP')));
    if ($ips) {
        $in = implode(',', array_fill(0, count($ips), '?'));
        $st = $pdo->prepare("SELECT IP, COUNT(DISTINCT AccountName) c FROM `$TABLE` WHERE IP IN ($in) GROUP BY IP HAVING c > 1");
        $st->execute($ips);
        foreach ($st->fetchAll(PDO::FETCH_ASSOC) as $r) $sharedIp[$r['IP']] = (int)$r['c'];
    }
    $gpcis = array_values(array_unique(array_column($rows, 'GPCI')));
    if ($gpcis) {
        $in2 = implode(',', array_fill(0, count($gpcis), '?'));
        $st2 = $pdo->prepare("SELECT GPCI, COUNT(DISTINCT AccountName) c FROM `$TABLE` WHERE GPCI IN ($in2) GROUP BY GPCI HAVING c > 1");
        $st2->execute($gpcis);
        foreach ($st2->fetchAll(PDO::FETCH_ASSOC) as $r) $sharedGpci[$r['GPCI']] = (int)$r['c'];
    }

    function buildLoginQuery($overrides) {
        $q = array_merge($_GET, $overrides);
        return '?' . http_build_query($q);
    }
?>
<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="robots" content="noindex, nofollow">
<title>لاگ‌های ورود (Login/IP)</title>
<style>
  * { box-sizing: border-box; }
  :root { --bg:#16171a; --panel:#1f2126; --panel-2:#24262c; --border:#33353c; --text:#e4e4e7; --muted:#9a9ba3; --accent:#6ab8ff; --accent-hover:#8ac8ff; --red:#f24b4b; --yellow:#e0c34a; }
  body { font-family:"Segoe UI",Tahoma,Arial,sans-serif; background:var(--bg); color:var(--text); padding:16px; margin:0; }
  .wrap { max-width:1300px; margin:0 auto; }
  .top { display:flex; justify-content:space-between; align-items:baseline; flex-wrap:wrap; gap:8px; margin-bottom:14px; }
  .topActions { display:flex; gap:14px; align-items:center; font-size:13px; }
  .topActions a { color:var(--muted); text-decoration:none; }
  .topActions a.logout { color:var(--red); font-weight:600; }
  .topActions button.revokeBtn { background:none; border:none; color:var(--red); font-weight:600; font-size:13px; cursor:pointer; padding:0; font-family:inherit; }
  h2 { color:#fff; margin:0; font-size:20px; font-weight:600; }
  .info { color:var(--muted); font-size:13px; }
  form.filters { background:var(--panel); border:1px solid var(--border); border-radius:12px; padding:16px; margin-bottom:18px; display:grid; grid-template-columns:repeat(auto-fit,minmax(170px,1fr)); gap:12px 16px; align-items:end; }
  form.filters .field { display:flex; flex-direction:column; }
  form.filters label { font-size:12px; color:var(--accent); margin-bottom:5px; font-weight:600; }
  form.filters input { background:var(--panel-2); border:1px solid var(--border); color:var(--text); padding:8px 10px; border-radius:8px; font-size:13px; width:100%; }
  .actions { display:flex; gap:10px; align-items:center; }
  .actions a.reset { color:var(--muted); text-decoration:none; font-size:13px; }
  form.filters button { background:var(--accent); color:#0f1a24; border:none; padding:9px 16px; border-radius:8px; font-weight:700; cursor:pointer; font-size:13px; }
  .table-card { background:var(--panel); border:1px solid var(--border); border-radius:12px; overflow:hidden; }
  .table-wrap { overflow-x:auto; max-height:65vh; }
  table { border-collapse:collapse; width:100%; min-width:900px; font-size:13px; }
  thead th { position:sticky; top:0; background:var(--panel-2); color:var(--accent); text-align:right; padding:10px 12px; border-bottom:1px solid var(--border); white-space:nowrap; }
  tbody td { padding:9px 12px; border-bottom:1px solid var(--border); white-space:nowrap; }
  .empty-row td { padding:30px; color:var(--muted); }
  .clickable { color:var(--text); text-decoration:none; border-bottom:1px dashed var(--muted); }
  .clickable:hover { color:var(--accent); border-color:var(--accent); }
  .warn { display:inline-block; margin-inline-start:6px; background:rgba(224,195,74,0.15); color:var(--yellow); padding:2px 7px; border-radius:6px; font-size:11px; font-weight:700; }
  .nav { display:flex; justify-content:space-between; align-items:center; margin-top:14px; gap:10px; flex-wrap:wrap; }
  .nav a { color:var(--text); text-decoration:none; background:var(--panel); border:1px solid var(--border); padding:8px 14px; border-radius:8px; }
  .nav a.disabled { color:var(--muted); pointer-events:none; }
  .page-indicator { display:flex; align-items:center; gap:8px; color:var(--muted); font-size:13px; }
  .page-indicator input { width:60px; background:var(--panel-2); border:1px solid var(--border); color:var(--text); border-radius:6px; padding:6px; text-align:center; }
  @media (max-width:760px) {
      form.filters { grid-template-columns:1fr 1fr; }
      table { min-width:0; }
      thead { display:none; }
      table, tbody, tr, td { display:block; width:100%; }
      tbody tr { margin-bottom:12px; border:1px solid var(--border); border-radius:10px; padding:6px 0; background:var(--panel-2); }
      td { display:flex; justify-content:space-between; gap:10px; border:none; padding:7px 14px; }
      td::before { content:attr(data-label); color:var(--accent); font-weight:600; font-size:12px; }
  }
</style>
</head>
<body>
<div class="wrap">

<div class="top">
  <h2>لاگ‌های ورود (Login / IP)</h2>
  <div class="topActions">
    <span class="info">صفحه <?= $page ?> از <?= $totalPages ?> — مجموع <?= $totalRows ?> رکورد</span>
    <a href="?">↩ بازگشت به انتخاب لاگ</a>
    <form method="post" style="display:inline" onsubmit="return confirm('Dastresiye in code kamelan hazf mishe va bayad dobare /codelog bezani. Motmaeni?');">
      <input type="hidden" name="csrf" value="<?= htmlspecialchars(csrf_token()) ?>">
      <input type="hidden" name="action" value="revoke_ip">
      <button type="submit" class="revokeBtn">خروج توی این IP لاگ</button>
    </form>
    <a class="logout" href="?action=logout">خروج</a>
  </div>
</div>

<form class="filters" method="get">
  <input type="hidden" name="view" value="login">
  <div class="field"><label>اسم اکانت</label><input type="text" name="playerName" value="<?= htmlspecialchars($f_name ?? '') ?>" placeholder="مثلا Persian"></div>
  <div class="field"><label>PID اکانت</label><input type="number" name="playerPID" value="<?= htmlspecialchars($f_pid ?? '') ?>"></div>
  <div class="field"><label>IP</label><input type="text" name="ip" value="<?= htmlspecialchars($f_ip ?? '') ?>" placeholder="مثلا 5.22"></div>
  <div class="field"><label>GPCI</label><input type="text" name="gpci" value="<?= htmlspecialchars($f_gpci ?? '') ?>"></div>
  <div class="field"><label>از تاریخ</label><input type="date" name="dateFrom" value="<?= htmlspecialchars($f_dateFrom ?? '') ?>"></div>
  <div class="field"><label>تا تاریخ</label><input type="date" name="dateTo" value="<?= htmlspecialchars($f_dateTo ?? '') ?>"></div>
  <div class="field">
    <label>تعداد ردیف در صفحه</label>
    <select name="perPage" style="background:#24262c;border:1px solid #33353c;color:#e4e4e7;padding:8px;border-radius:8px;">
      <?php foreach ($ALLOWED_PER_PAGE as $opt): ?>
        <option value="<?= $opt ?>" <?= $PER_PAGE === $opt ? 'selected' : '' ?>><?= $opt ?></option>
      <?php endforeach; ?>
    </select>
  </div>
  <div class="actions">
    <a class="reset" href="?view=login">پاک کردن فیلترها</a>
    <button type="submit">جست‌وجو</button>
  </div>
</form>

<div class="table-card">
<div class="table-wrap">
<table>
  <thead><tr><th>ID</th><th>اکانت</th><th>PID</th><th>IP</th><th>GPCI</th><th>زمان ورود</th></tr></thead>
  <tbody>
    <?php if (count($rows) === 0): ?>
      <tr class="empty-row"><td colspan="6">هیچ رکوردی پیدا نشد.</td></tr>
    <?php else: foreach ($rows as $row): ?>
      <tr>
        <td data-label="ID"><?= htmlspecialchars($row['id']) ?></td>
        <td data-label="اکانت"><a class="clickable" href="<?= buildLoginQuery(['playerName' => $row['AccountName'], 'page' => 1]) ?>"><?= htmlspecialchars($row['AccountName']) ?></a></td>
        <td data-label="PID"><?= htmlspecialchars($row['AccountPID']) ?></td>
        <td data-label="IP">
          <a class="clickable" href="<?= buildLoginQuery(['ip' => $row['IP'], 'playerName' => null, 'page' => 1]) ?>"><?= htmlspecialchars($row['IP']) ?></a>
          <?php if (isset($sharedIp[$row['IP']])): ?><span class="warn" title="این IP روی چند اکانت مختلف دیده شده">⚠ <?= $sharedIp[$row['IP']] ?> اکانت</span><?php endif; ?>
        </td>
        <td data-label="GPCI">
          <a class="clickable" href="<?= buildLoginQuery(['gpci' => $row['GPCI'], 'playerName' => null, 'ip' => null, 'page' => 1]) ?>"><?= htmlspecialchars(substr($row['GPCI'], 0, 12)) ?>…</a>
          <?php if (isset($sharedGpci[$row['GPCI']])): ?><span class="warn" title="این دستگاه روی چند اکانت مختلف دیده شده">⚠ <?= $sharedGpci[$row['GPCI']] ?> اکانت</span><?php endif; ?>
        </td>
        <td data-label="زمان ورود"><?= htmlspecialchars($row['LoginTime']) ?></td>
      </tr>
    <?php endforeach; endif; ?>
  </tbody>
</table>
</div>
</div>

<div class="nav">
  <?php if ($page < $totalPages): ?><a href="<?= buildLoginQuery(['page' => $page + 1]) ?>">قدیمی‌تر ⬅</a><?php else: ?><a class="disabled">قدیمی‌تر ⬅</a><?php endif; ?>
  <div class="page-indicator">
    صفحه <input type="number" id="gotoPage" min="1" max="<?= $totalPages ?>" value="<?= $page ?>"> از <?= $totalPages ?>
    <button type="button" onclick="goToPage()">برو</button>
  </div>
  <?php if ($page > 1): ?><a href="<?= buildLoginQuery(['page' => $page - 1]) ?>">➡ جدیدتر</a><?php else: ?><a class="disabled">➡ جدیدتر</a><?php endif; ?>
</div>

</div>
<script>
function goToPage() {
    const input = document.getElementById('gotoPage');
    let val = parseInt(input.value, 10);
    const max = parseInt(input.max, 10);
    if (isNaN(val) || val < 1) val = 1;
    if (val > max) val = max;
    const params = new URLSearchParams(window.location.search);
    params.set('page', val);
    window.location.search = params.toString();
}
document.getElementById('gotoPage').addEventListener('keydown', e => { if (e.key === 'Enter') goToPage(); });
</script>
</body>
</html>
<?php
}
