PHP_ARG_ENABLE(lobo_instrumentation,
  [Enable the lobo toy instrumentor extension build],
  [-enable-lobo-instrumentation]		Enable lobo instrumentation])

if test $PHP_LOBO_INSTRUMENTATION != "no"; then
  PHP_SUBST(LOBO_INSTRUMENTATION_SHARED_LIBADD)
  PHP_NEW_EXTENSION(lobo_instrumentation, instrumentation.c, $ext_shared)
fi
