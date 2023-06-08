// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

int ss;
int mm;
int hh;
RTC_DS1307 rtc;
DateTime now = rtc.now();

int secondpassed = now.second();

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup () {
  Serial.begin(9600);
  Serial.print("Tahamah");
  //  while (!Serial); // for Leonardo/Micro/Zero
  //
  //  if (! rtc.begin()) {
  //    Serial.println("Couldn't find RTC");
  //    while (1);
  //  }
  //  if (! rtc.isrunning()) {
  //    Serial.println("RTC is NOT running!");
  //    // following line sets the RTC to the date & time this sketch was compiled
  //    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //    // This line sets the RTC with an explicit date & time, for example to set
  //    // January 21, 2014 at 3am you would call:
  //    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  //  }

}
void loop () {

  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  // calculate a date which is 7 days and 30 seconds into the future
  // DateTime future (now + TimeSpan(7, 12, 30, 6));
  // Serial.print(" now + 7d + 30s: ");
  //    Serial.print(future.year(), DEC);
  //    Serial.print('/');
  //    Serial.print(future.month(), DEC);
  //    Serial.print('/');
  //    Serial.print(future.day(), DEC);
  //    Serial.print(' ');
  //    Serial.print(future.hour(), DEC);
  //    Serial.print(':');
  //    Serial.print(future.minute(), DEC);
  //    Serial.print(':');
  //    Serial.print(future.second(), DEC);
  //    Serial.println();
  //    Serial.println();
  //  delay(3000);
  Serial.println(secondpassed);
  //  if (secondpassed != now.second()) {
  //    secondpassed = now.second();
  //    Serial.println("second passed");
  //    Serial.print(hh);
  //    Serial.print(", ");
  //    Serial.print(mm);
  //    Serial.print(", ");
  //    Serial.print(ss);
  //    ss++;
  //    if (ss == 60) {
  //      ss = 0;
  //      mm++;
  //      if (mm == 60) {
  //        mm = 0;
  //        hh++;
  //
  //      }
  //    }



}
