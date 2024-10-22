/* Copyright 2024 Wimads
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/*scroll config*/
#define AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE 1 // trigger distance (pixels) for 2-finger scroll
#define TP3S_SCROLL_DIV 6.0                     // divisor (float) for slowing down 2-finger scroll

/*tap config*/
#define AZOTEQ_IQS5XX_TAP_DISTANCE 10 // error margin for tap (how many pixels movement to allow for registering tap).

/*HLCC config*/
#define LED_KANA_PIN GP26 // kana led pin for HLCC (Host LED Comms Channel)

/*combos*/
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 60

/*maccel curve parameters
 * IMPORTANT:
 * MACCEL_LIMIT_UPPER should normally *not* be set by user! Instead DPI setting should be adjusted.
 * Unfortunately, weird things happen in maccel when DPI is adjusted on the Azoteq sensor. Cause is yet unkown.
 * WORKAROUND:
 * 1. Do NOT touch default DPI device setting. Instead:
 * 2. Adjust value for MACCEL_LIMIT_UPPER to get a lower/higher sensitivity (equivalent to multiplying the default DPI of 1000)
 * 3. Unfortunate side effect is that a different upper limit, will affect how the other variables feel, so it may be a bit harder to dial in.
 */
#define MACCEL_TAKEOFF 1.8     // lower/higher value = curve starts more smoothly/abruptly
#define MACCEL_GROWTH_RATE 0.8 // lower/higher value = curve reaches its upper limit slower/faster
#define MACCEL_OFFSET 1.9      // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 0.8       // lower limit of accel curve (minimum acceleration factor)
#define MACCEL_LIMIT_UPPER 4   // lower/higher vaule = lower/higher maximum sensitivity (normally set to 1, but used as workaround for Azoteq)

/*maccel "under the hood" */
#define EECONFIG_USER_DATA_SIZE 20          // technical under the hood necessity for maccel
#define MACCEL_DEBUG                        // enable debug console
#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS    //
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1 // enable floats in debug console

/*VIA (not currently enabled yet)*/
#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 8
#endif // VIA_ENABLE
