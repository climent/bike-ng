//   The bike LEDs are composed of 7 strips:
//   * 2x 24 LED strips in the front fork, top to bottom
//   * 1x 60 LED strip in the frame, divided in
//     - 22 LEDs, from the base of the saddle post to the headset
//     - 27 LEDs, from the headset to the bottom bracket, and
//     - 11 LEDs, from the bottom bracket back to the sit post
//   * 1x 22 LED strip, divided in 2x 11 LED sections
//     - 11 LEDs, from the bottom bracket to the dropouts
//     - 11 LEDs, from the bottom of the base of the saddle post to the dropouts
//   * 2x 24 LED strips from the dropouts upwards, in the sissy bar.

#define DATA_PIN_F1 6
#define NUM_LEDS_F1 24
#define DATA_PIN_F2 7
#define NUM_LEDS_F2 24

#define DATA_PIN_F 8
#define NUM_LEDS_F 60

#define DATA_PIN_B1 9
#define NUM_LEDS_B1 22
#define DATA_PIN_B2 10
#define NUM_LEDS_B2 22

#define DATA_PIN_S1 11
#define NUM_LEDS_S1 30
#define DATA_PIN_S2 12
#define NUM_LEDS_S2 30

CRGB leds212[212];
CRGB leds136[136];

CRGB leds_f1[NUM_LEDS_F1];
CRGB leds_f2[NUM_LEDS_F2];
CRGB leds_f[NUM_LEDS_F];
CRGB leds_b1[NUM_LEDS_B1];
CRGB leds_b2[NUM_LEDS_B2];
CRGB leds_s1[NUM_LEDS_S1];
CRGB leds_s2[NUM_LEDS_S2];

