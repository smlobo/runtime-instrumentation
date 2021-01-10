#include <assert.h>

#include "instrument.h"
#include "php.h"

// Zend function pointer type
typedef void (*zend_fptr_t)(INTERNAL_FUNCTION_PARAMETERS);

// Pointers to the original built-in function
zend_fptr_t original_log10_fptr = NULL;

// Wrapper function for log10
ZEND_NAMED_FUNCTION(zif_instrumented_log10) {
    // Get the parameter passed
    assert(ZEND_NUM_ARGS() == 1);
    double input_parameter;
    if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, 
        ZEND_NUM_ARGS() TSRMLS_CC, "d", &input_parameter) == FAILURE) {
        php_printf("Executing log10() {from %s} : parameter parsing FAILED\n", 
            __func__);
    }
    else {
        php_printf("Executing log10() {from %s} : parameter: %.2f\n", __func__, 
            input_parameter);
    }

    // Call the original function
    (*original_log10_fptr)(ht, return_value, return_value_ptr, this_ptr, 
        return_value_used);

    // Get the return value
    if (return_value == NULL || return_value->type != IS_DOUBLE) {
        php_printf("Done executing log10() {from %s} : return value NOT "
            "available\n", __func__);
    }
    else {
        php_printf("Done executing log10() {from %s} : return value: %.2f\n", 
            __func__, return_value->value.dval);
    }
}

// Lookup the original function, cache a pointer to it, replace it with a pointer 
// to our wrapper
void instrument_log10() {
    if (original_log10_fptr == NULL) {
        zend_function* orig = NULL;
        if (zend_hash_find((executor_globals.function_table), "log10", 
            sizeof("log10"), (void**)&orig) == 0) { 
            original_log10_fptr = orig->internal_function.handler;
            orig->internal_function.handler = &zif_instrumented_log10;
            php_printf("Instrumented log10()\n");
        }
        else {
            php_printf("Unable to instrument log10()\n");
        }
    }
}
