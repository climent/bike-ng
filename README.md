# bike-ng
   The bike LEDs are composed of 7 strips:
   * 2x 24 LED strips in the front fork, top to bottom
   * 1x 60 LED strip in the frame, divided in
     - 22 LEDs, from the base of the saddle post to the headset
     - 27 LEDs, from the headset to the bottom bracket, and
     - 11 LEDs, from the bottom bracket back to the sit post
   * 1x 22 LED strip, divided in 2x 11 LED sections
     - 11 LEDs, from the bottom bracket to the dropouts
     - 11 LEDs, from the bottom of the base of the saddle post to the dropouts
   * 2x 30 LED strips from the dropouts upwards, in the sissy bar.

# This new release removes old functionality but implements:
   * a simpler interface
   * single button config option, including brightness levels and random palettes
   * many many more effects
   * palette integration
   * no demo mode, but a cycle mode that moves from effect to effect
   * state is saved across reboots using EEPROM memory
   * audio integration with a MAX9814 adafruit mic
   * all the effects allow an initialization function

# TODO:
   * define a better effect interface to allow init() and finally() as before and after running the effect
