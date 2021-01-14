#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <LiquidCrystal.h> 

const int hallPin=2;
const double circumference=84.823; //in
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
int totalRev=0;
double distance=0;
int timeAtLastRev=0;
double velocity=0.0;
double distance2;
double velocity2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("yo");
  lcd.setCursor(13,0);
  lcd.print("mph");
  lcd.setCursor(11,1);
  lcd.print("miles");
}

double findDistance() {
  distance=circumference*totalRev; //in
  distance=distance/12; //ft
  distance=distance/5280; //mi
  return distance;
}

double findVelocity() {
  velocity=circumference/(millis()-timeAtLastRev); //in/ms
  timeAtLastRev=millis();
  velocity=velocity/63360; //mi/ms
  velocity=velocity*3666666; //mph
  return velocity;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (analogRead(1)<=3 && millis()-timeAtLastRev>170) {
    totalRev++;
    distance2=findDistance();
    velocity2=findVelocity();
    lcd.setCursor(0,0);
    lcd.print(velocity2);
    lcd.setCursor(0,1);
    lcd.print(distance2);
  }
}
