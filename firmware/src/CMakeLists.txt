cmake_minimum_required(VERSION 3.10)

# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

# Project name
project("Classic2Gameport")

# Product filename
set(PRODUCT_NAME classic2gameport)

## AVR Chip Configuration
set(F_CPU 8000000UL)
# CPU, you can find the list here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU atmega8)

# AVR Fuses, must be in concordance with your hardware and F_CPU
set(H_FUSE 0xD9)
set(L_FUSE 0xE4)

# mmcu MUST be passed to both the compiler and linker, this handles the linker
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
    -mmcu=${MCU} # MCU
    -Wall -pedantic -Os -std=c99 -Werror
)

# Create one target
add_executable(${PRODUCT_NAME}.elf
    bit_tools.h
    main.c
    twi_func.c
    twi_func.h
    twi_speed.h
    )

target_compile_definitions(${PRODUCT_NAME}.elf PRIVATE
    -DF_CPU=${F_CPU}
)

add_custom_command(OUTPUT ${PRODUCT_NAME}.hex
    COMMAND avr-objcopy -j .text -j .data -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex
    DEPENDS ${PRODUCT_NAME}.elf)

add_custom_target(size
    COMMAND avr-size ${PRODUCT_NAME}.hex
    DEPENDS ${PRODUCT_NAME}.hex)


set(AVRDUDE_COMMAND avrdude -c usbasp-clone -p m8 -P /dev/ttyACM0)

add_custom_target(flash
    COMMAND ${AVRDUDE_COMMAND} -U flash:w:${PRODUCT_NAME}.hex:i)

add_custom_target(fuses
    COMMAND ${AVRDUDE_COMMAND} -U hfuse:w:${H_FUSE}:m -U lfuse:w:${L_FUSE}:m)
