#include<Wire.h>
void setup() {
 Serial.begin(115200);
 while(!Serial){}

 Wire.begin();
 Serial.println("Starting I2C Scan");
 
 int devfound=0;
 for (byte address=8; address<= 120; address++) {
  Wire.beginTransmission(address);
  byte error  = Wire. endTransmission();

  if (error==0){
    Serial.print("Device found at address 0x");
    if (address < 16) Serial.print("0");
    Serial.print(address,HEX);

    if (address==0x36) Serial.print(" Stemma QT");
    if (address==0x22) Serial.print(" sensor 1");
    if (address==0x78) Serial.print(" sensor 2");
    Serial.println();
    devfound++;
  }
  else if (error==4){
    Serial.print("Unknown error a address 0x:");
    if (address <16) Serial.print("0");
    Serial.println(address,HEX);
  }
 }
 Serial.println("Scan completed");
 Serial.print(devfound);
 Serial.println("device(s) found");

 if (devfound==0){
  Serial.println("PROBLEM");
 }

}

void loop() {
  
}
