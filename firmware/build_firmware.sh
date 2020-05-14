#!/bin/bash

# fail at first error
set -e

DIRECTORY=`dirname $0`
SCRIPT_DIR=`pwd`/${DIRECTORY}

docker build -t avr-docker ${SCRIPT_DIR}/docker/
docker run -v${SCRIPT_DIR}/src:/src -v${SCRIPT_DIR}/hex:/hex avr-docker /bin/sh -c 'avr-gcc --version && mkdir build && cd build && cmake /src && make size && cp classic2gameport.hex /hex'
