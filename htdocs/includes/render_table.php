<?php
defined('ARIANA_LOGS_APP') or die('دسترسی مستقیم مجاز نیست.');

/**
 * صفحه نمایش و جست‌وجوی لاگ‌ها.
 * $type فقط می‌تونه 'money' یا 'gold' باشه (قبل از فراخوانی این تابع چک شده)
 * پس استفاده از اسم جدول/ستون توی SQL از روی این آرایه‌ی ثابت امنه، نه از ورودی کاربر.
 */
function render_log_page($type) {
    $isGold = ($type === 'gold');

    $TABLE       = $isGold ? TBL_GOLD : TBL_MONEY;
    $AMOUNT_COL  = $isGold ? 'Gold' : 'Money';
    $AMOUNT_LBL  = $isGold ? 'طلا' : 'مبلغ';
    $TITLE_EXTRA = $isGold ? ' (طلا)' : '';
    $ACCENT      = $isGold ? '#e0b23e' : '#4f8ef7';
    $ACCENT_HOV  = $isGold ? '#f0c65a' : '#6ba0ff';
    $BTN_TEXT    = $isGold ? '#1a1a1a' : '#fff';
    $CMD_PH      = $isGold ? '/givegold' : '/givemoney';
    $AMOUNT_FROM = $isGold ? 'goldFrom' : 'moneyFrom';
    $AMOUNT_TO   = $isGold ? 'goldTo'   : 'moneyTo';

    $pdo = db();

    $ALLOWED_PER_PAGE = [20, 40, 50, 100];
    $PER_PAGE = isset($_GET['perPage']) && in_array((int)$_GET['perPage'], $ALLOWED_PER_PAGE)
        ? (int)$_GET['perPage']
        : 20;

    function g($key) {
        return isset($_GET[$key]) && trim($_GET[$key]) !== '' ? trim($_GET[$key]) : null;
    }

    $f_playerTarget    = g('playerTarget');
    $f_playerTargetRef = g('playerTargetRef');
    $f_playerGive      = g('playerGive');
    $f_playerGiveRef   = g('playerGiveRef');
    $f_admin           = g('admin');
    $f_adminRef        = g('adminRef');
    $f_command         = g('command');
    $f_reason          = g('reason');
    $f_dateFrom        = g('dateFrom');
    $f_dateTo          = g('dateTo');
    $f_type            = g('type');
    $f_amountFrom      = g($AMOUNT_FROM);
    $f_amountTo        = g($AMOUNT_TO);

    $where  = [];
    $params = [];

    if ($f_playerTarget !== null) { $where[] = "PlayerTarget LIKE :playerTarget"; $params[':playerTarget'] = "%$f_playerTarget%"; }
    if ($f_playerTargetRef !== null && is_numeric($f_playerTargetRef)) { $where[] = "PlayerTargetRef = :playerTargetRef"; $params[':playerTargetRef'] = (int)$f_playerTargetRef; }
    if ($f_playerGive !== null) { $where[] = "PlayerGive LIKE :playerGive"; $params[':playerGive'] = "%$f_playerGive%"; }
    if ($f_playerGiveRef !== null && is_numeric($f_playerGiveRef)) { $where[] = "PlayerGiveRef = :playerGiveRef"; $params[':playerGiveRef'] = (int)$f_playerGiveRef; }
    if ($f_admin !== null) { $where[] = "Admin LIKE :admin"; $params[':admin'] = "%$f_admin%"; }
    if ($f_adminRef !== null && is_numeric($f_adminRef)) { $where[] = "AdminRef = :adminRef"; $params[':adminRef'] = (int)$f_adminRef; }
    if ($f_command !== null) { $where[] = "Command LIKE :command"; $params[':command'] = "%$f_command%"; }
    if ($f_reason !== null) { $where[] = "Reason LIKE :reason"; $params[':reason'] = "%$f_reason%"; }
    if ($f_dateFrom !== null) { $where[] = "TimeLog >= :dateFrom"; $params[':dateFrom'] = $f_dateFrom . " 00:00:00"; }
    if ($f_dateTo !== null) { $where[] = "TimeLog <= :dateTo"; $params[':dateTo'] = $f_dateTo . " 23:59:59"; }
    if ($f_type === '1' || $f_type === '2') { $where[] = "PON = :pon"; $params[':pon'] = (int)$f_type; }
    if ($f_amountFrom !== null && is_numeric($f_amountFrom)) { $where[] = "`$AMOUNT_COL` >= :amountFrom"; $params[':amountFrom'] = (float)$f_amountFrom; }
    if ($f_amountTo !== null && is_numeric($f_amountTo)) { $where[] = "`$AMOUNT_COL` <= :amountTo"; $params[':amountTo'] = (float)$f_amountTo; }

    $whereSql = $where ? ("WHERE " . implode(" AND ", $where)) : "";

    $countStmt = $pdo->prepare("SELECT COUNT(*) FROM `$TABLE` $whereSql");
    $countStmt->execute($params);
    $totalRows  = (int)$countStmt->fetchColumn();
    $totalPages = max(1, (int)ceil($totalRows / $PER_PAGE));

    $page = isset($_GET['page']) ? (int)$_GET['page'] : 1;
    if ($page < 1) $page = 1;
    if ($page > $totalPages) $page = $totalPages;
    $offset = ($page - 1) * $PER_PAGE;

    $sql = "SELECT id, `$AMOUNT_COL`, PlayerTarget, PlayerTargetRef, PlayerGive, PlayerGiveRef,
                   Admin, AdminRef, Command, Reason, PON, TimeLog
            FROM `$TABLE` $whereSql
            ORDER BY id DESC
            LIMIT :limit OFFSET :offset";
    $stmt = $pdo->prepare($sql);
    foreach ($params as $k => $v) { $stmt->bindValue($k, $v); }
    $stmt->bindValue(':limit', $PER_PAGE, PDO::PARAM_INT);
    $stmt->bindValue(':offset', $offset, PDO::PARAM_INT);
    $stmt->execute();
    $rows = $stmt->fetchAll(PDO::FETCH_ASSOC);

    // فیلترها + نوع لاگ (view) موقع رفتن به صفحه بعد/قبل حفظ بشن
    function buildQuery($overrides) {
        $q = array_merge($_GET, $overrides);
        return '?' . http_build_query($q);
    }

    function typeBadge($pon) {
        $pon = (int)$pon;
        if ($pon === 1) return '<span class="badge badge-in">▲ واریز</span>';
        if ($pon === 2) return '<span class="badge badge-out">▼ برداشت</span>';
        return '<span class="badge badge-unknown">؟ نامشخص</span>';
    }
    function rowClass($pon) {
        $pon = (int)$pon;
        if ($pon === 1) return 'row-in';
        if ($pon === 2) return 'row-out';
        return '';
    }
?>
<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta name="robots" content="noindex, nofollow">
<title>لاگ‌های <?= htmlspecialchars($TABLE) ?></title>
<style>
  * { box-sizing: border-box; }
  :root {
      --bg: #16171a; --panel: #1f2126; --panel-2: #24262c; --border: #33353c;
      --text: #e4e4e7; --muted: #9a9ba3; --accent: <?= $ACCENT ?>; --accent-hover: <?= $ACCENT_HOV ?>;
      --green: #3ecf6c; --red: #f24b4b; --yellow: #e0c34a;
  }
  body { font-family: "Segoe UI", Tahoma, Arial, sans-serif; background: var(--bg); color: var(--text); padding: 16px; margin: 0; }
  .wrap { max-width: 1400px; margin: 0 auto; }
  .top { display:flex; justify-content:space-between; align-items:baseline; flex-wrap:wrap; gap:8px; margin-bottom:14px; }
  .topActions { display:flex; gap:14px; align-items:center; font-size:13px; }
  .topActions a { color: var(--muted); text-decoration:none; }
  .topActions a.logout { color: var(--red); font-weight:600; }
  .topActions button.revokeBtn { background:none; border:none; color: var(--red); font-weight:600; font-size:13px; cursor:pointer; padding:0; font-family:inherit; }
  h2 { color:#fff; margin:0; font-size:20px; font-weight:600; }
  .info { color: var(--muted); font-size:13px; }
  form.filters { background: var(--panel); border: 1px solid var(--border); border-radius: 12px; padding: 16px; margin-bottom: 18px; display: grid; grid-template-columns: repeat(auto-fit, minmax(170px, 1fr)); gap: 12px 16px; align-items: end; box-shadow: 0 2px 8px rgba(0,0,0,0.25); }
  form.filters .field { display:flex; flex-direction:column; }
  form.filters label { font-size:12px; color: var(--accent); margin-bottom:5px; font-weight:600; }
  form.filters input, form.filters select { background: var(--panel-2); border: 1px solid var(--border); color: var(--text); padding: 8px 10px; border-radius: 8px; font-size: 13px; outline: none; width: 100%; }
  .range-pair { display:flex; gap:6px; }
  .actions { display:flex; gap:10px; align-items:center; }
  .actions a.reset { color: var(--muted); text-decoration:none; font-size:13px; }
  form.filters button { background: var(--accent); color: <?= $BTN_TEXT ?>; border:none; padding:9px 16px; border-radius:8px; font-weight:700; cursor:pointer; font-size:13px; }
  .table-card { background: var(--panel); border:1px solid var(--border); border-radius:12px; overflow:hidden; }
  .table-wrap { overflow-x:auto; max-height:65vh; }
  table { border-collapse:collapse; width:100%; min-width:1100px; font-size:13px; }
  thead th { position:sticky; top:0; background: var(--panel-2); color: var(--accent); text-align:right; padding:10px 12px; border-bottom:1px solid var(--border); white-space:nowrap; }
  tbody td { padding:9px 12px; border-bottom:1px solid var(--border); white-space:nowrap; }
  tr.row-in { background: rgba(62, 207, 108, 0.06); }
  tr.row-out { background: rgba(242, 75, 75, 0.06); }
  .badge { padding:3px 8px; border-radius:6px; font-size:12px; font-weight:600; }
  .badge-in { background: rgba(62,207,108,0.15); color: var(--green); }
  .badge-out { background: rgba(242,75,75,0.15); color: var(--red); }
  .badge-unknown { background: rgba(224,195,74,0.15); color: var(--yellow); }
  .money-cell, .gold-cell { font-weight: 700; font-variant-numeric: tabular-nums; }
  .gold-cell { color: var(--accent); }
  .reason-cell { max-width: 260px; white-space: normal; }
  .empty-row td { padding: 30px; color: var(--muted); white-space: normal; }
  .nav { margin-top: 16px; display: flex; justify-content: space-between; align-items: center; flex-wrap: wrap; gap: 10px; background: var(--panel); border:1px solid var(--border); border-radius: 12px; padding: 12px 16px; }
  .nav a, .nav button.navbtn { background: var(--accent); color: <?= $BTN_TEXT ?>; border: none; padding: 9px 18px; border-radius: 8px; text-decoration: none; cursor: pointer; font-size: 13px; font-weight:600; }
  .nav a.disabled { background: #34363c; color: #777; pointer-events: none; }
  .page-indicator { color: var(--text); font-size: 13px; display: flex; align-items: center; gap: 6px; flex-wrap:wrap; justify-content:center; }
  .page-indicator input { width: 55px; text-align: center; background: var(--panel-2); border: 1px solid var(--border); color: var(--text); border-radius: 8px; padding: 7px; }
  .page-indicator button { background: var(--accent); color: <?= $BTN_TEXT ?>; border: none; padding: 7px 14px; border-radius: 8px; cursor: pointer; font-size: 13px; font-weight:600; }
  @media (max-width: 760px) {
      body { padding: 10px; }
      form.filters { grid-template-columns: 1fr 1fr; padding: 12px; gap: 10px; }
      form.filters .actions { grid-column: 1 / -1; justify-content: stretch; }
      form.filters .actions button, form.filters .actions a.reset { flex:1; }
      .table-wrap { max-height: none; overflow-x: visible; }
      table { min-width: 0; }
      thead { display: none; }
      table, tbody, tr, td { display: block; width: 100%; }
      tbody tr { margin-bottom: 12px; border: 1px solid var(--border); border-radius: 10px; padding: 6px 0; background: var(--panel-2); }
      tr.row-in { background: rgba(62, 207, 108, 0.10); }
      tr.row-out { background: rgba(242, 75, 75, 0.10); }
      td { text-align: right; white-space: normal; padding: 7px 14px; display: flex; justify-content: space-between; gap: 10px; border: none; }
      td::before { content: attr(data-label); color: var(--accent); font-weight: 600; font-size: 12px; flex-shrink:0; }
      .reason-cell { max-width: none; }
      .nav { flex-direction: column; }
      .nav a, .nav .page-indicator { width: 100%; text-align:center; justify-content:center; }
  }
</style>
</head>
<body>
<div class="wrap">

<div class="top">
  <h2>لاگ‌های <?= htmlspecialchars($TABLE) ?><?= $TITLE_EXTRA ?></h2>
  <div class="topActions">
    <span class="info">صفحه <?= $page ?> از <?= $totalPages ?> — مجموع <?= $totalRows ?> رکورد پیدا شده</span>
    <a href="?">↩ بازگشت به انتخاب لاگ</a>
    <a class="logout" href="?action=logout">خروج</a>
    <form method="post" style="display:inline" onsubmit="return confirm('Dastresiye in code kamelan hazf mishe va bayad dobare /codelog bezani. Motmaeni?');">
      <input type="hidden" name="csrf" value="<?= htmlspecialchars(csrf_token()) ?>">
      <input type="hidden" name="action" value="revoke_ip">
      <button type="submit" class="revokeBtn">خروج توی این IP لاگ</button>
    </form>
  </div>
</div>

<form class="filters" method="get">
  <input type="hidden" name="view" value="<?= htmlspecialchars($type) ?>">
  <div class="field"><label>نام هدف (PlayerTarget)</label><input type="text" name="playerTarget" value="<?= htmlspecialchars($f_playerTarget ?? '') ?>" placeholder="مثلا Ali_Ahmadi"></div>
  <div class="field"><label>آیدی هدف (PlayerTargetRef)</label><input type="number" name="playerTargetRef" value="<?= htmlspecialchars($f_playerTargetRef ?? '') ?>" placeholder="مثلا 15"></div>
  <div class="field"><label>نام دهنده (PlayerGive)</label><input type="text" name="playerGive" value="<?= htmlspecialchars($f_playerGive ?? '') ?>" placeholder="مثلا Reza_Karimi"></div>
  <div class="field"><label>آیدی دهنده (PlayerGiveRef)</label><input type="number" name="playerGiveRef" value="<?= htmlspecialchars($f_playerGiveRef ?? '') ?>" placeholder="مثلا 8"></div>
  <div class="field"><label>نام ادمین (Admin)</label><input type="text" name="admin" value="<?= htmlspecialchars($f_admin ?? '') ?>" placeholder="مثلا Admin_Sara"></div>
  <div class="field"><label>آیدی ادمین (AdminRef)</label><input type="number" name="adminRef" value="<?= htmlspecialchars($f_adminRef ?? '') ?>" placeholder="مثلا 2"></div>
  <div class="field"><label>دستور (Command)</label><input type="text" name="command" value="<?= htmlspecialchars($f_command ?? '') ?>" placeholder="مثلا <?= $CMD_PH ?>"></div>
  <div class="field"><label>دلیل (Reason)</label><input type="text" name="reason" value="<?= htmlspecialchars($f_reason ?? '') ?>" placeholder="مثلا جایزه رویداد"></div>
  <div class="field">
    <label>نوع تراکنش</label>
    <select name="type">
      <option value="">همه</option>
      <option value="1" <?= $f_type === '1' ? 'selected' : '' ?>>فقط واریز</option>
      <option value="2" <?= $f_type === '2' ? 'selected' : '' ?>>فقط برداشت</option>
    </select>
  </div>
  <div class="field">
    <label><?= $isGold ? 'مقدار طلا (Gold) از / تا' : 'مبلغ (Money) از / تا' ?></label>
    <div class="range-pair">
      <input type="number" name="<?= $AMOUNT_FROM ?>" value="<?= htmlspecialchars($f_amountFrom ?? '') ?>" placeholder="از">
      <input type="number" name="<?= $AMOUNT_TO ?>" value="<?= htmlspecialchars($f_amountTo ?? '') ?>" placeholder="تا">
    </div>
  </div>
  <div class="field"><label>از تاریخ</label><input type="date" name="dateFrom" value="<?= htmlspecialchars($f_dateFrom ?? '') ?>"></div>
  <div class="field"><label>تا تاریخ</label><input type="date" name="dateTo" value="<?= htmlspecialchars($f_dateTo ?? '') ?>"></div>
  <div class="field">
    <label>تعداد ردیف در هر صفحه</label>
    <select name="perPage">
      <?php foreach ($ALLOWED_PER_PAGE as $opt): ?>
        <option value="<?= $opt ?>" <?= $PER_PAGE === $opt ? 'selected' : '' ?>><?= $opt ?></option>
      <?php endforeach; ?>
    </select>
  </div>
  <div class="actions">
    <a class="reset" href="?view=<?= htmlspecialchars($type) ?>">پاک کردن فیلترها</a>
    <button type="submit">جست‌وجو</button>
  </div>
</form>

<div class="table-card">
<div class="table-wrap">
<table>
  <thead>
    <tr>
      <th>ID</th><th>نوع</th><th><?= $AMOUNT_LBL ?></th><th>PlayerTarget</th><th>PlayerTargetRef</th>
      <th>PlayerGive</th><th>PlayerGiveRef</th><th>Admin</th><th>AdminRef</th><th>Command</th><th>Reason</th><th>TimeLog</th>
    </tr>
  </thead>
  <tbody>
    <?php if (count($rows) === 0): ?>
      <tr class="empty-row"><td colspan="12">هیچ رکوردی با این فیلترها پیدا نشد.</td></tr>
    <?php else: ?>
      <?php foreach ($rows as $row): ?>
        <tr class="<?= rowClass($row['PON']) ?>">
          <td data-label="ID"><?= htmlspecialchars($row['id']) ?></td>
          <td data-label="نوع"><?= typeBadge($row['PON']) ?></td>
          <td data-label="<?= $AMOUNT_LBL ?>" class="<?= $isGold ? 'gold-cell' : 'money-cell' ?>"><?= htmlspecialchars($row[$AMOUNT_COL] ?? '0') ?></td>
          <td data-label="PlayerTarget"><?= htmlspecialchars($row['PlayerTarget'] ?? '') ?></td>
          <td data-label="PlayerTargetRef"><?= htmlspecialchars($row['PlayerTargetRef'] ?? '') ?></td>
          <td data-label="PlayerGive"><?= htmlspecialchars($row['PlayerGive'] ?? '') ?></td>
          <td data-label="PlayerGiveRef"><?= htmlspecialchars($row['PlayerGiveRef'] ?? '') ?></td>
          <td data-label="Admin"><?= htmlspecialchars($row['Admin'] ?? '') ?></td>
          <td data-label="AdminRef"><?= htmlspecialchars($row['AdminRef'] ?? '') ?></td>
          <td data-label="Command"><?= htmlspecialchars($row['Command'] ?? '') ?></td>
          <td data-label="Reason" class="reason-cell"><?= htmlspecialchars($row['Reason'] ?? '') ?></td>
          <td data-label="TimeLog"><?= htmlspecialchars($row['TimeLog'] ?? '') ?></td>
        </tr>
      <?php endforeach; ?>
    <?php endif; ?>
  </tbody>
</table>
</div>
</div>

<div class="nav">
  <?php if ($page < $totalPages): ?>
    <a href="<?= buildQuery(['page' => $page + 1]) ?>">قدیمی‌تر ⬅</a>
  <?php else: ?>
    <a class="disabled">قدیمی‌تر ⬅</a>
  <?php endif; ?>

  <div class="page-indicator">
    صفحه
    <input type="number" id="gotoPage" min="1" max="<?= $totalPages ?>" value="<?= $page ?>">
    از <?= $totalPages ?>
    <button type="button" onclick="goToPage()">برو</button>
  </div>

  <?php if ($page > 1): ?>
    <a href="<?= buildQuery(['page' => $page - 1]) ?>">➡ جدیدتر</a>
  <?php else: ?>
    <a class="disabled">➡ جدیدتر</a>
  <?php endif; ?>
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
document.getElementById('gotoPage').addEventListener('keydown', function(e) {
    if (e.key === 'Enter') goToPage();
});
</script>

</body>
</html>
<?php
}
