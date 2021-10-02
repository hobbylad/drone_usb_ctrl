/**
 * @file global.h
 * @author Hobbylad ()
 * @brief Definitions.
 * @version 0.1
 * @date 2021-07-15
 * @copyright Copyright (c) 2021
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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>

// ADC Max level expected from joysticks is 3.3V. Allow 10% as 5V ADC reference
// on Pro Micro ATMega32U4 used in prototype is connected to USB power which
// has this tolerance. Ideally a 3.3V reference would have been used in a
// custom board. Futhermore, drone simulators have joystick calibration which
// should allow this error to be corrected.
#define ADC_MAX ADC_LEVEL(3.3 * (1 + 0.1))

// Nominal reference voltage on Pro Micro ATMega32U4.
#define ADC_REFERENCE 5.0

// Convert voltage to 10-bit unsigned ADC code.
#define ADC_LEVEL(v) ((uint16_t) (((1024 * (v)) + (ADC_REFERENCE / 2)) / ADC_REFERENCE))

// Clamps ADC code to maximum value if necessary.
#define ADC_CLAMP(value) (((value) > ADC_MAX) ? ADC_MAX : (value))

#endif
