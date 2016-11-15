// set a global palette storage and default it to rainbow colors
CRGBPalette16 currentPalette(RainbowColors_p); // global palette storage
// options: LINEARBLENDING | NOBLEND
TBlendType    currentBlending = LINEARBLEND;

void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
}

void setPalette() {
  switch (paletteN) {
    case 0:
      currentPalette = CloudColors_p;
      break;
    case 1:
      currentPalette = LavaColors_p;
      break;
    case 2:
      currentPalette = OceanColors_p;
      break;
    case 3:
      SetupBlackAndWhiteStripedPalette();
      break;
    case 4:
      currentPalette = ForestColors_p;
      break;
    case 5:
      currentPalette = RainbowColors_p;
      break;
    case 6:
      currentPalette = PartyColors_p;
      break;
    case 7:
      currentPalette = HeatColors_p;
      break;
    case 8:
      currentPalette = CRGBPalette16(CRGB::Red, CRGB::Orange, CRGB::Gray);
      break;
    case 9:
      currentPalette = CRGBPalette16(CRGB::Blue, CRGB::Red, CRGB::Red);
      break;
    case 10:
      currentPalette = CRGBPalette16(CRGB::LightGrey, CRGB::MidnightBlue, CRGB::Black);
      break;
    case 11:
      currentPalette = CRGBPalette16(CRGB::DarkGreen, CRGB::PaleGreen);
      break;
    case 12:
      currentPalette = CRGBPalette16(CRGB::White, CRGB::White);
      break;
    default:
      currentPalette = RainbowColors_p;
      break;
  }
}

void cyclePalette() {
  paletteN++;
  if (paletteN > 11) paletteN = 0;
  setPalette();
}

void selectRandomPalette() {
  paletteN = random16(12);
  setPalette();
}

void selectPalette() {
  if (randomPalette) {
    selectRandomPalette();
  }
}

