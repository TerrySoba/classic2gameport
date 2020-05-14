#!/bin/bash

# fail at first error
set -e
avrdude -c usbasp-clone -p m8 -P /dev/ttyACM0 -U flash:w:hex/classic2gameport.hex:i