# Seed

ESO's Seed project. Point to point telemetry is here!
Mostly in C language.

## Getting started

The [LoRaReceiverESP32](LoRaReceiverESP32.ino) is to flash on the receiver unit.
The [LoRaSender](LoRaSender.ino) is to flash on the emmiter unit.

You have to respect the wiring diagram, because you know there are some sensors!

To implement that, we need a library for that kind of ESP32 Lora TTL which is available at [drive.google.com](https://drive.google.com/file/d/1L8ll-DeAC2SATBZn0-KbSaZsrinbnXkF/view).
You to download that big *.rar file and open it with a unrar program like 7zip.
Unzip the TTGO WIFI-OLED.zip and you get the TTGO WIFI-OLED folder.

Move the TTGO WIFI-OLED to yours Arduino's hardware folder in your Documents.

It looks something like this :

![arduino_path](ressources/arduino_path.jpg)

Restart Arduino and check in Tools -> Board that you have now some TTGO's board

## Installing and flashing

Clone this git or download it as a zip

```bash
git clone https://github.com/raymas/Seed.git
```

Open the [LoRaSender](LoRaSender.ino) script with arduino, upload it with the board : EPS8266 with defaults parameters. Don't forget to select the correct port.
And here we go again with the other unit, flash it with the [LoRaReceiverESP32](LoRaReceiverESP32.ino) script.

Power up the two modules and observe some messages displayed on the screen.