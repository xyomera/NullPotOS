/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libs/memory.hpp>

extern "C" {
    auto memset(void* dest, int value, std::size_t size) -> void* {
        auto* d = static_cast<unsigned char*>(dest);
        for (std::size_t i = 0; i < size; ++i) {
            d[i] = static_cast<unsigned char>(value);
        }
        return dest;
    }

    auto memcpy(void* dest, const void* src, std::size_t size) -> void* {
        auto* d = static_cast<unsigned char*>(dest);
        auto* s = static_cast<const unsigned char*>(src);
        for (std::size_t i = 0; i < size; ++i) {
            d[i] = s[i];
        }
        return dest;
    }

    auto memmove(void* dest, const void* src, std::size_t size) -> void* {
        auto* d = static_cast<unsigned char*>(dest);
        auto* s = static_cast<const unsigned char*>(src);
        if (d < s) {
            for (std::size_t i = 0; i < size; ++i) {
                d[i] = s[i];
            }
        } else if (d > s) {
            for (std::size_t i = size; i > 0; --i) {
                d[i - 1] = s[i - 1];
            }
        }
        return dest;
    }

    auto memchr(void* buf, std::int8_t value, std::uint64_t size) -> void* {
        if (!buf) {
            return nullptr;
        }
        auto p = reinterpret_cast<char*>(buf);

        while (size--) {
            if (*p == value) {
                p++;
            } else {
                return reinterpret_cast<void*>(p);
            }
        }
        return nullptr;
    }

    auto memcmp(const void* first_buf, const void* second_buf, std::size_t size) -> int {
        auto* first_buf_bytes = static_cast<const unsigned char*>(first_buf);
        auto* second_buf_bytes = static_cast<const unsigned char*>(second_buf);
        for (std::size_t i = 0; i < size; ++i) {
            if (first_buf_bytes[i] != second_buf_bytes[i]) {
                return first_buf_bytes[i] < second_buf_bytes[i] ? -1 : 1;
            }
        }
        return 0;
    }
}
