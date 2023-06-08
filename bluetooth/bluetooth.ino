
char junk;
String inputString = "";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available()) {
    while (Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
 

 Serial.println(inputString);
    while (Serial.available() > 0)
    {
      junk = Serial.read() ;  // clear the serial buffer
    }
    if (inputString == "a") {       //in case of 'a' turn the LED on
      digitalWrite(13, HIGH);
    } else if (inputString == "b") { //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
    }
    inputString = "";
  } 

}
