/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdint>
#include <drivers/serial/serial.hpp>
#include <limine.h>

namespace {
    [[gnu::used, gnu::section(".limine_requests")]] volatile std::uint64_t limine_base_revision[] =
            LIMINE_BASE_REVISION(6);
}

namespace {
    [[gnu::used, gnu::section(".limine_requests_start")]] volatile std::uint64_t limine_requests_start_marker[] =
            LIMINE_REQUESTS_START_MARKER;

    // kernel stack
    [[gnu::used, gnu::section(".limine_requests")]] volatile limine_stack_size_request kernel_stack_size = {
            .id = LIMINE_STACK_SIZE_REQUEST_ID,
            .revision = 3,
            .response = nullptr,
            .stack_size = static_cast<std::uint64_t>(1024 * 64),
    };

    // framebuffer
    [[gnu::used, gnu::section(".limine_requests")]] volatile limine_framebuffer_request kernel_framebuffer = {
            .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
            .revision = 0,
            .response = nullptr,
    };

    [[gnu::used, gnu::section(".limine_requests_end")]] volatile std::uint64_t limine_requests_end_marker[] =
            LIMINE_REQUESTS_END_MARKER;
} // namespace

extern "C" [[noreturn]] auto kernel_main() -> void {
    serial::SerialPort serial_port(serial::COM1);
    serial_port.serial_write("\nHello, NullPotOS!\n");

    if (kernel_framebuffer.response == nullptr) {
        serial_port.serial_write("[ERROR] framebuffer response address is nullptr\n");
    } else if (kernel_framebuffer.response->framebuffer_count < 1) {
        serial_port.serial_write("[ERROR] no framebuffer\n");
    } else {
        serial_port.serial_write("[INFO] succeed in getting framebuffer\n");
    }

    constexpr std::uint64_t size = 100;
    constexpr std::uint32_t blue = 0x000000FF;

    for (std::uint64_t y = 0; y < size; ++y) {
        auto* line = reinterpret_cast<std::uint32_t*>(
                reinterpret_cast<std::uint8_t*>(kernel_framebuffer.response->framebuffers[0]->address) +
                y * kernel_framebuffer.response->framebuffers[0]->pitch);
        for (std::uint64_t x = 0; x < size; ++x) {
            line[x] = blue;
        }
    }

    asm volatile("cli");
    while (true) {
        asm volatile("hlt");
    }
}
