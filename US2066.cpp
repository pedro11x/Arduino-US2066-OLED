/*
 * The US2066 OLED driver library via i2c interface
 * Written by Pedro Pacheco
 * Forked and modified from gadjet(Phil Grant)'s 1602 OLED Arduino Library on github
 */
 
/*SD on 78, off 79
 * 
 */
#include "US2066.h"
#include "Wire.h"
#define DEFAULTAddress 0x3c
#define OLED_Command_Mode 0x80
#define OLED_Data_Mode 0x40

US2066::US2066() {
  this->addr = DEFAULTAddress;
}
US2066::US2066(uint8_t address) {
  this->addr = address;
}
US2066::~US2066() {}


void US2066::init() {
  // *** I2C initialization from the OLEDM1602 datasheet *** //
  delay(100);
  Wire.begin();
  //Disable internal regulator
  //sendCommand(0x2a);
  //sendCommand(0x71);
  //sendCommand(0x00);
  //sendCommand(0x28);

  //set display to OFF
  sendCommand(0x08);

  //Set display clock devide ratio, oscillator freq
  sendCommand(0x2a);
  sendCommand(0x79);
  sendCommand(0xd5);
  sendCommand(0x70);
  sendCommand(0x78);

  //Set display mode
  sendCommand(0x08);

  //Set remap
  sendCommand(0x06);

  //CGROM/CGRAM Management
  sendCommand(0x72);
  sendCommand(0x00);//ROM A

  //Set OLED Characterization
  sendCommand(0x2a);
  sendCommand(0x79);
  
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
  sendCommand(0x78);
  sendCommand(0x28);

  //Clear display
  sendCommand(0x01);

  //Set DDRAM Address
  sendCommand(0x80);

  delay(100);
  //Set display to ON
  sendCommand(0x0c);
}

void US2066::cursor(uint8_t col, uint8_t row)
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
  sendCommand(0x08);  	// **** Turn on Off
}

void US2066::on()
{
  sendCommand(0x0C);  	// **** Turn on On
}

void US2066::home()
{
  cursor(0,0);    // **** Return home
}

void US2066::cursorOn()
{
  sendCommand(0x07);    // **** Return home
}

void US2066::sendCommand(unsigned char command)
{
  Wire.beginTransmission(addr); 	 // **** Start I2C
  Wire.write(OLED_Command_Mode);     		 // **** Set OLED Command mode
  Wire.write(command);
  Wire.endTransmission();                 	 // **** End I2C
  delay(10);
}

void US2066::setContrast(unsigned char contrast) // contrast as 0x00 to 0xFF
{
  //Set OLED Command set
  sendCommand(0x2A);
  sendCommand(0x79);

  sendCommand(0x81);  	// Set Contrast
  sendCommand(contrast);	// send contrast value
  sendCommand(0x78);  	// Exiting Set OLED Command set
  sendCommand(0x28);

}

void US2066::print(const char *String, uint8_t col, uint8_t row)
{
  cursor(col, row);
  print(String);
}

void US2066::print(const char *String)
{
  unsigned char i = 0;
  while (String[i])
  {
    sendData(String[i]);      // *** Show String to OLED
    i++;
  }
}


void US2066::sendData(unsigned char data)
{
  Wire.beginTransmission(addr);  	// **** Start I2C
  Wire.write(OLED_Data_Mode);     		// **** Set OLED Data mode
  Wire.write(data);
  Wire.endTransmission();                     // **** End I2C
}
void US2066::scrollString(char* message, byte row, unsigned int time)//written by Nathan Chantrell http://nathan.chantrell.net/
{
  char buffer[16];
  for (byte i = 0; i < strlen(message) + 16; i++) {
    byte pos = i + 1;
    for (byte j = 0; j < 16; j++) {
      if ((pos < 16) || (pos > strlen(message) + 15)) { // pad and trail with blank spaces
        buffer[j] = ' ';
      }
      else buffer[j] = message[pos - 16];
      pos++;
    }
    //cursPos(0,row); removed by PG
    print(buffer, 0, row); //Edited by PG tho include the cursor pos within the sendString command
    delay(time);
  }
}
