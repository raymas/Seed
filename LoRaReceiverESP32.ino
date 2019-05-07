#include <SPI.h>
#include <LoRa.h>
#include "SSD1306.h"


// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

// LORA paramters must be the same as the sender
#define SS      18
#define RST     14
#define DI0     26
#define BAND    433E6

SSD1306  display(0x3c, 4, 15);

String v = "";

void setup() {
  Serial.begin(115200);
  // while (!Serial); //if just the the basic function, must connect to a computer
  delay(1000);

  
  Serial.println("LoRa Receiver"); 
  
  SPI.begin(5,19,27,18);
  LoRa.setPins(SS,RST,DI0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa init completed!");
  
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    v = "";
    // read packet
    while (LoRa.available()) {
      v += (char)LoRa.read();
    }
    display.clear();
    display.drawString(0, 1, "LoRa Receiver");
    display.drawString(0, 10, String(v));
    display.display();

    Serial.print(v);
    
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }  
}
