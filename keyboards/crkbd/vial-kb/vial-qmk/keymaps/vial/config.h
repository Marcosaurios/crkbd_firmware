#pragma once

#define VIAL_KEYBOARD_UID {0x89, 0x36, 0x2A, 0xC7, 0xFA, 0xD8, 0x89, 0x45}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

// For MOD-TAP HomeRows
// Configure the global tapping term (default: 200ms)
// #define TAPPING_TERM 1000

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define QUICK_TAP_TERM 0

#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define RGB_MATRIX_DEFAULT_HUE 2 // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 3 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL 0 // Sets the default brightness value, if none has been set
