/*TO DO
 * Fix Oneshot-ish-mods: don't cancel oneshot when pressing multiple hot keys (ctrl+shift+a ..+c)
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
// oneshot-ish-mods (mods act as oneshot only for stacking mods):
#define OSMLCTL OSM(MOD_LCTL)
#define OSMLSFT OSM(MOD_LSFT)
#define OSMLALT OSM(MOD_LALT)
#define OSMLGUI OSM(MOD_LGUI)
#define OSMRCTL OSM(MOD_RCTL)
#define OSMRSFT OSM(MOD_RSFT)
#define OSMRALT OSM(MOD_RALT)
#define OSMRGUI OSM(MOD_RGUI)
// Tap-hold keys:
#define FFF_NUM LT(_NUM, KC_F)
#define JJJ_NUM LT(_NUM, KC_J)
#define TTT_NUM LT(_NUM, KC_T)
#define DDD_NUM LT(_NUM, KC_D)
#define SPCLSFT LSFT_T(KC_SPC)
#define SPCRSFT RSFT_T(KC_SPC)
#define UNDLSFT LSFT_T(KC_UNDS) // further defined in macro (because shifted keycodes in _T() is not possible)
#define EQLRALT RALT_T(KC_EQL)
// Auto-Dead-Key:   //auto-send space after deadkey, unless ADK_ key was held; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define ADK_A LT(11, KC_A)
#define ADK_E LT(11, KC_E)
#define ADK_U LT(11, KC_U)
#define ADK_I LT(11, KC_I)
#define ADK_O LT(11, KC_O)
#define ADK_N LT(11, KC_N)
// Other:
#define DOTCOMM LT(10, KC_DOT) // KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
// Macros:
enum custom_keycodes {
    CLEARKB = SAFE_RANGE, // clears all keys and/or layers that might be stuck
    EE_BOOT,              // clear eeprom, then boot mode
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
	  KC_Q,    KC_W,    ADK_E,   KC_R,    KC_T,             KC_Y,    ADK_U,   ADK_I,   ADK_O,   KC_P,
	  ADK_A,   KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    KC_QUOT,
	  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             ADK_N,   KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
            			OSMLALT, OSMLSFT, OSMLCTL,          OSMRALT, SPCRSFT, MO(_MISC)
  ),
  //Qwerty e: (unmodified qwerty layout for emulation in for example monkeytype)
  [_QTYe] = LAYOUT_split_3x5_3(
	  KC_V,    KC_L,    KC_M,    KC_G,    KC_QUOT,          KC_Q,    KC_K,    ADK_U,   ADK_O,   KC_Y,
      KC_S,    KC_R,    ADK_N,   TTT_NUM, KC_Z,             KC_X,    DDD_NUM, ADK_E,   ADK_A,   ADK_I,
	  KC_W,    KC_H,    KC_P,    KC_C,    KC_B,             KC_F,    KC_J,    KC_COMM, KC_DOT,  KC_EXLM,
			          	OSMLALT, OSMLSFT, OSMLCTL,          OSMRALT, SPCRSFT, MO(_MISC)
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
    uint16_t kc_deadkey;              // alternate keycode on auto_dead_key
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
    {ADK_N,     S(KC_N),    S(KC_GRV) }, //06  n N ~
    {KC_M,      S(KC_M),    KC_GRV    }, //07  m M `
    {KC_COMM,   KC_SCLN,    KC_QUOT   }, //08  , ; '
    {KC_DOT,    S(KC_SCLN), S(KC_QUOT)}, //09  . : "
    {KC_EXLM,   KC_QUES,    S(KC_CIRC)}, //10  ! ? ^
    // _NUM layer:
    {KC_SLSH,   KC_BSLS,    S(KC_CIRC)}, //11  / \ ^
    {KC_DLR,    RALT(KC_5), KC_NO     }, //12  $ €
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
    const int mutifunc_index = get_multifunc_index(keycode); // check if keycode is in multifunc map
    //  modifiers
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; // track shift state for custom shift behaviours (defined in multifunc keycodes)
    static bool    mod_held  = false;                       // check if any mod is being held down for oneshot-ish-mods
    //  dotcomm key
    static bool dotcomm_state = true; // true = dot; false = comma;
    //  Auto dead keys
    static uint16_t adk_record    = KC_SPC; // keycode to send after dead key (defined in multifunc keycodes)
    static uint16_t adk_mod_shift = 0;      // track shift state for auto_dead_key
    //  layer tap
    static bool hold_active = false; // active status of layer tap keys

    // ONESHOT-ISH-MODS:
    switch /* !! PUT NO MACROS IN THIS SWITCH !! */ (keycode) {
        /* Oneshot-ish-mods:
         *  Function as oneshot mods when followed by another mod
         *  Function as regular mods when followed by non-modifier (for example an alpha key)
         *  Effectively allows to stack mods by consecutively tapping them, without messing with regular mod behaviour for everything else.
         */
        // on modifier keypress:
        case KC_LCTL ... KC_RGUI: // clang-format off
        case OSMLCTL: case OSMLSFT: case OSMLALT: case OSMLGUI:
        case OSMRCTL: case OSMRSFT: case OSMRALT: case OSMRGUI:
        case SPCLSFT: case SPCRSFT: case UNDLSFT: case EQLRALT: // clang-format on
            if (record->event.pressed && !record->tap.count) {
                // ON HOLD:
                mod_held = true; // track modifier status
            } else {
                // ON TAP | RELEASE:
                mod_held = false; // track modifier status
            }
            break;

        // on non-modifier keypress:
        default:
            if (record->event.pressed && !mod_held) {
                // if non-mod is pressed, and no mods are being held:
                //  cancel one-shot behavior
                clear_oneshot_mods();
            } // else, don't cancel one-shot behavior
            break;

    } //..switch(keycode) oneshot-ish-mods

    // HOLD-FAIL-RELEASE:
    switch /* !! PUT NO MACROS IN THIS SWITCH !! */ (keycode) {
            // clang-format off
        /* On HOLD-FAIL-RELEASE execute TAP instead. (applies to tap-hold keys only)
         * Example:
         *  HOLD down LT(layer,tapcode) to activate layer
         *  FAIL to press any key on layer
         *  RELEASE the LT key, now tapcode is executed instead. (usually, no keycode would be executed at all)
         */

        // on listed TAP-HOLD keys:
        case SPCLSFT: case SPCRSFT: case UNDLSFT:
        case ADK_A:   case ADK_E:   case ADK_U:
        case ADK_I:   case ADK_O:   case ADK_N: // clang-format on
            if (record->event.pressed && !record->tap.count) {
                // ON HOLD:
                hold_active = true;
            } else if (record->event.pressed) {
                // ON TAP:
                if (hold_active) { // condition necessary to allow nested HOLD-FAIL-RELEASE sequences
                    hold_active = false;
                }
            } else {
                // ON RELEASE:
                if (hold_active) {
                    tap_code16(keycode);
                    hold_active = false;
                }
            }
            break;
        // on NON-TAP-HOLD keys:
        default:
            if (record->event.pressed && hold_active) {
                hold_active = false;
            }
            break;
    } // ..switch(keycode) lt keys

    // MACROS:
    switch (keycode) {
        case CLEARKB: // clear keyboard
            if (record->event.pressed) {
                clear_keyboard(); // clears all keys and modifiers that might be stuck
                layer_clear();    // clears all layers that might be stuck
            }
            return false;
        case EE_BOOT: // clear eeprom and boot
            if (record->event.pressed) {
                eeconfig_init();  // clear eeprom
                wait_ms(10);      // wait 10 ms
                reset_keyboard(); // enter bootmode
            }
            return false;

        // Mods:
        case OSMLALT:
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
                dotcomm_state = !dotcomm_state;                    // invert state
                tap_code16(KC_BSPC);                               // remove character output from first tap
            } else if (record->event.pressed && dotcomm_state) {   // when state is true
                if (mod_shift) {                                   // send comm when shifted
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

        // Auto-Dead-Keys:
        //  requires "English(NL)" or "Nederlands" language setting + "US International" keyboard setting in Windows.
        case ADK_A: case ADK_E: case ADK_U:
        case ADK_I: case ADK_O: case ADK_N: // clang-format on
            if (record->event.pressed && record->tap.count) {
                // ON TAP:
                if (mutifunc_index == -1 || adk_record == KC_SPC) { // check for multifunc keycode and adk state to avoid conflict with multifunc keycodes
                    return true;
                }
            } else if (record->event.pressed) {
                // ON HOLD:
                // adk_active = true;    // update auto_dead_key active status
                adk_record = keycode; // store keycode in auto_dead_key record
                if (is_caps_word_on()) {
                    adk_mod_shift = MOD_MASK_SHIFT; // store shift state of auto_dead_key
                } else {
                    adk_mod_shift = mod_shift; // store shift state of auto_dead_key
                }
                return false; // don't return keycode
            } else {
                // ON RELEASE:
                /*if (adk_active) {
                    // if adk still active on key release, that means adk-macro wasn't executed
                    // in which case execute TAP action instead:
                    tap_code16(keycode); // TAP action
                    adk_active = false;  // update auto_dead_key active status
                }*/
                adk_record = KC_SPC; // reset auto_dead_key record
                return true;
            }
        case KC_QUOT:
        case KC_GRV:
        case KC_TILD:
        case KC_CIRC:
            if (record->event.pressed && mutifunc_index == -1) { // check for multifunc keycode to avoid conflict
                tap_code16(keycode);                             // tap dead key
                unregister_mods(mod_shift);                      // unregister shift (if it was pressed)
                register_mods(adk_mod_shift);                    // register auto_dead_key shift state
                tap_code16(adk_record);                          // tap auto_dead_key (KC_SPC if no ADK_ keycode was held)
                unregister_mods(adk_mod_shift);                  // unregister auto_dead_key shift state
                register_mods(mod_shift);                        // re-register shift (if it was pressed)
                // adk_active = false;                              // update auto_dead_key active status
                hold_active = false;
                return false; // ignore default key behavior
            }

        default:
            if (mutifunc_index != -1) {
                // if multifunc key was pressed:
                if (record->event.pressed && adk_record != KC_SPC) {
                    // if auto_dead_key is active:
                    unregister_mods(mod_shift);                           // unregister shift (if it was pressed)
                    tap_code16(multifunc_map[mutifunc_index].kc_deadkey); // tap dead key
                    register_mods(adk_mod_shift);                         // register auto_dead_keyb shift state
                    tap_code16(adk_record);                               // tap auto_dead_key (KC_SPC if no ADK_ keycode w
                    unregister_mods(adk_mod_shift);                       // unregister auto_dead_key shift state
                    register_mods(mod_shift);                             // re-register shift (if it was pressed)
                    // adk_active = false;                                   // update auto_dead_key active status
                    hold_active = false;
                    return false; // ignore default key behaviour
                } else if (record->event.pressed && mod_shift) {
                    // if shift is pressed:
                    unregister_mods(mod_shift);                           // unregister shift
                    tap_code16(multifunc_map[mutifunc_index].kc_shifted); // tap custom shift key
                    register_mods(mod_shift);                             // re-register shift
                    return false;                                         // ignore default key behaviour
                }                                                         // else:
                return true;                                              // return default keycode

            } //..if(mutifunc_index != -1)

    } //..switch(keycode) macros

    return true; // if key is not in multifunc map or other macro, return normal key behaviour
};
///..Macros
