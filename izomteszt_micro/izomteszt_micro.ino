#include "HX711.h"
#include<Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int ledPin =  13;      // the number of the LED pin
const int buttonPin = 10;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

int offset=0;
int val;
int analog;
long reading = 0;
int x = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

HX711 scale;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void display0()
{
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.println();
display.println(x);
display.display();
}

void loop() {
if (scale.is_ready()) {
    long reading = scale.read();
    reading=reading-132700;
    reading=reading/640;
    x=reading;
    x=x*5;
    x=x-20;
    x=x*-1;

  } else {
    //Serial.println("HX711 not found.");
  }

  display0();
  delay(10);
}
