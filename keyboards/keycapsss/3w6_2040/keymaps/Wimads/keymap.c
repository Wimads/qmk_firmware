/*TO DO
 * implement dragscroll trigger via numlock
 * get into lighting layers to fix capsword led animation
 */

#include QMK_KEYBOARD_H

/**
 * \brief HLCC - Host LED Communication Channel
 *
 * HLCC enables communication between separate QMK devices
 * through the host's lock status LED's
 */
/*
#define HLCC_TIMEOUT 200
#define HLCCKEY KC_CAPS             // set which lock key acts as HLCC channel
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
    const bool     hlcc_led_state     = led_state.caps_lock;                    // set which LED to use for HLCC channel
    static bool    hlcc_led_tminus1   = 0;                                      // hlcc LED status at t - 1 (previous state)
    const bool     hlcc_led_changed   = abs(hlcc_led_state - hlcc_led_tminus1); // LED status changed? Results in 0 if status == tminus1, or in 1 if status != tminus 1.
    static uint8_t hlcc_blink_counter = 0;                                      // counting blinks of leds

    if (!hlcc_comms_mode) {
        // listen to comms channel:
        if (hlcc_timed >= HLCC_TIMEOUT) {
            // After timeout, store tally to comms_data and reset counter:
            hlcc_comms_data    = (int)hlcc_blink_counter / 2; // one blink = 2 counts
            hlcc_blink_counter = 0;

            // Execution of message here::

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
    const bool  mod_ctrl_state   = get_mods() & MOD_MASK_CTRL;
    static bool mod_ctrl_tminus1 = 0;
    bool        mod_ctrl_changed = abs(mod_ctrl_state - mod_ctrl_tminus1);
    if (mod_ctrl_changed) {
        // signal change in CTRL state over HLCC channel:
        hlcc_comms_mode = 1; // set HLCC to write mode
        hlcc_comms_data = 2; // blink 2 times over HLCC channel
    }
    mod_ctrl_tminus1 = mod_ctrl_state; // store ctrl state at t - 1 for next cycle

    // monitor hlcc comms mode:
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
        printf("3w6: hlcc_comms_data: %i \n", hlcc_comms_data);
        hlcc_comms_mode = 0; // return to listening mode
    }
}*/

////DEFINITIONS////
// Layers:
enum layers {
    _QTY  = 0, // QwerTY
    _QTYe = 1, // Qwerty for monkytype emulation
    _CAD  = 2, // CAD mode
    _NUM  = 3, // NUMbers and symbols
    _RNUM = 4, // NUMpad Right hand only
    _MISC = 9, // MISCelaneous;
};

/// Custom keycodes..
// Stack-mods: tapping mods consecutively stacks them.
static uint32_t stack_mod_timer;
#define STACK_MOD_TIMEOUT 350   // time-out for stack_mods
#define SM_LCTL LCTL_T(KC_LCTL) // Defined as mod-tap key for further processing in process_record_user
#define SM_LSFT LSFT_T(KC_LSFT)
#define SM_LALT LALT_T(KC_LALT)
#define SM_LGUI LGUI_T(KC_LGUI)
#define SM_RCTL RCTL_T(KC_RCTL)
#define SM_RSFT RSFT_T(KC_RSFT)
#define SM_RALT RALT_T(KC_RALT)
#define SM_RGUI RGUI_T(KC_RGUI)
// Tap-hold keys:
#define FFF_NUM LT(_NUM, KC_F)
#define JJJ_NUM LT(_NUM, KC_J)
#define TTT_NUM LT(_NUM, KC_T)
#define DDD_NUM LT(_NUM, KC_D)
#define SPCLSFT LSFT_T(KC_SPC)
#define SPCRSFT RSFT_T(KC_SPC)
#define UNDLSFT LSFT_T(KC_UNDS) // further defined in macro (because shifted keycodes in _T() is not possible)
#define EQLRALT RALT_T(KC_EQL)
// Diacritic keys:   //Type diacritics by holding DC_key followed by dead key; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define DC_A LT(11, KC_A)
#define DC_E LT(11, KC_E)
#define DC_U LT(11, KC_U)
#define DC_I LT(11, KC_I)
#define DC_O LT(11, KC_O)
#define DC_N LT(11, KC_N)
// Other:
#define DOTCOMM LT(10, KC_DOT) // KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
// Macros:
enum custom_keycodes {
    CLEARKB = SAFE_RANGE, // clears all keys and/or layers that might be stuck
    CADTOGG,              // toggle CAD mode
    RNUMTOG,              // toggle RNUM layer
    QTYTOGG,              // toggle QTYe layer
};
// Combos:
#include "gboards/g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def
///..custom keycodes

/// keymaps..
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
  //Qwerty:
  [_QTY] = LAYOUT_split_3x5_3(
	  KC_Q,    KC_W,    DC_E,    KC_R,    KC_T,             KC_Y,    DC_U,    DC_I,    DC_O,   KC_P,
	  DC_A,    KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    KC_QUOT,
	  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             DC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
            			SM_LALT, SM_LSFT, SM_LCTL,          SM_RALT, SPCRSFT, MO(_MISC)
  ),
  //Qwerty e: (unmodified qwerty layout for emulation in for example monkeytype)
  [_QTYe] = LAYOUT_split_3x5_3(
	  KC_V,    KC_L,    KC_M,    KC_G,    KC_QUOT,          KC_Q,    KC_K,    DC_U,    DC_O,    KC_Y,
      KC_S,    KC_R,    DC_N,    TTT_NUM, KC_Z,             KC_X,    DDD_NUM, DC_E,    DC_A,    DC_I,
	  KC_W,    KC_H,    KC_P,    KC_C,    KC_B,             KC_F,    KC_J,    KC_COMM, KC_DOT,  KC_EXLM,
			          	SM_LALT, SM_LSFT, SM_LCTL,          SM_RALT, SPCRSFT, MO(_MISC)
  ),
  //CAD mode: (a mostly transparent layer, but will activate extra combos)
  [_CAD] = LAYOUT_split_3x5_3(
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
						_______, SPCLSFT, _______,          _______, _______, _______
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_split_3x5_3(
	  KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, KC_TILD,          KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
	  KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
	  KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
						_______, UNDLSFT, _______,          EQLRALT, KC_0,    DOTCOMM
  ),
  [_RNUM] = LAYOUT_split_3x5_3(
	  _______, _______, _______, _______, _______,          KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
	  _______, _______, _______, _______, _______,          KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
	  _______, _______, _______, _______, _______,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
						_______, _______, _______,          EQLRALT, KC_0,    DOTCOMM
  ),
  //OTHER:
  [_MISC] = LAYOUT_split_3x5_3(
	  QK_BOOT, XXXXXXX, EE_CLR,  XXXXXXX, XXXXXXX,          KC_PGUP, KC_BRIU, KC_INS,  KC_VOLU, KC_PSCR,
	  XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX,          KC_PGDN, KC_BRID, XXXXXXX, KC_VOLD, XXXXXXX,
	  XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BRK,           KC_NUM,  KC_MENU, XXXXXXX, KC_MUTE, XXXXXXX,
						XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
    // clang-format on
};
///..keymaps

////LED INDICATORS////
/* LED numbering:
 * Left  hand LED = 0;
 * Right hand LED = 1;
 */
// rgb lighting variables:
int rgb_hue   = 40;
int rgb_sat   = 255;
int rgb_val   = 255;
int rgb_mode  = 1;   // initial values
int rgb_hue_q = 32;  // qwerty (yellow)
int rgb_hue_c = 60;  // CAD (lime)
int rgb_hue_n = 12;  // NUM (red/orange)
int rgb_hue_m = 185; // MISC (purple)
int rgb_hue_e = 165; // emulation (blue)

// animation speed:
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {2, 2, 2, 2};

// Set initial LED lighting state:
void keyboard_post_init_kb(void) {
    // initiate rgb underglow (default mode as per ASW_on true):
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(rgb_mode);                    // set light effect for both LEDs
    rgblight_sethsv_noeeprom(rgb_hue, rgb_sat, rgb_val); // set HSV value for both LEDs*/
};

// Capsword indicator:
void caps_word_set_user(bool active) {
    if (active) {
        rgb_mode = 2;
        rgblight_mode_noeeprom(rgb_mode);
        if (IS_LAYER_ON(_RNUM)) {
            rgblight_sethsv_noeeprom(rgb_hue_n, rgb_sat, rgb_val); // override both LEDs, since can't override one when mode = 2;
        } else {
            rgblight_sethsv_noeeprom(rgb_hue, rgb_sat, rgb_val);
        }
    } else {
        rgb_mode = 1;
        rgblight_mode_noeeprom(rgb_mode);
        rgblight_sethsv_noeeprom(rgb_hue, rgb_sat, rgb_val);
        if (IS_LAYER_ON(_RNUM)) {
            rgblight_sethsv_noeeprom(rgb_hue_n, rgb_sat, rgb_val);
            rgblight_sethsv_at(rgb_hue, rgb_sat, rgb_val, 0);
        }
    }
};

// Layer indicators:
layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, _RNUM) && is_caps_word_on()) {
        rgblight_mode_noeeprom(rgb_mode);
        rgblight_sethsv_noeeprom(rgb_hue_n, rgb_sat, rgb_val); // override both LEDs, since can't override one when mode = 2;
    } else if (IS_LAYER_ON_STATE(state, _RNUM)) {
        if (IS_LAYER_ON_STATE(state, _MISC)) {
            rgb_hue = rgb_hue_m;
        } else if (IS_LAYER_ON_STATE(state, _NUM)) {
            rgb_hue = rgb_hue_n;
        } else if (IS_LAYER_ON_STATE(state, _CAD)) {
            rgb_hue = rgb_hue_c;
        } else if (IS_LAYER_ON_STATE(state, _QTYe)) {
            rgb_hue = rgb_hue_e;
        } else {
            rgb_hue = rgb_hue_q;
        }
        rgblight_mode_noeeprom(rgb_mode);
        rgblight_sethsv_noeeprom(rgb_hue_n, rgb_sat, rgb_val);
        rgblight_sethsv_at(rgb_hue, rgb_sat, rgb_val, 0);
    } else {
        if (IS_LAYER_ON_STATE(state, _MISC)) {
            rgb_hue = rgb_hue_m;
        } else if (IS_LAYER_ON_STATE(state, _NUM)) {
            rgb_hue = rgb_hue_n;
        } else if (IS_LAYER_ON_STATE(state, _CAD)) {
            rgb_hue = rgb_hue_c;
        } else if (IS_LAYER_ON_STATE(state, _QTYe)) {
            rgb_hue = rgb_hue_e;
        } else {
            rgb_hue = rgb_hue_q;
        }
        rgblight_mode_noeeprom(rgb_mode);
        rgblight_sethsv_noeeprom(rgb_hue, rgb_sat, rgb_val);
    }
    return state;
};

////CUSTOM KEY BEHAVIOURS////
// Turn on/off CAD combos:
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case QTY_START ... QTY_FINAL:
            if (IS_LAYER_ON(_QTYe)) {
                return false;
            }
            return true;
        case QTYe_START ... QTYe_FINAL:
            if (!IS_LAYER_ON(_QTYe)) {
                return false;
            }
            return true;
        case CAD_START ... CAD_FINAL:
            if (!IS_LAYER_ON(_CAD)) {
                return false;
            }
            return true;
    }
    return true;
};

// Tap-hold per key config:
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
};

/// multifunc keycodes..
typedef struct _multifunc_keycode_t { // define multifunc keycode functions
    uint16_t kc_record;               // unmodified keycode
    uint16_t kc_shifted;              // alternate keycode on shift
    uint16_t kc_deadkey;              // alternate keycode on diacritic key
} multifunc_keycode_t;
// clang-format off
#define MULTIFUNC_COUNT 12 // specify number of multifunc keycodes
multifunc_keycode_t multifunc_map[MULTIFUNC_COUNT] = {
    // _DEF layer left:
//  {kc_record, kc_shifted, kc_deadkey}, //00  r S d
    {KC_Z,      S(KC_Z),    S(KC_CIRC)}, //01  z Z ^
    {KC_X,      S(KC_X),    S(KC_QUOT)}, //02  x X "
    {KC_C,      S(KC_C),    KC_QUOT   }, //03  c C '
    {KC_V,      S(KC_V),    KC_GRV    }, //04  v V `
    {KC_B,      S(KC_B),    S(KC_GRV) }, //05  b B ~
    // _DEF layer right:
    {DC_N,      S(KC_N),    S(KC_GRV) }, //06  n N ~
    {KC_M,      S(KC_M),    KC_GRV    }, //07  m M `
    {KC_COMM,   KC_SCLN,    KC_QUOT   }, //08  , ; '
    {KC_DOT,    S(KC_SCLN), S(KC_QUOT)}, //09  . : "
    {KC_EXLM,   KC_QUES,    S(KC_CIRC)}, //10  ! ? ^
    // _NUM layer:
    {KC_SLSH,   KC_BSLS,    S(KC_CIRC)}, //11  / \ ^
    {KC_DLR,    RALT(KC_5), KC_NO     }, //12  $ €   // KC_NO deadkey would result in keypress getting dropped, but edge case, so acceptable.
};
// clang-format on
int get_multifunc_index(uint16_t kc_record) { // find corresponding item in multifunc map for pressed key
    for (int mfi = 0; mfi < MULTIFUNC_COUNT; mfi++) {
        if (multifunc_map[mfi].kc_record == kc_record) return mfi;
    }
    return -1; // return -1 if pressed key is not in multifunc map
};
///..multifunc keycodes

/// Macros..
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // VARIABLES:
    //  general
    const int   mutifunc_index = get_multifunc_index(keycode); // check if keycode is in multifunc map
    static bool dotcomm_state  = true;                         // state of dotcomm key; true = dot; false = comma;
    //  Diacritic keys
    static uint16_t dc_record    = KC_SPC; // store DC_ keycode to send after dead key (defined in multifunc keycodes)
    static uint16_t dc_mod_shift = 0;      // store shift state of dc_record
    static bool     dc_pending   = false;  // status of Diacritic key
    //  modifiers
    static bool     mod_held    = false;                       // track if any mod is being held down (not tapped) for stack-mods
    static uint16_t stack_mod_1 = 0;                           // first slot in mod-stack
    static uint16_t stack_mod_2 = 0;                           // second slot in mod-stack
    const uint16_t  mod_shift   = get_mods() & MOD_MASK_SHIFT; // track shift state for custom shift behaviours (defined in multifunc keycodes)
    static uint16_t mod_pressed = 0;
    switch /*mod_pressed*/ (keycode) {
        // track which mod is pressed, return 0 if not a mod:
        case KC_LCTL ... KC_RGUI: // clang-format off
        case SM_LCTL: case SM_LSFT: case SM_LALT: case SM_LGUI:
        case SM_RCTL: case SM_RSFT: case SM_RALT: case SM_RGUI: // clang-format on
            if (record->event.pressed) {
                // TAP || HOLD:
                mod_pressed = MOD_BIT(keycode);
            } else {
                // RELEASE:
                mod_pressed = 0;
            }
            break;
            // clang-format off
        case SPCLSFT: case SPCRSFT: case UNDLSFT: case EQLRALT: // clang-format on
            if (record->event.pressed && !record->tap.count) {
                // HOLD:
                mod_pressed = MOD_BIT(keycode);
            } else {
                // TAP || RELEASE
                mod_pressed = 0;
            }
            break;
        default:
            mod_pressed = 0;
            break;
    } //..switch mod_pressed

    // STACK_MODS:
    switch /* STACK_MODS */ (keycode) {
        /* Stack_mods:
         *  Allows to stack mods by tapping them (ie. tap ctl then hold sft results in ctl+sft).
         *  Stacking needs to happen within timeout, else it will restart stacking at 1.
         *  The modifiers in the stack are registered only when the last mod is held down.
         *  All mods in the stack will remain registered, until the held down mod is released. On release the stack is cleared.
         *  If no mod is held down, any non-mod keypress will clear the stack, not returning any mods.
         *  Up to 3 mods can be stacked (ie. tap 2, hold one). If a third mod is tapped, it will restart stacking at 1.
         */

        // on any modifier keypress:
        case KC_LCTL ... KC_RGUI: // clang-format off
        case SM_LCTL: case SM_LSFT: case SM_LALT: case SM_LGUI:
        case SM_RCTL: case SM_RSFT: case SM_RALT: case SM_RGUI:
        case SPCLSFT: case SPCRSFT: case UNDLSFT: case EQLRALT: // clang-format on
            if (record->event.pressed && record->tap.count) {
                // ON TAP, add mods to stack:
                mod_held = false; // set mod_held state
                if (timer_elapsed32(stack_mod_timer) >= STACK_MOD_TIMEOUT) {
                    // if timed out, clear mod stack
                    stack_mod_1 = 0;
                    stack_mod_2 = 0;
                }
                if (!stack_mod_1) {
                    // if 0 mods in stack:
                    //  mod-taps like SPCLSFT return 0 for mod_pressed when tapped, thus won't get stacked;
                    stack_mod_1 = mod_pressed;
                } else if (!stack_mod_2 && mod_pressed) {
                    // if 1 mod in stack && a mod is pressed:
                    if (stack_mod_1 == mod_pressed) {
                        // if stack_mod_1 is tapped again, clear stack
                        stack_mod_1 = 0;
                    } else {
                        stack_mod_2 = mod_pressed;
                        printf("MOD_STACK >>> mod_held: %i; stack_mod_1: %04x; stack_mod_2: %04x; mod_pressed: %04x; TAP: if(!stack_mod_2){if(stack_mode_1 != mod_pressed)}\n", mod_held, stack_mod_1, stack_mod_2, mod_pressed);
                    }
                } else if (stack_mod_2 == mod_pressed) {
                    // if mod 2 tapped a second time, clear entire stack
                    stack_mod_1 = 0;
                    stack_mod_2 = 0;
                    printf("MOD_STACK >>> mod_held: %i; stack_mod_1: %04x; stack_mod_2: %04x; mod_pressed: %04x; TAP: if(stack_mod_2 == mod_pressed)\n", mod_held, stack_mod_1, stack_mod_2, mod_pressed);
                } else {
                    // if a non-mod was pressed (ie mod-tap) ||
                    //  or if mod 1 was pressed a second time ||
                    //  or if a 3rd new mod was pressed,
                    // then restart stacking in slot 1:
                    stack_mod_1 = mod_pressed; // in case of mod-tap, mod_pressed == 0, which ie. clears the entire stack;
                    stack_mod_2 = 0;
                    printf("MOD_STACK >>> mod_held: %i; stack_mod_1: %04x; stack_mod_2: %04x; mod_pressed: %04x; TAP: else()\n", mod_held, stack_mod_1, stack_mod_2, mod_pressed);
                }
            } else if (record->event.pressed) {
                // ON HOLD, register stacked mods
                mod_held = true; // set mod_held state
                if (timer_elapsed32(stack_mod_timer) >= STACK_MOD_TIMEOUT) {
                    // if timed out, clear mod stack
                    stack_mod_1 = 0;
                    stack_mod_2 = 0;
                }
                if (stack_mod_1 == keycode || stack_mod_2 == keycode) {
                    // if held key == stacked key, clear stack;
                    stack_mod_1 = 0;
                    stack_mod_2 = 0;
                }
                if (stack_mod_1) register_mods(stack_mod_1);
                if (stack_mod_2) register_mods(stack_mod_2);
                // held mod will be returned in MACRO switch statement below
            } else {
                // ON RELEASE, unregister mods and clear stack:
                if (mod_held) {
                    // after hold, clear mod stack
                    mod_held = false; // reset mod_held state
                    if (stack_mod_1) unregister_mods(stack_mod_1);
                    if (stack_mod_2) unregister_mods(stack_mod_2);
                    stack_mod_1 = 0;
                    stack_mod_2 = 0;
                }                                 // else, after tap, ignore release
                stack_mod_timer = timer_read32(); // reset timer
            }
            break; // keycodes are not returned here, but in MACRO switch statement below
        // on non-modifier keypress:
        default:
            if (record->event.pressed && !mod_held) {
                // Clear stack on normal keypress if no mod was held
                stack_mod_1 = 0;
                stack_mod_2 = 0;
            }
            break;
    } //..switch(keycode) stack-mods

    // MACROS:
    switch /*MACROS*/ (keycode) {
        case CLEARKB: // clear keyboard
            if (record->event.pressed) {
                clear_keyboard(); // clears all keys and modifiers that might be stuck
                layer_clear();    // clears all layers that might be stuck
            }
            return false;

        // Mods:
        case SM_LALT:
            if (record->event.pressed && record->tap.count) {
                // ON TAP:
                set_oneshot_mods(MOD_BIT(KC_LALT));
                // slowed down tap (for vectorworks):
                register_mods(MOD_BIT(KC_LALT));
                wait_ms(100);
                unregister_mods(MOD_BIT(KC_LALT));
                return false;
            }
            return true;
        case UNDLSFT:
            if (record->event.pressed && record->tap.count) {
                tap_code16(S(KC_UNDS));
                return false;
            }
            return true;

        // layer toggles:
        case CADTOGG: // toggle CAD mode
            if (record->event.pressed) {
                layer_off(_RNUM);   // always turn off _RNUM when toggling CAD mode on/off
                layer_invert(_CAD); // toggle CAD mode on/off
            }
            return false;
        case RNUMTOG: // toggle numpad on/off (only right hand side)
            if (record->event.pressed) {
                layer_invert(_RNUM);
            }
            return false;
        case QTYTOGG: // toggle emulation mode (unmodified qwerty layout)
            if (record->event.pressed) {
                layer_invert(_QTYe);
            }
            return false;

        // special keycodes:
        case DOTCOMM:
            if (record->event.pressed && record->tap.count == 2) { // invert DOTCOMM state on double tap
                // on double tap, invert state & correct character from previous tap
                dotcomm_state = !dotcomm_state;
                tap_code16(KC_BSPC);
                if (dotcomm_state) {
                    tap_code16(KC_DOT);
                } else {
                    tap_code16(KC_COMM);
                }
            } else if (record->event.pressed && dotcomm_state) { // when state is true
                if (mod_shift) {                                 // send comm when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_COMM);
                    register_mods(mod_shift);
                } else { // send dot by default
                    tap_code16(KC_DOT);
                }
            } else if (record->event.pressed) { // when state is false
                if (mod_shift) {                // send dot when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_DOT);
                    register_mods(mod_shift);
                } else { // send comm by default
                    tap_code16(KC_COMM);
                }
            }
            return false;
            // clang-format off

        /* Diacritic keys:
         * Diacritics (ãàáäâ) can be typed by holding a DC_key, and then tapping a dead key (ie ' " ` ~ ^)
         * If no DC_key was held, dead keys are automatically followed by a space, so they no longer behave as "dead".
         * This allows for example to type quotes without the extra space, so the typing flow doesn't get interrupted;
         *  but still allows to type diacritics easily
         */
        case DC_A: case DC_E: case DC_U:
        case DC_I: case DC_O: case DC_N: // clang-format on
            if (record->event.pressed && record->tap.count) {
                // ON TAP:
                if (mutifunc_index == -1 || !dc_pending) { // check for multifunc keycode and DC_ state to avoid conflict with multifunc keycodes
                    return true;
                } // else return keycode as per default case below
            } else if (record->event.pressed) {
                // ON HOLD:
                dc_pending = true;    // track status of DC_-key
                dc_record  = keycode; // store record of DC_-key
                if (is_caps_word_on()) {
                    dc_mod_shift = MOD_MASK_SHIFT; // store shift state of DC_-key
                } else {
                    dc_mod_shift = mod_shift; // store shift state of DC_-key
                }
                return false; // don't return keycode
            } else {
                // ON RELEASE:
                if (dc_pending) {
                    // Diacritic key failure mode: no key was pressed while DC_ was held
                    tap_code16(keycode);
                }
                dc_pending = false;
                dc_record  = KC_SPC; // if no DC_-key was pressed, a space is sent automatically after a dead key.
                return true;
            }
        case KC_QUOT:
        case KC_GRV:
        case KC_TILD:
        case KC_CIRC:
            if (record->event.pressed && mutifunc_index == -1) { // check for multifunc keycode to avoid conflict
                tap_code16(keycode);                             // tap dead key
                unregister_mods(mod_shift);                      // unregister shift (if it was pressed)
                register_mods(dc_mod_shift);                     // register stored DC_key shift state
                tap_code16(dc_record);                           // tap diacritic key (KC_SPC if no DC_ keycode was held)
                unregister_mods(dc_mod_shift);                   // unregister stored DC_key shift state
                register_mods(mod_shift);                        // re-register shift (if it was pressed)
                dc_pending = false;                              // reset DC_key state
                return false;
            } // else process keycode as per default case below;

        default:
            if (mutifunc_index != -1) {
                // if multifunc key was pressed:
                if (record->event.pressed && dc_pending) {
                    // if diacritic key is active:
                    unregister_mods(mod_shift);                           // unregister shift (if it was pressed)
                    tap_code16(multifunc_map[mutifunc_index].kc_deadkey); // tap dead key
                    register_mods(dc_mod_shift);                          // register stored DC_key shift state
                    tap_code16(dc_record);                                // tap diacritic key (KC_SPC if no DC_ keycode w
                    unregister_mods(dc_mod_shift);                        // unregister stored DC_key shift state
                    register_mods(mod_shift);                             // re-register shift (if it was pressed)
                    dc_pending = false;                                   // reset DC_key state
                    return false;
                } else if (record->event.pressed && mod_shift) {
                    // if shift is pressed:
                    unregister_mods(mod_shift);                           // unregister shift
                    tap_code16(multifunc_map[mutifunc_index].kc_shifted); // tap custom shift key
                    register_mods(mod_shift);                             // re-register shift
                    return false;                                         // ignore default key behaviour
                }                                                         // else:
                return true;                                              // return default keycode

            } else {
                if (dc_pending) {
                    // Diacritic key failure mode: non-deadkey was pressed while DC_ was held
                    tap_code16(dc_record);
                    dc_pending = false;
                    dc_record  = KC_SPC;
                }
                return true;
            }

    } //..switch macros

    return true; // if not covered by any of the cases above, return true;
};               //..process_record_user
