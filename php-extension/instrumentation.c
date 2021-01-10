#include "instrumentation.h"
#include "instrument.h"

ZEND_FUNCTION(hello_lobo_instrumentation) {
    php_printf("Hello from lobo_instrumentation.so!!\n");
}

zend_function_entry php_lobo_instrumentation_functions[] = {
    ZEND_FE(hello_lobo_instrumentation, NULL)
    ZEND_FE_END
};

PHP_MINIT_FUNCTION(lobo_instrumentation) {
    php_printf("In minit function: %s\n", __func__);
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(lobo_instrumentation) {
    php_printf("In mshutdown function: %s\n", __func__);
    return SUCCESS;
}

PHP_RINIT_FUNCTION(lobo_instrumentation) {
    php_printf("In rinit function: %s\n", __func__);

    // Instrument functions
    instrument_log10();
    
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(lobo_instrumentation) {
    php_printf("In rshutdown function: %s\n", __func__);
    return SUCCESS;
}

zend_module_entry lobo_instrumentation_module_entry = {
    STANDARD_MODULE_HEADER,
    "lobo_instrumentation",                 // extension name
    php_lobo_instrumentation_functions,     // functions
    PHP_MINIT(lobo_instrumentation),        // MINIT
    PHP_MSHUTDOWN(lobo_instrumentation),    // MSHUTDOWN
    PHP_RINIT(lobo_instrumentation),        // RINIT
    PHP_RSHUTDOWN(lobo_instrumentation),    // RSHUTDOWN
    NULL,                                   // MINFO
    "0.1",                                  // extension version
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_LOBO_INSTRUMENTATION
ZEND_GET_MODULE(lobo_instrumentation)
#endif
