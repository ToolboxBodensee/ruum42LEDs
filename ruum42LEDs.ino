#include<FastLED.h>
#define NUM_LEDS 135

int OnSwitch = 3;

static uint8_t hue;
CRGBArray<NUM_LEDS> leds;

void setup() {
  FastLED.addLeds<NEOPIXEL, 5>(leds, NUM_LEDS);
  pinMode(OnSwitch, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(OnSwitch) == LOW) {
    farbe(1000, 10);
    rainbow(100, 10);
    richtng(2, 20, 4);
    richtng(5, 5, 30);
    richtng2(4, 10, 1);
    richtng2(4, 20, 80);
    richtng(4, 20, 1);
    snake(1, 30, 4);
    snake(2, 2, 80);
    snake(2, 10, 4);
    snake(4, 30, 4);
  }
  else {
    leds.fadeToBlackBy(255);
    FastLED.show();
  }
}

void snake(int durchlauf, int zeit, int aus) {
  int anzahl = 0;
  do {
    anzahl = anzahl + 1;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.fadeToBlackBy(aus);
      leds[i] = CHSV(hue++, 255, 255);
      FastLED.show();
      if (digitalRead(OnSwitch) == HIGH) {
        anzahl = durchlauf;
        i = NUM_LEDS;
      }
      delay(zeit);
    }
  } while (anzahl < durchlauf);
}

void richtng2(int durchlauf, int zeit, int aus) {
  int anzahl = 0;
  do {
    anzahl = anzahl + 1;
    for (int i = 0; i < NUM_LEDS / 2; i++) {
      leds.fadeToBlackBy(aus);
      leds[i] = CHSV(hue++, 255, 255);
      leds[i + NUM_LEDS / 2] = CHSV(hue++, 255, 255);
      FastLED.show();
      if (digitalRead(OnSwitch) == HIGH) {
        anzahl = durchlauf;
        i = NUM_LEDS / 2;
      }
      delay(zeit);
    }
  } while (anzahl < durchlauf);
}

void richtng(int durchlauf, int zeit, int aus) {
  int anzahl = 0;
  do {
    anzahl = anzahl + 1;
    for (int i = 0; i < NUM_LEDS / 2; i++) {
      leds.fadeToBlackBy(aus);
      leds[i] = CHSV(hue++, 255, 255);
      leds[NUM_LEDS - 5 - i] = CHSV(hue++, 255, 255);
      FastLED.show();
      if (digitalRead(OnSwitch) == HIGH) {
        anzahl = durchlauf;
        i = NUM_LEDS / 2;
      }
      delay(zeit);
    }
  } while (anzahl < durchlauf);
}

void farbe(int durchlauf, int zeit) {
  int anzahl = 0;
  int color = 40;
  do {
    anzahl = anzahl + 1;
    color = color + 1;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(color, 255, 255);
    }
    FastLED.show();
    if (digitalRead(OnSwitch) == HIGH) {
      anzahl = anzahl + durchlauf;
    }
    delay(zeit);
  } while (anzahl < durchlauf);
}

void rainbow(int durchlauf, int zeit) {
  int anzahl = 0;
  do {
    anzahl = anzahl + 1;
    fill_rainbow(leds, NUM_LEDS, --hue + 5, 5);
    FastLED.show();
    if (digitalRead(OnSwitch) == HIGH) {
      anzahl = anzahl + durchlauf * 10;
    }
    delay(zeit);
  } while (anzahl < durchlauf * 10);
}

