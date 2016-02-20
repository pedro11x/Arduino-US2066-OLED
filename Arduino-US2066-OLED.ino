/*
Example sketch
*/

#include "US2066.h"
US2066 LCD;
float digit; //Variable to hold sample temperature value
char t[20];


void setup()
{
  Wire.begin();
  LCD.init();
}
void loop()
{
  snprintf(t, 20, "%lu", millis());
  //LCD.cursorOn();
  LCD.print("hello\n\r");
  
  //LCD.print("This is a NewHaven OLED");
  delay(1000);
  
  LCD.print("world!");
  while(1);
  //LCD.clear();
}
