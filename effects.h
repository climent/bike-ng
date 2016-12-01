void addGlitter(CRGB * leds, uint8_t num_leds) {
  if ( random8() < chanceOfGlitter) {
    leds[random16(num_leds)] += CRGB::White;
  }
}

void allAddGlitterBy() {
  addGlitter(leds_f1, NUM_LEDS_F1);
  addGlitter(leds_f2, NUM_LEDS_F2);
  addGlitter(leds_f,  NUM_LEDS_F);
  addGlitter(leds_b1, NUM_LEDS_B1);
  addGlitter(leds_b2, NUM_LEDS_B2);
  addGlitter(leds_s1, NUM_LEDS_S1);
  addGlitter(leds_s2, NUM_LEDS_S2);
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

void fadeToBlack() {
  if (effectInit == false) {
    effectInit = true;
  }
  if (fader == -1) fader = 100;
  allFadeToBlackBy(fader);
}

void theaterChase() {
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    if (rainbow) {
      currentPalette = RainbowColors_p;
    } else {
      selectPalette();
    }
  }
  allFadeToBlackBy(100);
  for (int i = tail; i < head; i = i + 3) {
    if (i + cycle < head) {
      //      mapTo136(i + cycle, CHSV(gHue + i, 255, 192));
      //      mapTo136(i + cycle, CRGB::White);
      mapTo136(i + cycle, ColorFromPalette(currentPalette, gHue + (i * 2), currentBrightness));
    }
  }
}

void cylon() {
  if (effectInit == false) {
    effectInit = true;
    fadeAll = true;
  }
  //  int gHue = 250; // pink, like my bike
  allFadeToBlackBy(5);
  int j = beatsin8(20, 0, 92);
  //  display.println(j);
  //  display.display();
  for (int pos = j - 1 ; pos < j + 1 ; pos++) {
    constrain(pos, 0, 92);
    mapTo93(pos, CHSV(gHue, 255, 192));
  }
}

void allTwinkleMapPixels() {
  if (effectInit == false) {
    effectInit = true;
    fadeAll = true;
    head = 0;
    tail = 0;
    for (int i = 0; i < 212 ; i++) {
      ledState212[i] = SteadyDim;
      leds212[i] = CRGB(0, 0, 0);
    }
  }
  if (fadeAll == false) {
    random16_add_entropy(random8());
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
          leds212[i] -= CRGB(twinkle, twinkle, twinkle);
        }
      }
      mapTo212(i, leds212[i]);
    }
  }
}

void fillRainbow() {
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    fadeAll = true;
  }
  fill_rainbow(leds136, 136, gHue, 2);
  for (int i = tail; i < head; i++) {
    mapTo136(i, leds136[map(i, 0, 135, 135, 0)]);
  }
}

void allFillRainbow() {
  head = 136;
  tail = 0;
  fillRainbow();
}


void allFillRainbowWithGlitter() {
  fillRainbow();
  fadeToBlack();
  allAddGlitterBy();
}

void allBpm136Audio()
{
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    fadeAll = true;
    selectPalette();
  }
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  audioRead();
  uint8_t beat = beatsin8(bpm, 64, 255);
  for (int i = tail; i < head; i++) {
    mapTo136(i, ColorFromPalette(currentPalette, gHue + (i * 2), beat - map(spectrumDecay, 1, 600, 0, 255) - (i * 10)));
  }
}

void allBpm136()
{
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    fadeAll = true;
    selectPalette();
  }
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t beat = beatsin8(bpm, 64, 255);
  for (int i = tail; i < head; i++) {
    mapTo136(i, ColorFromPalette(currentPalette, gHue + (i * 2), beat - gHue + (i * 10)));
  }
}

void audioVuMeter() {
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    fadeAll = true;
    selectPalette();
  }
  if (fadeAll == false) {
    audioRead();
    fader = 100;
    //  fadeToBlack();
    //  mapAudioToAllLeds(spectrumDecay);
    mapAudio(spectrumDecay);
  }
}

void swipe() {
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    fadeAll = true;
    selectPalette();
  }
  headMax = 93;
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  for (int i = tail; i < head; i++) {
    allArrayFTB(i, ColorFromPalette(currentPalette, gHue + (i * 2), currentBrightness));
  }
}

void blinker() {
  if (effectInit == false) {
    effectInit = true;
    fadeAll = true;
    fader = 10;
    tail = 0;
    head = 0;
  }
  EVERY_N_SECONDS(2) {
    for (int i = 0; i < 212; i++) {
      mapTo212(i, CRGB::White);
    }
  }
  fader = 10;
  fadeToBlack();
}

void configBlinker() {
  EVERY_N_SECONDS(1) {
    for (int i = 0; i < 48; i++) mapTo212(i, CRGB::White);
  }
  FastLED.show();
  fader = 10;
  fadeToBlack();
}

void draft() {
  if (effectInit == false) {
    effectInit = true;
    head = 0;
    tail = 0;
    increaseHead = true;
    fadeAll = true;
    selectPalette();
  }
  headMax = 93;
  tailMax = 93;
  if (tail == tailMax) head = tail = 0;
  if (head >= 10) if (tail < tailMax) tail++;
  fader = 255;
  fadeToBlack();
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  for (int i = tail; i < head; i++) {
    allArrayFTB(i, ColorFromPalette(currentPalette, gHue + (i * 2), currentBrightness));
  }
}


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
