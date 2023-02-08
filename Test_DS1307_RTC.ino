//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test DS1307 RTC

//################################################################################################################################
//# -DS1307 12 Hour Format : https://forum.arduino.cc/index.php?topic=22029.0                                                    #
//# -RTClib.h : https://github.com/adafruit/RTClib                                                                               #
//################################################################################################################################

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

int _day, _month, _year, _hour24, _hour12, _minute, _second, _dtw;
int hr24;

String st;

char nameoftheday[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino RTC DS1307");
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
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> Use this line of code if it doesn't work in "if (! rtc.isrunning())"
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  // If the time and date are successfully set, then deactivate the code line (make the code a comment), then re-upload the code.
  // if not done then the time and date will return to the beginning when it was set when arduino is reset or restarted.
}

void loop() {
  GetDateTime();
  Serial.print(nameoftheday[_dtw]);
  Serial.print(',');    
  Serial.print(_day, DEC);
  Serial.print('/');
  Serial.print(_month, DEC);
  Serial.print('/');
  Serial.print(_year, DEC);
  Serial.print(" ");   
  Serial.print(_hour24, DEC);
  Serial.print(':');
  Serial.print(_minute, DEC);
  Serial.print(':');
  Serial.print(_second, DEC);

  Serial.print(' ');

  Serial.print(_hour12, DEC);
  Serial.print(':');
  Serial.print(_minute, DEC);
  Serial.print(':');
  Serial.print(_second, DEC);
  Serial.print(' ');
  Serial.print(st);

  Serial.println();
  delay(1000);
}

//------------------------------------------------------------------------Subroutine to retrieve or update the time and date from DS1307
void GetDateTime() {
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
    st="AM";
  }
  else {
    st="PM"; 
  }  
}
//------------------------------------------------------------------------

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



