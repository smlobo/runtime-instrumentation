#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry lobo_instrumentation_module_entry;
#define phpext_lobo_instrumentation_ptr &lobo_instrumentation_module_entry

#endif
