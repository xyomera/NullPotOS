/*
 * Copyright (C) 2026 xyomera
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/serial/serial.hpp>
#include <hal/io/io.hpp>

using namespace serial;

SerialPort::SerialPort(const std::uint16_t serial_port_id) : serial_port_id_(serial_port_id) {
    io::outb(serial_port_id_ + 1, 0x00);
    io::outb(serial_port_id_ + 3, 0x80);
    io::outb(serial_port_id_ + 0, 0x03);
    io::outb(serial_port_id_ + 1, 0x00);
    io::outb(serial_port_id_ + 3, 0x03);
    io::outb(serial_port_id_ + 2, 0xc7);
    io::outb(serial_port_id_ + 4, 0x0b);
    io::outb(serial_port_id_ + 4, 0x1e);
    io::outb(serial_port_id_ + 0, 0xae);

    if (io::inb(serial_port_id_ + 0) != 0xae) {
        io::kernel_halt();
    }

    io::outb(serial_port_id_ + 4, 0x0f);
}

auto SerialPort::is_transmit_empty() -> bool {
    return io::inb(serial_port_id_ + 5) & 0x20;
}

auto SerialPort::serial_received() -> bool {
    return io::inb(serial_port_id_ + 5) & 1;
}

auto SerialPort::serial_read() -> char {
    while (serial_received() == 0) {
    }
    return io::inb(serial_port_id_);
}

auto SerialPort::serial_write_char(char s) -> void {
    while (is_transmit_empty() == 0) {
    }
    io::outb(serial_port_id_, s);
}

auto SerialPort::serial_write(std::string_view string) -> void {
    for (const char c: string) {
        if (c == '\n') {
            serial_write_char('\r');
        }
        serial_write_char(c);
    }
}
