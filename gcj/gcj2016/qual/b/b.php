<?php
function solve($s) {
    $prev = 'z';
    $cnt = 0;

    // echo "input: $s";

    $len = strlen($s);
    for ($i = 0; $i < $len; $i++) {
    	if ($prev != $s[$i]) {
	   $cnt += 1;
	}
	$prev = $s[$i];
    }

    if (substr($s, -1) == '+') {
       $cnt -= 1;
    }

    return $cnt;
}
$T = (int)fgets(STDIN);
for ($t = 1; $t <= $T; $t++) {
    $s = trim(fgets(STDIN));
    $res = solve($s);
    echo "Case #$t: $res\n";
}
?>
