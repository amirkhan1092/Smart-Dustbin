#include <LiquidCrystal.h>
//#include <HCSR04.h>
#include<Servo.h>

Servo myservo;

const int TRIG_PIN1 = 6;
const int ECHO_PIN1 = 7;
const int TRIG_PIN2 = 8;
const int ECHO_PIN2 = 9;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;


// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//HCSR04 hcout(6,7);//initialisation class HCSR04 (trig pin , echo pin)
//HCSR04 hcin(8,9);//initialisation class HCSR04 (trig pin , echo pin)

void setup()
{ 
  lcd.begin(16, 2);
  myservo.attach(10);  // servo motor input pin connected to the pin 10 in Arduino Uno 
  lcd.setCursor(0, 0);
  lcd.print("Smart Dustbin ");
  delay(2000);
  myservo.write(0); 
  
  pinMode(TRIG_PIN1, OUTPUT);
  digitalWrite(TRIG_PIN1, LOW);

  pinMode(TRIG_PIN2, OUTPUT);
  digitalWrite(TRIG_PIN2, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN1, INPUT);
  pinMode(ECHO_PIN2, INPUT);
  
}
int disout,disin;
void loop()
{ 
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN1) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN1) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  disout = pulse_width / 58.0;
//  disout = hcout.dist();
  delay(100);

digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN2) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN2) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  disin = pulse_width / 58.0;
//  disin = hcin.dist();
  if(disout < 10)
  {
    myservo.write(60);
    lcd.setCursor(0, 1);
    lcd.print("Object Detected");
    delay(4000);
  }
  else{
    myservo.write(0);
    lcd.setCursor(0, 1);
    lcd.print(" Clean India   ");
    delay(1000);
  }
  if (disin < 4)
  {
    lcd.setCursor(0, 1);
    lcd.print("  Dustbin Full ");
    delay(1000);
  }


  delay(100);
  
}
