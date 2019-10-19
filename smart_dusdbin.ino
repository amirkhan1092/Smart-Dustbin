#include <LiquidCrystal.h>
#include <HCSR04.h>
#include<Servo.h>

Servo myservo;

// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

HCSR04 hcout(6,7);//initialisation class HCSR04 (trig pin , echo pin)
HCSR04 hcin(8,9);//initialisation class HCSR04 (trig pin , echo pin)

void setup()
{ 
  lcd.begin(16, 2);
  myservo.attach(10);  // servo motor input pin connected to the pin 10 in Arduino Uno 
  lcd.setCursor(0, 0);
  lcd.print("Smart Dustbin ");
  delay(2000);
  myservo.write(0); 
}
int disout,disin;
void loop()
{ 
  disout = hcout.dist();
  delay(100);
  disin = hcin.dist();
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
