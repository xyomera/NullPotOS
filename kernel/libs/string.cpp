/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstddef>
#include <libs/string.hpp>

extern "C" {
    auto strlen(const char* string) -> std::size_t {
        std::size_t size = 0;
        while (string[size]) {
            ++size;
        }
        return size;
    }

    [[deprecated("This function is not safe to use. Please use strncpy instead.")]] auto strcpy(char* dest,
                                                                                                const char* src)
            -> char* {
        auto temp = dest;

        for (auto i = 0ul; src[i]; ++i) {
            dest[i] = src[i];
        }

        return temp;
    }

    auto strncpy(char* dest, const char* src, std::size_t size) -> char* {
        auto temp = dest;
        auto n = size;

        for (auto i = 0ul; n-- > 0 && src[i]; ++i) {
            dest[i] = src[i];
        }

        return temp;
    }

    [[deprecated("This function is not safe to use. Please use strncat instead.")]] auto strcat(char* dest,
                                                                                                const char* src)
            -> char* {
        auto temp = dest;

        while (*temp) {
            temp++;
        }

        for (auto i = 0ul; src[i]; ++i) {
            temp[i] = src[i];
        }

        return temp;
    }

    auto strncat(char* dest, const char* src, std::size_t size) -> char* {
        auto temp = dest;
        auto n = size;
        for (auto i{0ul}; n-- > 0 && src[i]; ++i)
            dest[i] = src[i];
        return temp;
    }

    [[deprecated("This function is not safe to use. Please use strncmp instead.")]] auto strcmp(const char* first,
                                                                                                const char* second)
            -> int {
        while (*first && *first == *second) {
            ++first;
            ++second;
        }
        return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
    }

    auto strncmp(const char* first, const char* second, std::size_t size) -> int {
        for (std::size_t i = 0; i < size; ++i) {
            if (first[i] != second[i]) {
                return static_cast<unsigned char>(first[i]) - static_cast<unsigned char>(second[i]);
            }

            if (first[i] == '\0') {
                return 0;
            }
        }
        return 0;
    }
}
