#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial ss(9, 8); // RX, TX
TinyGPSPlus gps;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("GPS Started!");
  ss.begin(9600);
  ss.println("Hello, world?");
}

void loop() {
  while(ss.available() > 0) {
    gps.encode(ss.read());
    float lati = gps.location.lat();
    float longi = gps.location.lng();
    String pkg = String(lati,6)+","+String(longi,6)+",";
    //if(lati!=0.0)
      Serial.println(pkg);
  }
  
}
