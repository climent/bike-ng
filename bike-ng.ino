#include <FastLED.h>

#define BUTTON_PIN 9

#define DATA_PIN_F1 1
#define NUM_LEDS_F1 24
#define DATA_PIN_F2 0
#define NUM_LEDS_F2 24

#define DATA_PIN_F 6
#define NUM_LEDS_F 60

//int f1 = 22;
//int f2 = 27;
//int f3 = 11;

#define DATA_PIN_B1 5
#define NUM_LEDS_B1 22
#define DATA_PIN_B2 4
#define NUM_LEDS_B2 22

#define DATA_PIN_S1 10
#define NUM_LEDS_S1 24
#define DATA_PIN_S2 11
#define NUM_LEDS_S2 24

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

int ledStrips[87] = {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,
                     22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
                     0,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
                    };

int ledArray[87] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                    3,
                    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
                   };
int allLeds = 87;

CRGB leds_f1[NUM_LEDS_F1];
CRGB leds_f2[NUM_LEDS_F2];
CRGB leds_f[NUM_LEDS_F];
CRGB leds_b1[NUM_LEDS_B1];
CRGB leds_b2[NUM_LEDS_B2];
CRGB leds_s1[NUM_LEDS_S1];
CRGB leds_s2[NUM_LEDS_S2];


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F1>(leds_f1, NUM_LEDS_F1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F2>(leds_f2, NUM_LEDS_F2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F>(leds_f, NUM_LEDS_F);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_B1>(leds_b1, NUM_LEDS_B1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_B2>(leds_b2, NUM_LEDS_B2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_S1>(leds_s1, NUM_LEDS_S1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_S2>(leds_s2, NUM_LEDS_S2);
  FastLED.setBrightness(100);
  // Initialize the button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(BUTTON_PIN, HIGH);

}

int  count = 0;
int  color = 0;
CRGB color_rgb;

void loop() {
  EVERY_N_MILLISECONDS(50) {
    if (count < 87) {
      count++;
    } else {
      count = 0;
      color ++;
      if (color == 3) color = 0;
    }
  }
  color_rgb = CRGB::Blue;
  // put your main code here, to run repeatedly:
  //  audioVuMeter();
  //  allAddGlitterBy(80)
  //  cylon();
  //  allArrayFrontToBack(count);
  switch (color) {
    case 0:
      color_rgb = CRGB::Blue;
      allArrayBTF(count, color_rgb);
      break;
    case 1:
      color_rgb = CRGB::Green;
      allArrayBTF(count, color_rgb);
      break;
    case 2:
      color_rgb = CRGB::Red;
      allArrayBTF(count, color_rgb);
      break;
  }
  FastLED.show();

}

void cylon() {
  int gHue = 250; // pink, like my bike
  allFadeToBlackBy(5);
  int j = beatsin8(20, 0, 87);
  for (int pos = j - 1 ; pos < j + 1 ; pos++) {
    if (pos < 0) pos = 0;
    if (pos > 87) pos = 87;
    int loc = ledArray[pos];
    int b1_pos;
    int f_pos;
    switch (loc) {
      case 1:
        leds_f1[ledStrips[pos]] += CHSV( gHue, 255, 192);
        break;
      case 2:
        leds_f[pos - 24 + 22] += CHSV( gHue, 255, 192);
        f_pos = map(pos - 24, 0, 27, 0, 22);
        leds_f[21 - f_pos] += CHSV( gHue, 255, 192);
        break;
      case 3:
        for (int i = 0; i < 11; i++) {
          leds_f[i + 22 + 27] += CHSV( gHue, 255, 192);
        }
        break;
      case 4:
        b1_pos = pos - 24 - 27 - 1;
        leds_b1[b1_pos] += CHSV( gHue, 255, 192);
        leds_b1[21 - b1_pos] += CHSV( gHue, 255, 192);
        break;
      case 5:
        leds_s1[pos - 24 - 27 - 1 - 11] += CHSV( gHue, 255, 192);
        break;
    }
  }
}

void allArrayFTB(int pos, CRGB color) {
  int loc = ledArray[pos];
  switch (loc) {
    case 1:
      leds_f1[map(pos, 0, 23, 23, 0)] = leds_f2[map(pos, 0, 23, 23, 0)] = color;
      break;
    case 2:
      leds_f[map(pos, 24, 50, 22, 48)] = leds_f[map(pos, 24, 50, 21, 0)] = color;
      break;
    case 3:
      leds_f[49] = leds_f[59] = color;
      break;
    case 4:
      if (ledStrips[pos] <= 4) {
        leds_f[50 + ledStrips[pos]] = leds_f[58 - ledStrips[pos]] = color;
      }
      leds_b1[ledStrips[pos]] = leds_b2[21 - ledStrips[pos]] = color;
      leds_b1[map(ledStrips[pos], 0, 10, 21, 11)] = color;
      leds_b2[21 - map(ledStrips[pos], 0, 10, 21, 11)] = color;
      break;
    case 5:
      leds_s1[ledStrips[pos]] = leds_s2[ledStrips[pos]] = color;
      break;
  }
}
void allArrayBTF(int pos, CRGB color) {
  pos = map(pos, 0, 87, 87 , 0);
  int loc = ledArray[pos];
  switch (loc) {
    case 1:
      leds_f1[ledStrips[pos]] = leds_f2[ledStrips[pos]] = color;
      break;
    case 2:
      if (ledStrips[pos] >= 44) {
        leds_f[50 + 48 - ledStrips[pos]] = leds_f[58 - 48 + ledStrips[pos]] = color;
      }
      leds_f[ledStrips[pos]] = leds_f[map(ledStrips[pos], 22, 48, 21, 0)] = color;
      break;
    case 3:
      leds_f[49] = leds_f[59] = color;
      break;
    case 4:
      leds_b1[ledStrips[pos]] = leds_b2[21 - ledStrips[pos]] = color;
      leds_b1[map(ledStrips[pos], 0, 10, 21, 11)] = color;
      leds_b2[21 - map(ledStrips[pos], 0, 10, 21, 11)] = color;
      break;
    case 5:
      leds_s1[ledStrips[pos]] = leds_s2[ledStrips[pos]] = color;
      break;
  }
}

void audioVuMeter(CRGB color) {
  int level = vuMeter();
//  color = CRGB::Blue;
  mapToLeds(leds_f1,  0, 23, level, color);
  mapToLeds(leds_f,   0, 21, level, color);
  mapToLeds(leds_f,  22, 48, level, color);
  mapToLeds(leds_f,  49, 59, level, color);
  mapToLeds(leds_b1,  0, 10, level, color);
  mapToLeds(leds_b1, 11, 22, level, color);
  mapToLeds(leds_s1,  0, 23, level, color);
}

void mapToLeds(CRGB * leds, int first, int num_leds, int peak, CRGB color) {
  // First fade all the LEDs to black. This adds a fading efect instead of colors going black immediately.
  fadeToBlackBy(leds, num_leds, 128);
  // Then map the peak to a numbers of LEDs.
  int level = map(peak, 1, 600, -1, num_leds - first + 1);
  // And now color them.
  for (int led = first; led <= first + level; led++)
  {
    leds[led] = color;
  }
}


int maximum = 600;
uint16_t sampleWindow = 50;
unsigned int sample;

int vuMeter() {
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 600;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);

    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }

  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  if (peakToPeak < 0) peakToPeak = 0;
  else if (peakToPeak > 1023) peakToPeak = 0;
  return peakToPeak;
}


void allFadeToBlackBy(int by) {
  // We list all the strips and fade them all by a percent defined by x/256.
  fadeToBlackBy(leds_f1, NUM_LEDS_F1, by);
  fadeToBlackBy(leds_f2, NUM_LEDS_F2, by);
  fadeToBlackBy(leds_f,  NUM_LEDS_F,  by);
  fadeToBlackBy(leds_b1, NUM_LEDS_B1, by);
  fadeToBlackBy(leds_b2, NUM_LEDS_B2, by);
  fadeToBlackBy(leds_s1, NUM_LEDS_S1, by);
  fadeToBlackBy(leds_s2, NUM_LEDS_S2, by);
}


void allAddGlitterBy(int by) {
  addGlitter(leds_f1, NUM_LEDS_F1, by);
  addGlitter(leds_f2, NUM_LEDS_F2, by);
  addGlitter(leds_f,  NUM_LEDS_F,  by);
  addGlitter(leds_b1, NUM_LEDS_B1, by);
  addGlitter(leds_b2, NUM_LEDS_B2, by);
  addGlitter(leds_s1, NUM_LEDS_S1, by);
  addGlitter(leds_s2, NUM_LEDS_S2, by);
}


void addGlitter(CRGB * leds, uint8_t num_leds, fract8 chanceOfGlitter) {
  if ( random8() < chanceOfGlitter) {
    leds[random16(num_leds)] += CRGB::White;
  }
  fadeToBlackBy(leds, num_leds, 192);
}

