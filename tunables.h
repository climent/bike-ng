//* Tunable knobs to change the behavior of the animations
#define cycleTime 5000

#define MAXBRIGHTNESS 192
#define STARTBRIGHTNESS 63

// Whether to use the OLED screen. Affects the definitions of display functions.
#define USE_OLED 1

byte currentBrightness = STARTBRIGHTNESS; // 0-255 will be scaled to 0-MAXBRIGHTNESS

// Time after changing settings before settings are saved to EEPROM
#define EEPROMDELAY 2000

//* Variables that we need in order to run
uint8_t count =     0;
uint8_t color =     0;
uint8_t gHue =      0;
uint8_t cycle =     0;
uint8_t head =      0;
uint8_t headMax =   0;
uint8_t tailMax =   0;
uint8_t tail =      0;
uint8_t mode =      1;
uint8_t animation = 1;
uint8_t fader =     0;
uint8_t twinkle =   2;
uint8_t bpm =      62;

byte paletteN;

fract8 chanceOfGlitter = 100;

uint8_t currentEffect;
uint8_t currentConfig = 0;
uint8_t buttonClick;

bool autoCycle        = true; // flag for automatic effect changes
bool increaseHead     = false;
bool effectInit       = true;;
bool randomizedEffect = false;
bool rainbow;
bool fadeAll          = false;
bool eepromOutdated;
bool randomPalette    = true;
bool configMode       = false;

unsigned long now;
unsigned long lastCycle = millis();
unsigned long eepromMillis;

// Definitions for twinkles.
#define PEAK_COLOR CRGB(100,100,100)
int ledState212[212];
enum {SteadyDim, GettingBrighter, GettingDimmerAgain};
