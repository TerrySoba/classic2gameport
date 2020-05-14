#!/bin/bash

# fail at first error
set -e
avrdude -c usbasp-clone -p m8 -P /dev/ttyACM0 -U hfuse:w:0xD9:m -U lfuse:w:0xE4:m
