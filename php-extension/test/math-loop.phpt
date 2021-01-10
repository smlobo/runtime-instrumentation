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
Instrumented log10()
Executing log10() {from zif_instrumented_log10} : parameter: 1.00
Done executing log10() {from zif_instrumented_log10} : return value: 0.00
[0] power = 1; log(power) = 0
Executing log10() {from zif_instrumented_log10} : parameter: 10.00
Done executing log10() {from zif_instrumented_log10} : return value: 1.00
[1] power = 10; log(power) = 1
Executing log10() {from zif_instrumented_log10} : parameter: 100.00
Done executing log10() {from zif_instrumented_log10} : return value: 2.00
[2] power = 100; log(power) = 2
Executing log10() {from zif_instrumented_log10} : parameter: 1000.00
Done executing log10() {from zif_instrumented_log10} : return value: 3.00
[3] power = 1000; log(power) = 3
In rshutdown function: zm_deactivate_lobo_instrumentation
