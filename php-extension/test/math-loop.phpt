--TEST--
echo - test instrumentation of the log builtin function
--FILE--
<?php
    for ($i = 0; $i < 4; $i++) {
        $power = pow(10, $i);
        $theLog = log10($power);
        echo "[$i] power = $power; log(power) = $theLog\n";
    }
?>
--EXPECT--
In minit function: zm_startup_lobo_instrumentation
In rinit function: zm_activate_lobo_instrumentation
[0] power = 1; log(power) = 0
[1] power = 10; log(power) = 1
[2] power = 100; log(power) = 2
[3] power = 1000; log(power) = 3
In rshutdown function: zm_deactivate_lobo_instrumentation
