
// Interfacing Arduino with DHT11 humidity and temperature sensor
 
// include LCD library code
#include <LiquidCrystal.h>
// include DHT library code
#include "DHT.h"
 
#define DHTPIN 8            // DHT11 data pin is connected to Arduino pin 8
#define pwm 10
 
// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Gas = 9;
int redLed = 7;
int greenLed = 6;
 
#define DHTTYPE DHT11       // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library
 
char temperature[] = "Temp = 00.0 C  ";
char humidity[]    = "RH   = 00.0 %  ";

void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  dht.begin();
  pinMode(Gas , INPUT);
}
 
void loop() {

  while(analogRead(A0) > 600){
    if(digitalRead(Gas) == HIGH){
      lcd.clear();
      break;
    }
    
    int ldr= analogRead(A0);
  
    lcd.setCursor(0,0);
    lcd.print("Ldr out= ");
    lcd.print(ldr);
    lcd.setCursor(0,1);
    lcd.print("Lower light!");
  }

    while(analogRead(A0) < 200){
    if(digitalRead(Gas) == HIGH){
      lcd.clear();
      break;
    }

      
    int ldr= analogRead(A0);
  
    lcd.setCursor(0,0);
    lcd.print("Ldr out= ");
    lcd.print(ldr);
    lcd.setCursor(0,1);
    lcd.print("Increase light!");
  }


  
  //delay(1000);           // wait 1s between readings
  while(digitalRead(Gas) == HIGH){
    lcd.setCursor(0,0);
    lcd.print("Gas Detected Yes");
    analogWrite(pwm, 255);
    //digitalWrite(10 , HIGH);
    //digitalWrite(6, LOW);
  }
  analogWrite(pwm, 0);
  lcd.clear();
  
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(RH) || isnan(Temp)) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error");
    return;
  }
 
  temperature[7]     = Temp / 10 + 48;
  temperature[8]     = Temp % 10 + 48;
  temperature[11]    = 223;
  humidity[7]        = RH / 10 + 48;
  humidity[8]        = RH % 10 + 48;
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);
  delay(300);
  lcd.clear();
 // }
}
