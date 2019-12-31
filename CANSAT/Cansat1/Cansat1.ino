#include <AltSoftSerial.h>
#include <Wire.h>
#include <MPU9255.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <LoRa.h>
#include "Seeed_BME280.h"
#define alpha 0.5
SoftwareSerial AA(5, 6); //RX, TX
AltSoftSerial ss;
TinyGPSPlus gps;
MPU9255 mpu;
BME280 bme280;
double fXg = 0;
double fYg = 0;
double fZg = 0;
void setup() {
  Serial.begin(115200);
  LoRa.setPins(10, 7, 2);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(505E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(17);

  if (!bme280.init()) {
    Serial.println("BME Error!");
    while (1);
  }
  if (mpu.init())
  {
    Serial.println("MPU Error!");
    //while (1);
  }
  AA.begin(9600);
  ss.begin(9600);
  
}
int  i=0;
float lati, longi , pressure;
void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }
  if (gps.location.isUpdated()) {
    lati = gps.location.lat(), 6;
    longi = gps.location.lng(), 6;
  }
  pressure = bme280.getPressure();
  String Final = String(i);
  Final += " E "  + String(lati, 6) + "," + String(longi, 6) + " S " + String(bme280.getTemperature()) + "," + String(pressure) ;
  Final += "," + String(bme280.calcAltitude(pressure)) + "," + String(bme280.getHumidity());
  mpu.read_acc();
  fXg =mpu.ax * alpha + (fXg * (1.0 - alpha));
  fYg = mpu.ay * alpha + (fYg * (1.0 - alpha));
  fZg = mpu.az * alpha + (fZg * (1.0 - alpha));
  double roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
  double pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
  Final +=  " D " + String(roll) + "," + String(pitch)+"R";
  LoRa.beginPacket();
  LoRa.print(Final);
  LoRa.endPacket();
  AA.print(Final);
  Serial.println(Final);
  delay(500);
  i++;
}
