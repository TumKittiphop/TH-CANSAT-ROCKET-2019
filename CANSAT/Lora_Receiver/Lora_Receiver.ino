#include <SPI.h> 
#include <LoRa.h> 
void setup() { 
 Serial.begin(115200); 
 while (!Serial); 
 LoRa.setPins(10,9,2); 
 Serial.println("LoRa Rcv"); 
 if (!LoRa.begin(505E6)) { 
 Serial.println("Starting LoRa failed!"); 
 while (1); 
 }
} 
int i=0;
String Str;
void loop () { 
 int packetSize = LoRa.parsePacket(); 
 if (packetSize ) { 
    Serial.print("Received packet '");
    while (LoRa.available()) { 
      Serial.print ((char)LoRa.read()); 
    } 
    Serial.print ("' with RSSI "); 
    Serial.println (LoRa.packetRssi()); 
    i=0;
 } 
 i++;
}
