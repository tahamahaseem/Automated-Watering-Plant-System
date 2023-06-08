#include "RTClib.h"
RTC_DS3231 rtc;
int statusTime = 61;
int ss = -1;
int mm = 0;
int hh = 0;
int os;


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26, 16, 2); // set the LCD address to 0x26 for a 16 chars and 2 line display

//Moisture Sensor
const int AirValue = 520;   //you need to replace this value with Value_1
const int WaterValue = 240;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;


//BLUETOOTH
char junk;
String inputString = "";
String lightLevelDisplayValue;



//Humidity/Temp
#include <dht.h>
#define dht_apin A2 // Analog Pin sensor is connected to

dht DHT;


//LED MATRIX
#include <FastLED.h>
#define NUM_LEDS      64
#define LED_TYPE   WS2811
#define COLOR_ORDER   GRB
#define DATA_PIN        5
#define VOLTS          12
#define MAX_MA       4000
CRGBArray<NUM_LEDS> leds;
#define TWINKLE_SPEED 4
#define TWINKLE_DENSITY 5
#define SECONDS_PER_PALETTE  30
CRGB gBackgroundColor = CRGB::Black;
#define AUTO_SELECT_BACKGROUND_COLOR 0
#define COOL_LIKE_INCANDESCENT 1
CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;

const int fanPin = 12;
const int waterPump = 13;
boolean cooldown = false;
int cooldownFinished;



const int photoResistor = A3;
int moistureSensor = A1;
boolean lightStatus = false;
boolean noInterrupt = true;
const int buzzer = 11; //buzzer
float moistureValue = 0;

const int button = 2;
int next = 1;
boolean buttonPressed = false;
boolean buttonReleased = true;

int waterLevel = A0;
String waterLevelStatus;
boolean waterPumpBool = false;


#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);   // tell servo to go to position in variable 'pos'



  Serial.begin(9600);
  delay( 3000 ); //safety startup delay

  pinMode(button, INPUT );
  pinMode(moistureSensor, INPUT );
  pinMode(fanPin, OUTPUT);//Fan relay control
  pinMode(waterPump, OUTPUT);//Pump relay control
  pinMode(photoResistor, INPUT);// Photoresistor input
  pinMode(buzzer, OUTPUT); // Buzzer

  //LED MATRIX
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
  .setCorrection(TypicalLEDStrip);
  chooseNextColorPalette(gTargetPalette);


  lcd.init();
  lcd.backlight();








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
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }


}


void loop()
{
  //manages time to display on LCD 
  DateTime now = rtc.now();
  os = now.second();

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



//temperature and humidity sensor
  DHT.read11(dht_apin);

  if ((DHT.temperature >= 28) || (DHT.humidity >= 50 )) {
    myservo.write(180);
    digitalWrite(fanPin, HIGH);

  } else {
    myservo.write(0);
    digitalWrite(fanPin, LOW);
  }

//waterlevel sensor

  float waterLevelValue = analogRead(waterLevel);
  if (waterLevelValue <= 200) {
    waterLevelStatus = "Empty";
  }
  else if (waterLevelValue <= 500) {
    waterLevelStatus = "Low";
  }
  else if (waterLevelValue <= 560) {
    waterLevelStatus = "Low";
  }
  else if (waterLevelValue > 560) {
    waterLevelStatus = "High";
  }

  if (waterLevelValue <= 500) {
    if (ss % 2 == 0) {
      tone(buzzer, 500); // Send 1KHz sound signal...

    } else {
      noTone(buzzer);
    }
  } else {
    noTone(buzzer);
  }





  //SOIL MOISTURE
  soilMoistureValue = analogRead(moistureSensor);  //put Sensor insert into soil
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent >= 100)
  {
    soilmoisturepercent = 100;
  }
  else if (soilmoisturepercent <= 0)
  {
    soilmoisturepercent = 0;
  }

  if (soilmoisturepercent < 20 && (cooldown != true) && (waterLevelValue >= 500)) {
    digitalWrite(fanPin, LOW);
    delay(250);
    digitalWrite(waterPump, HIGH);
    delay(1500);
    digitalWrite(waterPump, LOW);
    delay(250);
    cooldown = true;
    cooldownFinished = ss - 1;
    ss = 0;
    mm = 0;
    hh = 0;
    if (ss == 0) {
      cooldownFinished = 59;
    }
  }
  if ((ss == (cooldownFinished)) && (cooldown == true)) {
    cooldown = false;
  }




  //Photo Resistor for light levels
  int lightValue = analogRead(photoResistor);

  if (lightValue <= 5) {
    lightLevelDisplayValue = "Poor";

  } else if (lightValue <= 20) {
    lightLevelDisplayValue = "Satisfactory";

  }
  else if (lightValue < 100) {
    lightLevelDisplayValue = "Good";

  }
  else {
    lightLevelDisplayValue = "Amazing :)";


  }



  //PUSH BUTTON and BUZZER
  if (digitalRead(button) == 0) {
    buttonPressed = true;
    buttonReleased = false;

  }
  if (digitalRead(button) == 1) {
    buttonReleased = true;

  }

  if (buttonPressed && buttonReleased) {
    buttonPressed = false;
    if (next == 6) {
      next = 1;
    } else {
      next++;
    }
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(200);
    noTone(buzzer);     // Stop sound...
  }

  if (ss % 2 == 0 || (buttonPressed && buttonReleased)) {


    lcd.clear();
    lcd.setCursor(0, 0);
    switch (next) {
      case 1:
        lcd.print("WATER LEVELS:");
        lcd.setCursor(8, 1);
        lcd.print(waterLevelStatus);
        break;
      case 2:
        lcd.print("MOISTURE LEVELS:");
        lcd.setCursor(8, 1);
        lcd.print(soilmoisturepercent);
        lcd.print("%");
        break;
      case 3:
        lcd.print("LIGHT LEVELS:");
        lcd.setCursor(4, 1);
        lcd.print(lightLevelDisplayValue);
        break;

      case 4:
        lcd.print("HUMIDITY LEVEL:");
        lcd.setCursor(8, 1);
        //lcd.print(sensorValues[3]);
        lcd.print(DHT.humidity);
        lcd.print("%  ");
        break;
      case 5:
        lcd.print("TEMPERATURE:");
        lcd.setCursor(8, 1);
        lcd.print(DHT.temperature);
        lcd.print("C  ");
        break;
      case 6:
        lcd.print("LAST WATERED:");
        lcd.setCursor(8, 1);
        // lcd.print("RTC TIME");
        lcd.print(hh);
        lcd.setCursor(10, 1);
        lcd.print(":");
        lcd.setCursor(11, 1);
        lcd.print(mm);
        lcd.setCursor(13, 1);
        lcd.print(":");
        lcd.setCursor(14, 1);
        lcd.print(ss);
        break;
      case 0:
        lcd.clear();
        break;
    }
  }







  //LED MATRIX AND PHOTORESISTOR INTERACTION
  EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
    chooseNextColorPalette( gTargetPalette );
  }
  EVERY_N_MILLISECONDS( 10 ) {
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 12);
  }

  //Serial.println(lightValue);
  if (lightValue >= 10) {
    lightStatus = true;
  } else if (lightValue <= 5) {
    lightStatus = false;
  }

  FastLED.show();
  if (lightStatus) {
    FastLED.setBrightness(0);
  } else {
    drawTwinkles( leds);
    FastLED.setBrightness(255);
  }





  // BLUETOOTH
  if (Serial.available()) {
    //Serial.println(inputString);
    while (Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
      //Serial.println(inputString);
    }



    while (Serial.available() > 0)
    {
      junk = Serial.read() ;  // clear the serial buffer
    }
    // Serial.println(inputString);
    Serial.print("WATER LEVELS:  ");
    Serial.println(waterLevelStatus);
    Serial.print("MOISTURE LEVELS:   ");
    Serial.print(soilmoisturepercent);
    Serial.println("%");
    Serial.print("LIGHT LEVELS:  ");
    Serial.println(lightLevelDisplayValue);
    Serial.print("HUMIDITY LEVELS:   ");
    Serial.print(DHT.humidity);
    Serial.println("%  ");
    Serial.print("TEMPERATURE:  ");
    Serial.print(DHT.temperature);
    Serial.println("C  ");
    Serial.print("WATERED LAST SINCE:  ");
    Serial.print(hh);
    Serial.print(":");
    Serial.print(mm);
    Serial.print(":");
    Serial.println(ss);
    Serial.println();

    inputString = "";
  }


}


//LED MATRIX
void drawTwinkles( CRGBSet& L)
{

  uint16_t PRNG16 = 11337;
  uint32_t clock32 = millis();
  CRGB bg;
  if ( (AUTO_SELECT_BACKGROUND_COLOR == 1) &&
       (gCurrentPalette[0] == gCurrentPalette[1] )) {
    bg = gCurrentPalette[0];
    uint8_t bglight = bg.getAverageLight();
    if ( bglight > 64) {
      bg.nscale8_video( 16); // very bright, so scale to 1/16th
    } else if ( bglight > 16) {
      bg.nscale8_video( 64); // not that bright, so scale to 1/4th
    } else {
      bg.nscale8_video( 86); // dim, scale to 1/3rd.
    }
  } else {
    bg = gBackgroundColor; // just use the explicitly defined background color
  }
  uint8_t backgroundBrightness = bg.getAverageLight();

  for ( CRGB& pixel : L) {
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    uint16_t myclockoffset16 = PRNG16; // use that number as clock offset
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    // use that number as clock speed adjustment factor (in 8ths, from 8/8ths to 23/8ths)
    uint8_t myspeedmultiplierQ5_3 =  ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t  myunique8 = PRNG16 >> 8; // get 'salt' value for this pixel

    // We now have the adjusted 'clock' for this pixel, now we call
    // the function that computes what color the pixel should be based
    // on the "brightness = f( time )" idea.
    CRGB c = computeOneTwinkle( myclock30, myunique8);

    uint8_t cbright = c.getAverageLight();
    int16_t deltabright = cbright - backgroundBrightness;
    if ( deltabright >= 32 || (!bg)) {
      // If the new pixel is significantly brighter than the background color,
      // use the new color.
      pixel = c;
    } else if ( deltabright > 0 ) {
      // If the new pixel is just slightly brighter than the background color,
      // mix a blend of the new color and the background color
      pixel = blend( bg, c, deltabright * 8);
    } else {
      // if the new pixel is not at all brighter than the background color,
      // just use the background color.
      pixel = bg;
    }
  }
}


CRGB computeOneTwinkle( uint32_t ms, uint8_t salt)
{
  uint16_t ticks = ms >> (8 - TWINKLE_SPEED);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8( slowcycle16);
  slowcycle16 =  (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

  uint8_t bright = 0;
  if ( ((slowcycle8 & 0x0E) / 2) < TWINKLE_DENSITY) {
    bright = attackDecayWave8( fastcycle8);
  }

  uint8_t hue = slowcycle8 - salt;
  CRGB c;
  if ( bright > 0) {
    c = ColorFromPalette( gCurrentPalette, hue, bright, NOBLEND);
    if ( COOL_LIKE_INCANDESCENT == 1 ) {
      coolLikeIncandescent( c, fastcycle8);
    }
  } else {
    c = CRGB::Black;
  }
  return c;
}

uint8_t attackDecayWave8( uint8_t i)
{
  if ( i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i / 2));
  }
}

void coolLikeIncandescent( CRGB& c, uint8_t phase)
{
  if ( phase < 128) return;

  uint8_t cooling = (phase - 128) >> 4;
  c.g = qsub8( c.g, cooling);
  c.b = qsub8( c.b, cooling * 2);
}


const TProgmemRGBPalette16 BlueRed_p FL_PROGMEM =
{ CRGB::Blue, CRGB::Red, CRGB::Blue, CRGB::Red,
  CRGB::Blue, CRGB::Red, CRGB::Blue, CRGB::Red,
  CRGB::Blue, CRGB::Red, CRGB::Blue, CRGB::Red,
  CRGB::Blue, CRGB::Red, CRGB::Blue, CRGB::Red
};


const TProgmemRGBPalette16* ActivePaletteList[] = {
  &BlueRed_p,
};


void chooseNextColorPalette( CRGBPalette16& pal)
{
  const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
  static uint8_t whichPalette = -1;
  whichPalette = addmod8( whichPalette, 1, numberOfPalettes);

  pal = *(ActivePaletteList[whichPalette]);
}
