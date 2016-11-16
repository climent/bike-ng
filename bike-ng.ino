// Bike LEDs for burning man.
// bike-ng.ino

#include <FastLED.h>
#include <EEPROM.h>

#include "tunables.h"
#include "ledconfig.h"
#include "buttons.h"
#include "ledmaps.h"
#include "palettes.h"
#include "mappingfunctions.h"
#include "audiov2.h"
#include "effects.h"

typedef void (*functionList)(); // definition for list of effect function pointers

functionList effectList[] = {
  swipe,
  blinker,
  fillRainbow,
  audioVuMeter,
  allTwinkleMapPixels,
  cylon,
  allBpm136,
  allBpm136Audio,
  theaterChase,
  allFillRainbowWithGlitter,
  draft,
};

const byte numEffects = (sizeof(effectList) / sizeof(effectList[0]));

void setup() {
  delay(2000);
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F1>(leds_f1, NUM_LEDS_F1).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F2>(leds_f2, NUM_LEDS_F2).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_F >(leds_f,  NUM_LEDS_F ).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_B1>(leds_b1, NUM_LEDS_B1).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_B2>(leds_b2, NUM_LEDS_B2).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_S1>(leds_s1, NUM_LEDS_S1).setCorrection(TypicalLEDStrip);;
  FastLED.addLeds<NEOPIXEL, DATA_PIN_S2>(leds_s2, NUM_LEDS_S2).setCorrection(TypicalLEDStrip);;
  FastLED.setBrightness(100);

  // Initialize pixel state to SteadyDim:
  memset(ledState212, SteadyDim, 212);

  // Initialize the button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(BUTTON_PIN, HIGH);

  Serial.begin(9600); // USB is always 12 Mbit/sec

  // check to see if EEPROM has been used yet
  // if so, load the stored settings
  byte eepromWasWritten = EEPROM.read(0);
  if (eepromWasWritten == 99) {
    currentEffect =     EEPROM.read(1);
    autoCycle =         EEPROM.read(2);
    currentBrightness = EEPROM.read(3);
    //randomizedEffect =  EEPROM.read(4);
    paletteN =          EEPROM.read(5);
    randomPalette =     EEPROM.read(6);
  }
  if (currentEffect > (numEffects - 1)) currentEffect = 0;

  // set global brightness value
  FastLED.setBrightness( scale8(currentBrightness, MAXBRIGHTNESS) );
}

bool initial = true;

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

  random16_add_entropy(random8());
  now = millis();

  if (autoCycle == true && now - lastCycle > cycleTime) nextEffect();

  buttons();

  if (configMode) {
    configBlinker();
  } else {
    switch (mode) {
      case 1:
        everyCycle();
        break;
      case 99:
        fader = 50;
        fadeToBlack();
        break;
    }
  }

  FastLED.show();
  checkEEPROM();
}

void everyCycle() {
  if (autoCycle == true && now - lastCycle > cycleTime) nextEffect();
  setPalette();

  if (fadeAll == true) {
    fader = 10;
    fadeToBlack();
    if (allColor(CRGB::Black)) {
      fadeAll = false;
      lastCycle = millis();
    }
  } else {
    // Make sure the headMax stays in boundaries, and set a default if it is 0.
    if (headMax >= 136 || headMax == 0) headMax = 136;
    // FIXME(): add increaseHead(0/1) and increaseHeadDelay(millis) as parameters.
    if (head < headMax) head++;
    effectList[currentEffect]();
  }
}

void nextEffect() {
  if (randomizedEffect == false) {
    currentEffect++;
    if (currentEffect > (numEffects - 1)) currentEffect = 0;
  } else {
    currentEffect = random16(numEffects);
  }
  effectInit = false;
  // FIXME(): move the defaults of the effects here.
  // reset the headMax, let the individual effects set something different
  headMax = 136;
  lastCycle = millis();
}

void buttons() {
  int singleClick = checkButton();
  switch (singleClick) {
    case 1:
      if (configMode) {
        currentBrightness += 51; // increase the brightness (wraps to lowest)
        for (int i = 0; i < 59; i++) leds_f[i] = CRGB::Red;
        for (int i = 0; i < 21; i++) leds_b1[i] = leds_b2[i] = CRGB::Red;
        for (int i = 0; i < scale8(currentBrightness, 30); i++) leds_s1[i] = leds_s2[i] = CRGB::Red;
        FastLED.show();
        delay(100);
        FastLED.setBrightness(scale8(currentBrightness, MAXBRIGHTNESS));
        for (int i = 0; i < 59; i++) leds_f[i] = CRGB::Red;
        for (int i = 0; i < 21; i++) leds_b1[i] = leds_b2[i] = CRGB::Red;
        for (int i = 0; i < scale8(currentBrightness, 30); i++) leds_s1[i] = leds_s2[i] = CRGB::Red;
      } else {
        nextEffect();
      }
      break;
    case 2:
      if (configMode) {
        randomPalette = not randomPalette;
        if (randomPalette) {
          for (int i = 48; i < 212; i++) mapTo212(i, CRGB::Blue);
        } else {
          for (int i = 48; i < 212; i++) mapTo212(i, CRGB::Cyan);
        }
      } else {
        autoCycle = not autoCycle;
      }
      break;
    case 3:
      mode = 100 - mode;
      break;
    case 4:
      configMode = not configMode;
      break;
  }
}

// write EEPROM value if it's different from stored value
void updateEEPROM(byte location, byte value) {
  if (EEPROM.read(location) != value) EEPROM.write(location, value);
}

// Write settings to EEPROM if necessary
void checkEEPROM() {
  if (eepromOutdated) {
    if (now - eepromMillis > EEPROMDELAY) {
      updateEEPROM(0, 99);
      updateEEPROM(1, currentEffect);
      updateEEPROM(2, autoCycle);
      updateEEPROM(3, currentBrightness);
      updateEEPROM(4, randomizedEffect);
      updateEEPROM(5, paletteN);
      updateEEPROM(6, randomPalette);
      eepromOutdated = false;
    }
  }
}
