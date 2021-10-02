/**
 * @file HIDController.h
 * @author Hobbylad ()
 * @brief Drone controller USB HID.
 * @version 0.1
 * @date 2021-07-15
 * @copyright Copyright (c) 2021
 *
 * Simple USB drone controller for PC simulator.
 *
 * Prototyped on 5V Pro Micro ATMega32U4 (Arduino Leonardo) and wired to hacked left & right
 * 2-axis joystick drone controller outputing 0 - 3.3V per axis.
 *
 * Appears at HID standard device and does not need custom driver.
 *
 * Use axis calibration and axis "invert" if necessary in drone simulator controller setup.
 *
 * Compiled with Arduino 1.8.13 IDE and tested on CurryKitten FPV Simulator (PC). *
 *
  *
 * MIT License
 *
 * Copyright (c) 2021 Hobbylad
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HID_CONTROLLER_H
#define HID_CONTROLLER_H

#include "stdint.h"

typedef struct __attribute__((packed)) _HID_controller_report
{
    uint16_t right_stick_x;
    uint16_t right_stick_y;
    uint16_t left_stick_y;
    uint16_t left_stick_x;
    uint16_t buttons;
} HID_controller_report;

class HIDController
{
    public:
    void begin();
    void send(const HID_controller_report &report);
};

#endif
