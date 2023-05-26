// On/Off Mode

int sensor = A0; //assign A0 value to integer sensor
int Actuator= 6; //assign pin 6 value to integer Actuator
int pv = 0; //assign value 0 to integer pv
int CO = 0; //assign value 0 to integer CO
int sp = 0;// assign value 0 to integer sp
int hys = 0;// assign value 0 to integer hys
int select = 0;// assign value 0 to integer select


//button variables:
#include <ezButton.h> //adds the button debounce library 
ezButton b1(8);// create ezButton object that attach to pin 2
ezButton b2(9);// create ezButton object that attach to pin 3
ezButton b3(10);// create ezButton object that attach to pin 4
ezButton b4(11);// create ezButton object that attach to pin 5

// include the library code:
#include <LiquidCrystal.h>// this is the libray for the LCD display
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);// setup for the LCD pins

const long interval = 100;//setup the time interval for the delay 
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


if (select == 0){//if select is 0, this is he first page/parameter

    unsigned long currentMillis = millis();//this is a delay function without using delay
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;//this allows the LCD to print the live value of the pv and CO once every amount of time set

lcd.setCursor(0, 0);//set the lcd cursor to the 1st column and 1st row
lcd.print("PV=");
lcd.print(pv);//print the value of pv to the lcd
lcd.print("           ");// print spaces to avoid visual bugs

lcd.setCursor(8, 0);//set the lcd cursor to the 9th column and 1st row
lcd.print("CO=");
lcd.print(CO);//print the value of CO to the lcd
lcd.print("           ");// print spaces to avoid visual bugs
    }

if(b3.isPressed())//library command for when b3 is pressed
  sp = sp +100;//sp + 100
    if (sp >= 1030)//sp value capped at 1030
   sp = 1030;

if(b4.isPressed())//library command for when b4 is pressed
  sp = sp -100;//sp -100
   if (sp <= 0)//sp value minimum set at 0
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

lcd.setCursor(0, 0);//set the lcd cursor to the first column and the first row
lcd.print("PV=");//print the text
lcd.print(pv);//print the value of pv to the lcd
lcd.print("           ");// print spaces to avoid visual bugs

lcd.setCursor(8, 0);//set the lcd cursor to the ninth column and the second row
lcd.print("CO=");//print the text
lcd.print(CO);//print the value of CO to the lcd
lcd.print("           ");// print spaces to avoid visual bugs
    }

if(b3.isPressed())//library command for when b3 is pressed
  hys = hys +15;//hys+15
    if (hys >= 155)//hys value capped at 155
   hys = 155;

if(b4.isPressed())//library command for when b4 is pressed
  hys = hys -15;//hys -15
   if (hys <= 0)//hys minimum set at 0
   hys = 0;

lcd.setCursor(0, 1);//set the lcd cursor to the first column and the second row
lcd.print("hys=  ");//print the text
lcd.print(hys);//print the value of sp to the lcd
lcd.print("           "); // print spaces to avoid visual bugs


}


pv = analogRead(sensor);//assign the sensor value to thepv
if (pv <= (sp - hys)){//if the pv is lower than sp plus hys, the CO turns on
  CO= 255;
}
 else if (pv >= (sp + hys)){//if the pv is higher than sp plus hys, the CO turns off

   CO= 0;
 }
analogWrite(Actuator, CO);//write the value of CO to the actuator pin 


Serial.print("select=  "); 
Serial.print(select); //print the select value to the serial monitor
Serial.print("       ");

Serial.print("    hys=  ");//prints value of hys
Serial.print(hys); //print the hys value to the serial monitor
Serial.print("       ");

Serial.print("    sp=  ");//prints sp
Serial.print(sp); //print the sp value to the serial monitor
Serial.print("       ");

Serial.print("    pv=  ");// prints pv
Serial.print(pv); //print the pv value to the serial monitor
Serial.println("       ");

}
