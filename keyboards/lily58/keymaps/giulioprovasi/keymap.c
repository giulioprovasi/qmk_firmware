#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

#define _COLEMAK 0
#define _QWERTY 1
#define _NUMPAD 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  NUMPAD,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define KC_XXXX KC_NO

#define KC_CMK COLEMAK
#define KC_QWE COLEMAK
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_QRAS QRAISE
#define KC_ADJT ADJUST
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
//#define KC_CATDEL LCTL(LALT(KC_DEL)) // Ctrl alt del
#define KC_CPY LCTL(KC_C)
#define KC_PST LCTL(KC_V)
#define KC_SELA LCTL(KC_A)
#define KC_UDO LCTL(KC_Z)
#define KC_CUT LCTL(KC_X)
#define KC_SVE LCTL(KC_S)
#define KC_OSH OSM(MOD_LSFT)
#define KC_OCTL OSM(MOD_LCTL)
#define KC_NUMP TT(_NUMPAD)
#define KC_SESC MT(MOD_LSFT,KC_ESC)
#define KC_SENT MT(MOD_RSFT,KC_ENT)
#define KC_SPR LT(RAISE, KC_SPC)
#define KC_SPL LT(LOWER, KC_SPC)
//#define KC_NUMP TG(_NUMPAD)  // Toggle layer NUMPAD for use in KC_keymaps
//#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK (Mod-DH is used. https://colemakmods.github.io/mod-dh/)
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    | 1  | 2  | 3  | 4  | 5  |                  | 6  | 7  | 8  | 9  | 0  |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |TAB | Q  | W  | F  | P  | B  |                  | J  | L  | U  | Y  |SCLN|BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |SESC| A  | R  | S  | T  | G  |-----|      |-----| K  | N  | E  | I  | O  |SENT|
 * |----+----+----+----+----+----+LBRC |      |RBRC |----+----+----+----+----+----|
 * |OCTL| Z  | X  | C  | D  | V  |-----|      |-----| M  | H  |COMM|DOT |SLSH|RCTL|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             | LALT|LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             |-----+----+----/----/            \----\----+----+-----|
 */
  [_COLEMAK] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
    KC_TAB , KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
    KC_SESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    KC_SENT, \
    KC_OCTL, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LBRC,          KC_RBRC, KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL, \
                               KC_LALT, KC_LGUI, LOWER ,  KC_SPL,           KC_SPR,  RAISE,   KC_LEFT, KC_RIGHT \
  ),

/* QWERTY
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |ESC | 1  | 2  | 3  | 4  | 5  |                  | 6  | 7  | 8  | 9  | 0  |GRV |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |TAB | Q  | W  | E  | R  | T  |                  | Y  | U  | I  | O  | P  |BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |LCTL| A  | S  | D  | F  | G  |-----|      |-----| H  | J  | K  | L  |SCLN|ENT |
 * |----+----+----+----+----+----|LBRC |      |RBRC |----+----+----+----+----+----|
 * |LSFT| Z  | X  | C  | V  | B  |-----|      |-----| M  | H  |COMM|DOT |SLSH|RSFT|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             |-----+----+----/----/            \----\----+----+-----|
 */
  [_QWERTY] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
    KC_TAB , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,          KC_RBRC, KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                               KC_LALT, KC_LGUI, LOWER ,  KC_SPL,           KC_SPR,  RAISE,   KC_LEFT, KC_RIGHT \
  ),

/* NUMPAD
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    |    |    |    |    |    |                  |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |    |    |    |    |    |                  |    |ASTR| P7 | P8 | P9 |SLSH|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----|      |-----|    |PIPE| P4 | P5 | P6 |MINS|
 * |----+----+----+----+----+----|     |      |     |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----|      |-----|    |COMM| P1 | P2 | P3 |PLUS|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             |-----+----+----/----/            \----\----+----+-----|
 */
  [_NUMPAD] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                            _______, KC_ASTR, KC_P7,   KC_P8,   KC_P9,   KC_SLSH, \
    _______, _______, _______, _______, _______, _______,                            _______, KC_PIPE, KC_P4,   KC_P5,   KC_P6,   KC_MINS, \
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_COMM, KC_P1,   KC_P2,   KC_P3,   KC_PLUS, \
                               KC_LALT, KC_LGUI, LOWER ,  KC_SPL,           KC_SPR,  RAISE,   KC_LEFT, KC_RIGHT \
  ),

/* LOWER
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    |    |    |    |    |    |                  |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |    |    |    |    |CAPS|                  |    |PGUP|HOME| UP |END |BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |SELA|LALT|LSFT|LCTL|SVE |-----|      |-----|    |PGDN|LEFT|DOWN|RGHT|DEL |
 * |----+----+----+----+----+----|LBRC |      |RBRC |----+----+----+----+----+----|
 * |    |UDO |CUT |CPY |PST |    |-----|      |-----|    |    |    |COMM|DOT |SLSH|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             |-----+----+----/----/            \----\----+----+-----|
 */
  [_LOWER] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                            _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC, \
    _______, KC_SELA, KC_LALT, KC_LSFT, KC_LCTL, KC_SVE,                             _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, \
    _______, KC_UDO,  KC_CUT,  KC_CPY,  KC_PST,  XXXXXXX, KC_LBRC,          KC_RBRC, _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, \
                               KC_LALT, KC_LGUI, LOWER ,  KC_SPL,           KC_SPR,  RAISE,   KC_LEFT, KC_RIGHT \
  ),

/* RAISE
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    |    |    |    |    |    |                  |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |AMPR|PERC|HASH|EXLM|LPRN|                  |ASTR|RPRN| AT |DLR |CIRC|BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |GRV |TILD|XXXX|EQL |PLUS|-----|      |-----|UNDS|MINS|COMM|DOT |SLSH|ENT |
 * |----+----+----+----+----+----|LBRC |      |RBRC |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----|      |-----|    |    |    |    |    |    |
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             |-----+----+----/----/            \----\----+----+-----|
 */
  [_RAISE] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    _______, KC_AMPR, KC_PERC, KC_HASH, KC_EXLM, KC_LPRN,                            KC_ASTR, KC_RPRN, KC_AT,   KC_DLR,  KC_CIRC, KC_BSPC, \
    _______, KC_GRV,  KC_TILD, XXXXXXX, KC_EQL,  KC_PLUS,                            KC_UNDS, KC_MINS, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
    _______, _______, _______, _______, _______, _______, KC_LBRC,          KC_RBRC, _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, \
                               KC_LALT, KC_LGUI, LOWER ,  KC_SPL,           KC_SPR,  RAISE,   KC_LEFT, KC_RIGHT \
  ),

/* ADJUST
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    |    |    |    |    |    |                  |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * | F1 | F2 | F3 | F4 | F5 | F6 |                  |    |CMK |QWE |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * | F7 | F8 | F9 |F10 |F11 |F12 |-----|      |-----|    |    |    |MPRV|MNXT|MPLY|
 * |----+----+----+----+----+----|     |      |     |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----|      |-----|    |    |    |VOLD|VOLU|MUTE|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             |-----+----+----/----/            \----\----+----+-----|
 */
  [_ADJUST] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              _______, KC_CMK, KC_QWE,   _______,  _______, _______, \
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                             _______, _______, _______, KC_MPRV,  KC_MNXT, KC_MPLY,  \
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, KC_VOLD, KC_VOLU,  KC_MUTE, \
                               KC_LALT, KC_LGUI, LOWER ,  KC_SPL,           KC_SPR,  RAISE,   KC_LEFT, KC_RIGHT \
  )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);

      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

