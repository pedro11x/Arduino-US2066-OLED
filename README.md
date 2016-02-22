US2066 OLED driver library for Arduino
=========================
The US2066 driver is user in some EastRising displays like the ER-OLEDM1602 - 4

This is my atempt at writing a library for the US2066 based on the [1602-OLED-Arduino-Library(for the Wide.HK OLED 1602 display)](https://github.com/gadjet/1602-OLED-Arduino-Library) Written by Phil Grant (gadjet).

## The setup
1. Make sure the hardware hardware switches are ***0 1 0*** (BS2=0, BS1=1, BS0=0) to make the display talk via I2C.  
The ER-OLEDM1602 came with 8080 parallel as default (1 1 0) which needs to be changed by changing the position of the resistor BS2.

2. Ground pins D7-D3, RD, RW, DC and CS and pull the reset pin HIGH(or connect it to the arduino if you want the arduino to reset it at any time).
This is essential for the stability of the display.
Setting the DC pin HIGH instead of LOW will change the I2C address from 0x3C to 0x3D.

3. Connect GND (VSS) to Ground.  
VDD to +5v or +3.3v.
Connect both D2 and D1 to SDA ( A4 on the arduino uno ).
Connect D0 to SCL ( A5 on the uno  ).
You also should pull both SCL and SDA high (individually!) using two 4.7k resistors.

4. Write the code by beginning to create the US2066 object and calling init();
By running init, the OLED will be initialized with the **CGROM A** which is required for the bar function to work.
(Note: init does not turn off the internal regulator which i don't think is necessary but i could be wrong. If you want to uncomment the code at the beginning of init)

5. print!  

  
    #include"US2066.h"

    US2066 OLED();

    void setup()  
    {  
      OLED.init();  
      OLED.print("Hello world!");  
    }  
    ...

## Library Functions
##### Default constructor (for default address Ox3C)  

    US2066();

##### Constructor for custom I2C address  

    US2066(uint8_t addr);

##### Destructor  

    ~US2066();

##### Initialize the display  

    void init();

##### Print character from current cursor position  

    void print(char c);

##### Print from current cursor position  

    void print(const char *String);

##### Print from defined cursor position  
  col - Starting column  
  row - Starting row  

    void print(uint8_t row, uint8_t col, const char *String);

##### Display progress bar on screen  
  col - column in which the bar starts  
  row - row in which the bar starts  
  size - size of the bar when full (in number of on screen characters)  
  value - status of the bar in percentage (0 - 100)  
  This only works if the CGROM A is selected  
  (which is selected, by default, by the init function)

    void bar(uint8_t row, uint8_t col, int size, int value);  

##### Clears the display  

    void clear();

##### Sends cursor home (row = 0, column = 0)  

    void home();

##### Turn on blinking cursor  
  true   - on  
  false  - off  

    void blinkingCursor(uint8_t state);

##### Set cursor position  

    void cursor(uint8_t row, uint8_t col);
