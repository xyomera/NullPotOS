#
# Copyright (C) 2026 xyomera
# SPDX-License-Identifier: Apache-2.0
#

file(GLOB_RECURSE KERNEL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/**.cpp
)

add_executable(kernel ${KERNEL_SOURCES})

add_dependencies(kernel limine)

target_include_directories(kernel PRIVATE
    ${CMAKE_BINARY_DIR}/limine/src/limine/limine-protocol/include
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_compile_options(kernel PRIVATE
    $<$<CONFIG:Debug>:-Og -g3>
    $<$<CONFIG:Release>:-O2 -flto>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti>
    -nostdlib
    -Wall -Wextra -static
    -fno-builtin -fPIC
    -fno-stack-check -fno-stack-protector
    $<$<BOOL:$<STREQUAL:${TARGET_ARCH},x86_64>>:-mno-red-zone>
)

target_link_options(kernel PRIVATE
    $<$<CONFIG:Release>:-flto>
    -fuse-ld=lld
    -nostdlib
    -static
    -T ${CMAKE_CURRENT_SOURCE_DIR}/arch/${TARGET_ARCH}/linker.lds
)