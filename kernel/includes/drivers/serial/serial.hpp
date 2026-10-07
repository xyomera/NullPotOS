/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <cstdint>
#include <string_view>

namespace serial {
    constexpr auto COM1 = 0x3F8;

    class SerialPort {
    private:
        const std::uint16_t serial_port_id_;

    public:
        explicit SerialPort(const std::uint16_t serial_port_id);
        ~SerialPort() = default;

        SerialPort() = delete ("Please set the serial port id!");

        auto serial_received() -> bool;
        auto is_transmit_empty() -> bool;
        auto serial_read() -> char;
        auto serial_write_char(char s) -> void;
        auto serial_write(std::string_view string) -> void;
    };
} // namespace serial
