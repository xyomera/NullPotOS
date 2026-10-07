#
# Copyright (C) 2026 xyomera
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 4.4.0)

include(ExternalProject)
include(${CMAKE_SOURCE_DIR}/cmake/env.cmake)

project(NullPotOS VERSION "0.0.1" LANGUAGES ASM CXX HOMEPAGE_URL "https://github.com/xyomera/NullPotOS" DESCRIPTION "A unix-like HobbyOS")

ExternalProject_Add(limine
  URL        https://github.com/Limine-Bootloader/Limine/releases/download/v${LIMINE_VERSION}/limine-${LIMINE_VERSION}.tar.gz
  URL_HASH   SHA256=416bfd0368a66044bed0060415752377e11b7513190a1b2c62f865f652a5ac9e
  PREFIX    ${CMAKE_BINARY_DIR}/limine
  CONFIGURE_COMMAND <SOURCE_DIR>/configure TOOLCHAINS=llvm --enable-all
  BUILD_COMMAND     ${CMAKE_COMMAND} -E env make -j ${NPROC}
  INSTALL_COMMAND "" 
)

add_subdirectory(${CMAKE_SOURCE_DIR}/kernel)

add_custom_target(iso ALL
    COMMENT "Making ISO image for ${PROJECT_NAME}"
    DEPENDS limine kernel
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/iso/efi/boot
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/iso/${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/limine/src/limine-build/bin/BOOTX64.EFI ${CMAKE_BINARY_DIR}/iso/efi/boot/bootx64.efi
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/limine/src/limine-build/bin/limine-bios.sys ${CMAKE_BINARY_DIR}/iso/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/limine/src/limine-build/bin/limine-uefi-cd.bin ${CMAKE_BINARY_DIR}/iso/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/limine/src/limine-build/bin/limine-bios-cd.bin ${CMAKE_BINARY_DIR}/iso/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/assets/iso/limine.conf ${CMAKE_BINARY_DIR}/iso/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/kernel/kernel ${CMAKE_BINARY_DIR}/iso/${PROJECT_NAME}/kernel.elf
    COMMAND xorriso -as mkisofs -R -r -J -b limine-bios-cd.bin
        -no-emul-boot -boot-load-size 4 -boot-info-table
        -hfsplus -apm-block-size 2048
        --efi-boot limine-uefi-cd.bin
        -efi-boot-part --efi-boot-image --protective-msdos-label
        ${CMAKE_BINARY_DIR}/iso -o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.iso
)

add_custom_target(run
    COMMENT "Running ${PROJECT_NAME} ISO image in QEMU"
    DEPENDS iso
    USES_TERMINAL
    COMMAND qemu-system-x86_64 -name ${PROJECT_NAME}
    -m 1G -serial file:${CMAKE_BINARY_DIR}/qemu.log -drive if=pflash,format=raw,readonly=on,file=${CMAKE_SOURCE_DIR}/assets/ovmf/${TARGET_ARCH}/ovmf_code.fd
    -cdrom ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.iso
)

add_custom_target(debug
    COMMENT "Debugging ${PROJECT_NAME} ISO image in QEMU"
    DEPENDS iso
    USES_TERMINAL
    COMMAND qemu-system-x86_64 -name ${PROJECT_NAME}
        -m 1G -serial file:${CMAKE_BINARY_DIR}/qemu.log -drive if=pflash,format=raw,readonly=on,file=${CMAKE_SOURCE_DIR}/assets/ovmf/${TARGET_ARCH}/ovmf_code.fd
        -cdrom ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.iso -S -s &
        lldb ${CMAKE_BINARY_DIR}/kernel/kernel -o "gdb-remote 1234"
)