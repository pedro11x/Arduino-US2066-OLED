/*
 * The US2066 OLED driver library via i2c interface
 * Written by Pedro Pacheco
 * Modified from gadjet(Phil Grant)'s 1602 OLED Arduino Library on github
 * 
 * Functions documented on the US2066.h file
 */
 
/* Notes:
 * SD on 78, off 79
 * 
 */
#include "US2066.h"
#include "Wire.h"
#include "Math.h"
#define DEFAULTAddress 0x3c
#define OLED_Command_Mode 0x80
#define OLED_Data_Mode 0x40

#define BAR_Beggining 0xDA //Works only in ROM-A

US2066::US2066() {}
US2066::US2066(uint8_t address) {
  this->addr = address;
}
US2066::~US2066() {}


void US2066::init() {
  // *** I2C initialization from the OLEDM1602 datasheet *** //
  delay(100);
  Wire.begin();
  
  
  //Disable internal regulator
  //sendCommand(0x2a); //RE=1
  //sendCommand(0x71);
  //sendCommand(0x00);
  //sendCommand(0x28); //RE=0, IS=0

  //set display to OFF
  sendCommand(0x08);

  //Set display clock devide ratio, oscillator freq
  sendCommand(0x2a); //RE=1
  sendCommand(0x79); //SD=1
  sendCommand(0xd5);
  sendCommand(0x70);
  sendCommand(0x78); //SD=0

  //Set display mode
  sendCommand(0x08);

  //Set remap
  sendCommand(0x06);

  //CGROM/CGRAM Management
  sendCommand(0x72);
  sendData(0x01);    //ROM A
  
  //Set OLED Characterization
  sendCommand(0x2a); //RE=1
  sendCommand(0x79); //SD=1
  
  
  //Set SEG pins Hardware configuration
  sendCommand(0xda);
  sendCommand(0x10);

  //Set contrast control
  sendCommand(0x81);
  sendCommand(0xff);

  //Set precharge period
  sendCommand(0xd9);
  sendCommand(0xf1);

  //Set VCOMH Deselect level
  sendCommand(0xdb); 
  sendCommand(0x30);

  //Exiting Set OLED Characterization
  sendCommand(0x78); //SD=0
  sendCommand(0x28); //RE=0, IS=0

  //Clear display
  sendCommand(0x01);

  //Set DDRAM Address
  sendCommand(0x80);

  delay(100);
  //Set display to ON
  sendCommand(0x0c);
  
  
}


void US2066::cursor(uint8_t row, uint8_t col)
{
  int row_offsets[] = { 0x00, 0x40 };
  sendCommand(0x80 | (col + row_offsets[row]));
}

void US2066::clear()
{
  sendCommand(0x01);
}

void US2066::off()
{
  state &= ~ON;
  updateState();
}

void US2066::on()
{
  state |= ON;
  updateState();
}

void US2066::home()
{
  cursor(0,0);
}

void US2066::blinkingCursor(uint8_t state)
{
  if(state)
  {
    this->state |= BLINKING_CURSOR;
  }
  else
  {
    this->state &= ~BLINKING_CURSOR;
  }
  updateState();
}

void US2066::print(uint8_t row, uint8_t col, const char *String)
{
  cursor(row, col);
  print(String);
}

void US2066::print(const char *String)
{
  int i = 0;
  while (String[i])
  {
    sendData(String[i]);
    i++;
  }
}

void US2066::print(char c)
{
  sendData(c);
}

void US2066::bar(uint8_t row, uint8_t col, int size, int value){
  char bar[size+2];
  int i=0;
  for(;i < size*value/100;i++){
    bar[i] = BAR_Beginning - 4;//Full bar char
  }
  int v = (size*value)%100/20;
  if(!v)
    bar[i]=' ';
  else
    bar[i] = BAR_Beginning-(v-1);
  bar[++i]=0;
  print(row, col, bar);
}

void US2066::updateState(){
  sendCommand( 0x08 | state );
}

void US2066::sendCommand(unsigned char command)
{
  Wire.beginTransmission(addr);
  Wire.write(OLED_Command_Mode);
  Wire.write(command);
  Wire.endTransmission();
}

void US2066::sendData(unsigned char data)
{
  Wire.beginTransmission(addr);
  Wire.write(OLED_Data_Mode);
  Wire.write(data);
  Wire.endTransmission();
}

void US2066::sendDataContinuation(unsigned char data)
{
  Wire.beginTransmission(addr);
  Wire.write(OLED_Data_Mode | OLED_Command_Mode);
  Wire.write(data);
  Wire.endTransmission();
}

void US2066::contrast(unsigned char contrast)
{
  sendCommand(0x2A);
  sendCommand(0x79);      //Set OLED Command set

  sendCommand(0x81);      // Set Contrast
  sendCommand(contrast);  // send contrast value
  sendCommand(0x78);      // Exiting Set OLED Command set
  sendCommand(0x28);

}

