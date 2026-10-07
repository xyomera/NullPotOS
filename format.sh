#!/usr/bin/sh

find kernel/ \
    -type f \( -name "*.cpp" -o -name "*.hpp" \) \
    -exec clang-format -i {} +
