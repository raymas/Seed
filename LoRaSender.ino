#include <SPI.h>
#include <LoRa.h>
#include <Arduino.h>

// OLED
#include "SSD1306.h"

//ADAFRUIT I2C Adafruit_BMP085 library compatible with BMP180
#include <Adafruit_BMP085.h>

// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

#define SS      18
#define RST     14
#define DI0     26
#define BAND    433E6  //915E6 -- 这里的模式选择中，检查一下是否可在中国实用915这个频段

SSD1306  display(0x3c, 4, 15);

Adafruit_BMP085 bmp;
typedef struct {
  float temperature;
  float pressure;
  float altitude;
  float seaLevelPressure;
} sensor_struct;
sensor_struct * sv;

int counter = 0;

void setup() {
  pinMode(25,OUTPUT); //Send success, LED will bright 1 second
  
  Serial.begin(115200);
  while (!Serial); //If just the the basic function, must connect to a computer
  
  SPI.begin(5,19,27,18);
  LoRa.setPins(SS,RST,DI0);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initial OK!");

  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  getSensorValue(sv);

  //Format is "Temp,Pressure,Altitude,SeaLevelPressure,checksum"
  String payload = String(sv->temperature) + "," + String(sv->pressure) + "," + String(sv->altitude) + "," + String(sv->seaLevelPressure) + ","
  payload += String(checksum(payload));

  display.clear();
  display.drawString(0, 1, "LoRa Sender");
  display.drawString(0, 10, payload;
  display.display();

  // send packet
  LoRa.beginPacket();
  LoRa.print(value);
  LoRa.endPacket();

  counter++;
  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  
  delay(500);
}


void getSensorValue(sensor_struct * sensorValues) {
  sensorValues->temperature = bmp.readTemperature();      // °C
  sensorValues->pressure = bmp.readPressure();         // Pa
  sensorValues->altitude =  bmp.readAltitude();         // m
  sensorValues->seaLevelPressure = bmp.readSealevelPressure(); //Pa
}

int checksum(String s) {
  unsigned int summed = 0;
  for (int c=0; c < s.length; s++) {
    summed += (char)s.charAt(c);
  }
  return summed % 256;
}