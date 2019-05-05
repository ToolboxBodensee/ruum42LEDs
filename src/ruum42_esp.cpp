#include <Arduino.h>
#include <ESP8266WiFi.h>

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include<FastLED.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "ota_update.h"
#include "eeprom_settings.h"

#define URL_Version_Info_Default "http://releases.tbbs.me/firmware/ruum42/version"
#define URL_Firmware_Default "http://releases.tbbs.me/firmware/ruum42/nodemcuv2.bin"

// Which pin on the MCU is connected to the NeoPixels?
//#define NODEMCU
#ifndef NODEMCU
#define PIN D5
//#define ON_SWITCH
#else
#define PIN D1
#define ON_SWITCH D5
#endif

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 135

static uint8_t hue;
CRGBArray<NUMPIXELS> leds;

#include "led_big_animation.h"

//This is running on a nodeMCU V1.0 ESP12E or wemos d1 mini

eepromData_t cfg;
HTTPClient http;

void onFirmwareUpdateDone(unsigned int newVersion)
{
    //update was done, save new version number
    cfg.firmwareVer = newVersion;
    saveConfig(cfg);
}

void setup()
{
    loadConfig(cfg);
    if (cfg.initialized != 1)
    {
        //not initialized
        cfg.initialized = 1;
        strncpy(cfg.SSID, "<ssid>", sizeof("<ssid>"));
        strncpy(cfg.password, "<password>", sizeof("<password>"));
        cfg.firmwareVer = 0;
        strncpy(cfg.version_info_url, URL_Version_Info_Default, sizeof(URL_Version_Info_Default));
        strncpy(cfg.version_update_url, URL_Firmware_Default, sizeof(URL_Firmware_Default));
        cfg.debug = 1;
        saveConfig(cfg);
    }

    Serial.begin(115200);
    Serial.println("");
    Serial.println("Start");
    WiFi.mode(WIFI_STA);
    WiFi.begin(cfg.SSID, cfg.password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("O");
    }                                     // Verbunden
    Serial.println("");
    Serial.println("Verbunden");

    OTA_CONFIG ota_config = {
        .version = cfg.firmwareVer,
        .check_url = cfg.version_info_url,
        .binary_url = cfg.version_update_url,
        .debug = (bool) cfg.debug,
    };

    FirmwareUpdate(ota_config, &onFirmwareUpdateDone);

    //FastLed init
    FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMPIXELS);
    //switch init
    pinMode(ON_SWITCH, INPUT_PULLUP);
}

void loop()
{
    led_big_annimation();
}
