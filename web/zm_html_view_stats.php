<?php
	if ( !canView( 'Events' ) )
	{
		$view = "error";
		return;
	}
	$result = mysql_query( "select S.*,E.*,Z.Name as ZoneName,M.Name as MonitorName,M.Width,M.Height from Stats as S left join Events as E on S.EventId = E.Id left join Zones as Z on S.ZoneId = Z.Id left join Monitors as M on E.MonitorId = M.Id where S.EventId = '$eid' and S.FrameId = '$fid' order by S.ZoneId" );
	if ( !$result )
		die( mysql_error() );
	while ( $row = mysql_fetch_assoc( $result ) )
	{
		$stats[] = $row;
	}
?>
<html>
<head>
<title>ZM - <?= $zmSlangStats ?> <?= $eid."-".$fid ?></title>
<link rel="stylesheet" href="zm_styles.css" type="text/css">
<script language="JavaScript">
window.focus();
function closeWindow()
{
	window.close();
}
</script>
</head>
<body>
<table width="96%" border="0">
<tr>
<td align="left" class="smallhead"><b><?= $zmSlangFrame ?> <?= $eid."-".$fid ?></b></td>
<td align="right" class="text"><a href="javascript: closeWindow();"><?= $zmSlangClose ?></a></td>
</tr>
<tr><td colspan="2"><table width="100%" border="0" bgcolor="#7F7FB2" cellpadding="3" cellspacing="1"><tr bgcolor="#FFFFFF">
<td class="smallhead"><?= $zmSlangZone ?></td>
<td class="smallhead" align="right"><?= $zmSlangAlarmPx ?></td>
<td class="smallhead" align="right"><?= $zmSlangFilterPx ?></td>
<td class="smallhead" align="right"><?= $zmSlangBlobPx ?></td>
<td class="smallhead" align="right"><?= $zmSlangBlobs ?></td>
<td class="smallhead" align="right"><?= $zmSlangBlobSizes ?></td>
<td class="smallhead" align="right"><?= $zmSlangAlarmLimits ?></td>
<td class="smallhead" align="right"><?= $zmSlangScore ?></td>
</tr>
<?php
	if ( count($stats) )
	{
		foreach ( $stats as $stat )
		{
?>
<tr bgcolor="#FFFFFF">
<td class="text"><?= $stat[ZoneName] ?></td>
<td class="text" align="right"><?= $stat[AlarmPixels] ?></td>
<td class="text" align="right"><?= $stat[FilterPixels] ?></td>
<td class="text" align="right"><?= $stat[BlobPixels] ?></td>
<td class="text" align="right"><?= $stat[Blobs] ?></td>
<td class="text" align="right"><?= $stat[MinBlobSize]."-".$stat[MaxBlobSize] ?></td>
<td class="text" align="right"><?= $stat[MinX].",".$stat[MinY]."-".$stat[MaxX].",".$stat[MaxY] ?></td>
<td class="text" align="right"><?= $stat[Score] ?></td>
</tr>
<?php
		}
	}
	else
	{
?>
<tr bgcolor="#FFFFFF">
<td class="text" colspan="8" align="center"><br><?= $zmSlangNoStatisticsRecorded ?><br><br></td>
</tr>
<?php
	}
?>
</table></td>
</tr>
</table>
</body>
</html>