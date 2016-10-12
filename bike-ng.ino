// Bike LEDs for burning man.
// bike-ng.ino

#include <FastLED.h>

#define BUTTON_PIN 9

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

#define DATA_PIN_F1 1
#define NUM_LEDS_F1 24
#define DATA_PIN_F2 2
#define NUM_LEDS_F2 24

#define DATA_PIN_F 6
#define NUM_LEDS_F 60

#define DATA_PIN_B1 7
#define NUM_LEDS_B1 22
#define DATA_PIN_B2 8
#define NUM_LEDS_B2 22

#define DATA_PIN_S1 10
#define NUM_LEDS_S1 30
#define DATA_PIN_S2 11
#define NUM_LEDS_S2 30

const int ledArray93[93] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                            3,
                            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
                           };

const int ledArray136[136] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                              2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                              2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                              3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
                             };

const int ledArray212[212] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                              2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                              3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                              3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                              5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                              6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                              7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                             };

// Definitions for twinkles.
#define PEAK_COLOR CRGB(100,100,100)
int ledState212[212];
enum {SteadyDim, GettingBrighter, GettingDimmerAgain};

CRGB leds212[212];
CRGB leds136[136];

CRGB leds_f1[NUM_LEDS_F1];
CRGB leds_f2[NUM_LEDS_F2];
CRGB leds_f[NUM_LEDS_F];
CRGB leds_b1[NUM_LEDS_B1];
CRGB leds_b2[NUM_LEDS_B2];
CRGB leds_s1[NUM_LEDS_S1];
CRGB leds_s2[NUM_LEDS_S2];


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F1>(leds_f1, NUM_LEDS_F1).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F2>(leds_f2, NUM_LEDS_F2).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F>(leds_f, NUM_LEDS_F).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_B1>(leds_b1, NUM_LEDS_B1).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_B2>(leds_b2, NUM_LEDS_B2).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_S1>(leds_s1, NUM_LEDS_S1).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_S2>(leds_s2, NUM_LEDS_S2).setCorrection(TypicalLEDStrip);;
  FastLED.setBrightness(100);

  // Initialize pixel state to SteadyDim:
  memset(ledState212, SteadyDim, 212);

  //initialize all to black:
//  memset(leds_f1, NUM_LEDS_F1, CRGB::Black);
//  memset(leds_f2, NUM_LEDS_F2, CRGB::Black);
//  memset(leds_f,  NUM_LEDS_F,  CRGB::Black);
//  memset(leds_b1, NUM_LEDS_B1, CRGB::Black);
//  memset(leds_b2, NUM_LEDS_B2, CRGB::Black);
//  memset(leds_s1, NUM_LEDS_S1, CRGB::Black);
//  memset(leds_s2, NUM_LEDS_S2, CRGB::Black);

  // Initialize the button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(BUTTON_PIN, HIGH);

}

//* Turnable knobs to change the behavior of the animations

//#define GHUE_SPEED 5        // How fast the rainbow colors change
//#define CYCLE_SPEED 100     // How fast we move the theater chase animation
#define SHOWTIME 2000       // How long we stop in some animations
#define NUM_M_ANIMATIONS 2  // How many animations we cycle through

//* Variables that we need in order to run
uint8_t count =        0;
uint8_t color =        0;
uint8_t gHue =         0;
uint8_t cycle =        0;
uint8_t head =         0;
uint8_t mode =         1;
unsigned long start_time;
unsigned long now;

CRGB    color_rgb = CRGB::Blue;
CHSV    color_hsv;

// Variables to control the flow of the animations
int m_animation = 1;       // Initial animation
int next_animation = 1;    // Next animation

// Variables to control the transitions
bool auto_transition = false;    // Automatically move to the next animation/transition
bool skip_transition = false;   // Skip transitions and only output animations
bool t_speed         = 1000;

void loop() {
  // cycle controls the theater chase animation
  EVERY_N_MILLISECONDS( 100 ) {
    cycle++;
    if (cycle == 3) {
      cycle = 0;
    }
  }
  // gHue controls the rainbow
  EVERY_N_MILLISECONDS( 5 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
  EVERY_N_MILLISECONDS( 1 ) {
    if (count < 93) {
      count++;
    } else {
      count = 0;
      color ++;
      if (color == 3) color = 0;
    }
  }

  switch (mode) {
    case 1:
      mode1();
      break;
    case 2:
      demo();
      break;
    case 3:
      audioVuMeter(color_rgb);
      break;
    case 4:
      allFadeToBlackBy(50);
      break;
    default:
      mode1();
      break;
  }

  FastLED.show();
  buttons();
}

void mode1() {
  switch (m_animation) {
    case 1:
      if (m_animation == next_animation) {
        if (head < 136) head++;
        fillRainbow(head, 0);
      } else {
        allFadeToBlackBy(10);
        if (allColor(CRGB::Black)) {
          m_animation = next_animation;
          head = 0;
          memset(ledState212, 212, SteadyDim);
        }
      }
      break;
    case 2:
      if (m_animation == next_animation) {
        if (head < 136) head++;
        allTwinkleMapPixels(2);
      } else {
        for (int i = 0; i < 212 ; i++) {
          leds212[i] = CRGB::Black;
        }
        allFadeToBlackBy(10);
        if (allColor(CRGB::Black)) {
          m_animation = next_animation;
          head = 0;
        }
      }
      break;
    case 3:
      break;
    default:
      break;
  }
}

// List of patterns to cycle through.  Each is defined as a separate function below.
//typedef void (*patternList[])();
//patternList gPatterns = { allFillRainbow, allBpm13, , sinelon, juggle, bpm };
//
//void mode3() {
//  gPatterns[gCurrentPatternNumber]();
//}

int animation = 1;
int glitter   = 0;
int fader     = 0;
unsigned long next_delay;
void next() {
  next_delay = random16(2000, 5000);
}
void demo() {
  switch (animation) {
    case 1:
      if (allColor(CRGB::Black)) {
        start_time = millis();
        head = 0;
        animation++;
        next();
      } else {
        allFadeToBlackBy(50);
      }
      break;
    case 2:
      glitter = 0;
      EVERY_N_MILLISECONDS(10) {
        if (head < 136) head++;
        if (head == 135) {
          start_time = millis();
        }
      }
      now = millis();
      if (now - start_time > next_delay && head == 136) {
        next();
        animation++;
      }
      fillRainbow(head, 0);
      break;
    case 3:
      EVERY_N_MILLISECONDS(20) {
        if (glitter < 100) {
          glitter++;
        }
      }
      now = millis();
      allFillRainbow();
      allAddGlitterBy(glitter);
      fader = 1;
      if (glitter == 99) {
        start_time = millis();
      }
      if (now - start_time > next_delay && glitter == 100) {
        fader = 0;
        animation++;
        next();
      }
      break;
    case 4:
      EVERY_N_MILLISECONDS(10) {
        if (fader < 255) {
          fader++;
        }
      }
      if (fader == 254) {
        start_time = millis();
      }
      now = millis();
      allFillRainbow();
      allFadeToBlackBy(fader);
      allAddGlitterBy(glitter);
      if (now - start_time > 3000 && fader >= 254) {
        animation++;
      }
      break;
    case 5:
      EVERY_N_MILLISECONDS(30) {
        if (fader > 2) {
          fader--;
        }
        if (glitter > 0) {
          glitter--;
        }
      }
      now = millis();
      allTwinkleMapPixels(fader);
      allAddGlitterBy(glitter);
      if (fader == 2 && now - start_time > 2000) {
        animation++;
        start_time = millis();
      }
      break;
    case 6:
      cylon();
//      allAddGlitterBy(10);
      now = millis();
      if (now - start_time > 8000) {
        animation++;
      }
      //      audioVuMeter(color_rgb);
      break;
    case 7:
      allFadeToBlackBy(10);
      if (allColor(CRGB::Black)) {
        start_time = millis();
        animation++;
        head = 0;
      }
      break;
    case 8:
      now = millis();
      EVERY_N_MILLISECONDS(20) {
        if (head < 136) head++;
        if (head == 135) {
          start_time = millis();
        }
      }
      allBpm136(head, 0, 62);
      if (now - start_time > 3000 && head == 136) {
        animation++;
        head = 0;
      }
      break;
    case 9:
      EVERY_N_MILLISECONDS(20) {
        if (head < 136) head++;
        if (head == 135) {
          start_time = millis();
        }
      }
      now = millis();
      allBpm136(136, head, 62);
      theaterChase(head, 0, false);
      if (now - start_time > 5000 && head == 136) {
        animation++;
        head = 0;
      }
      break;
    case 10:
      EVERY_N_MILLISECONDS(20) {
        if (head < 136) head++;
        if (head == 135) {
          start_time = millis();
        }
      }
      now = millis();
      theaterChase(136, 0, false);
      theaterChase(head, 0, true);
      if (now - start_time > 5000 && head == 136) {
        animation = 2;
        head = 0;
      }
      break;
    case 11:
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
        case 3:
          color_rgb = CRGB::Blue;
          allArrayFTB(count, color_rgb);
          break;
        case 4:
          color_rgb = CRGB::Green;
          allArrayFTB(count, color_rgb);
          break;
        case 5:
          color_rgb = CRGB::Red;
          allArrayFTB(count, color_rgb);
          break;
      }
      break;
  }
}

bool allColor(CRGB color) {
  for (int i = 0; i < 136; i++) {
    switch (ledArray136[i]) {
      case 1:
        // 0-23
        if (leds_f1[i] != color) return false;
        if (leds_f2[i] != color) return false;
        break;
      case 2:
        if (leds_f[i - 24]  != color) return false;
        break;
      case 3:
        if (leds_b1[i - 24 - 60] != color) return false;
        if (leds_b2[i - 24 - 60] != color) return false;
        break;
      case 4:
        if (leds_s1[i - 24 - 60 - 22] != color) return false;
        if (leds_s2[i - 24 - 60 - 22] != color) return false;
        break;
    }
  }
  return true;
}

void allBpm136(int head, int tail, int bpm)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(bpm, 64, 255);
  for ( int i = tail; i < head; i++) {
    mapTo136(i, ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10)));
  }
}


// FIXME()
void allFillRainbow() {
  fillRainbow(136, 0);
}

void fillRainbow(int head, int tail) {
  fill_rainbow(leds136, 136, gHue, 2);
  for (int i = tail; i < head; i++) {
    mapTo136(i, leds136[map(i, 0, 135, 135, 0)]);
  }
}

void theaterChase(int head, int tail, bool rainbow) {
  allFadeToBlackBy(100);
  for (int i = tail; i < head; i = i + 3) {
    if (i + cycle < head) {
      if (rainbow == true) {
        mapTo136(i + cycle, CHSV(gHue + i, 255, 192));
      } else {
        mapTo136(i + cycle, CRGB::White);
      }
    }
  }
}

void mapTo212(int pos, CRGB color) {
  switch (ledArray212[pos]) {
    case 1:
      leds_f1[pos] = color;
      break;
    case 2:
      leds_f2[pos - 24] = color;
      break;
    case 3:
      leds_f[pos - 24 - 24] = color;
      break;
    case 4:
      leds_b1[pos - 24 - 24 - 60] = color;
      break;
    case 5:
      leds_b2[pos - 24 - 24 - 60 - 22] = color;
      break;
    case 6:
      leds_s1[pos - 24 - 24 - 60 - 22 - 22] = color;
      break;
    case 7:
      leds_s2[pos - 24 - 24 - 60 - 22 - 22 - 30] = color;
      break;
  }
}

void mapTo136(int pos, CRGB color) {
  switch (ledArray136[pos]) {
    case 1:
      leds_f1[map(pos, 0, 23, 23, 0)] = leds_f2[map(pos, 0, 23, 23, 0)] = color;
      break;
    case 2:
      leds_f[map(pos, 24, 83, 0, 59)] = color;
      break;
    case 3:
      leds_b1[map(pos, 84, 105, 0, 21)] = leds_b2[map(pos, 84, 105, 0, 21)] = color;
      break;
    case 4:
      leds_s1[map(pos, 106, 135, 0, 29)] = leds_s2[map(pos, 106, 135, 0, 29)] = color;
      break;
  }
}

void mapTo93(int pos, CRGB color) {
  switch (ledArray93[pos]) {
    case 1:
      leds_f1[map(pos, 0, 23, 23, 0)] += CHSV( gHue, 255, 192);
      leds_f2[map(pos, 0, 23, 23, 0)] += CHSV( gHue, 255, 192);
      break;
    case 2:
      leds_f[map(pos, 24, 50, 22, 48)] += CHSV( gHue, 255, 192);
      leds_f[map(pos, 24, 50, 21,  0)] += CHSV( gHue, 255, 192);
      break;
    case 3:
      for (int i = 0; i < 11; i++) {
        leds_f[map(i, 0, 10, 49, 59)] += CHSV( gHue, 255, 192);
      }
      break;
    case 4:
      leds_b1[map(pos, 52, 62,  0, 10)] += CHSV( gHue, 255, 192);
      leds_b1[map(pos, 52, 62, 21, 11)] += CHSV( gHue, 255, 192);
      leds_b2[map(pos, 52, 62,  0, 10)] += CHSV( gHue, 255, 192);
      leds_b2[map(pos, 52, 62, 21, 11)] += CHSV( gHue, 255, 192);
      break;
    case 5:
      leds_s1[map(pos, 63, 92,  0, 29)] += CHSV( gHue, 255, 192);
      leds_s2[map(pos, 63, 92,  0, 29)] += CHSV( gHue, 255, 192);
      break;
  }
}

void cylon() {
  int gHue = 250; // pink, like my bike
  allFadeToBlackBy(5);
  int j = beatsin8(20, 0, 93);
  for (int pos = j - 1 ; pos < j + 1 ; pos++) {
    if (pos < 0) pos = 0;
    if (pos > 93) pos = 93;
    mapTo93(pos, CHSV(gHue, 255, 192));
  }
}

void allArrayFTB(int pos, CRGB color) {
  int loc = ledArray93[pos];
  switch (loc) {
    case 1:
      //  0-23 -> 1(23-0)
      leds_f1[map(pos, 0, 23, 23, 0)] = leds_f2[map(pos, 0, 23, 23, 0)] = color;
      break;
    case 2:
      // 24-50 -> 2(22-48, 21, 0)
      leds_f[map(pos, 24, 50, 22, 48)] = leds_f[map(pos, 24, 50, 21, 0)] = color;
      break;
    case 3:
      // 51 -> 2(49, 59)
      leds_f[49] = leds_f[59] = color;
      break;
    case 4:
      // 52-56 -> 2(50-54, 58-54)
      // 52-62 -> 3(0-10, 21-11)
      if (pos <= 56) {
        leds_f[map(pos, 52, 56, 50, 54)] = leds_f[map(pos, 52, 56, 58, 54)] = color;
      }
      leds_b1[map(pos, 52, 62, 0, 10)] = leds_b1[map(pos, 52, 62, 21, 11)] = color;
      leds_b2[map(pos, 52, 62, 0, 10)] = leds_b2[map(pos, 52, 62, 21, 11)] = color;
      break;
    case 5:
      // 63-86 -> 4(0-23)
      leds_s1[map(pos, 63, 92, 0, 29)] = leds_s2[map(pos, 63, 92, 0, 29)] = color;
      break;
  }
}

void allArrayBTF(int pos, CRGB color) {
  pos = map(pos, 0, 93, 93 , 0);
  int loc = ledArray93[pos];
  switch (loc) {
    case 1:
      //  0-23 -> 1(23-0)
      leds_f1[map(pos, 0, 23, 23, 0)] = leds_f2[map(pos, 0, 23, 23, 0)] = color;
      break;
    case 2:
      // 24-50 -> 2(22-48, 21-0)
      // 46-50 -> 2(50-54, 58-54))
      if (pos >= 46) {
        leds_f[map(pos, 50, 46, 50, 54)] = leds_f[map(pos, 50, 46, 58, 54)] = color;
      }
      leds_f[map(pos, 24, 50, 22, 48)] = leds_f[map(pos, 24, 50, 21, 0)] = color;
      break;
    case 3:
      // 51 -> 2(49, 59)
      leds_f[49] = leds_f[59] = color;
      break;
    case 4:
      // 52-62 -> 3(0-10, 21-11)
      leds_b1[map(pos, 52, 62, 0, 10)] = leds_b1[map(pos, 52, 62, 21, 11)] = color;
      break;
    case 5:
      leds_s1[map(pos, 63, 92, 0, 29)] = leds_s2[map(pos, 63, 92, 0, 29)] = color;
      break;
  }
}

void audioVuMeter(CRGB color) {
  int level = vuMeter();
  allFadeToBlackBy(240);
  mapToLeds(leds_f1,  0, 23, level, color);
  mapToLeds(leds_f2,  0, 23, level, color);
  mapToLeds(leds_f,   0, 21, level, color);
  mapToLeds(leds_f,  22, 48, level, color);
  mapToLeds(leds_f,  49, 59, level, color);
  mapToLeds(leds_b1,  0, 10, level, color);
  mapToLeds(leds_b1, 11, 22, level, color);
  mapToLeds(leds_b2,  0, 10, level, color);
  mapToLeds(leds_b2, 11, 22, level, color);
  mapToLeds(leds_s1,  0, 29, level, color);
  mapToLeds(leds_s2,  0, 29, level, color);
}

void mapToLeds(CRGB * leds, int first, int last, int peak, CRGB color) {
  fill_rainbow(leds136, 136, gHue, 5);
  // Map the peak to a numbers of LEDs.
  int level = map(peak, 1, 600, -1, last - first + 1);
  // And now color them.
  for (int led = first; led <= first + level; led++)
  {
    leds[led] = leds136[led];
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
  //fadeToBlackBy(leds, num_leds, 192);
}


void allTwinkleMapPixels(int fade) {
  //  fadeToBlackBy( leds, num_leds, 20);
  random16_add_entropy(random());
  for ( uint16_t i = 0; i < 212; i++) {
    if ( ledState212[i] == SteadyDim) {
      // this pixels is currently: SteadyDim
      // so we randomly consider making it start getting brighter
      if ( random16(0, 212) < 1) {
        ledState212[i] = GettingBrighter;
      }

    } else if ( ledState212[i] == GettingBrighter ) {
      // this pixels is currently: GettingBrighter
      // so if it's at peak color, switch it to getting dimmer again
      if ( leds212[i] >= PEAK_COLOR) {
        ledState212[i] = GettingDimmerAgain;
      } else {
        // otherwise, just keep brightening it:
        leds212[i] += CRGB(4, 4, 4);
      }

    } else { // getting dimmer again
      // this pixels is currently: GettingDimmerAgain
      // so if it's back to base color, switch it to steady dim
      if (leds212[i] <= CRGB(0, 0, 0) ) {
        leds212[i] = CRGB(0, 0, 0); // reset to exact base color, in case we overshot
        ledState212[i] = SteadyDim;
      } else {
        // otherwise, just keep dimming it down:
        leds212[i] -= CRGB(fade, fade, fade);
      }
    }
    mapTo212(i, leds212[i]);
  }
}


// Button timing variables
unsigned int debounce = 20; // ms debounce period to prevent flickering when pressing or releasing the button
unsigned int DCgap = 250; // max ms between clicks for a double click event
unsigned int holdTime = 2000; // ms hold period: how long to wait for press+hold event
unsigned int longHoldTime = 5000; // ms long hold period: how long to wait for press+hold event

// Other button variables
boolean buttonVal = HIGH; // value read from button
boolean buttonLast = HIGH; // buffered value of the button's previous state
boolean DCwaiting = false; // whether we're waiting for a double click (down)
boolean DConUp = false; // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true; // whether it's OK to do a single click
long downTime = -1; // time the button was pressed down
long upTime = -1; // time the button was released
boolean ignoreUp = false; // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false; // when held, whether to wait for the up event
boolean holdEventPast = false; // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

int checkButton()
{
  int event = 0;
  // Read the state of the button
  buttonVal = digitalRead(BUTTON_PIN);
  // Button pressed down
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce) {
    downTime = millis();
    ignoreUp = false;
    waitForUp = false;
    singleOK = true;
    holdEventPast = false;
    longHoldEventPast = false;
    if ((millis() - upTime) < DCgap && DConUp == false && DCwaiting == true) DConUp = true;
    else DConUp = false;
    DCwaiting = false;
  }
  // Button released
  else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce) {
    if (not ignoreUp) {
      upTime = millis();
      if (DConUp == false) DCwaiting = true;
      else {
        event = 2;
        DConUp = false;
        DCwaiting = false;
        singleOK = false;
      }
    }
  }
  // Test for normal click event: DCgap expired
  if ( buttonVal == HIGH && (millis() - upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true) {
    event = 1;
    DCwaiting = false;
  }
  // Test for hold
  if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
    // Trigger "normal" hold
    if (not holdEventPast) {
      event = 3;
      waitForUp = true;
      ignoreUp = true;
      DConUp = false;
      DCwaiting = false;
      //downTime = millis();
      holdEventPast = true;
    }
    // Trigger "long" hold
    if ((millis() - downTime) >= longHoldTime) {
      if (not longHoldEventPast) {
        event = 4;
        longHoldEventPast = true;
      }
    }
  }
  buttonLast = buttonVal;
  return event;
}

void buttons() {
  int b = checkButton();
  if (b == 1) {
    mode = 1;
    next_animation++;
    head = 0;
    if (next_animation > NUM_M_ANIMATIONS)
      next_animation = 1;
  }
  if (b == 2) {
    mode++;
    if (mode > 4) mode = 1;
  }
  if (b == 3) {
    mode = 3;
  }
  if (b == 4) {
    mode = 4;
  }
}

//// Snakes
//
//#include <FastLED.h>
//
//#define DATA_PIN 6
//#define BUTTON_PIN 9
//
//int  ledState[144];
//int  ledColor[144];
//int  ledDir[144];
//int  newLedState[144];
//int  newLedColor[144];
//int  newLedDir[144];
//CRGB leds[144];
//
//void setup() {
//  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, 144).setCorrection(TypicalLEDStrip);;
//  FastLED.setBrightness(100);
//  
//  pinMode(BUTTON_PIN, INPUT_PULLUP);
//  digitalWrite(BUTTON_PIN, HIGH);
//}
//
//void loop() {
//    EVERY_N_MILLISECONDS(100) {
//      int led = random16(144);
//      int color = random8(3);
//      int siz = random8(20);
//      int dir = random8(2);
//  
//      ledState[led] = siz;
//      ledColor[led] = color;
//      ledDir[led] = dir;
//    }
////  ledState[40] = 10;
////  ledColor[40] = 0;
////  ledDir[40] = 1;
//
//  for (int i = 0; i < 144; i++) {
//    if (ledState[i] > 0) {
//      if (ledDir[i] == 0) { // The direction of the LED is negative
//        if (i - 1 >= 0)
//          switch (ledColor[i]) {
//            case 0:
//              leds[i - 1].red += 255;
//              break;
//            case 1:
//              leds[i - 1].green += 255;
//              break;
//            case 2:
//              leds[i - 1].blue += 255;
//              break;
//          }
//          newLedColor[i - 1] = ledColor[i];
//          newLedColor[i] = 3;
//          newLedState[i - 1] = ledState[i] - 1;  // Decrease the next pixel count.
//          newLedState[i] = 0;                    // Reset the current pixel.
//          newLedDir[i - 1] = ledDir[i];
//      }
//      if (ledDir[i] == 1) { // The direction of the LED is positive
//        if (i + 1 <= 143) {
//          switch (ledColor[i]) {
//            case 0:
//              leds[i + 1].red += 255;
//              break;
//            case 1:
//              leds[i + 1].green += 255;
//              break;
//            case 2:
//              leds[i + 1].blue += 255;
//              break;
//          }
//          newLedColor[i + 1] = ledColor[i];
//          newLedColor[i] = 3;
//          newLedState[i + 1] = ledState[i] - 1;  // Decrease the next pixel count.
//          newLedState[i] = 0;                    // Reset the current pixel.
//          newLedDir[i + 1] = ledDir[i];
//        }
//      }
//    }
//  }
//  for (int i = 0; i < 144; i++) {
//    ledState[i] = newLedState[i];
//    ledColor[i] = newLedColor[i];
//    ledDir[i] = newLedDir[i];
//  }
//  fadeToBlackBy(leds, 144, 100);
//  FastLED.show();
//  delay(50);
//  //  for (int i = 0; i < 144; i++) {
//  //    leds[i] = CRGB::White;
//  //    FastLED.show();
//  //    leds[i] = CRGB::Black;
//  //  }
//}
//
//CRGB color(int color) {
//  switch (color) {
//    case 0:
//      return CRGB::Red;
//      break;
//    case 1:
//      return CRGB::Green;
//      break;
//    case 2:
//      return CRGB::Blue;
//      break;
//    case 3:
//      return CRGB::Black;
//      break;
//  }
//}
