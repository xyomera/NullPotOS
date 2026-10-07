/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdint>
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

    [[gnu::used, gnu::section(".limine_requests_end")]] volatile std::uint64_t limine_requests_end_marker[] =
            LIMINE_REQUESTS_END_MARKER;
} // namespace

extern "C" [[noreturn]] auto kernel_main() -> void {
    asm volatile("cli");
    while (true) {
        asm volatile("hlt");
    }
}
