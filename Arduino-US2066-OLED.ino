/*
Example sketch
*/
#include "US2066.h"
US2066 OLED;
float digit; //Variable to hold sample temperature value



void setup()
{
  Wire.begin();
  OLED.init();
}

void loop()
{ char* buf;
  //Printing, no cursor
  OLED.print("hello");
  //Progress bar!
  for(int i=0;i<=100;i+=5){
    OLED.bar(0, 6, 5, i);
    delay(100);
  }
  
  delay(50);

  //Printing in a particular place, by defining the row and column
  OLED.print(0, 6, "world!");

  delay(500);
  
  //Seting a cursor position, from which to start writing
  OLED.cursor(1, 0);
  
  //Turning on the blinking cursor
  OLED.blinkingCursor(HIGH);

  delay(500);

  //Printing one character at a time
  animatedPrint("The US2066 lib");

  delay(1000);
  
  OLED.cursor(1, 0);
  animatedPrint("Blinking cursor!");
  
  delay(500);
  
  OLED.cursor(1, 0);  
  animatedPrint("Setting contrast");

  //Changing the contrast
  for(uint8_t i =255;i>0;i-=15){
    OLED.contrast(i);
    delay(50);
  }
  delay(200);
  for(uint8_t i =0;i<255;i+=15){
    OLED.contrast(i);
    delay(50);
  }
  
  delay(1500);
  
  OLED.print(1,0,"                 ");//clearing row 1
  OLED.cursor(1,0);
  animatedPrint("Going to sleep");

  delay(100);
  //Turning the display off
  OLED.off();

  delay(1000);
  OLED.print(1,0,"                 ");//clearing row 1
  OLED.cursor(1,0);
  OLED.print(1,0,"Waking up");

  //Waking it up
  OLED.on();
  
  delay(10000);
  OLED.clear();
  OLED.home();
  OLED.blinkingCursor(false);
}

void animatedPrint(String buf){
  for(int i=0;buf[i];i++){
    OLED.print(buf[i]);
    delay(50);
  }
}
