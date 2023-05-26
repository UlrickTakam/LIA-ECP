// Manual Control

// include the library code:
#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // setup for the LCD pins

#include <ezButton.h>
ezButton b1(8);// create ezButton object that attach to pin 8
ezButton b2(9);// create ezButton object that attach to pin 9


int sensor = A0; //assign A0 value to integer sensor
int Actuator= 6; //assign pin 6 value to integer Actuator
int pv = 0; //assign value 0 to integer pv
int inputVal = 0; //assign value 0 to integer inputVal
int CO = 0; //assign value 0 to integer CO



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);// begin the serial monitor
pinMode(Actuator, OUTPUT);// set the actuator pin declared previously as output
lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows. 

}

void loop() {
  // put your main code here, to run repeatedly:
  b1.loop(); // MUST call the loop() function first
  b2.loop(); // MUST call the loop() function first
pv = analogRead(sensor); //give the value of the sensor to the pv

if(b1.isPressed()) //library command for when b1 is pressed
  inputVal = inputVal +50; //increase inpute value by 50
    if (inputVal >= 1023){ //input value capped at 1023
   inputVal = 1023;}

if(b2.isPressed()) //library command for when b2 is pressed
  inputVal = inputVal -50; //decrease input value by 50
   if (inputVal <= 0){ //input value minimum set to 0
   inputVal = 0;}



CO = map  (inputVal, 0, 1023 , 0, 255);


//no need to convert the CO to 255 value because it's set in the previous lines
analogWrite(Actuator, CO);

lcd.setCursor(0, 0); //set the lcd cursor to the first column and 1st row
lcd.print("CO=  ");
lcd.print(CO); //print the CO balue on the lcd
lcd.print("           ");

lcd.setCursor(0, 1); //set the lcd cursor to the first column and 2nd row
lcd.print("PV=");
lcd.print(pv); //print the pv value on the lcd
lcd.print("           ");


Serial.print("CO=  ");
Serial.print(CO); //print the CO value to the serial monitor
Serial.print("           ");
Serial.print("PV=  ");
Serial.print(pv); //print the pv value to the serial monitor

Serial.print("           ");
Serial.print("inputVal=  ");
Serial.println(inputVal); //print the input value to the serial monitor

}