#!/bin/bash

# fail at first error
set -e

DIRECTORY=`dirname $0`
SCRIPT_DIR=`pwd`/${DIRECTORY}

docker build -t avr-docker ${SCRIPT_DIR}/docker/
docker run -v${SCRIPT_DIR}/src:/src avr-docker /bin/sh -c 'mkdir build && cd build && cmake /src && make size'
