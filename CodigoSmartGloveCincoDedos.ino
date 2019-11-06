#include "Wire.h"



const int MPU_addr = 0x68; 

int16_t AcX, AcY, AcZ;

void setup() {

 

  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
  check_I2c(MPU_addr); 

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  reiniciaCom();

  

}


void reiniciaCom() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
}

void trocaParaDedo1() {
  digitalWrite(D0, LOW);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);

}

void trocaParaDedo2() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
}


void trocaParaDedo3() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, LOW);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
}

void trocaParaDedo4() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
}

void trocaParaDedo5() {
  digitalWrite(D0, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, LOW);
}


void lerUmDedo() {

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); 
  Wire.endTransmission(false);

  Wire.requestFrom(MPU_addr, 14, true); 
  AcX = Wire.read() << 8 | Wire.read(); 
  AcY = Wire.read() << 8 | Wire.read(); 
  AcZ = Wire.read() << 8 | Wire.read(); 
  Serial.print(AcX);
  Serial.print("  "); Serial.print(AcY);
  Serial.print("  "); Serial.print(AcZ);
  Serial.print("  ");
  Wire.endTransmission(true);
  delay(100);


}
void loop() {


  trocaParaDedo1();
  delay(100);
  lerUmDedo();
  trocaParaDedo2();
  delay(100);
  lerUmDedo();
  trocaParaDedo3();
  delay(100);
  lerUmDedo();
  trocaParaDedo4();
  delay(100);
  lerUmDedo();
  trocaParaDedo5();
  delay(100);
  lerUmDedo();
  Serial.println("");

  delay(1000);
  reiniciaCom();
}

byte check_I2c(byte addr) {
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
