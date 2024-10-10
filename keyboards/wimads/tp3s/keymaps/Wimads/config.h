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
#define TP3S_SCROLL_DIV 6.0                     // devisor (float) for slowing down 2-finger scroll

/*combos*/
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 60

/*maccel*/
#define EECONFIG_USER_DATA_SIZE 20
#define MACCEL_DEBUG // enable debug console
#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1 // enable floats in debug console

/*VIA (not currently enabled yet)*/
#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 8
#endif // VIA_ENABLE
