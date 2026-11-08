#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <Servo.h>
LSM9DS1 imu;
#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

Servo S1;
Servo S2;
Servo S3;
Servo S4;
Servo S5;
Servo S6;

int VS1 = 95;
int VS2 = 95;
int VS3 = 161;
int VS4 = 154;
int VS5 = 25;
int VS6 = 47;

int AZ;
const int sensor1 = A0;
const int sensor2 = A2;

void setup () {
  Serial.begin(115200);
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  imu.settings.accel.scale = 16; // Set accel range to +/-16g
  imu.settings.gyro.scale = 2000; // Set gyro range to +/-2000dps
  imu.settings.mag.scale = 8; // Set mag range to +/-8Gs
  imu.begin();
  
  S1.attach(3);
  S2.attach(5);
  S3.attach(6);
  S4.attach(9);
  S5.attach(10);
  S6.attach(11);
  
  S1.write(VS1);
  S2.write(VS2);
  S3.write(VS3);
  S4.write(VS4);
  S5.write(VS5);
  S6.write(VS6); 
  
/* FERMO
  S1.write(92);
  S2.write(95);
  S3.write(90);
  S4.write(94);
  S5.write(130);
  S6.write(128); 
*/

  delay(2000);
  start();
}

void start() {
  ldown();
  forward();
  delay(1000);
  lup();
  cdown();
  delay(100);

  do {
    imu.readAccel();
    AZ = imu.calcAccel(imu.az) * 100;
    Serial.print(AZ);
  } 
  while (AZ > -29 || AZ < -31);
  delay(150);
  do {
    imu.readAccel();
    AZ = imu.calcAccel(imu.az) * 100;
    Serial.print(AZ);
  } 
  while (AZ > -29 || AZ < -31);
  
  S3.write(51);
  S6.write(157);
  delay(300);
  S3.write(161);
  S6.write(47);
  VS1=140;
  VS2=50;
  S1.write(VS1);
  S2.write(VS2);  
  delay(200);
  cup();
  delay(300);
}

void backward() {
  for(VS1=45; VS1<=95; VS1++ && VS2--) {
    S1.write(VS1);
    S2.write(VS2);
    delay(10);
  }
}

void forward() {
  for(VS1=95; VS1>=45; VS1-- && VS2++) {
    S1.write(VS1);
    S2.write(VS2);
    delay(10);
  }
  for(VS1=45; VS1<=48; VS1++ && VS2--) {
    S1.write(VS1);
    S2.write(VS2);
    delay(10);
  } 
}

void cdown() {
  for(VS4=154; VS4>=129; VS4-- && VS5++) {
   S4.write(VS4);
   S5.write(VS5);
   delay(10);
 }
}

void cup() {
  for(VS4=129; VS4<=154; VS4++ && VS5--) {
   S4.write(VS4);
   S5.write(VS5);
   delay(10);
  }
}

void ldown() {
  for(VS3=161; VS3>=141; VS3-- && VS6++) {
   S3.write(VS3);
   S6.write(VS6);
   delay(10);
  }
}

void lup() {
  for(VS3=141; VS3<=161; VS3++ && VS6--) {
   S3.write(VS3);
   S6.write(VS6);
   delay(10);
  }
}

void step1() {
  do {
    imu.readAccel();
    AZ = imu.calcAccel(imu.az) * 100;
    Serial.print(AZ);
  } 
  while (AZ < 29 || AZ > 31);
  delay(150);
  do {
    imu.readAccel();
    AZ = imu.calcAccel(imu.az) * 100;
    Serial.print(AZ);
  } 
  while (AZ < 29 || AZ > 31);

  ldown();  
  S4.write(59);
  S5.write(140);
  delay(300);
  S4.write(154);
  S5.write(25);
  VS1=48;
  VS2=142;
  S1.write(VS1);
  S2.write(VS2);
  delay(200);
  lup(); 
  delay(300);
}

void step2() {
  do {
    imu.readAccel();
    AZ = imu.calcAccel(imu.az) * 100;
    Serial.print(AZ);
  } 
  while (AZ > -29 || AZ < -31);
  delay(150);
  do {
    imu.readAccel();
    AZ = imu.calcAccel(imu.az) * 100;
    Serial.print(AZ);
  } 
  while (AZ > -29 || AZ < -31);
  
  cdown();  
  S3.write(46);
  S6.write(162);
  delay(300);
  S3.write(161);
  S6.write(47);
  VS1=140;
  VS2=50;
  S1.write(VS1);
  S2.write(VS2);  
  delay(200);
  cup();
  delay(300);
}
  
void loop () {
  while(analogRead(sensor1) > 100) {
    cdown();
    S3.write(81);
    S6.write(127);
    delay(200);
    S3.write(161);
    S6.write(47);

    S1.write(150);
    S2.write(65); 
    delay(500);
    cup();
    ldown();
    delay(100);
    S4.write(34);
    S5.write(145);
    delay(300);
    S4.write(154);
    S5.write(25);
    S1.write(140);
    S2.write(50);
    lup();
    delay(250);
  }
  step1();
  
  while(analogRead(sensor2) > 100) {
    cdown();
    S3.write(81);
    S6.write(127);
    delay(200);
    S3.write(161);
    S6.write(47);

    S1.write(65);
    S2.write(150); 
    delay(500);
    cup();
    ldown();
    delay(100);
    S4.write(34);
    S5.write(145);
    delay(300);
    S4.write(154);
    S5.write(25);
    S1.write(48);
    S2.write(142);
    lup(); 
    delay(20);   
  }
  step2();    
}

