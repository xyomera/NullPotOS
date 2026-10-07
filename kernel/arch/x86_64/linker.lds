/*
* Copyright (C) 2026 xyomera
* SPDX-License-Identifier: Apache-2.0
*/

OUTPUT_FORMAT(elf64-x86-64)

/* kernel start */
ENTRY(kernel_main)

PHDRS {
    limine_requests PT_LOAD FLAGS(0x06);
    text PT_LOAD FLAGS(0x05);
    rodata PT_LOAD FLAGS(0x04);
    data PT_LOAD FLAGS(0x06);
}

SECTIONS {
    /* higher half kernel */
    . = 0xffffffff80000000;

    /* limine requests */
    limine_requests : {
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))
    } :limine_requests

    /* move to the next memory page */
    . = ALIGN(CONSTANT(MAXPAGESIZE));

    /* kernel text section */
    .text : {
        *(.text .text.*)
    } :text

    /* move to the next memory page */
    . = ALIGN(CONSTANT(MAXPAGESIZE));

    /* kernel read-only data section */
    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    .note.gnu.build-id : {
        *(.note.gnu.build-id)
    } :rodata

    /* move to the next memory page */
    . = ALIGN(CONSTANT(MAXPAGESIZE));

    /* C++ */
    .init_array : {
        __init_array = .;
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP(*(.init_array))
        __init_array_end = .;
    } :data

    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data

    /* discard sections */
    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }
}