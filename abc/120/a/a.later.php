<?php
list($a, $b, $c) = explode(' ', fgets(STDIN));
echo min(intdiv($b, $a), $c);
?>
