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

/* Custom keyccodes */
#define LMB KC_BTN1
#define RMB KC_BTN2
#define MMB KC_BTN3
#define BCK KC_BTN4
#define FWD KC_BTN5
#define ZOOMKEY LMB // sets LMB as "zoom_key" - can be changed to any - brief below.
#include "gboards/g/keymap_combo.h"

/**
 * \brief ZOOM_KEY
 *
 * zoom_key is a mouse button, which, when scrolling, doubles as CTRL for zooming.
 * LMB is used as the zoom_key, because it is the only one wired up right now.
 * But in final setup MMB will be more ideal as the zoom_key.
 */
static bool     zoom_key_pressed = false; // is zoom_key pressed?
static bool     scroll_active    = false; // is scrolling active?
static bool     scroll_changed   = false; // stored scroll state from previous cycle to determine change in state.
static uint16_t current_keycode  = 0;     // current value of zoom_key keycode.

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    /*zoom_key*/

    // check current scroll state:
    scroll_active = mouse_report.h | mouse_report.v;

    // update zoom_key based on change in scroll state:
    if (scroll_active && scroll_active != scroll_changed) {
        // when scrolling state changes to active:
        if (zoom_key_pressed && current_keycode != KC_LCTL) {
            // Update zoom_key if pressed & current_keycode doesn't match:
            unregister_code16(current_keycode);
            current_keycode = KC_LCTL;
            register_code16(current_keycode);
            wait_ms(15); // delay between updating keycode and sending mouse report
        }
    } // when scroll state changes to *in*active, don't update zoom_key, to avoid unintended mouse butten presses after zooming

    // store scroll state for next cycle:
    scroll_changed = scroll_active;

    /*maccel*/
#ifdef MACCEL_ENABLE
    return pointing_device_task_maccel(mouse_report);
#endif // !MACCEL_ENABLE
} // !pointing_device_task_user

enum dilemma_keymap_layers { _DEF = 0 };

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper_TP3S(sw1, sw2, sw3) LAYOUT_wrapper(sw3, sw2, KC_NO, sw1)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_wrapper_TP3S(
        RMB,
        MMB,
        LMB // bootmagic
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ZOOMKEY:
            if (record->event.pressed && !current_keycode) {
                // when pressed and no zoom_key is registered yet:
                if (scroll_active) {
                    current_keycode = KC_LCTL;
                } else {
                    current_keycode = ZOOMKEY;
                }
                register_code16(current_keycode);
                zoom_key_pressed = true;
                // update LCC LED bit1:
            } else {
                // when released:
                unregister_code16(current_keycode);
                zoom_key_pressed = false;
                current_keycode  = 0;
            }
            return false;

        default:
            return true;

    } // !switch
    return true;
} // !process_record_user

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    keyboard_post_init_maccel();
    // debug_keyboard=true;
    // debug_mouse=true;
}
