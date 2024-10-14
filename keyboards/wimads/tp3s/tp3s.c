/**
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include "tp3s.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#    ifndef TP3S_MINIMUM_DEFAULT_DPI
#        define TP3S_MINIMUM_DEFAULT_DPI 200
#    endif // TP3S_MINIMUM_DEFAULT_DPI

#    ifndef TP3S_DEFAULT_DPI_CONFIG_STEP
#        define TP3S_DEFAULT_DPI_CONFIG_STEP 200
#    endif // TP3S_DEFAULT_DPI_CONFIG_STEP

#    ifndef TP3S_MINIMUM_SNIPING_DPI
#        define TP3S_MINIMUM_SNIPING_DPI 100
#    endif // TP3S_MINIMUM_SNIPING_DPI

#    ifndef TP3S_SNIPING_DPI_CONFIG_STEP
#        define TP3S_SNIPING_DPI_CONFIG_STEP 100
#    endif // TP3S_SNIPING_DPI_CONFIG_STEP

// divisor to slow down scroll
#    ifndef TP3S_SCROLL_DIV
#        define TP3S_SCROLL_DIV 6.0
#    endif // TP3S_SCROLL_DIV

#    define TP3S_MOUSE_TIMEOUT 200

typedef union {
    uint8_t raw;
    struct {
        uint16_t pointer_default_dpi : 10; // 16 steps available.
        uint16_t pointer_sniping_dpi : 1;  // 4 steps available.
        bool     is_sniping_enabled : 1;
    } __attribute__((packed));
} tp3s_config_t;

static tp3s_config_t g_tp3s_config = {0};

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_sniping_enabled` are purposefully
 * ignored since we do not want to persist this state to memory.  In practice,
 * this state is always written to maximize write-performances.  Therefore, we
 * explicitly set them to `false` in this function.
 */
static void read_tp3s_config_from_eeprom(tp3s_config_t* config) {
    config->raw                = eeconfig_read_kb() & 0xff;
    config->is_sniping_enabled = false;
}

/**
 * \brief Save the value of `config` to eeprom.
 *
 * Note that all values are written verbatim, including whether
 * and/or sniper mode are enabled.  `read_tp3s_config_from_eeprom(…)`
 * resets these 2 values to `false` since it does not make sense to persist
 * these across reboots of the board.
 */
static void write_tp3s_config_to_eeprom(tp3s_config_t* config) {
    eeconfig_update_kb(config->raw);
}

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_default_dpi(tp3s_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * TP3S_DEFAULT_DPI_CONFIG_STEP + TP3S_MINIMUM_DEFAULT_DPI;
}

/** \brief Return the current value of the pointer's sniper-mode DPI. */
static uint16_t get_pointer_sniping_dpi(tp3s_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * TP3S_SNIPING_DPI_CONFIG_STEP + TP3S_MINIMUM_SNIPING_DPI;
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(tp3s_config_t* config) {
    if (config->is_sniping_enabled) {
        pointing_device_set_cpi(get_pointer_sniping_dpi(config));
    } else {
        pointing_device_set_cpi(get_pointer_default_dpi(config));
    }
}

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to tp3s_DEFAULT_DPI_CONFIG_STEP.
 */
static void step_pointer_default_dpi(tp3s_config_t* config, bool forward) {
    config->pointer_default_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to TP3S_SNIPING_DPI_CONFIG_STEP.
 */
static void step_pointer_sniping_dpi(tp3s_config_t* config, bool forward) {
    config->pointer_sniping_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

uint16_t tp3s_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_tp3s_config);
}

uint16_t tp3s_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_tp3s_config);
}

void tp3s_cycle_pointer_default_dpi_noeeprom(bool forward) {
    step_pointer_default_dpi(&g_tp3s_config, forward);
}

void tp3s_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_tp3s_config, forward);
    write_tp3s_config_to_eeprom(&g_tp3s_config);
}

void tp3s_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
    step_pointer_sniping_dpi(&g_tp3s_config, forward);
}

void tp3s_cycle_pointer_sniping_dpi(bool forward) {
    step_pointer_sniping_dpi(&g_tp3s_config, forward);
    write_tp3s_config_to_eeprom(&g_tp3s_config);
}

bool tp3s_get_pointer_sniping_enabled(void) {
    return g_tp3s_config.is_sniping_enabled;
}

void tp3s_set_pointer_sniping_enabled(bool enable) {
    g_tp3s_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_tp3s_config);
}

void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_tp3s_config);
    pointing_device_init_user();
}

/**
 * \brief Augment the pointing device behavior.
 *
 * Implement scroll devisor.
 */
static void pointing_device_task_tp3s(report_mouse_t* mouse_report) {
    /*2 FINGER SCROLL*/
    // timer
    static uint32_t hv_timer;
    static uint32_t hv_delta_time;
    // carry-over of rounding errors (dropped floats from integer reports)
    static float h_rounding_carry = 0;
    static float v_rounding_carry = 0;
    // (re)set hv_timer when hv report is non-zero
    if (mouse_report->h || mouse_report->v) {
        hv_delta_time = timer_elapsed32(hv_timer);
        hv_timer      = timer_read32();
    }
    // reset rounding_carry if timed out:
    if (hv_delta_time > TP3S_MOUSE_TIMEOUT) {
        h_rounding_carry = 0;
        v_rounding_carry = 0;
    }
    // Reset carry when scroll swaps direction:
    if (mouse_report->h * h_rounding_carry < 0) h_rounding_carry = 0;
    if (mouse_report->v * v_rounding_carry < 0) v_rounding_carry = 0;
    // apply scroll divisor:
    float h_new = h_rounding_carry + (float)mouse_report->h / TP3S_SCROLL_DIV;
    float v_new = v_rounding_carry + (float)mouse_report->v / TP3S_SCROLL_DIV;
    // reverse scroll direction on CTRL (zoom) - only works with CTRL on TP3S device itself:
    if (get_mods() & MOD_MASK_CTRL) {
        v_new *= -1;
    }
    // carry rounded off float to next scroll report:
    h_rounding_carry = h_new - (int)h_new;
    v_rounding_carry = v_new - (int)v_new;
    // update scroll reports with new value:
    mouse_report->h = (int)h_new;
    mouse_report->v = (int)v_new;
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // print("test 1");
    if (is_keyboard_master()) {
        // print("test 2");
        pointing_device_task_tp3s(&mouse_report);               // first apply tp3s mouse effect (ie. glide & scroll divisor)
        mouse_report = pointing_device_task_user(mouse_report); // then apply user mouse effects (ie. maccel)
    }
    return mouse_report;
}

#    if defined(POINTING_DEVICE_ENABLE) && !defined(NO_TP3S_KEYCODES)
/** \brief Whether SHIFT mod is enabled. */
static bool has_shift_mod(void) {
#        ifdef NO_ACTION_ONESHOT
    return mod_config(get_mods()) & MOD_MASK_SHIFT;
#        else
    return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#        endif // NO_ACTION_ONESHOT
}
#    endif // POINTING_DEVICE_ENABLE && !NO_TP3S_KEYCODES

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
#    ifdef POINTING_DEVICE_ENABLE
#        ifndef NO_TP3S_KEYCODES
    switch (keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                tp3s_cycle_pointer_default_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                tp3s_cycle_pointer_default_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                tp3s_cycle_pointer_sniping_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                tp3s_cycle_pointer_sniping_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case SNIPING_MODE:
            tp3s_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                tp3s_set_pointer_sniping_enabled(!tp3s_get_pointer_sniping_enabled());
            }
            break;
    }
#        endif // !NO_TP3S_KEYCODES
#    endif     // POINTING_DEVICE_ENABLE
    return true;
}

void eeconfig_init_kb(void) {
    g_tp3s_config.raw                 = 0;
    g_tp3s_config.pointer_default_dpi = 4; // DPI=1000
    write_tp3s_config_to_eeprom(&g_tp3s_config);
    maybe_update_pointing_device_cpi(&g_tp3s_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_tp3s_config_from_eeprom(&g_tp3s_config);
    matrix_init_user();
}
#endif // POINTING_DEVICE_ENABLE

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void keyboard_pre_init_kb(void) {
    // Ensures that GP26 through GP29 are initialized as digital inputs (as
    // opposed to analog inputs).  These GPIOs are shared with A0 through A3,
    // respectively.  On RP2040-B2 and later, the digital inputs are disabled by
    // default (see RP2040-E6).
    gpio_init(GP26);
    gpio_init(GP27);
    gpio_init(GP28);
    gpio_init(GP29);

    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    return true;
}
