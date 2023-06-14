#!/bin/bash

cd ../../../
docker rmi -f ereva/valgrind/smartcalc
docker build . -t ereva/valgrind/smartcalc -f materials/build/Valgrind/Dockerfile
docker run --rm ereva/valgrind/smartcalc