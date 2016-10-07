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
#define NUM_LEDS_S1 24
#define DATA_PIN_S2 11
#define NUM_LEDS_S2 24

int ledArray87[87] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                      3,
                      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
                     };

int ledArray130[130] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
                       };

CRGB leds130[130];

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
  //  FastLED.setBrightness(100);

  // Initialize the button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(BUTTON_PIN, HIGH);

}

int     count = 0;
int     color = 0;
uint8_t gHue =  0;
CRGB    color_rgb = CRGB::Blue;
CHSV    color_hsv;
int     cycle = 0;
unsigned long start_time;
unsigned long now;
uint16_t showtime = 2000;

int NUM_F_ANIMATIONS = 5;
int f_animation = 1;
int MODES = 2;
int mode = 1;
bool auto_transition = true;
bool skip_transitions = false;
int head = 0;

void loop() {
  EVERY_N_MILLISECONDS( 100 ) {
    cycle++;
    if (cycle == 3) {
      cycle = 0;
    }
  }
  EVERY_N_MILLISECONDS( 5 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
  EVERY_N_MILLISECONDS( 1 ) {
    if (count < 87) {
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
      mode1();
      break;
  }
  FastLED.show();
  buttons();
}

void mode1() {
  switch (f_animation) {
    case 1:
      // transition
      if (allColor(CRGB::Black) && skip_transitions == false) {
        allFadeToBlackBy(50);
      } else {
        head = 0;
        f_animation++;
      }
      break;
    case 2:
      // transition
      if (skip_transitions == true) {
        head = 130;
        f_animation++;
      }
      EVERY_N_MILLISECONDS(100) {
        if (head < 130) head++;
        if (head == 129) start_time = millis();
      }
      allFillRainbow(head, 0);
      break;
    case 3:
      now = millis();
      head = 130;
      if (now - start_time > showtime && auto_transition) {
        f_animation++;
        start_time = millis();
      }
      allFillRainbow(head, 0);
      break;
    case 4:
      theaterChase(head, 0, false);
      break;
    case 5:
      allAddGlitterBy(80);
      break;
    case 6:
      cylon();
      break;
    case 10:
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
          //    case 3:
          //      color_rgb = CRGB::Blue;
          //      allArrayFTB(count, color_rgb);
          //      break;
          //    case 4:
          //      color_rgb = CRGB::Green;
          //      allArrayFTB(count, color_rgb);
          //      break;
          //    case 5:
          //      color_rgb = CRGB::Red;
          //      allArrayFTB(count, color_rgb);
          //      break;
      }
    case 200:
      audioVuMeter(color_rgb);
      break;
  }
}

bool allColor(CRGB color) {
  for (int i = 0; i < 130; i++) {
    switch (ledArray130[i]) {
      case 1:
        // 0-23
        if (leds_f1[i] != color) return false;
        if (leds_f2[i] != color) return false;
        break;
      case 2:
        if (leds_f[i] != color) return false;
        break;
      case 3:
        if (leds_b1[i] != color) return false;
        if (leds_b2[i] != color) return false;
        break;
      case 4:
        if (leds_s1[i] != color) return false;
        if (leds_s2[i] != color) return false;
        break;
    }
  }
  return true;
}

void allBpm130(int head, int tail, int bpm)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(bpm, 64, 255);
  for ( int i = 0; i < head; i++) {
    allFill130(i, ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10)));
  }
}

void allFillRainbow(int head, int tail) {
  fill_rainbow(leds130, 130, gHue, 5);
  for (int i = tail; i < head; i++) {
    allFill130(i, leds130[i]);
  }
}

void theaterChase(int head, int tail, bool rainbow) {
  allFadeToBlackBy(100);
  for (int i = tail; i < head; i = i + 3) {
    if (i + cycle < head) {
      if (rainbow == true) {
        allFill130(i + cycle, CHSV(gHue + i, 255, 192));
      } else {
        allFill130(i + cycle, CRGB::White);
      }
    }
  }
}

void allFill130(int pos, CRGB color) {
  switch (ledArray130[pos]) {
    case 1:
      // 0-23
      leds_f1[map(pos, 0, 23, 23, 0)] = leds_f2[map(pos, 0, 23, 23, 0)] = color;
      break;
    case 2:
      leds_f[map(pos, 24, 83, 0, 59)] = color;
      break;
    case 3:
      leds_b1[map(pos, 84, 105, 0, 21)] = leds_b2[map(pos, 84, 105, 0, 21)] = color;
      break;
    case 4:
      leds_s1[map(pos, 106, 129, 0, 23)] = leds_s2[map(pos, 106, 129, 0, 23)] = color;
      break;
  }
}

void cylon() {
  int gHue = 250; // pink, like my bike
  allFadeToBlackBy(5);
  int j = beatsin8(20, 0, 87);
  for (int pos = j - 1 ; pos < j + 1 ; pos++) {
    if (pos < 0) pos = 0;
    if (pos > 87) pos = 87;
    int loc = ledArray87[pos];
    int b1_pos;
    int f_pos;
    switch (loc) {
      case 1:
        leds_f1[map(pos, 0, 23, 23, 0)] += CHSV( gHue, 255, 192);
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
        break;
      case 5:
        leds_s1[map(pos, 63, 86,  0, 23)] += CHSV( gHue, 255, 192);
        break;
    }
  }
}

void allArrayFTB(int pos, CRGB color) {
  int loc = ledArray87[pos];
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
      leds_s1[map(pos, 63, 86, 0, 23)] = leds_s2[map(pos, 63, 86, 0, 23)] = color;
      break;
  }
}
void allArrayBTF(int pos, CRGB color) {
  pos = map(pos, 0, 87, 87 , 0);
  int loc = ledArray87[pos];
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
      leds_s1[map(pos, 63, 86, 0, 23)] = leds_s2[map(pos, 63, 86, 0, 23)] = color;
      break;
  }
}

void audioVuMeter(CRGB color) {
  int level = vuMeter();
  allFadeToBlackBy(192);
  mapToLeds(leds_f1,  0, 23, level, color);
  mapToLeds(leds_f,   0, 21, level, color);
  mapToLeds(leds_f,  22, 48, level, color);
  mapToLeds(leds_f,  49, 59, level, color);
  mapToLeds(leds_b1,  0, 10, level, color);
  mapToLeds(leds_b1, 11, 22, level, color);
  mapToLeds(leds_s1,  0, 23, level, color);
}

void mapToLeds(CRGB * leds, int first, int last, int peak, CRGB color) {
  fill_rainbow(leds130, 130, gHue, 5);
  // Map the peak to a numbers of LEDs.
  int level = map(peak, 1, 600, -1, last - first + 1);
  // And now color them.
  for (int led = first; led <= first + level; led++)
  {
    leds[led] = leds130[led];
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


void buttons() {
  int b = checkButton();
  if (b == 1) {
    f_animation++;
    if (f_animation > NUM_F_ANIMATIONS)
      f_animation = 1;
  }

  if (b == 2) {
    mode++;
    if (mode > MODES)
      mode = 1;
  }
  //  if (b == 3) {
  //    f_animation = 50;
  //    b_animation = 50;
  //  }
    if (b == 4) {
      f_animation = 200;
    }
}


// Button timing variables
int debounce = 20; // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250; // max ms between clicks for a double click event
int holdTime = 2000; // ms hold period: how long to wait for press+hold event
int longHoldTime = 5000; // ms long hold period: how long to wait for press+hold event

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
