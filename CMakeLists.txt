cmake_minimum_required(VERSION 3.20)

# ----------------------
# kernel.img	ARMv6 (32-bit)	Pi 1 (A, B, B+), Zero, Zero W, Compute Model 1 = arm1176jzf-s
# kernel7.img	ARMv7 (32-bit)	Pi 2 (v1.1) = cortex-a7
# kernel7l.img	ARMv7+LPAE (32-bit)	Pi 4B, Pi 400 (De 'l' staat voor Large Physical Address Extension) = cortex-a72
# kernel7.img	ARMv8 (32-bit)	Zero 2 W, Pi 3  = cortex-a53
# kernel8.img	ARMv8 (64-bit)	Zero 2 W, Pi 3  = cortex-a53
# kernel8.img	ARMv8 (64-bit) Pi 4 = cortex-a72
# kernel8.img	ARMv8 (32-bit and 64-bit) Pi 5 = cortex-a76
# ----------------------

# In windows create a systemvariable called ARM_NONE_EABI and ARM_AARCH64 and direct it to the arm-none-eabi-gcc and aarch64-none-elf-gcc directory.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# ----------------------
# User options
# ----------------------
include(${CMAKE_SOURCE_DIR}/CMakeFiles/utils.cmake)

set(ARCH "arm64" CACHE STRING "Target architecture")
set_property(CACHE ARCH PROPERTY STRINGS arm32 arm64)
validate_choice(ARCH arm32 arm64)

set(BOARD "RPIZ2W" CACHE STRING "Raspberry Pi model")
set_property(CACHE BOARD PROPERTY STRINGS RPIA RPIB RPIA_PLUS RPIB_PLUS RPI2B10 RPI2B11 RPI2B12 RPIALPHA RPICM1 RPI3B11 RPI3B12 RPI3B13 RPIZ1 RPICM3 RPIZ1W RPI3A_PLUS RPICM3_PLUS RPI4B RPI3B_PLUS RPI400 RPICM4 RPIZ2W RPI5 RPICM5 RPI500 RPICM5_LITE)
validate_choice(BOARD RPIA RPIB RPIA_PLUS RPIB_PLUS RPI2B10 RPI2B11 RPI2B12 RPIALPHA RPICM1 RPI3B11 RPI3B12 RPI3B13 RPIZ1 RPICM3 RPIZ1W RPI3A_PLUS RPICM3_PLUS RPI4B RPI3B_PLUS RPI400 RPICM4 RPIZ2W RPI5 RPICM5 RPI500 RPICM5_LITE)

print_choice(ARCH
    arm32 "arm32 build"
    arm64 "arm64 build"
)

print_choice(BOARD
    RPIA            "Building for Raspberry Pi 1A"
    RPIB            "Building for Raspberry Pi 1B"
    RPIA_PLUS       "Building for Raspberry Pi 1A+"
    RPIB_PLUS       "Building for Raspberry Pi 1B+"
    RPI2B           "Building for Raspberry Pi 2B"
    RPIALPHA        "Building for Raspberry Pi Alpha"
    RPICM1          "Building for Raspberry Pi Compute Module 1"
    RPI3B11         "Building for Raspberry Pi 3B"
    RPI3B12         "Building for Raspberry Pi 3B"
    RPI3B13         "Building for Raspberry Pi 3B"
    RPIZ1           "Building for Raspberry Pi Zero 1"
    RPICM3          "Building for Raspberry Pi Compute Module 3"
    RPIZ1W          "Building for Raspberry Pi Zero 1W"
    RPI3A_PLUS      "Building for Raspberry Pi 3A+"
    RPICM3_PLUS     "Building for Raspberry Pi Compute Module 3+"
    RPI4B           "Building for Raspberry Pi 4B"
    RPI3B_PLUS      "Building for Raspberry Pi 3B+"
    RPI400          "Building for Raspberry Pi 400"
    RPICM4          "Building for Raspberry Pi Compute Module 4"
    RPIZ2W          "Building for Raspberry Pi Zero 2(W)"
    RPI5            "Building for Raspberry Pi 5"
    RPICM5          "Building for Raspberry Pi Compute Module 5"
    RPI500          "Building for Raspberry Pi 500"
    RPICM5_LITE     "Building for Raspberry Pi Compute Module 5 Lite"
)

# ----------------------
# Validating user choices
# ----------------------
if(BOARD STREQUAL "RPIA" OR BOARD STREQUAL "RPIB" OR BOARD STREQUAL "RPIA_PLUS" OR BOARD STREQUAL "RPIB_PLUS" OR BOARD STREQUAL "RPIALPHA" OR BOARD STREQUAL "RPICM1" OR BOARD STREQUAL "RPIZ1" OR BOARD STREQUAL "RPIZ1W")
    if(ARCH STREQUAL "arm64")
        message(FATAL_ERROR "Model does not support arm64")
    endif()
endif()

# ----------------------
# Raspberry Pi CPU map
# ----------------------
if(BOARD STREQUAL "RPIA" OR BOARD STREQUAL "RPIB" OR BOARD STREQUAL "RPIA_PLUS" OR BOARD STREQUAL "RPIB_PLUS" OR BOARD STREQUAL "RPIALPHA" OR BOARD STREQUAL "RPICM1" OR BOARD STREQUAL "RPIZ1" OR BOARD STREQUAL "RPIZ1W")
    set(RPI_CPU         arm1176jzf-s)
    set(ARM_BITS        arm32)
    set(IMAGEFILE       kernel.img)
elseif(BOARD STREQUAL "RPI2B10" OR BOARD STREQUAL "RPI2B11" OR BOARD STREQUAL "RPI3B11")
    set(RPI_CPU         cortex-a7)
    set(ARM_BITS        ${ARCH})   # arm32 / arm64
    set(IMAGEFILE       kernel7.img)
elseif(BOARD STREQUAL "RPI2B12" OR BOARD STREQUAL "RPI3B12" OR BOARD STREQUAL "RPI3B13" OR BOARD STREQUAL "RPICM3" OR BOARD STREQUAL "RPICM3_PLUS" OR BOARD STREQUAL "RPI3A_PLUS" OR BOARD STREQUAL "RPI3B_PLUS" OR BOARD STREQUAL "RPIZ2W")
    set(RPI_CPU         cortex-a53)
    set(ARM_BITS        ${ARCH})   # arm32 / arm64
    if(ARCH STREQUAL "arm64")
         set(IMAGEFILE  kernel8.img)
    else()
         set(IMAGEFILE  kernel7.img)
    endif()
elseif(BOARD STREQUAL "RPI4B" OR BOARD STREQUAL "RPI400" OR BOARD STREQUAL "RPICM4" OR BOARD STREQUAL "RPICM4")    
    set(RPI_CPU         cortex-a72)
    set(ARM_BITS        ${ARCH})   # arm32 / arm64
    if(ARCH STREQUAL "arm64")
         set(IMAGEFILE  kernel8.img)
    else()
         set(IMAGEFILE  kernel7l.img)
    endif()
elseif(BOARD STREQUAL "RPI5" OR BOARD STREQUAL "RPICM5" OR BOARD STREQUAL "RPI500" OR BOARD STREQUAL "RPICM5_LITE")
    set(RPI_CPU         cortex-a76)
    set(ARM_BITS        ${ARCH})   # arm32 / arm64
    set(IMAGEFILE       kernel8.img)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Build type (Debug, Release)" FORCE)
endif()

# ----------------------
# Auto select toolchains and Startup files for selected ARCH
# ----------------------
if(ARM_BITS STREQUAL "arm32")
    set(CMAKE_C_COMPILER "$ENV{ARM_NONE_EABI}/arm-none-eabi-gcc.exe" CACHE PATH "C compiler" FORCE)
    set(CMAKE_ASM_COMPILER "$ENV{ARM_NONE_EABI}/arm-none-eabi-gcc.exe" CACHE PATH "ASM compiler" FORCE)
    set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/src/start32.s)
elseif(ARM_BITS STREQUAL "arm64")
    set(CMAKE_C_COMPILER "$ENV{ARM_AARCH64}/aarch64-none-elf-gcc.exe" CACHE PATH "C compiler" FORCE)
    set(CMAKE_ASM_COMPILER "$ENV{ARM_AARCH64}/aarch64-none-elf-gcc.exe" CACHE PATH "ASM compiler" FORCE)
    set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/src/start64.s)
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ----------------------
# Linker script defines
# ----------------------
set(LINKER_DEFINES "")

# ----------------------
# Set output directory for SD-Card
# ----------------------
set(SDCARD_DIR ${CMAKE_SOURCE_DIR}/sdcard)

# ----------------------
# Bronbestanden
# ----------------------
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/lib/*.c
    ${STARTUP_FILE}
)

# ----------------------
# Project setup
# ----------------------
project(doublepulse
    VERSION 1.0
    LANGUAGES C ASM)

# ----------------------
# Explicit Debug / Release flags
# ----------------------
set(CMAKE_C_FLAGS_DEBUG "-Og -g3" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-O2 -g3 -DNDEBUG" CACHE STRING "" FORCE)

set(CMAKE_ASM_FLAGS_DEBUG "-g3" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE STRING "" FORCE)

message(STATUS "Building for CPU: ${RPI_CPU} ")

# ----------------------
# Kernel image & linker load address
# ----------------------
if(ARM_BITS STREQUAL "arm64") 
    set(LINKER_LOAD_ADDR 0x80000)
    set(ARM_64BIT 1)
    # Extra namen waar de firmware naar zoekt op 64-bit systemen
    set(ALT_IMAGEFILES kernel8-71.img kernel8-2712.img)
else() # 32-bit
    set(LINKER_LOAD_ADDR 0x8000)
    set(ARM_64BIT 0)
    set(ALT_IMAGEFILES kernel7.img kernel7l.img)
endif()

# ----------------------
# Linker script generation
# ----------------------
set(LINKER_PP     ${CMAKE_BINARY_DIR}/bin/linker.ld.pp)
set(LINKER_SCRIPT ${CMAKE_BINARY_DIR}/bin/linker.ld)

# Stap 1: CMake-variabelen vervangen (@VAR@)
configure_file(
    ${CMAKE_SOURCE_DIR}/src/linker.ld.S
    ${LINKER_PP}
    @ONLY
)

# ----------------------
# Executable
# ----------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# Forceer dat ASM geen C compile flags meekrijgt bij linking
set_source_files_properties(${STARTUP_FILE} PROPERTIES
     COMPILE_FLAGS "-x assembler-with-cpp"
)

add_custom_command(
    OUTPUT ${LINKER_SCRIPT}
    COMMAND ${CMAKE_C_COMPILER} -E -P -x c
            ${LINKER_DEFINES}
            ${LINKER_PP}
            -o ${LINKER_SCRIPT}
    DEPENDS ${LINKER_PP}
    COMMENT "Preprocessing linker script"
)

add_custom_target(generate_linker_script DEPENDS ${LINKER_SCRIPT})
add_dependencies(${PROJECT_NAME} generate_linker_script)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
    LINK_DEPENDS ${LINKER_SCRIPT}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# ----------------------
# Compiler settings
# ----------------------

if(DUALCORE STREQUAL "on")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
    DUALCORE)
endif()

if(ARM_BITS STREQUAL "arm64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:ARCH_ARM64>
    $<$<COMPILE_LANGUAGE:ASM>:${BOARD}>)  # Voegt bijv. -DRPIZ1 toe aan ASM
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:ASM>:ARCH_ARM32>
    $<$<COMPILE_LANGUAGE:ASM>:${BOARD}>)  # Voegt bijv. -DRPIZ1 toe aan ASM
endif()

# Compiler flags
set(ARCH_FLAGS "")

if(ARM_BITS STREQUAL "arm64")
    set(ARCH_FLAGS -mstrict-align -mcpu=${RPI_CPU})
else() # 32-bit
    set(ARCH_FLAGS -mcpu=${RPI_CPU})
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<COMPILE_LANGUAGE:C>: -Wall -fno-builtin -fno-strict-aliasing>
	${ARCH_FLAGS}
)
message(STATUS "Compiler flags: ${ARCH_FLAGS} ")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug flags: ${CMAKE_C_FLAGS_DEBUG}")
else()
    message(STATUS "Release flags: ${CMAKE_C_FLAGS_RELEASE}")
endif()

# ----------------------
# Linker flags
# ----------------------

target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=${RPI_CPU}
    -nostartfiles
    -nostdlib
    -ffreestanding
    -T${LINKER_SCRIPT}
    -Wl,-Map=${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}.map
)

target_link_libraries(${PROJECT_NAME} PRIVATE gcc)

# ----------------------
# Post-build acties
# ----------------------

set(BOOTFILES_DIR ${CMAKE_SOURCE_DIR}/CMakeFiles/boot/PI)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
            $<TARGET_FILE:${PROJECT_NAME}>
            ${CMAKE_BINARY_DIR}/bin/${IMAGEFILE}
    COMMAND ${CMAKE_OBJCOPY} --srec-forceS3
            $<TARGET_FILE:${PROJECT_NAME}>
            ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}.srec
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S $<TARGET_FILE:${PROJECT_NAME}> > ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}.lst
    )
    set(JTAG_ENABLE "gpio=22-27=a4")
    if(RPI_CPU STREQUAL "cortex-a72")
        set(MODEL_CONFIG "enable_jtag_gpio=1")
    endif()
endif()

# Zorg dat de kernel altijd gebouwd wordt als je 'make' doet
add_custom_target(kernel ALL
    DEPENDS ${PROJECT_NAME}
)

# ----------------------
# Configuratiebestand voor de SD-kaart
# ----------------------
configure_file(
    ${CMAKE_SOURCE_DIR}/CMakeFiles/boot/config.txt.in
    ${CMAKE_BINARY_DIR}/bin/config.txt
    @ONLY
)

# Copy model-specific boot files
add_custom_target(copy_boot_files ALL
    # verwijder bestaande sdcard dir (indien aanwezig)
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${SDCARD_DIR} 
    # maak hem opnieuw aan
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SDCARD_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${BOOTFILES_DIR} ${SDCARD_DIR}
# Kopieer ALLE gegenereerde kernel bestanden naar de SD kaart
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/${IMAGEFILE} ${SDCARD_DIR}/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/config.txt ${SDCARD_DIR}
)
