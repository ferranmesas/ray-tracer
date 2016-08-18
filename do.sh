#!/bin/bash
set -e
set -u
set -o pipefail
make
./raytracer "$@" < scene | convert - test.png
open test.png
