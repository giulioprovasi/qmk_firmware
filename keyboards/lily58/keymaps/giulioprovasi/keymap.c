#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _COLEMAK = 0,
  _QWERTY,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
};

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
#define KC_QWE QWERTY
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_ADJT ADJUST
#define KC_RST RESET
#define KC_DBUG DEBUG
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
#define KC_SPR LT(_RAISE, KC_SPC)
#define KC_SPL LT(_LOWER, KC_SPC)
//#define KC_NUMP TG(_NUMPAD)  // Toggle layer NUMPAD for use in KC_keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK (Mod-DH is used. https://colemakmods.github.io/mod-dh/)
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    | 1  | 2  | 3  | 4  | 5  |                  | 6  | 7  | 8  | 9  | 0  |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |TAB | Q  | W  | F  | P  | B  |                  | J  | L  | U  | Y  |SCLN|    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |SESC| A  | R  | S  | T  | G  |-----|      |-----| K  | N  | E  | I  | O  |BSPC|
 * |----+----+----+----+----+----+LBRC |      |RBRC |----+----+----+----+----+----|
 * |OCTL| Z  | X  | C  | D  | V  |-----|      |-----| M  | H  |COMM|DOT |SLSH|RCTL|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             | LALT|LGUI|LOWER/SPC /          \ENT \RAISE|BSPC|     |
 *             `-----+----+----/----/            \----\----+----+-----'
 */
  [_COLEMAK] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX, \
    KC_TAB , KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, XXXXXXX, \
    KC_SESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    KC_BSPC, \
    KC_OCTL, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LBRC,          KC_RBRC, KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL, \
                               KC_LALT, KC_LGUI, KC_LOWR,  KC_SPC,           KC_ENT, KC_RASE, KC_BSPC, XXXXXXX \
  ),

/* QWERTY
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |ESC | 1  | 2  | 3  | 4  | 5  |                  | 6  | 7  | 8  | 9  | 0  |GRV |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |TAB | Q  | W  | E  | R  | T  |                  | Y  | U  | I  | O  | P  |BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |LCTL| A  | S  | D  | F  | G  |-----|      |-----| H  | J  | K  | L  |SCLN|ENT |
 * |----+----+----+----+----+----|     |      |     |----+----+----+----+----+----|
 * |LSFT| Z  | X  | C  | V  | B  |-----|      |-----| M  | H  |COMM|DOT |SLSH|RSFT|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             `-----+----+----/----/            \----\----+----+-----'
 */
  [_QWERTY] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
    KC_TAB , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,          _______, KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                               _______, _______, _______, _______,          _______, _______, _______, _______ \
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
 *             `-----+----+----/----/            \----\----+----+-----'
 */
  [_NUMPAD] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                            _______, KC_ASTR, KC_P7,   KC_P8,   KC_P9,   KC_SLSH, \
    _______, _______, _______, _______, _______, _______,                            _______, KC_PIPE, KC_P4,   KC_P5,   KC_P6,   KC_MINS, \
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, KC_COMM, KC_P1,   KC_P2,   KC_P3,   KC_PLUS, \
                               _______, _______, _______, _______,          _______, _______, _______, _______ \
  ),

/* LOWER
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    |    |    |    |    |    |                  |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |    |    |    |    |CAPS|                  |    |PGUP|HOME| UP |END |BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |SELA|LALT|LSFT|LCTL|SVE |-----|      |-----|    |PGDN|LEFT|DOWN|RGHT|DEL |
 * |----+----+----+----+----+----|     |      |     |----+----+----+----+----+----|
 * |    |UDO |CUT |CPY |PST |    |-----|      |-----|    |    |    |COMM|DOT |SLSH|
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             `-----+----+----/----/            \----\----+----+-----'
 */
  [_LOWER] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                            _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC, \
    _______, KC_SELA, KC_LALT, KC_LSFT, KC_LCTL, KC_SVE,                             _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, \
    _______, KC_UDO,  KC_CUT,  KC_CPY,  KC_PST,  XXXXXXX, _______,          _______, _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, \
                               _______, _______, _______, _______,          _______, _______, _______, _______ \
  ),

/* RAISE
 * ,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
 * |    |    |    |    |    |    |                  |    |    |    |    |    |    |
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |AMPR|PERC|HASH|EXLM|LPRN|                  |ASTR|RPRN| AT |DLR |CIRC|BSPC|
 * |----+----+----+----+----+----|                  |----+----+----+----+----+----|
 * |    |GRV |TILD|XXXX|EQL |PLUS|-----|      |-----|UNDS|MINS|COMM|DOT |SLSH|ENT |
 * |----+----+----+----+----+----|     |      |     |----+----+----+----+----+----|
 * |    |    |    |    |    |    |-----|      |-----|    |    |    |    |    |    |
 * `----+----+----+----+----+----/    /        \    \----+----+----+----+----+----'
 *             |LALT |LGUI|LOWER/SPL /          \SPR \RAISE|LEFT|RIGHT|
 *             `-----+----+----/----/            \----\----+----+-----'
 */
  [_RAISE] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, \
    _______, KC_AMPR, KC_PERC, KC_HASH, KC_EXLM, KC_LPRN,                            KC_ASTR, KC_RPRN, KC_AT,   KC_DLR,  KC_CIRC, KC_BSPC, \
    _______, KC_GRV,  KC_TILD, XXXXXXX, KC_EQL,  KC_PLUS,                            KC_UNDS, KC_MINS, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, \
                               _______, _______, _______, _______,          _______, _______, _______, _______ \
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
 *             `-----+----+----/----/            \----\----+----+-----'
 */
  [_ADJUST] = LAYOUT( \
 /* _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              XXXXXXX, DF(0),   DF(1),   XXXXXXX, XXXXXXX, XXXXXXX, \
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                             XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, KC_MPLY,  \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU,  KC_MUTE, \
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  )
};

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

char wpm_str[10];

void oled_task_user(void) {
  if (is_keyboard_master()) {
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_scroll_left();  // Turns on scrolling
    switch (biton32(layer_state)){
      case _COLEMAK:
          oled_write_ln_P(PSTR("       COLEMAK"), false);
          break;
      case _QWERTY:
          oled_write_ln_P(PSTR("       QWERTY"), false);
          break;
      case _RAISE:
          oled_write_ln_P(PSTR("       RAISE"), false);
          break;
      case _LOWER:
          oled_write_ln_P(PSTR("       LOWER"), false);
          break;
      case _NUMPAD:
          oled_write_ln_P(PSTR("       NUMPAD"), false);
          break;
      case _ADJUST:
          oled_write_ln_P(PSTR("       ADJUST"), false);
          break;
      default:
          oled_write_ln_P(PSTR("       ?????"), false);
  }
  oled_write(read_logo(), false);

  } else {
    // sprintf(wpm_str, "       WPM: %03d", get_current_wpm());
    // oled_write_ln(wpm_str, false);
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    // set_keylog(keycode, record);
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

