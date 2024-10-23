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

/**
 * \brief HLCC - Host LED Communication Channel
 *
 * HLCC enables communication between separate QMK devices
 * through the host's lock status LED's
 */
/*
#define HLCC_TIMEOUT 200
#define HLCCKEY KC_CAPS             // set which lock key acts as HLCC
static uint8_t hlcc_comms_data = 0; // last data stored from HLCC
static bool    hlcc_comms_mode = 0; // 0 = listening // 1 = writing

// listen to HLCC channel
bool led_update_user(led_t led_state) {
    // Timer:
    static uint32_t hlcc_timer;
    static uint32_t hlcc_timed;
    hlcc_timed = timer_elapsed32(hlcc_timer);
    hlcc_timer = timer_read();
    // hlcc LED status:
    const bool     hlcc_led_state     = led_state.caps_lock;                    // set which LED to use for HLCC
    static bool    hlcc_led_tminus1   = 0;                                      // hlcc LED status at t - 1 (previous state)
    const bool     hlcc_led_changed   = abs(hlcc_led_state - hlcc_led_tminus1); // LED status changed? Results in 0 if status == tminus1, or in 1 if status != tminus 1.
    static uint8_t hlcc_blink_counter = 0;                                      // counting blinks of leds

    if (!hlcc_comms_mode) {
        // listen to comms channel:
        if (hlcc_timed >= HLCC_TIMEOUT) {
            // After timeout, store tally to comms_data and reset counter:
            hlcc_comms_data    = (int)hlcc_blink_counter / 2; // one blink = 2 counts
            hlcc_blink_counter = 0;
            printf("tp3s: hlcc_comms_data: %i \n", hlcc_comms_data);
            // Execution of message here::
            if (hlcc_comms_data == 2) {
                // if message consists of 2 blinks, then do:
                uint16_t mod_ctrl = get_mods() & MOD_MASK_CTRL;
                if (mod_ctrl) {
                    unregister_mods(mod_ctrl);
                } else {
                    register_mods(MOD_MASK_CTRL);
                }
            }

        } else if (hlcc_led_changed) {
            // count state changes if within timeout
            hlcc_blink_counter += 1;
        }
    }

    hlcc_led_tminus1 = hlcc_led_state; // store led_status at t - 1 for next cycle
    return false;                      // do not override led_update_kb()
}

// write to HLCC channel
void matrix_scan_user(void) {
    // monitor CTRL state
    const bool  mod_ctrl         = get_mods() & MOD_MASK_CTRL;
    static bool mod_ctrl_tminus1 = 0;
    bool        mod_ctrl_changed = abs(mod_ctrl - mod_ctrl_tminus1);
    if (mod_ctrl_changed) {
        // signal change in CTRL state over HLCC channel:
        hlcc_comms_mode = 1; // set HLCC to write mode
        hlcc_comms_data = 2; // blink 2 times over HLCC channel
    }
    mod_ctrl_tminus1 = mod_ctrl; // store ctrl state at t - 1 for next cycle

    // monitor HLCC comms mode:
    if (hlcc_comms_mode) {
        // write data to hlcc channel:
        if (hlcc_comms_data > 0) {
            // blink LED 1x
            tap_code16(HLCCKEY);
            wait_ms(2);
            tap_code16(HLCCKEY);
            wait_ms(2);
        }
        if (hlcc_comms_data > 1) {
            // blink LED 2x
            tap_code16(HLCCKEY);
            wait_ms(2);
            tap_code16(HLCCKEY);
            wait_ms(2);
        }
        if (hlcc_comms_data > 2) {
            // blink LED 3x
            tap_code16(HLCCKEY);
            wait_ms(2);
            tap_code16(HLCCKEY);
            wait_ms(2);
        }
        if (hlcc_comms_data > 3) {
            // blink LED 4x
            tap_code16(HLCCKEY);
            wait_ms(2);
            tap_code16(HLCCKEY);
            wait_ms(2);
        }
        hlcc_comms_mode = 0; // return to listening mode
    }
} */

/* Custom keyccodes */
#define LMB KC_BTN1
#define RMB KC_BTN2
#define MMB KC_BTN3
#define BCK KC_BTN4
#define FWD KC_BTN5
#define ZOOMKEY MMB // sets MMB as "zoom_key" - can be changed to any - brief below.
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
