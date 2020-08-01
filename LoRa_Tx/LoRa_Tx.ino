#include <LoRa.h>

int pot = A1;

int val;


void setup()
{
  Serial.begin(9600);
  pinMode(pot, INPUT);
  while (!Serial);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(20);  //20 max power
  LoRa.setSpreadingFactor(12);  //12 for max range
  LoRa.setSignalBandwidth(62.5E3); //Supported values are 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3=default, and 250E3.

}

void loop()
{

  val = map(analogRead(pot), 0, 1024, 0, 255);
  Serial.println("Sending packet: ");

  // send packet
  LoRa.beginPacket();
  LoRa.print(" Value:");
  LoRa.print(val);
  LoRa.endPacket();

  Serial.print("Value:");
  Serial.print(val);
  Serial.println("");
  delay(50);
}
