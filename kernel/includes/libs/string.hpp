/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <cstddef>

extern "C" {
    auto strlen(const char* string) -> std::size_t;
    [[deprecated("This function is not safe to use. Please use strncpy instead.")]] auto strcpy(char* dest,
                                                                                                const char* src)
            -> char*;
    auto strncpy(char* dest, const char* src, std::size_t size) -> char*;
    [[deprecated("This function is not safe to use. Please use strncat instead.")]] auto strcat(char* dest,
                                                                                                const char* src)
            -> char*;
    auto strncat(char* dest, const char* src, std::size_t size) -> char*;
    [[deprecated("This function is not safe to use. Please use strncmp instead.")]] auto strcmp(const char* first,
                                                                                                const char* second)
            -> int;
    auto strncmp(const char* first, const char* second, std::size_t size) -> int;
}
