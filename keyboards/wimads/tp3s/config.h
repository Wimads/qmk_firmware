/*
 * Copyright 2024 Wim aan de Stegge (@Wimads)
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

////HARDWARE CONFIG////
/*Azoteq driver*/
#define AZOTEQ_IQS5XX_TPS65
#define POINTING_DEVICE_MOTION_PIN GP27

/*Azoteq over I2C*/
#define I2C1_SDA_PIN GP10
#define I2C1_SCL_PIN GP11
#define I2C_DRIVER I2CD1
// #define AZOTEQ_IQS5XX_ADDRESS    // (Optional) Sets the I2C Address for the Azoteq trackpad	0xE8
// #define AZOTEQ_IQS5XX_TIMEOUT_MS //	(Optional) The timeout for i2c communication with in milliseconds.

/*trackpad orientation*/
// #define POINTING_DEVICE_INVERT_Y
// #define POINTING_DEVICE_INVERT_X
// #define AZOTEQ_IQS5XX_ROTATION_90
// #define AZOTEQ_IQS5XX_ROTATION_180
// #define AZOTEQ_IQS5XX_ROTATION_270

/*mcu reset*/
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17

/*Unknown RP2040 voodoo*/
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

////USER CONFIG////
#define MOUSE_EXTENDED_REPORT
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
