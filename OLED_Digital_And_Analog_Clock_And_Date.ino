
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OLED Analog and Digital Clock and Date

//----------------------------------------Include Library
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//----------------------------------------

//----------------------------------------Initialize RTC_DS1307Initialize RTC_DS1307
RTC_DS1307 rtc;
//----------------------------------------

//----------------------------------------OLED size configuration in Pixels
#define SCREEN_WIDTH 128 //--> OLED display width, in pixels
#define SCREEN_HEIGHT 64 //--> OLED display height, in pixels
//----------------------------------------

//----------------------------------------Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//----------------------------------------

//----------------------------------------Variables for Time and Date
byte _day, _month, _hour24, _hour12, _minute, _second, _dtw;
int _year;
byte hr24;
char st[2];
char _nameoftheDay[9];
char _monthsName[3];

const char daysOfTheWeek_0[] PROGMEM = "Sunday";   
const char daysOfTheWeek_1[] PROGMEM = "Monday";
const char daysOfTheWeek_2[] PROGMEM = "Tuesday";
const char daysOfTheWeek_3[] PROGMEM = "Wednesday";
const char daysOfTheWeek_4[] PROGMEM = "Thursday";
const char daysOfTheWeek_5[] PROGMEM = "Friday";
const char daysOfTheWeek_6[] PROGMEM = "Saturday";

const char* const daysOfTheWeek_table[] PROGMEM = {daysOfTheWeek_0, daysOfTheWeek_1, daysOfTheWeek_2, daysOfTheWeek_3, daysOfTheWeek_4, daysOfTheWeek_5, daysOfTheWeek_6};

const char months_name_0[] PROGMEM = "Jan";   
const char months_name_1[] PROGMEM = "Feb";
const char months_name_2[] PROGMEM = "Mar";
const char months_name_3[] PROGMEM = "Apr";
const char months_name_4[] PROGMEM = "May";
const char months_name_5[] PROGMEM = "Jun";
const char months_name_6[] PROGMEM = "Jul";
const char months_name_7[] PROGMEM = "Aug";
const char months_name_8[] PROGMEM = "Sep";
const char months_name_9[] PROGMEM = "Oct";
const char months_name_10[] PROGMEM = "Nov";
const char months_name_11[] PROGMEM = "Dec";

const char* const months_name_table[] PROGMEM = {months_name_0, months_name_1, months_name_2, months_name_3, 
                                                 months_name_4, months_name_5, months_name_6, months_name_7,
                                                 months_name_8, months_name_9, months_name_10, months_name_11,};
//----------------------------------------

//----------------------------------------Variables for the x and y axis midpoint values of the Analog Clock
byte clockCenterX=31;
byte clockCenterY=31;
//----------------------------------------

//----------------------------------------Variable for Analog Clock Frames
// 'Clock', 63x63px
const unsigned char Clock_Frame [] PROGMEM = {
  0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xe0, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0xf0, 0x18, 0x70, 0x1e, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x28, 0x88, 0x07, 0x80, 0x00, 
  0x00, 0x07, 0x00, 0x08, 0x08, 0x01, 0xc0, 0x00, 0x00, 0x1c, 0x00, 0x08, 0x10, 0x00, 0x70, 0x00, 
  0x00, 0x38, 0x20, 0x08, 0x20, 0x10, 0x38, 0x00, 0x00, 0x70, 0x20, 0x08, 0x40, 0x10, 0x1c, 0x00, 
  0x00, 0xe0, 0x10, 0x3e, 0xf8, 0x20, 0x0e, 0x00, 0x01, 0xc0, 0x10, 0x00, 0x00, 0x20, 0x07, 0x00, 
  0x01, 0x80, 0x08, 0x00, 0x00, 0x40, 0x03, 0x00, 0x03, 0x00, 0x08, 0x00, 0x00, 0x40, 0x01, 0x80, 
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x38, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 
  0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
  0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
  0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
  0xc7, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 0xc6, 0xc8, 0x80, 0x00, 0x07, 0xc0, 0x00, 0x02, 0x26, 
  0xc8, 0x80, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x26, 0xc7, 0x80, 0x00, 0x0c, 0x60, 0x00, 0x00, 0xc6, 
  0xc0, 0x80, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x26, 0xc1, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x02, 0x26, 
  0xce, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 0xc6, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
  0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
  0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
  0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x38, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
  0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x08, 0x00, 0x00, 0x20, 0x01, 0x80, 
  0x01, 0x80, 0x08, 0x00, 0x00, 0x20, 0x03, 0x00, 0x01, 0xc0, 0x10, 0x00, 0x00, 0x10, 0x07, 0x00, 
  0x00, 0xe0, 0x10, 0x03, 0x80, 0x10, 0x0e, 0x00, 0x00, 0x70, 0x20, 0x06, 0x00, 0x08, 0x1c, 0x00, 
  0x00, 0x38, 0x20, 0x04, 0x00, 0x08, 0x38, 0x00, 0x00, 0x1c, 0x00, 0x07, 0x80, 0x00, 0x70, 0x00, 
  0x00, 0x07, 0x00, 0x04, 0x40, 0x01, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x04, 0x40, 0x07, 0x80, 0x00, 
  0x00, 0x00, 0xf0, 0x03, 0x80, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xe0, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00
};
//----------------------------------------

//----------------------------------------Variables for Millis to update Time and Date. Also for the Alarm interval
unsigned long previousMillisGetTimeDate = 0; //--> will store last time was updated
const long intervalGetTimeDate = 1000; //--> interval (milliseconds)         
//----------------------------------------

//________________________________________________________________________void setup()
void setup() {
  Serial.begin(9600);
  delay(1000);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> If that doesn't work, use this line of code outside of "if (! rtc.isrunning())"
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  // following line sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> Use this line of code if it doesn't work in "if (! rtc.isrunning())"
  // rtc.adjust(DateTime(2020, 12, 2, 22, 23, 0));
  // If the time and date are successfully set, then deactivate the code line (make the code a comment), then re-upload the code.
  // if not done then the time and date will return to the beginning when it was set when arduino is reset or restarted.

  //----------------------------------------SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x3C for 128x32 and Address 0x3D for 128x64.
  // But on my 128x64 module the 0x3D address doesn't work. What works is the 0x3C address.
  // So please try which address works on your module.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //--> Don't proceed, loop forever
  }
  //----------------------------------------
  
  //----------------------------------------Show initial display buffer contents on the screen
  // the library initializes this with an Adafruit splash screen.
  // Show the display buffer on the screen(Update screen). You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(1000);
  //----------------------------------------
}
//________________________________________________________________________

//________________________________________________________________________void loop()
void loop() {
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++ To update the Time and Date
  unsigned long currentMillisGetTimeDate = millis();
  if (currentMillisGetTimeDate - previousMillisGetTimeDate >= intervalGetTimeDate) {
    // save the last time you blinked the LED
    previousMillisGetTimeDate = currentMillisGetTimeDate;

    GetDateTime();
    
    display.clearDisplay();
    
    Draw_Clock_Frame();
    Analog_Clock(_hour12,_minute,_second);
    Digital_Clock_and_Date(_hour24, _minute, _second, _dtw, _day, _month ,_year);

    display.display();
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
//________________________________________________________________________

//________________________________________________________________________Subroutine to retrieve or update the time and date from DS1307 RTC
void GetDateTime(){
  DateTime now = rtc.now();
  _day=now.day();
  _month=now.month();
  _year=now.year();
  _hour24=now.hour();
  _minute=now.minute();
  _second=now.second();
  _dtw=now.dayOfTheWeek();

  hr24=_hour24;
  if (hr24>12) {
    _hour12=hr24-12;
  }
  else if (hr24==0) {
    _hour12=12;
  }
  else {
    _hour12=hr24;
  }

  if (hr24<12) {
    strcpy(st, "AM");
  }
  else {
    strcpy(st, "PM");
  }  
}
//________________________________________________________________________

//________________________________________________________________________Subroutine for drawing Analog Clock
void Analog_Clock(byte h, byte m, byte s) {
  Draw_Line_Seconds(s);
  Draw_Line_Minutes(m);
  Draw_Line_Hours(h,m);
  
  for (byte i = 30; i < 33; i++) {
    display.drawPixel(i, 30, SSD1306_BLACK);
    display.drawPixel(i, 31, SSD1306_BLACK);
    display.drawPixel(i, 32, SSD1306_BLACK);
  }
}
//________________________________________________________________________

//________________________________________________________________________Subroutines for drawing Seconds on an Analog Clock
void Draw_Line_Seconds(int s) {
  float angle = s * 6 ;
  angle = (angle / 57.29577951); //--> Convert degrees to radians 
   
  // 16 is the length of the "second line" on the Analog Clock
  int xS = (clockCenterX + (sin(angle) * (16)));
  int yS = (clockCenterY - (cos(angle) * (16)));

  //----------------------------------------Special condition at the 15th second, because at that second the line is not symmetrical
  if (s == 15) {
    display.drawLine(clockCenterX, clockCenterY, xS, yS + 1, WHITE);
  } else {
    display.drawLine(clockCenterX, clockCenterY, xS, yS, WHITE);
  }
  //----------------------------------------
}
//________________________________________________________________________

//________________________________________________________________________Subroutine for drawing Minutes on an Analog Clock
void Draw_Line_Minutes(int m) {
  float angle = m * 6 ;
  angle = (angle / 57.29577951) ; //Convert degrees to radians  

  // 17 is the length of the "minute line" on the Analog Clock
  int xM = (clockCenterX + (sin(angle) * (17)));
  int yM = (clockCenterY - (cos(angle) * (17)));

  //----------------------------------------Special condition at minute 15, because at that minute the line is not symmetrical
  if (m == 15) {
    display.drawLine(clockCenterX, clockCenterY - 1, xM, yM + 1, WHITE);
    display.drawLine(clockCenterX - 1, clockCenterY, xM, yM + 1, WHITE);
    display.drawLine(clockCenterX, clockCenterY, xM, yM + 1, WHITE);
    display.drawLine(clockCenterX + 1, clockCenterY, xM, yM + 1, WHITE);
    display.drawLine(clockCenterX, clockCenterY + 1, xM, yM + 1, WHITE);
  } else {
    display.drawLine(clockCenterX, clockCenterY - 1, xM, yM, WHITE);
    display.drawLine(clockCenterX - 1, clockCenterY, xM, yM, WHITE);
    display.drawLine(clockCenterX, clockCenterY, xM, yM, WHITE);
    display.drawLine(clockCenterX + 1, clockCenterY, xM, yM, WHITE);
    display.drawLine(clockCenterX, clockCenterY + 1, xM, yM, WHITE);
  }
  //----------------------------------------
}
//________________________________________________________________________

//________________________________________________________________________Subroutine for drawing Hour on an Analog Clock
void Draw_Line_Hours(int h, int m) {
  float angle = h * 30 + int((m / 12) * 6);
  angle = (angle / 57.29577951) ; //Convert degrees to radians

  // 12 is the length of the "hour line" on the Analog Clock
  int xH = (clockCenterX + (sin(angle) * (12)));
  int yH = (clockCenterY - (cos(angle) * (12)));

  //----------------------------------------Special condition at 12 o'clock, because at that hour the line is not symmetrical
  if (h == 12 && m < 12) {
    display.drawLine(clockCenterX, clockCenterY - 2, xH + 1, yH, WHITE);
    display.drawLine(clockCenterX - 2, clockCenterY, xH + 1, yH, WHITE);    
    display.drawLine(clockCenterX, clockCenterY - 1, xH + 1, yH, WHITE);
    display.drawLine(clockCenterX - 1, clockCenterY, xH + 1, yH, WHITE);
    display.drawLine(clockCenterX, clockCenterY, xH + 1, yH, WHITE);
    display.drawLine(clockCenterX + 1 ,clockCenterY, xH + 1, yH, WHITE);
    display.drawLine(clockCenterX, clockCenterY + 1, xH + 1, yH, WHITE);
    display.drawLine(clockCenterX + 2, clockCenterY, xH + 1, yH ,WHITE);
    display.drawLine(clockCenterX, clockCenterY + 2, xH + 1, yH, WHITE);
  } else {
    display.drawLine(clockCenterX, clockCenterY - 2, xH, yH, WHITE);
    display.drawLine(clockCenterX - 2, clockCenterY, xH, yH, WHITE);    
    display.drawLine(clockCenterX, clockCenterY - 1, xH, yH, WHITE);
    display.drawLine(clockCenterX - 1, clockCenterY, xH, yH, WHITE);
    display.drawLine(clockCenterX, clockCenterY, xH, yH, WHITE);
    display.drawLine(clockCenterX + 1 ,clockCenterY, xH, yH, WHITE);
    display.drawLine(clockCenterX, clockCenterY + 1, xH, yH, WHITE);
    display.drawLine(clockCenterX + 2, clockCenterY, xH, yH ,WHITE);
    display.drawLine(clockCenterX, clockCenterY + 2, xH, yH, WHITE);
  }
  //----------------------------------------
}
//________________________________________________________________________

//________________________________________________________________________Subroutine for drawing frames on an analog clock
void Draw_Clock_Frame() {
  display.drawBitmap(0, 0, Clock_Frame, 63, 63, WHITE); //--> display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
}
//________________________________________________________________________

//________________________________________________________________________Subroutines for displaying Digital Clock and Date
void Digital_Clock_and_Date(byte h, byte m, byte s, byte dtw, byte dy, byte mt, int yr) {
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //----------------------------------------To display Digital Clock
  display.setCursor(73, 0);
  if (h < 10) {
    display.print("0");
    display.print(h);
  } else {
    display.print(h);
  }
  display.print(":");
  if (m < 10) {
    display.print("0");
    display.print(m);
  } else {
    display.print(m);
  }
  display.print(":");
  if (s < 10) {
    display.print("0");
    display.print(s);
  } else {
    display.print(s);
  }    
  //----------------------------------------

  //----------------------------------------To display Day Name
  strcpy_P(_nameoftheDay,(char*)pgm_read_word(&(daysOfTheWeek_table[dtw])));
  byte display_center_area = (127 - 65) / 2;
  byte center_text = (strlen(_nameoftheDay) * 6) / 2;
  byte x_text = 66 + (display_center_area - center_text);
  display.setCursor(x_text, 23); //--> (x position, y position)
  display.println(_nameoftheDay); 
  //----------------------------------------

  //----------------------------------------To display the Date
  strcpy_P(_monthsName,(char*)pgm_read_word(&(months_name_table[mt-1])));
  display.setCursor(76, 45); //--> (x position, y position)
  if (dy < 10) {
    display.print("0");
    display.print(dy);
  } else {
    display.print(dy);
  }
  display.print(", ");
  display.print(_monthsName);
  display.setCursor(85, 55);
  display.print(yr);
  //----------------------------------------
}
//________________________________________________________________________

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



