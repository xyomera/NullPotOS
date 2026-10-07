/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#include <hal/io/io.hpp>

namespace io {
    auto outb(std::uint16_t port, std::uint8_t value) -> void {
        asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
    }

    auto outw(std::uint16_t port, std::uint16_t value) -> void {
        asm volatile("outw %1, %0" : : "dN"(port), "a"(value));
    }

    auto outl(std::uint16_t port, std::uint32_t value) -> void {
        asm volatile("outl %1, %0" : : "dN"(port), "a"(value));
    }

    auto outsw(std::uint16_t port, const void* buf, unsigned long n) -> void {
        asm volatile("cld; rep; outsw" : "+S"(buf), "+c"(n) : "d"(port));
    }

    auto outsl(std::uint32_t port, const void* addr, int cnt) -> void {
        asm volatile("cld;"
                     "repne; outsl;"
                     : "=S"(addr), "=c"(cnt)
                     : "d"(port), "0"(addr), "1"(cnt)
                     : "memory", "cc");
    }

    auto inb(std::uint16_t port) -> std::uint8_t {
        std::uint8_t ret;
        asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
        return ret;
    }

    auto inw(std::uint16_t port) -> std::uint16_t {
        std::uint16_t ret;
        asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
        return ret;
    }

    auto inl(std::uint16_t port) -> std::uint32_t {
        std::uint32_t ret;
        asm volatile("inl %1, %0" : "=a"(ret) : "dN"(port));
        return ret;
    }

    auto insw(std::uint16_t port, void* buf, unsigned long n) -> void {
        asm volatile("cld; rep; insw" : "+D"(buf), "+c"(n) : "d"(port));
    }

    auto insl(std::uint32_t port, void* addr, int cnt) -> void {
        asm volatile("cld;"
                     "repne; insl;"
                     : "=D"(addr), "=c"(cnt)
                     : "d"(port), "0"(addr), "1"(cnt)
                     : "memory", "cc");
    }

    auto disable_interrupts() -> void {
        asm volatile("cli" ::: "memory");
    }

    [[noreturn]] auto kernel_halt() -> void {
        disable_interrupts();
        while (true) {
            asm volatile("hlt");
        }
    }
} // namespace io
