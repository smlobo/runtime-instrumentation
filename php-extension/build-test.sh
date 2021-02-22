#!/usr/bin/env bash

set -e

# Build
phpize --clean
phpize
./configure -enable-lobo-instrumentation
make clean
make

# Test
make test TESTS=./test
