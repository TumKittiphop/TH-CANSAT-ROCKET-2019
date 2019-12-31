#include <SPI.h>
#include <LoRa.h>
#define RED 4
#define WHITE 3
#define BUZ 5
void setup() {
  Serial.begin(115200);
  while (!Serial);
  LoRa.setPins(10, 7, 2);
  pinMode(RED, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(BUZ, OUTPUT);
  Serial.println("LoRa Rcv");
  if (!LoRa.begin(455E6)) {
    Serial.println("Starting LoRa failed!");
    digitalWrite(RED, HIGH);
    while (1);
  }

}
unsigned long i = 1;
int count = 0;
bool ch;
String Str;
void loop () {
  
  int packetSize = LoRa.parsePacket();
  if (packetSize ) {
    count = 0;
    int space = 0;
    ch = true;
    Str = "";

    digitalWrite(BUZ, HIGH);
    digitalWrite(WHITE, HIGH);
    delay(500);
    digitalWrite(BUZ, LOW);
    digitalWrite(WHITE, LOW);

    while (LoRa.available()) {
      char t = (char)LoRa.read();
      if (t == 'E' || t == 'S' || t == 'D' || t == 'R') {
        count++;
        continue;
      }
      else if (!((t >= '0' && t <= '9') || t == '.' || t == ' ' || t == ',' || t == '-' || t == ':')) {
        ch = false;
      }
      if (space == 1 && t == ' ') {
        space = 0;
        continue;
      }
      else if (t == ' ' && space == 0) {
        space++;
      }
      else {
        space = 0;
      }
      Str += t;
      //Serial.println(String(t) + String(count)+String(ch));
      //delay(100);
    }
    //Serial.println(Str);
    //Serial.print("-------------");
    if (ch && count == 4) {
      Serial.println(Str);
      //Serial.print("Received packet '");
      //Serial.print(String(i));
      i++;
      //Serial.print ("' with RSSI ");
      //Serial.println (LoRa.packetRssi());
    }

  }
}
