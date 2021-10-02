/**
 * @file HIDController.cpp
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

#include "global.h"

#include "HIDController.h"

#include "Arduino.h"
#include "HID.h"

static const uint8_t hid_report_descriptor[] PROGMEM =
{
    0x05, 0x01,                                          // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                                          // USAGE (Game Pad)
    0xa1, 0x01,                                          // COLLECTION (Application)
    0xa1, 0x00,                                          //   COLLECTION (Physical)
    0x85, 0x01,                                          //     REPORT_ID (1)
    0x05, 0x01,                                          //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                                          //     USAGE (X)
    0x09, 0x31,                                          //     USAGE (Y)
    0x09, 0x32,                                          //     USAGE (Z)
    0x09, 0x35,                                          //     USAGE (Rz)
    0x16, 0x00, 0x00,                                    //     LOGICAL_MINIMUM (0)
    0x26, (ADC_MAX & 0xFF), ((ADC_MAX >> 8u) & 0xFFu),   //     LOGICAL_MAXIMUM (255)
    0x95, 0x04,                                          //     REPORT_COUNT (4)
    0x75, 0x10,                                          //     REPORT_SIZE (16)
    0x81, 0x02,                                          //     INPUT (Data,Var,Abs)
    0x05, 0x09,                                          //     USAGE_PAGE (Button)
    0x19, 0x01,                                          //     USAGE_MINIMUM (Button 1)
    0x29, 0x0A,                                          //     USAGE_MAXIMUM (Button 10)
    0x15, 0x00,                                          //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                                          //     LOGICAL_MAXIMUM (1)
    0x75, 0x0A,                                          //     REPORT_SIZE (10)
    0x95, 0x01,                                          //     REPORT_COUNT (1)
    0x81, 0x02,                                          //     INPUT (Data,Var,Abs)
    0x95, 0x01,                                          //     REPORT_COUNT (1)
    0x75, 0x06,                                          //     REPORT_SIZE (6)
    0x81, 0x03,                                          //     INPUT (Cnst)
    0xc0,                                                //   END_COLLECTION
    0xc0                                                 // END_COLLECTION
};

static HIDSubDescriptor node(hid_report_descriptor, sizeof(hid_report_descriptor));

void HIDController::begin()
{
    HID().AppendDescriptor(&node);
}

void HIDController::send(const HID_controller_report &report)
{
    HID_controller_report report2(report);

    report2.right_stick_x = ADC_CLAMP(report2.right_stick_x);
    report2.right_stick_y = ADC_CLAMP(report2.right_stick_y);
    report2.left_stick_y = ADC_CLAMP(report2.left_stick_y);
    report2.left_stick_x = ADC_CLAMP(report2.left_stick_x);

    HID().SendReport(0x01, &report2, sizeof(report2));
}
