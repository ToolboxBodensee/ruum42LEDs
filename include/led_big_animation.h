void snake(int durchlauf, int zeit, int aus) {
  int anzahl = 0;
  do {
    ++anzahl;
    for (int i = 0; i < NUMPIXELS; i++) {
      leds.fadeToBlackBy(aus);
      leds[i] = CHSV(hue++, 255, 255);
      FastLED.show();
      if (digitalRead(ON_SWITCH) == HIGH) return;
      delay(zeit);
    }
  } while (anzahl < durchlauf);
}

void richtng2(int durchlauf, int zeit, int aus) {
  int anzahl = 0;
  do {
    ++anzahl;
    for (int i = 0; i < NUMPIXELS / 2; i++) {
      leds.fadeToBlackBy(aus);
      leds[i] = CHSV(hue++, 255, 255);
      leds[i + NUMPIXELS / 2] = CHSV(hue++, 255, 255);
      FastLED.show();
      if (digitalRead(ON_SWITCH) == HIGH) return;
      delay(zeit);
    }
  } while (anzahl < durchlauf);
}

void richtng(int durchlauf, int zeit, int aus) {
  int anzahl = 0;
  do {
    ++anzahl;
    for (int i = 0; i < NUMPIXELS / 2; i++) {
      leds.fadeToBlackBy(aus);
      leds[i] = CHSV(hue++, 255, 255);
      leds[NUMPIXELS - 5 - i] = CHSV(hue++, 255, 255);
      FastLED.show();
      if (digitalRead(ON_SWITCH) == HIGH) return;
      delay(zeit);
    }
  } while (anzahl < durchlauf);
}

void farbe(int durchlauf, int zeit) {
  int anzahl = 0;
  int color = 40;
  do {
    ++anzahl;
    ++color;
    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i] = CHSV(color, 255, 255);
    }
    FastLED.show();
    if (digitalRead(ON_SWITCH) == HIGH) return;

    delay(zeit);
  } while (anzahl < durchlauf);
}

void rainbow(int durchlauf, int zeit) {
  int anzahl = 0;
  do {
    ++anzahl;
    fill_rainbow(leds, NUMPIXELS, --hue + 5, 5);
    FastLED.show();
    if (digitalRead(ON_SWITCH) == HIGH) return;

    delay(zeit);
  } while (anzahl < durchlauf * 10);
}

void led_big_annimation() {
  Serial.print("Switch position: ");
  Serial.println(digitalRead(ON_SWITCH));
  if (digitalRead(ON_SWITCH) == LOW) {
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
    delay(100);
  }
}
