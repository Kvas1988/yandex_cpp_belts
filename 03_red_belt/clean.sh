#!/bin/bash

for path in [0-9][0-9]_week; do
  find $path -name 'CMakeLists.txt' -delete
  find $path -name 'build' -delete
  find $path -name 'cmake-build-debug' -delete
#  echo $path
done