/*
  Hotspot 1D
  By: Cristian Delgado
  Commisioned by: Dr. Miguel Condes Lara
  
  An arduino shield for measuring inflamation and pain
  
  Libraries:
  LM35 By Guillermo Goms Zucco
  Adafruit Unified Sensor By Adafruit
  Adafruit TMP006 By Adafruit
  
  Circuit:
  BTN1 -> 8
  BTN2 -> 9
  LM35 -> A3
   TMP006:
   SDA -> A4
   SCL -> A5
*/




//Libraries
#include <LM35.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TMP006.h"
#include <SPI.h>
#include <SD.h>

//Defines
#define BTN1  8
#define BTN2  9
#define mSec  50
#define lmCalib 3

//Objects
LM35 temp(A3);
Adafruit_TMP006 tmp006;

float tempObj = 0;
float tempAmb = 0;
int btn1 = 0;
int btn2 = 0;

String msg;
String file;
char baseName;

void setup() {
  pinMode(A3,INPUT);
  pinMode(BTN1,INPUT);
  pinMode(BTN2,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);

  if(!SD.begin(4))
  {
    Serial.println("Error en la tarjeta SD");
    return;
  } else {
    Serial.println("Tarjeta SD presente");
  }
  
  if(! tmp006.begin()){
    Serial.println("Error en sensor tmp006");
    while(1){
      digitalWrite(13,LOW);
      delay(1000);
      digitalWrite(13,HIGH);
      delay(1000);
      
    }
  }
  /*
  Serial.println("Nombre del experimento?");
  Serial.readBytesUntil('\n',baseNombre,8);
  nombreArchivo += ".csv"; 
  Serial.println("Guardando en: " + nombreArchivo);
  */
  /*
  nombreArchivo = "datos";
  nombreArchivo += "-";
  nombreArchivo += random(1,300);
  nombreArchivo += ".csv";
  delay(random(500,1000));
  Serial.println("Guardando en :" + nombreArchivo);
  delay(3000);
  */
}

void loop() {
  String data = "";
  File file = SD.open("data.csv",FILE_WRITE);

  tempAmb = temp.cel();
  tempObj = tmp006.readObjTempC();
  btn1 = digitalRead(BTN1);
  btn2 = digitalRead(BTN2);
  
  data = tempAmb;
  data += ",";
  data += tempObj;
  data += ",";
  data += btn1;
  data += ",";
  data += btn2;
  if (file){
    file.println(data);
    file.close();
  }
  Serial.println(tempObj);

  delay(mSec);
}
