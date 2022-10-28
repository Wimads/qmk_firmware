/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

//!!! qmk develop branch
#include QMK_KEYBOARD_H

/*********KEYMAPS*******/

#define LAYOUT(                                          \
  k00, k01, k02, k03, k04,      k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14,      k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24,      k64, k63, k62, k61, k60, \
  k34, k31, k32, k33, k30,      k70, k73, k72            \
)                                                        \
{                                                        \
  {   k00,   k01,   k02,   k03,   k04 },                 \
  {   k10,   k11,   k12,   k13,   k14 },                 \
  {   k20,   k21,   k22,   k23,   k24 },                 \
  {   k30,   k31,   k32,   k33,   k34 },                 \
  {   k40,   k41,   k42,   k43,   k44 },                 \
  {   k50,   k51,   k52,   k53,   k54 },                 \
  {   k60,   k61,   k62,   k63,   k64 },                 \
  {   k70, KC_NO,   k72,   k73, KC_NO },                 \
}

//layers
enum charybdis_keymap_layers {
    _DEF = 0, //default
    _NUM = 1, //numbers and symbols
    _NAV = 2, //navigation and mouse keys
    _FUN = 3,  //function keys
    _SET = 4 //settings
};

//Custom Keycodes
enum custom_keycodes {
    //Switch windows keyboard language
    LANGC = CHARYBDIS_SAFE_RANGE, //correction for language tracker
    CLEARKB, //clears all registered keycodes, to solve stuck keycodes/layers/modifiers
    //modified mouse buttons
    M_A1, M_A2,
    M_AS1, M_AS2,
    M_CS1, M_CS2,
    M_CA1, M_CA2,
    M_MEH1, M_MEH2
};
//language key
#define LANG LGUI(KC_SPC)
//tap-hold keys
#define TH_A LT(10, KC_A)
#define TH_QUOT LT(10, KC_QUOT)
#define TH_5 LT(10, KC_5)
#define TH_8 LT(10, KC_8)
#define TH_PDOT LT(10, KC_DOT)
#define TH_EQL LT(10, KC_EQL)
#define DEL_NAV LT(_NAV, KC_DEL)
#define BSP_NUM LT(_NUM, KC_BSPC)
#define SPC_SET LT(_SET, KC_SPC)
//mouse buttons
#define M_1 KC_BTN1
#define M_2 KC_BTN2
#define M_3 KC_BTN3
#define M_4 KC_BTN4
#define M_5 KC_BTN5

#include "g/keymap_combo.h"

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEF] = LAYOUT(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      TH_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    TH_QUOT,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
               M_1,     M_2,     DEL_NAV, KC_LSFT, KC_LCTL,    KC_LALT, KC_SPC,  BSP_NUM   //trackball = mouse
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_NUM] = LAYOUT(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      KC_ASTR, KC_7,    TH_8,    KC_9,    KC_PPLS,                      KC_DLR,  KC_UNDS, KC_LPRN, KC_RPRN, KC_PERC,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_PSLS, KC_4,    TH_5,    KC_6,    KC_PMNS,                      KC_HASH, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_CIRC, KC_1,    KC_2,    KC_3,    TH_EQL,                       KC_PIPE, KC_AMPR, KC_LT,   KC_GT,   KC_BSLS,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             KC_0,    TH_PDOT,   KC_RALT, KC_RSFT, KC_RCTL,    KC_SCRL, MO(_FUN), _______   //trackball = scroll
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_NAV] = LAYOUT(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      M_MEH1,  M_CA1,   M_CA2,   M_MEH2,  XXXXXXX,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSCR,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      KC_CAPS, M_CS1,   M_CS2,   DRG_TOG, DRGSCRL,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      M_4,     M_AS1,   M_AS2,   M_5,     SNIPING,                      KC_NUM,  KC_MENU, XXXXXXX, KC_BRK, XXXXXXX,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
               M_A1,    M_A2,    _______, SPC_SET, CLEARKB,    KC_LCTL, KC_LSFT, DRG_TOG   //trackball = mouse
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_FUN] = LAYOUT(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      XXXXXXX, KC_F7,   KC_F8,   KC_F9,   XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, KC_F4,   KC_F5,   KC_F6,   XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             KC_F10,   KC_F11,   KC_F12,  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX   //trackball = scroll
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

  [_SET] = LAYOUT(
  // ╭────────────────────────────────────────────╮                   ╭─────────────────────────────────────────────╮
      XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, KC_VOLU, KC_BRIU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├────────────────────────────────────────────┤                   ├─────────────────────────────────────────────┤
      XXXXXXX, KC_VOLD, KC_BRID, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────────────╮  ╭─────────────────────────────────────────────────────╯
             XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX   //trackball = scroll
  //        ╰─────────────────╯ ╰──────────────────────────╯  ╰──────────────────────────╯
  ),

};

/*********CUSTOM KEY BEHAVIOURS********/
//tap-hold configurations:
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEL_NAV:   return true;
        case BSP_NUM:   return true;
        case MO(_FUN):  return true;
        case SPC_SET:   return true;
        default:        return false; // disable permissive hold for TH keys
    }
};
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEL_NAV:   return TAPPING_TERM;
        case BSP_NUM:   return TAPPING_TERM;
        case MO(_FUN):  return TAPPING_TERM;
        case SPC_SET:   return TAPPING_TERM;
        default:        return 225; // set tapping term for TH keys
    }
};
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEL_NAV:   return false;
        case BSP_NUM:   return false;
        case MO(_FUN):  return false;
        case SPC_SET:   return false;
        default:        return true; // enable tapping force hold for TH keys
    }
};

//taphold keycodes (TH_):
typedef struct _taphold_keycode_t { //define taphold functions
    uint16_t keycode_record;  //key input
    uint16_t keycode_hold; //key output on hold
} taphold_keycode_t;

#define KEY_MAP_SIZE 6 //amount of keys in taphold map (30 on _DEF, 30 on _NUM)

taphold_keycode_t keymap[KEY_MAP_SIZE] = { // taphold mapping, format: {keycode_record, keycode_tap, keycode_hold}
    {TH_A,    KC_AT},
    {TH_QUOT, KC_GRV},
    {TH_EQL,  KC_TILD},
    {TH_PDOT, KC_COMM},
    {TH_5,    KC_DLR},
    {TH_8,    KC_NO},
};

int get_index_taphold(uint16_t keycode_record) { //find corresponding item in taphold map for pressed key
    for (int i = 0; i < KEY_MAP_SIZE; i++) {
        if (keymap[i].keycode_record == keycode_record) return i;
    }
    return -1; //return -1 if pressed key is not in taphold map
};

//macros: taphold, custom combos, custom shift behaviours:
bool process_record_user(uint16_t keycode, keyrecord_t* record) { //execute autswap behaviours
    int index = get_index_taphold(keycode);// check if keycode is in taphold map
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift state for custom shift behaviours
    static bool language_EN = true; // track windows keyboard language, default is English (US), may require manual correction on startup
    switch(keycode) {
        case CLEARKB:
            if (record->event.pressed) {
                clear_keyboard(); //clears all keys and modifiers that might be stuck
                layer_clear(); //clears all layers that might be stuck
            } return false;

        //custom shift behaviours:
        case KC_COMM:
            if (record->event.pressed && mod_shift) {
                unregister_mods(mod_shift);
                tap_code16(KC_SCLN);
                register_mods(mod_shift);
                return false;
            } return true;
        case KC_DOT:
            if (record->event.pressed && mod_shift) {
                unregister_mods(mod_shift);
                tap_code16(S(KC_SCLN));
                register_mods(mod_shift);
                return false;
            } return true;
        case KC_EXLM:
            if (record->event.pressed && mod_shift) {
                unregister_mods(mod_shift);
                tap_code16(S(KC_SLSH));
                register_mods(mod_shift);
                return false;
            } return true;
        case DEL_NAV:
            if (record->event.pressed && record->tap.count && mod_shift){
                unregister_mods(mod_shift);
                tap_code16(KC_BSPC);
                register_mods(mod_shift);
                return false;
            } return true;
        case BSP_NUM:
            if (record->event.pressed && record->tap.count && mod_shift) { //when tapped
                unregister_mods(mod_shift);
                tap_code16(KC_BSPC);
                register_mods(mod_shift);
                return false;
            } else if (record->event.pressed) {
                charybdis_set_pointer_dragscroll_enabled(true);
            } else {
                charybdis_set_pointer_dragscroll_enabled(false);
            } return true;

        //Language tracker
        case LANG:
            if (record->event.pressed) {
                language_EN = !language_EN;
            } return true;
        case LANGC:
            if (record->event.pressed) {
                language_EN = !language_EN;
            } return false;

        //Mouse buttons
        case M_A1:
            if (record->event.pressed) {
                register_mods(MOD_MASK_ALT);
                register_code16(KC_BTN1);
            } else {
                unregister_code16(KC_BTN1);
                wait_ms(10);
                unregister_mods(MOD_MASK_ALT);
            } return false;
        case M_A2:
            if (record->event.pressed) {
                register_mods(MOD_MASK_ALT);
                register_code16(KC_BTN2);
            } else {
                unregister_code16(KC_BTN2);
                wait_ms(10);
                unregister_mods(MOD_MASK_ALT);
            } return false;
        case M_AS1:
            if (record->event.pressed) {
                register_mods(MOD_MASK_SA);
                register_code16(KC_BTN1);
            } else {
                unregister_code16(KC_BTN1);
                wait_ms(10);
                unregister_mods(MOD_MASK_SA);
            } return false;
        case M_AS2:
            if (record->event.pressed) {
                register_mods(MOD_MASK_SA);
                register_code16(KC_BTN2);
            } else {
                unregister_code16(KC_BTN2);
                wait_ms(10);
                unregister_mods(MOD_MASK_SA);
            } return false;
        case M_CS1:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CS);
                register_code16(KC_BTN1);
            } else {
                unregister_code16(KC_BTN1);
                wait_ms(10);
                unregister_mods(MOD_MASK_CS);
            } return false;
        case M_CS2:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CS);
                register_code16(KC_BTN2);
            } else {
                unregister_code16(KC_BTN2);
                wait_ms(10);
                unregister_mods(MOD_MASK_CS);
            } return false;
        case M_CA1:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CA);
                register_code16(KC_BTN1);
            } else {
                unregister_code16(KC_BTN1);
                wait_ms(10);
                unregister_mods(MOD_MASK_CA);
            } return false;
        case M_CA2:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CA);
                register_code16(KC_BTN2);
            } else {
                unregister_code16(KC_BTN2);
                wait_ms(10);
                unregister_mods(MOD_MASK_CA);
            } return false;
        case M_MEH1:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CSA);
                register_code16(KC_BTN1);
            } else {
                unregister_code16(KC_BTN1);
                wait_ms(10);
                unregister_mods(MOD_MASK_CSA);
            } return false;
        case M_MEH2:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CSA);
                register_code16(KC_BTN2);
            } else {
                unregister_code16(KC_BTN2);
                wait_ms(10);
                unregister_mods(MOD_MASK_CSA);
            } return false;

        //taphold keys:
        default:
            if (index != -1) { //if key is in taphold map, then custom tap/hold behaviour below:
                if (record->event.pressed && record->tap.count == 0) { //hold action
                    if (keymap[index].keycode_hold == KC_NO) { //work around for € sign.
                        if (!language_EN) {
                            tap_code16(RALT(KC_5)); //€ sign on dutch layout
                        } else {
                            tap_code16(C(A(KC_E))); //€ sign on english(us) layout
                        }
                    } else {
                    tap_code16(keymap[index].keycode_hold);
                    }
                    return false;
                } return true; //if tap, return true

                return false; //if key is in taphold map, ignore original key behaviour
            }//end of if(index != -1)

    }//end of switch(keycode)
    return true; //if key is not in taphold map, return original key behaviour
};

