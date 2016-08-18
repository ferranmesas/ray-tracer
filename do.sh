#!/bin/bash
set -e
set -u
set -o pipefail
make
./raytracer "$@" | convert - test.png
open test.png
