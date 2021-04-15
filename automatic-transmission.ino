#include "Adafruit_VL53L0X.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN     5
#define LED_COUNT   5
#define START_OF_RANGE 10
#define END_OF_RANGE 20
#define HANDLE_OFFSET 15
#define PIN_PHOTO_SENSOR A0

const int colors[] = {
  0xFF0000, //P(красный)
  0x009AFF, //R(синий)
  0xFF0000, //N(красный)
  0xFFFF00, //D(желтый)
  0x52FF00, //2(зеленый)
  0xFFD700  //1(золотой)
  };
  
Adafruit_VL53L0X rangeFinder = Adafruit_VL53L0X();
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  rangeFinder.begin();
  strip.begin();                     
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  int photoSensorVal = analogRead(PIN_PHOTO_SENSOR);
  int ledBrightness = map(photoSensorVal, 0, 1023, 0, 255);
  strip.setBrightness(ledBrightness);
  
  int startOfRange = START_OF_RANGE;
  int endOfRange = END_OF_RANGE;

  if (measure.RangeStatus != 4) {
    int range = measure.RangeMilliMeter;
    for (int activeColor = 0; activeColor < LED_COUNT; activeColor++) {
      if (range > startOfRange && range <= endOfRange) {        
        strip.setPixelColor(activeColor, colors[activeColor]);
        break;
      }
      startOfRange += HANDLE_OFFSET;
      endOfRange += HANDLE_OFFSET;
    }
  }
  
  strip.show();  

  delay(500);
}
