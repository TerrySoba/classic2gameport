FROM alpine:3.11

RUN apk add --update \
    avrdude \
    avr-libc \
    cmake \
    gcc-avr \
    make  \
  && rm -rf /var/cache/apk/*
