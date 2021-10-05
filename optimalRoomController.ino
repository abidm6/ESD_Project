
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
    delay(300);
    lcd.clear();
    
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
    delay(300);
    lcd.clear();
      
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

  lcd.clear();
  analogWrite(pwm, 0);
  analogWrite(6,0);
  
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
  //lcd.print(Temp);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  //lcd.print(RH);
  lcd.print(humidity);
  delay(300);
  lcd.clear();
  while(Temp > 22){

    if(digitalRead(Gas) == HIGH){
      while(digitalRead(Gas) == HIGH){
        delay(300);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Gas Detected Yes");
        analogWrite(pwm, 255);
        //digitalWrite(10 , HIGH);
        //digitalWrite(6, LOW);
      }
    }
    
    if(byte Temp = dht.readTemperature() <23){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temp optimal");
      lcd.setCursor(0,1);
      lcd.print("Fan turned off");
      delay(1000);
      break;
    }
    delay(300);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Too hot!");
    lcd.setCursor(0,1);
    lcd.print("Fan turned on");
    analogWrite(pwm, 255);
  }
 while(Temp<18){
  analogWrite(6,255);
  delay(300);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Too cold!");
  lcd.setCursor(0,1);
  lcd.print("Heater on");

 if(digitalRead(Gas) == HIGH){
      while(digitalRead(Gas) == HIGH){
        delay(300);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Gas Detected Yes");
        analogWrite(pwm, 255);
        //digitalWrite(10 , HIGH);
        //digitalWrite(6, LOW);
      }
    }

 if(byte Temp = dht.readTemperature() >17){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp optimal");
    lcd.setCursor(0,1);
    lcd.print("Heater turned off");
    delay(1000);
    analogWrite(6,0);
    break;
    }
 }

 while(RH>60){
  analogWrite(pwm,255);
  delay(300);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Too humid!");
  lcd.setCursor(0,1);
  lcd.print("Fan turned on");

 if(digitalRead(Gas) == HIGH){
      while(digitalRead(Gas) == HIGH){
        delay(300);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Gas Detected Yes");
        analogWrite(pwm, 255);
        //digitalWrite(10 , HIGH);
        //digitalWrite(6, LOW);
      }
    }

 if(byte RH = dht.readHumidity() <61){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity optimal");
    lcd.setCursor(0,1);
    lcd.print("Fan turned off");
    delay(1000);
    analogWrite(6,0);
    break;
    }
 }
 // }
}
