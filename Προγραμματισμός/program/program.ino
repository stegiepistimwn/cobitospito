//Στέγη Επιστημών Ερμιονίδας 2023
//Διαγωνισμός Ρομποτικής ΕΛΛΑΚ 2023

#include <Wire.h> 
#include <LM35.h>
#include <LiquidCrystal_I2C.h>

LM35 sensor(1);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int fos1Status = 0;
int fos2Status = 0;
int fosHome = 3;
int fosAvli = 2;
int switchHome = 10;
int switchAvli = 9;


void setup()
{
  lcd.init();                      // initialize the lcd 
  pinMode(fosHome, OUTPUT);
  pinMode(fosAvli, OUTPUT);  
  pinMode(switchHome, INPUT); 
  pinMode(switchAvli, INPUT); 
  
  // Print a message to the LCD.
  lcd.backlight();
}


void loop()
{


  lcd.setCursor(2,3);  
  lcd.print(sensor.getTemp());
  
  int sw1 = digitalRead(switchHome);
  int sw2 = digitalRead(switchAvli);
  lcd.setCursor(2,2);
  lcd.print(sw1);
  lcd.setCursor(10,2);
  lcd.print(sw2);


  if ( sw1 == 1) {
    if (fos1Status == 0 ) {
        fos1Status = 1;
        lcd.setCursor(0,0);
        lcd.print("FosHome  ON  ");
        digitalWrite(fosHome, HIGH);
    }
    else { 
        fos1Status = 0;
       // lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("FosHome OFF  ");
        digitalWrite(fosHome, LOW);      
    }
  }

    if ( sw2 == 1) {
    if (fos2Status == 0 ) {
        fos2Status = 1;
        lcd.setCursor(0,1);
        lcd.print("FosAvli  ON  ");
        digitalWrite(fosAvli, HIGH);        
    }
    else { 
        fos2Status = 0;
        lcd.setCursor(0,1);
        lcd.print("FosAvli  OFF ");
        digitalWrite(fosAvli, LOW);
    }    
  } 

  delay(1000);
  
}
