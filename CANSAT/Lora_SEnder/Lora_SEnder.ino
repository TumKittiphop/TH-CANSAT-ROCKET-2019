#include <SPI.h> 
#include <LoRa.h> 
int counter = 0; 
void setup() { 
  Serial.begin(115200); 
  while (!Serial); 
  LoRa.setPins(10,7,2); 
  Serial.println("LoRa Sender"); 
  if (!LoRa.begin(433E6)) { 
    Serial.println("Starting LoRa failed!"); 
    while (1); 
  } 
  LoRa.setTxPower(10); 
} 
void loop() { 
 Serial.print("Sending packet: "); 
 Serial.println(counter); 
 LoRa.beginPacket(); 
 LoRa.print("hello world"); 
 LoRa.print(counter); 
 LoRa.endPacket(); 
 counter++; 
 delay(1000); 
}
