#include "Wire.h"

const int MPU_addr = 0x68; // I2C address of the MPU-6050

int16_t AcX, AcY, AcZ;

void setup() {
  
  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
  check_I2c(MPU_addr); // Check that there is an MPU

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  reiniciaCom();
  
}
 void reiniciaCom(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
 }

void trocaParaDedo1(){
  digitalWrite(D0, LOW);
  digitalWrite(D5, HIGH);
  
//  //verificar se o dedo 1 está na possição de Horizontal
//  if(AcX < 1400){
////  Serial.println("");
////  Serial.println("Horizontal d1");
//  }
//  //verificar se o dedo 1 está na possição de Vertical
//  else if (AcX > 3000){
//  Serial.println("");
//  Serial.println("Vertical d1");
//  }
//  //não está em posição nenhuma
//  else{
//  Serial.println("");
//  Serial.println("Movendo-se");
//  }

}

void trocaParaDedo2(){
  digitalWrite(D0, HIGH);
  digitalWrite(D5, LOW);

//  //verificar se o dedo 2 está na possição de Horizontal
//  if(AcX < 1400){
//  Serial.println("");
//  Serial.println("Horizontal d2");
//  }
//  //verificar se o dedo 2 está na possição de Vertical
//  else if (AcX > 3000){
//  Serial.println("");
//  Serial.println("Vertical d2");
//  }
//  //não está em posição nenhuma
//  else{
//  Serial.println("");
//  Serial.println("Movendo-se");
//  }
}

void lerUmDedo(){
 
  //check_I2c(MPU_addr); // Check that there is an MPU
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  

  
  
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
                      Serial.print(AcX);
  Serial.print("  "); Serial.print(AcY);
  Serial.print("  "); Serial.print(AcZ);
  Serial.print("  ");
  Wire.endTransmission(true);
    delay(100);
   
 
}
void loop() { 

trocaParaDedo1();
delay(50);
lerUmDedo();
trocaParaDedo2();
delay(50);
lerUmDedo();
Serial.println(""); 
 
delay(1000); // Wait 0.5 seconds and scan again
reiniciaCom();
}

byte check_I2c(byte addr) {
  // We are using the return value of
  // the Write.endTransmisstion to see if
  // a device did acknowledge to the address.
  byte error;
  Wire.beginTransmission(addr);
  error = Wire.endTransmission();

  if (error == 0)
  {
//    Serial.print(" Device Found at 0x");
//    Serial.println(addr, HEX);
  }
  else
  {
    Serial.print(" No Device Found at 0x");
    Serial.print(addr, HEX);
  }
  return error;
}
