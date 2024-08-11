/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

// Enables support for extended i16 mouse reports (instead of i8).
#define MOUSE_EXTENDED_REPORT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

// Adjust trackpad rotation.
// #define POINTING_DEVICE_ROTATION_90

// Configure for the Cirque model used on the Dilemma.
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_INVERT_X
// #define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll.
// #define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE // flicking
//

/* VBUS detection. */
#define USB_VBUS_PIN GP19

/* CRC. */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* Cirque trackpad over SPI. */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP14            // SP1
#define SPI_MOSI_PIN GP15           // SP1
#define SPI_MISO_PIN GP12           // SP1
#define POINTING_DEVICE_CS_PIN GP13 // SP1
#undef CIRQUE_PINNACLE_DIAMETER_MM
#define CIRQUE_PINNACLE_DIAMETER_MM 40

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17

/* Bootmagic. */
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

#define DRIVER_LED_TOTAL 4
