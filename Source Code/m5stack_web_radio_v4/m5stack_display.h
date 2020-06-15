// m5stack_display.h
//
// Contributed by harm@certeza.nl
// Separated from the main sketch to allow M5Stack display.
// Tested on 320 x 240.
// Below set your dsp_getwidth() and dsp_getwidth() to suite your display.

#define M5STACK
#define TFT_BL 0

#include <M5Stack.h>

// Color definitions for the TFT screen
#define CYAN    GREEN | BLUE
#define MAGENTA RED | BLUE
#define YELLOW  RED | GREEN
#define WHITE   RED | BLUE | GREEN

// Data to display.  There are TFTSECS sections
#define TFTSECS 4

scrseg_struct tftdata[TFTSECS] =                        // Screen divided in 3 segments + 1 overlay
{                                                       // One text line is 8 pixels
  { false, WHITE,    0,  16, "" },                      // 1 top line
  { false, CYAN,    30, 128, "" },                      // 8 lines in the middle
  { false, YELLOW, 164,  64, "" },                      // 4 lines at the bottom
  { false, GREEN,  164,  64, "" }                       // 4 lines at the bottom for rotary encoder
} ;

// For instance of display driver
bool dsp_tft = false;

// Various macro's to mimic the ILI9341 version of display functions
#define dsp_setRotation()       //tft->setRotation (3)               // Use landscape format, not needed on M5Stack
#define dsp_print(a)            M5.Lcd.print ( a )                   // Print a string 
#define dsp_println(b)          M5.Lcd.println ( b )                 // Print a string followed by newline 
#define dsp_fillRect(a,b,c,d,e) M5.Lcd.fillRect ( a, b, c, d, e ) ;  // Fill a rectange
#define dsp_setTextSize(a)      M5.Lcd.setTextSize(a)                // Set the text size
#define dsp_setTextColor(a)     M5.Lcd.setTextColor(a)               // Set the text color
#define dsp_setCursor(a,b)      M5.Lcd.setCursor ( a, b )            // Position the cursor
#define dsp_erase()             M5.Lcd.fillScreen ( BLACK ) ;        // Clear the screen
#define dsp_getwidth()          320                                  // Adjust to your display
#define dsp_getheight()         240                                  // Get height of screen
#define dsp_update()                                                 // Updates to the physical screen
#define dsp_usesSPI()           true                                 // Does use SPI


bool dsp_begin()
{
  dsp_tft = true;
  M5.begin();                                                    // Init TFT interface
  return ( true ) ;
}

//**************************************************************************************************
//                                      D I S P L A Y B A T T E R Y                                *
//**************************************************************************************************
// Show the current battery charge level on the screen.                                            *
// It will overwrite the top divider.                                                              *
// No action if bat0/bat100 not defined in the preferences.                                        *
//**************************************************************************************************
void displaybattery()
{
  if ( dsp_tft )
  {
    if ( ini_block.bat0 < ini_block.bat100 )              // Levels set in preferences?
    {
      static uint16_t oldpos = 0 ;                        // Previous charge level
      uint16_t        ypos ;                              // Position on screen
      uint16_t        v ;                                 // Constrainted ADC value
      uint16_t        newpos ;                            // Current setting

      v = constrain ( adcval, ini_block.bat0,             // Prevent out of scale
                      ini_block.bat100 ) ;
      newpos = map ( v, ini_block.bat0,                   // Compute length of green bar
                     ini_block.bat100,
                     0, dsp_getwidth() ) ;
      if ( newpos != oldpos )                             // Value changed?
      {
        oldpos = newpos ;                                 // Remember for next compare
        ypos = tftdata[1].y - 7 ;                         // Just before 1st divider
        dsp_fillRect ( 0, ypos, newpos, 2, GREEN ) ;      // Paint green part
        dsp_fillRect ( newpos, ypos,
                       dsp_getwidth() - newpos,
                       2, RED ) ;                          // Paint red part
      }
    }
  }
}


//**************************************************************************************************
//                                      D I S P L A Y V O L U M E                                  *
//**************************************************************************************************
// Show the current volume as an indicator on the screen.                                          *
// The indicator is 2 pixels heigh.                                                                *
//**************************************************************************************************
void displayvolume()
{
  if ( dsp_tft )
  {
    static uint8_t oldvol = 0 ;                         // Previous volume
    uint8_t        newvol ;                             // Current setting
    uint16_t       pos ;                                // Positon of volume indicator

    newvol = vs1053player->getVolume() ;                // Get current volume setting
    if ( newvol != oldvol )                             // Volume changed?
    {
      oldvol = newvol ;                                 // Remember for next compare
      pos = map ( newvol, 0, 100, 0, dsp_getwidth() ) ; // Compute position on TFT
      dsp_fillRect ( 0, dsp_getheight() - 6,
                     pos, 2, RED ) ;                    // Paint red part
      dsp_fillRect ( pos, dsp_getheight() - 6,
                     dsp_getwidth() - pos, 2, GREEN ) ; // Paint green part
    }
  }
}


//**************************************************************************************************
//                                      D I S P L A Y T I M E                                      *
//**************************************************************************************************
// Show the time on the LCD at a fixed position in a specified color                               *
// To prevent flickering, only the changed part of the timestring is displayed.                    *
// An empty string will force a refresh on next call.                                              *
// A character on the screen is 8 pixels high and 6 pixels wide.                                   *
//**************************************************************************************************
void displaytime ( const char* str, uint16_t color )
{
  static char oldstr[9] = "........" ;             // For compare
  uint8_t     i ;                                  // Index in strings
  uint16_t    pos = dsp_getwidth() + TIMEPOS ;     // X-position of character, TIMEPOS is negative

  if ( str[0] == '\0' )                            // Empty string?
  {
    for ( i = 0 ; i < 8 ; i++ )                    // Set oldstr to dots
    {
      oldstr[i] = '.' ;
    }
    return ;                                       // No actual display yet
  }
  if ( dsp_tft )                                       // TFT active?
  {
    dsp_setTextColor ( color ) ;                   // Set the requested color
    for ( i = 0 ; i < 8 ; i++ )                    // Compare old and new
    {
      if ( str[i] != oldstr[i] )                   // Difference?
      {
        dsp_fillRect ( pos, 0, 12, 16, BLACK ) ;   // Clear the space for new character
        dsp_setCursor ( pos, 0 ) ;                 // Prepare to show the info
        dsp_print ( str[i] ) ;                     // Show the character
        oldstr[i] = str[i] ;                       // Remember for next compare
      }
      pos += 12 ;                                   // Next position
    }
  }
}
