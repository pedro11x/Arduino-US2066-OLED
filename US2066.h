/**
 * US2066 OLED I2C Library
 */
#ifndef US2066_h
#define US2066_h

#define DEFAULTAddress 0x3c
#define OLED_Command_Mode 0x80
#define OLED_Data_Mode 0x40

#define DEFAULT_STATE 0x0C //OLED is ON, no cursor
#define ON 0x04
#define BLINKING_CURSOR 0x01

#define BAR_Beginning 0xDA //Works only in ROM-A


#include "Arduino.h"
#include "Wire.h"

class US2066{
  public:
    /**I2C address*/
    uint8_t addr = DEFAULTAddress;
    uint8_t state = ON; 

    /**Default constructor (for default address Ox3C)*/
		US2066();
    /**Constructor for custom I2C address*/
    US2066(uint8_t addr);
    /**Destructor*/
		~US2066();

    
    /**
     * Initialize the display
    */
		void init();
    /**
     * Print character from current cursor position
    */
    void print(char c);
    
    /**
     * Print from current cursor position
    */
    void print(const char *String);
    
    /**
     * Print from defined cursor position
     * col - Starting column
     * row - Starting row
    */
		void print(uint8_t row, uint8_t col, const char *String);
   
    /**
     * Display progress bar on screen
     * col - column in which the bar starts
     * row - row in which the bar starts
     * size - size of the bar when full (in number of on screen characters)
     * value - status of the bar in percentage (0 - 100)
     * This only works if the CGROM A is selected
     * (which is selected, by default, by the init function)
    */
		void bar(uint8_t row, uint8_t col, int size, int value);
   
    /**
     * Clears the display
    */
		void clear();
   
    /**
     * Sends cursor home (row = 0, column = 0)
    */
    void home();
    
    /**
     * Turn on blinking cursor
     * state =  high - on
     *           low - off
    */
    void blinkingCursor(uint8_t state);
    
    /**
     * Set cursor position
    */
		void cursor(uint8_t row, uint8_t col);
		void scrollString(char* message, byte row, unsigned int time); //written by Nathan Chantrell http://nathan.chantrell.net/
   
		/**Turn display off*/
		void off();
   
    /**Turn display on*/
		void on();
    
    /**Set the display contrast from 0 to 255*/
		void contrast(unsigned char contrast);
  private:
    void sendCommand(unsigned char command);
    void sendData(unsigned char data);
    void sendDataContinuation(unsigned char data);
    void updateState();
};
#endif
