/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* 
 * Keymap for HID Liberator controller
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
#define KEYMAP( \
    KG1, KH7, KJ7, KJ6, KJ1, KO5, KL1, KA6, KA7, KD7, KD5, KD1, KD2,      KB5, KB3, KO3, \
    KG7, KG5, KH5, KJ5, KI5, KI7, KK7, KK5, KL5, KA5, KC5, KC7, KL7, KD6, KQ7, KN7, KM7, \
    KG6, KG3, KH3, KJ3, KI3, KI6, KK6, KK3, KL3, KA3, KC3, KC6, KL6, KD4, KP7, KN5, KM5, \
    KH6, KG4, KH4, KJ4, KI4, KI1, KK1, KK4, KL4, KA4, KC4, KC1, KD0,                     \
    KF6, KH1, KG0, KH0, KJ0, KI0, KI2, KK2, KK0, KL0, KA0, KC2, KF4,           KN1,      \
    KO7, KE6, KB1,           KP1,                     KB2, KR4, KA2, KO0, KN2, KP2, KQ2  \
) { \
/*             0         1         2         3         4         5         6         7     */ \
/* A */   { KC_##KA0, KC_NO   , KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5, KC_##KA6, KC_##KA7 }, \
/* B */   { KC_NO   , KC_##KB1, KC_##KB2, KC_##KB3, KC_NO   , KC_##KB5, KC_NO   , KC_NO    }, \
/* C */   { KC_NO   , KC_##KC1, KC_##KC2, KC_##KC3, KC_##KC4, KC_##KC5, KC_##KC6, KC_##KC7 }, \
/* D */   { KC_##KD0, KC_##KD1, KC_##KD2, KC_NO   , KC_##KD4, KC_##KD5, KC_##KD6, KC_##KD7 }, \
/* E */   { KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##KE6, KC_NO    }, \
/* F */   { KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##KF4, KC_NO   , KC_##KF6, KC_NO    }, \
/* G */   { KC_##KG0, KC_##KG1, KC_NO   , KC_##KG3, KC_##KG4, KC_##KG5, KC_##KG6, KC_##KG7 }, \
/* H */   { KC_##KH0, KC_##KH1, KC_NO   , KC_##KH3, KC_##KH4, KC_##KH5, KC_##KH6, KC_##KH7 }, \
/* I */   { KC_##KI0, KC_##KI1, KC_##KI2, KC_##KI3, KC_##KI4, KC_##KI5, KC_##KI6, KC_##KI7 }, \
/* J */   { KC_##KJ0, KC_##KJ1, KC_NO   , KC_##KJ3, KC_##KJ4, KC_##KJ5, KC_##KJ6, KC_##KJ7 }, \
/* K */   { KC_##KK0, KC_##KK1, KC_##KK2, KC_##KK3, KC_##KK4, KC_##KK5, KC_##KK6, KC_##KK7 }, \
/* L */   { KC_##KL0, KC_##KL1, KC_NO   , KC_##KL3, KC_##KL4, KC_##KL5, KC_##KL6, KC_##KL7 }, \
/* M */   { KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##KM5, KC_NO   , KC_##KM7 }, \
/* N */   { KC_NO   , KC_##KN1, KC_##KN2, KC_NO   , KC_NO   , KC_##KN5, KC_NO   , KC_##KN7 }, \
/* O */   { KC_##KO0, KC_NO   , KC_NO   , KC_##KO3, KC_NO   , KC_##KO5, KC_NO   , KC_##KO7 }, \
/* P */   { KC_NO   , KC_##KP1, KC_##KP2, KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##KP7 }, \
/* Q */   { KC_NO   , KC_NO   , KC_##KQ2, KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##KQ7 }, \
/* R */   { KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##KR4, KC_NO   , KC_NO   , KC_NO    }  \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    1,              // Fn1
    2,              // Fn2
    3,              // Fn3
    4,              // Fn4
    5,              // Fn5
    6,              // Fn6
    7               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_NO,          // Fn2
    KC_NO,          // Fn3
    KC_NO,          // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};

/*
 * Tenkeyless keyboard default layout, ISO & ANSI (ISO is between Left Shift
 * and Z, and the ANSI \ key above Return/Enter is used for the additional ISO
 * switch in the ASD row next to enter.  Use NUBS as keycode for the first and
 * NUHS as the keycode for the second.
 *
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shft|ISO|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 */


static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default Layer
 *
 * ANSI:
 *
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |FN1   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shft|iso|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 */

  KEYMAP(\
    ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10,  F11,  F12,       PSCR, SLCK,  BRK, \
    GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0, MINS,  EQL, BSPC,  INS, HOME, PGUP, \
    TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P, LBRC, RBRC, BSLS,  DEL,  END, PGDN, \
    FN1,   A,   S,   D,   F,   G,   H,   J,   K,   L, SCLN, QUOT,       ENT,                   \
    LSFT, NUBS, Z,   X,   C,   V,   B,   N,   M, COMM, DOT, SLSH,      RSFT,         UP,       \
    LCTL, LGUI, LALT,             SPC,                RALT, RGUI, APP, RCTL, LEFT, DOWN, RGHT),

/*  EXAMPLE ISO keymap, see the NUBS and NUHS keycodes 
 *  KEYMAP(\
 *    ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PSCR, SLCK, BRK, \
 *    GRV, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, MINS, EQL, BSPC, INS, HOME, PGUP, \
 *    TAB, Q, W, E, R, T, Y, U, I, O, P, LBRC, RBRC, NUHS, DEL, END, PGDN, \
 *    CAPS, A, S, D, F, G, H, J, K, L, SCLN, QUOT, ENT, \
 *    LSFT, NUBS, Z, X, C, V, B, N, M, COMM, DOT, SLSH, RSFT, UP, \
 *    LCTL, FN1, LALT, SPC, RALT, RGUI, APP, RCTL, LEFT, DOWN, RGHT),
 */


/*  
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Slp|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|Mut|V- |V+ |Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|MSt|Ply|Prv|Nxt|Media| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |FN1   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shft|iso|  Z|  X|Clc|  V|  B|  N|  M|  ,|  .|  /|Caps      |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 */

 KEYMAP(\
    ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10,  F11,  F12,       PSCR, SLCK, SLEP, \
    GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,MUTE, VOLD, VOLU, BSPC,  INS, HOME, PGUP, \
    TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,MSTP,MPLY, MPRV, MNXT, MSEL,  DEL,  END, PGDN, \
    FN1,   A,   S,   D,   F,   G,   H,   J,   K,   L, SCLN, QUOT,       ENT,                   \
    LSFT, NUBS, Z,   X,CALC,   V,   B,   N,   M, COMM, DOT, SLSH,      CAPS,         UP,       \
    LCTL, LGUI, LALT,             SPC,                RALT, RGUI, APP, RCTL, LEFT, DOWN, RGHT),


};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}
