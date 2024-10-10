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

/*Azoteq driver*/
#define AZOTEQ_IQS5XX_TPS65
#define POINTING_DEVICE_MOTION_PIN GP27

/*Azoteq over I2C*/
#define I2C1_SDA_PIN GP10
#define I2C1_SCL_PIN GP11
#define I2C_DRIVER I2CD1

/*mcu reset*/
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17

/*Unknown RP2040 voodoo*/
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/*mouse reports*/
#define MOUSE_EXTENDED_REPORT

/*bootmagic -> sw3 on argos controller*/
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

/*trackpad orientation*/
// #define POINTING_DEVICE_INVERT_Y
// #define POINTING_DEVICE_INVERT_X
// #define AZOTEQ_IQS5XX_ROTATION_90
// #define AZOTEQ_IQS5XX_ROTATION_180
// #define AZOTEQ_IQS5XX_ROTATION_270
