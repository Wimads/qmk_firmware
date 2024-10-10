/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

#include QMK_KEYBOARD_H
#include "maccel/maccel.h"

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
#ifdef MACCEL_ENABLE
    return pointing_device_task_maccel(mouse_report);
#endif
}

enum my_keycodes {
    MA_STEEPNESS = QK_USER, // mouse acceleration curve steepness step key
    MA_OFFSET,              // mouse acceleration curve offset step key
    MA_LIMIT,               // mouse acceleration curve limit step key
    MA_TAKEOFF
};

#define LMB KC_BTN1
#define RMB KC_BTN2
#define MMB KC_BTN3
#define BCK KC_BTN4
#define FWD KC_BTN5

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if (!process_record_maccel(keycode, record, MA_STEEPNESS, MA_OFFSET, MA_LIMIT)) {
    //     return false;
    // }
    return true;
}

#ifdef COMBO_ENABLE
#    include "gboards/g/keymap_combo.h"
#endif

enum dilemma_keymap_layers { LAYER_BASE = 0 };

#ifndef POINTING_DEVICE_ENABLE
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#define LAYOUT_wrapper_TP3S(sw1, sw2, sw3) LAYOUT_wrapper(sw3, sw2, KC_NO, sw1)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_wrapper_TP3S(
        RMB,
        MMB,
        LMB
    )
};
// clang-format on

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    keyboard_post_init_maccel();
    // debug_keyboard=true;
    // debug_mouse=true;
}
