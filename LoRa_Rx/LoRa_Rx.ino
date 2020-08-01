#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//int led = 3;
int val = 0;
int nss = 10;
int RESET = 9;
int dio0 = 2;
String full_string;
String inString = "";
int rssi;
void setup()
{
  LoRa.setPins(nss, RESET, dio0);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  //  pinMode(led,OUTPUT);
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(62.5E3);



}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  full_string = "";

  if (packetSize)
  {
    // received a paket
    Serial.println("");
    //Serial.println("...................................");
    Serial.println("Received packet: ");

    // read packet

    while (LoRa.available()) {
      char incoming = (char)LoRa.read();
      full_string += incoming;
      //Serial.print(incoming);
      if (incoming == 'c')
      {
        Serial.print("Error");
      }
      else
      {
        Serial.print(incoming);
      }
      rssi = LoRa.packetRssi();
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print(full_string);
      display.print("            RSSI:- ");
      display.println(rssi);
      display.display();
    }
    Serial.print("RSSI ");
    Serial.print(rssi);

  }
}
