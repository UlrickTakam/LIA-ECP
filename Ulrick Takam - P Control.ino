// P Control

int sensor = A0; //assign A0 value to integer sensor
int Actuator= 6; //assign pin 6 value to integer Actuator
int pv = 0; //assign value 0 to integer pv
int CO = 0; //assign value 0 to integer CO
int sp = 0;// assign value 0 to integer sp
int select = 0;// assign value 0 to integer select
int error = 0; // assign value 0 to integer error
float gain =0.5 ; //assign the value 0.5 to the float gain



//button variables:
#include <ezButton.h>//this adds the button debounce library 
ezButton b1(8);// create ezButton object that attach to pin 8
ezButton b2(9);// create ezButton object that attach to pin 9
ezButton b3(10);// create ezButton object that attach to pin 10
ezButton b4(11);// create ezButton object that attach to pin 11

// include the library code:
#include <LiquidCrystal.h>// this is the libray for the LCD display
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);// setup for the LCD pins

const long interval = 300;//setup the time interval for the delay 
unsigned long previousMillis = 0; //set previousMillis as unsigned long

void setup() {
Serial.begin(9600);// begin the serial monitor
pinMode(Actuator, OUTPUT);// set the actuator pin declared previously as output
lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows. 


}

void loop() {
  b1.loop(); // MUST call the loop() function first
  b2.loop(); // MUST call the loop() function first
  b3.loop(); // MUST call the loop() function first
  b4.loop(); // MUST call the loop() function first




    if(b1.isPressed()) //library command for when b1 is pressed
     select = select +1;//increase the select value by 1

    if(b2.isPressed()) //library command for when b2 is pressed
     select = select -1;//decrease the select value by 1

if(select >=1){//condition for when select is bigger than the number
 
  select = 1;
}
if(select <=0){//condition for when select is smaller than the number

  select = 0;
}


if (select == 0){//if select = 0, this is he first page/parameter

    unsigned long currentMillis = millis();//this is a delay function without using delay
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;//this allows the LCD to print the live value of the pv and CO once every amount of time set

lcd.setCursor(0, 0);//set the lcd cursor to the 1st column and 1st row
lcd.print("PV=");
lcd.print(pv);//print the value of pv to the lcd
lcd.print("           ");// print spaces to avoid visual bugs

lcd.setCursor(8, 0);//set the lcd cursor to the 9th column and 1st row
lcd.print("error=");
lcd.print(error);//print the value of CO to the lcd
lcd.print("           ");// print spaces to avoid visual bugs
    }

if(b3.isPressed())//library command for when b3 is pressed
  sp = sp +50;//sp + 50
    if (sp >= 1030)//sp value capped at 1030
   sp = 1030;

if(b4.isPressed())//library command for when b4 is pressed
  sp = sp -50;//sp -50
   if (sp <= 0)//sp minimum set at 0
   sp = 0;



lcd.setCursor(0, 1);//set the lcd cursor to the 1st column and 2nd row
lcd.print("SP=  ");
lcd.print(sp);//print the value of sp to the lcd
lcd.print("           ");// print spaces to avoid visual bugs
}


if (select == 1){
  unsigned long currentMillis = millis();//serves the same funtion as the part on top, to delay the LCD print
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

lcd.setCursor(0, 0);//set the lcd cursor to the 1st column and 1st row
lcd.print("PV=");
lcd.print(pv);//print the value of pv to the lcd
lcd.print("           ");// print spaces to avoid visual bugs

lcd.setCursor(8, 0);//set the lcd cursor to the 9th column and 1st row
lcd.print("error=");
lcd.print(error);//print the value of CO to the lcd
lcd.print("           ");// print spaces to avoid visual bugs
    }

if(b3.isPressed())//library command for when b3 is pressed
  gain = gain +0.02;
    if (gain >= 5.0)//gain value capped at 5.0
   gain = 5.0;

if(b4.isPressed())//library command for when b4 is pressed
  gain = gain -0.02;
   if (gain <= 0.002) //gain value minimum set at 0.002
   gain = 0.002;

lcd.setCursor(0, 1);//setup the position for the text x=0 y=1
lcd.print("gain=  ");//print the text
lcd.print(gain);//print the value of sp
lcd.print("           ");// print spaces to avoid visual bugs

}


pv = analogRead(sensor);//pv = the value read from analog pin "sens"
error = (sp-pv);
CO = (gain*error);

if (CO >= 255){//if the pv is lower than sp plus hys, the CO turns on
  CO= 255;
}
 else if (CO <= 0){//if the pv is higher than sp plus hys, the CO turns off

   CO= 0;
 }
analogWrite(Actuator, CO);//write the value of CO to the actuator pin 


Serial.print("select=  "); 
Serial.print(select); //print the select value to the serial monitor
Serial.print("       ");// print spaces to avoid visual bugs

Serial.print("    gain=  ");
Serial.print(gain); //print the gain value to the serial monitor
Serial.print("       ");// print spaces to avoid visual bugs

Serial.print("    sp=  ");
Serial.print(sp); //print the sp value to the serial monitor
Serial.print("       "); // print spaces to avoid visual bugs

Serial.print("    CO=  ");
Serial.print(CO); //print the CO value to the serial monitor
Serial.print("       "); // print spaces to avoid visual bugs

Serial.print("    pv=  ");
Serial.print(pv); //print the pv value to the serial monitor
Serial.println("       "); // print spaces to avoid visual bugs

}