#include<Wire.h>
#include "tmag_5273.h"
#include <Adafruit_seesaw.h>

// sensor 0 (as the mark on the diameter_sensor says 0, 0x22)
// the slope and intercept values taken from the excel file
const float slope_0= -1.09411E-05;
const float intercept_0= 2.035149174;

 // sensor 1 (as the mark on the diameter_sensor says 1, 0x78)
const float slope_1 = -1.05908E-05;
const float intercept_1= 2.012869585;

TMAG5273 sensor0;
TMAG5273 sensor1;

// encoder constants
const float gear_ccm= 22.85714285714285714;
const int enc_ppr=100;
const float mm_per_count= gear_ccm/enc_ppr;
Adafruit_seesaw seesaw;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
while(!Serial){};
Wire.begin();

if(!seesaw.begin(0x36)){
  Serial.print("# Seesaw not found");
  while(1);
}
seesaw.setEncoderPosition(0);
// seesaw.enableEncoderInterrupt();
//Initialize sensor 0
sensor0.begin(0x22, Wire);
sensor0.setConvAvg(0x05);
sensor0.setReadMode(0x00);
sensor0.setMagneticChannel(0x04);
sensor0.setLowPower(0x00);
sensor0.setZAxisRange(0x00);
sensor0.setMagTemp(0x01);
Serial.println("# Sensor_0 configured!");
//if(sensor0.begin(0x22, Wire)==1){
  //Serial.println("Sensor_0 found!");
//}else{
//Serial.println("Sensor_0 not found!");
///    while(1);
//  }
//Initialize sensor 1
sensor1.begin(0x78, Wire);
sensor1.setConvAvg(0x05);
sensor1.setReadMode(0x00);
sensor1.setMagneticChannel(0x04);
sensor1.setLowPower(0x00);
sensor1.setZAxisRange(0x00);
sensor1.setMagTemp(0x01);
Serial.println("# Sensor_1 configured!");
//if(sensor1.begin(0x78, Wire)==1){
  //Serial.println("Sensor_1 found!");
//}else{
  //  Serial.println("Sensor_1 not found!");
    //while(1);
 // }

}



void loop() {

int32_t count = -(seesaw.getEncoderPosition());
float length = count*mm_per_count;
  
  // Read sensor 0 like Tyler does
  float z_buffer0 = 0;
  if(sensor0.getMagneticChannel() != 0) {
    sensor0.setTemperatureEn(true);
    for(int i = 0; i < 250; i++) {
      z_buffer0 += sensor0.getZDataRaw();
    }
    z_buffer0 = z_buffer0 / 250;
  }

  // Read sensor 1 the same way
  float z_buffer1 = 0;
  if(sensor1.getMagneticChannel() != 0) {
    sensor1.setTemperatureEn(true);
    for(int i = 0; i < 250; i++) {
      z_buffer1 += sensor1.getZDataRaw();
    }
    z_buffer1 = z_buffer1 / 250;
  }

  // Apply calibration equations
  float d1 = (slope_0 * z_buffer0) + intercept_0;
  float d2 = (slope_1 * z_buffer1) + intercept_1;

  Serial.print(length,3);
  Serial.print(",");
  Serial.print(d1, 4);
  Serial.print(",");
  Serial.println(d2, 4);

}
