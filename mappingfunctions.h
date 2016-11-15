// mappingfunctions.h

void mapTo212(int pos, CRGB color) {
  switch (ledArray212[pos]) {
    case 1:
      leds_f1[pos] = color;
      break;
    case 2:
      leds_f2[pos - 24] = color;
      break;
    case 3:
      leds_f[pos - 48] = color;
      break;
    case 4:
      leds_b1[pos - 108] = color;
      break;
    case 5:
      leds_b2[pos - 130] = color;
      break;
    case 6:
      leds_s1[pos - 152] = color;
      break;
    case 7:
      leds_s2[pos - 182] = color;
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
      // 63-86 -> 4(0-29)
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

#define analyzerFadeFactor 5
#define analyzerScaleFactor 2
#define analyzerPaletteFactor 2

CRGB getColor(int peak, int numleds, int delta) {
  const float yScale = 255.0 / numleds;
  int senseValue = peak / analyzerScaleFactor - yScale * (numleds - 1 - delta);

  int pixelBrightness = senseValue * analyzerFadeFactor;
  if (pixelBrightness > 255) pixelBrightness = 255;
  if (pixelBrightness < 0) pixelBrightness = 0;

  int pixelPaletteIndex = senseValue / analyzerPaletteFactor - 15;
  if (pixelPaletteIndex > 240) pixelPaletteIndex = 240;
  if (pixelPaletteIndex < 0) pixelPaletteIndex = 0;

  CRGB pixelColor = ColorFromPalette(currentPalette, pixelPaletteIndex, pixelBrightness, currentBlending);

  return pixelColor;
}

void mapAudio(int peak) {
  //  fill_rainbow(leds136, 136, gHue, 5);
  //  SelectRandomPalete();
  for (int i = 0; i < 136; i++) {
    switch (ledArray136[i]) {
      case 1:
        mapTo136(23 - i, getColor(peak, 24, i));
        break;
      case 2:
        if (i > 23 && i < 46) mapTo136(i, getColor(peak, 23, i - 23));
        if (i > 45 && i < 73) mapTo136(i, getColor(peak, 27, i - 46));
        if (i > 72 && i < 84) mapTo136(156 - i, getColor(peak, 11, i - 73));
        break;
      case 3:
        mapTo136(i, getColor(peak, 22, i - 84));
        break;
      case 4:
        mapTo136(136 - i + 105, getColor(peak, 30, i - 106));
        break;
    }
  }
}

void mapAudioToLeds(CRGB * leds, int first, int last, int peak) {
  // FIXME(): use a palette, instead of a fixed rainbow color schema
  fill_rainbow(leds136, 136, gHue, 5);
  // Map the peak to a numbers of LEDs.
  int level = map(peak, 1, 600, -1, last - first + 1);
  // And now color them.
  for (int led = first; led <= first + level; led++)
  {
    leds[led] = leds136[led];
  }
}

void mapAudioToAllLeds(int level) {
  mapAudioToLeds(leds_f1,  0, 23, level);
  mapAudioToLeds(leds_f2,  0, 23, level);
  mapAudioToLeds(leds_f,   0, 21, level);
  mapAudioToLeds(leds_f,  22, 48, level);
  mapAudioToLeds(leds_f,  49, 59, level);
  mapAudioToLeds(leds_b1,  0, 10, level);
  mapAudioToLeds(leds_b1, 11, 22, level);
  mapAudioToLeds(leds_b2,  0, 10, level);
  mapAudioToLeds(leds_b2, 11, 22, level);
  mapAudioToLeds(leds_s1,  0, 29, level);
  mapAudioToLeds(leds_s2,  0, 29, level);
}

