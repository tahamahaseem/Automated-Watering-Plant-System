// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;
int statusTime = 61;
int ss = -1;
int mm = 0;
int hh = 0;
int os;

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(9600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop () {
  DateTime now = rtc.now();
  os = now.second();
  //Serial.print(os);
  //Serial.print(" ");
  //Serial.println(statusTime);

  //Serial.print(now.second(), DEC);
  if (os != statusTime) {
    statusTime = os;
    ss++;
    if (ss == 60) {
      mm++;
      ss = 0;
      if (mm == 60) {
        hh++;
        mm = 0;
      }
      if (hh == 24) {
        hh = 0;
      }
    }
  }
  Serial.print(hh);
  Serial.print(" : ");
  Serial.print(mm);
  Serial.print(" : ");
  Serial.print(ss);

}
