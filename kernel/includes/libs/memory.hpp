/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <cstdint>

extern "C" {
    auto memset(void* dest, int value, std::size_t size) -> void*;
    auto memcpy(void* dest, const void* src, std::size_t size) -> void*;
    auto memmove(void* dest, const void* src, std::size_t size) -> void*;
    auto memchr(void* buf, std::int8_t value, std::uint64_t size) -> void*;
    auto memcmp(const void* first_buf, const void* second_buf, std::size_t size) -> int;
}
