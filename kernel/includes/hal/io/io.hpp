/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <cstdint>

namespace io {
    auto outb(std::uint16_t port, std::uint8_t) -> void;
    auto outw(std::uint16_t port, std::uint16_t) -> void;
    auto outl(std::uint16_t port, std::uint32_t) -> void;
    auto outsw(std::uint16_t port, const void* buf, unsigned long n) -> void;
    auto outsl(std::uint32_t port, const void* addr, int cnt) -> void;

    auto inb(std::uint16_t port) -> std::uint8_t;
    auto inw(std::uint16_t port) -> std::uint16_t;
    auto inl(std::uint16_t port) -> std::uint32_t;
    auto insw(std::uint16_t port, void* buf, unsigned long n) -> void;
    auto insl(std::uint32_t port, void* addr, int cnt) -> void;

    auto get_cr0() -> std::uint32_t;
    auto set_cr0(std::uint32_t cr0) -> void;

    auto enable_interrupts() -> void;
    auto disable_interrupts() -> void;

    [[noreturn]] auto kernel_halt() -> void;
} // namespace hal::io
