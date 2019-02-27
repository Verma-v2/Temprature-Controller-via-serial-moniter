/*   Copyright [2019] [Gyanendra Verma]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.*/

#include<LiquidCrystal.h>
#include <DallasTemperature.h> //Library

//Pins initilization
int ONE_WIRE_BUS=2;

const int rs = 12, en = 11, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int powled= 8;
int led= 3;
int ledPin = 13;
// variable Setup
float dstemp; 
int mintemp = 23; // default Min Temperature
int maxtemp = 29; // default Min Temperature


OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);


/****************************************************void setup******************************************************************************/
void setup() {
   Serial.begin(9600);
     lcd.setCursor(0,0);
  lcd.print("Welcome");
  delay(3000);
  lcd.begin(16,2);
  sensors.begin();
    
pinMode(powled,OUTPUT);
 pinMode(led,OUTPUT);
 pinMode(ledPin, OUTPUT); 
  
}
/**********************************************************************void loop***********************************/
void loop() {
  sensors.requestTemperatures(); 
 dstemp= (sensors.getTempCByIndex(0));
 delay(2000);
 
 lcd.setCursor(0,0);
 lcd.println("Temp:");
 lcd.print( dstemp );
  lcd.print((char)223);
  lcd.print("C");
  Serial.print( dstemp );
   Serial.println("Temp:");
 
//  lcd1.print(0, 0, "Temp= ");
  //lcd1.print( 5,0, dstemp );

/*************************************************************Logic**********************************************************/
 if ( dstemp >=mintemp && dstemp<= maxtemp){
      digitalWrite(powled,HIGH);
      digitalWrite(led,LOW);
      lcd.setCursor(0,1);
      lcd.print("DEVICE ST:");
      lcd.print("ON  ");
    //  lcd1.print(0, 1,"DEVICE ST:");
      //lcd1.print( 10 ,1 ,"ON  " );
     
      }
      else{
    
        digitalWrite(powled,LOW);
        digitalWrite(led,HIGH);
        lcd.setCursor(0,1);
        lcd.print("DEVICE ST:");
        lcd.print("OFF");
        //lcd1.print(0, 1,"DEVICE ST:");
        //lcd1.print( 10 ,1 ,"OFF" );
        
       
        }
/******************************************Serial Read*********************************************************************/
        if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a'){
      mintemp += 1;
      Serial.println("mintemp");
      Serial.println(mintemp);}
    else if(temp == '-' || temp == 'z'){
      mintemp -= 1;
      Serial.println("mintemp");
      Serial.println(mintemp);}
    else if(temp == 's') {
      maxtemp += 1;  
      Serial.println("maxtemp");
      Serial.println(maxtemp); }
    else if(temp == 'x') {
      maxtemp -= 1;  
      Serial.println("maxtemp");
      Serial.println(maxtemp);
  
  }
}
}
