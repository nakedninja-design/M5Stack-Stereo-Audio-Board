#ifndef DDP
#define DDP

#include "Arduino.h"
#include "SPI.h"

class DualDigitalPotmeter
{
  private:
    byte wiper0writeAddr = B00000000;
    byte wiper1writeAddr = B00010000;
    byte tconwriteAddr   = B01000000;
    byte tcon_0off_1on   = B11110000;
    byte tcon_0on_1off   = B00001111;
    byte tcon_0off_1off  = B00000000;
    byte tcon_0on_1on    = B11111111;
    int8_t cs_pin;                     // Pin where CS line is connected
    int8_t shutdown_pin;
    int8_t current_volume = 0;
    bool SPI_activated;

  protected:
    // This function takes care of sending SPI data to the pot.
    void digitalPotWrite ( int address, int value ) {  
      // take the SS pin low to select the chip:
      digitalWrite(cs_pin, LOW);
      //  send in the address and value via SPI:
      SPI.transfer(address);
      SPI.transfer(value);
      // take the SS pin high to de-select the chip:
      digitalWrite(cs_pin, HIGH); 
    }
  
  public:
    // Constructor.  Only sets pin values.  Doesn't touch the chip.  Be sure to call begin()!
    DualDigitalPotmeter ( int8_t _cs_pin, int8_t _shutdown_pin, bool _SPI_activated ) ;
    void begin();                    // Begin operation.  Sets pins correctlycand prepares SPI bus.
    int8_t getVolume();
    void setVolume( int value); 

};


DualDigitalPotmeter::DualDigitalPotmeter ( int8_t _cs_pin, int8_t _shutdown_pin, bool _SPI_activated ):  
   cs_pin (_cs_pin), shutdown_pin (_shutdown_pin), SPI_activated ( _SPI_activated ) 
{
}

// Begin operation.  Sets pins correctlycand prepares SPI bus
void DualDigitalPotmeter::begin()                     
{
    // set the slaveSelectPin as an output:
    pinMode( cs_pin, OUTPUT ) ;                  

    if (!SPI_activated) {
       // This should not happen!!!
       // initialize SPI:
       SPI.begin();
    }
  
    if (shutdown_pin > 0) {
      // set the shutdown pin as an output
      pinMode (shutdown_pin, OUTPUT);  
      //Turn off shutdown
      digitalWrite(shutdown_pin, HIGH); 
    }
    setVolume(0); // 0-255
}

int8_t DualDigitalPotmeter::getVolume () 
{      
  return current_volume;
}

void DualDigitalPotmeter::setVolume (int value) 
{   
  int mapped_value; 
  
  // map value to potmeter range
  mapped_value = map(value, 0, 100, 0, 255);
 
  digitalPotWrite (wiper0writeAddr, value); // Set wiper 0 to value
  digitalPotWrite (wiper1writeAddr, value); // Set wiper 1 to value
  current_volume = value;
  delay(10);
  
  //digitalPotWrite(tconwriteAddr, tcon_0off_1on); // Disconnect wiper 0 with TCON register
  //delay(10);
  
  //digitalPotWrite(tconwriteAddr, tcon_0off_1off); // Disconnect both wipers with TCON register
  //digitalPotWrite(wiper0writeAddr, 255); //Set wiper 0 to 255
  //delay(10);
  
  //digitalPotWrite(tconwriteAddr, tcon_0on_1on); // Connect both wipers with TCON register
}

#endif
