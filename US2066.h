/*
 * 
 */
#ifndef US2066_h
#define US2066_h	
#include "Arduino.h"
#include "Wire.h"

class US2066{
public:
    uint8_t addr;
		US2066();
    US2066(uint8_t addr);
		~US2066();
		void init();
    void print(const char *String);
		void print(const char *String, uint8_t col, uint8_t row);
		
		void clear();
    void home();
    void cursorOn();
		void cursor(uint8_t, uint8_t); // cloumn, row
		void scrollString(char* message, byte row, unsigned int time); //written by Nathan Chantrell http://nathan.chantrell.net/
		void off();
		void on();
		void setContrast(unsigned char contrast); // contrast should be the hex value between 0x00 and 0xFF
  private:
    void sendCommand(unsigned char command);
    void sendData(unsigned char data);
};
#endif
