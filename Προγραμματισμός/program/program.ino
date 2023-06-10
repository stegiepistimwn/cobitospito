//Στέγη Επιστημών Ερμιονίδας 2023
// Animusa ex machina
//Διαγωνισμός Ρομποτικής ΕΛΛΑΚ 2023
//Το πρόγραμμα υλοποιεί τα παρακάτω:
// 1. χρησιμοποιεί ένα αισθητήρα DHT11 για να διαβάσει την θερμοκρασία και την
//    υγρασία από το εσωτερικό του σπιτιού
// 2. Εμφανίζει την υγρασία και την θερμοκρασία στην οθόνη LCD
// 3. Διαβάζει την κατάσταση των δύο διακοπτών 
// 4. Εφόσον πατηθεί ο πρώτος διακόπτης και ΑΝ είναι σβησμένο το φως στην κατοικία
//    τότε το ανάβει. Διαφορετικά αν είναι ήδη αναμένο το φως τότε το σβήνει
// 5. Ο διακόπτης 2 λειτουργεί με τον ίδιο τρόπος όπως ο 1 για να ανάψει ή να σβήσει 
//    το φως στην αυλή. 
// 6. Χρησιμοποιεί LCD οθόνη 20x4 για να εμφανίσει τα δεδομένα

#include <Wire.h> 
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHT11_PIN 5
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHT11_PIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int fos1Status = 0;
int fos2Status = 0;
int fosHome = 3;
int fosAvli = 2;
int switchHome = 10;
int switchAvli = 9;


void setup()
{
  lcd.init();                     // Αρχικοποίηση τη; οθόνης LCD
  pinMode(fosHome, OUTPUT);       // Αρχικοποίηση των εξόδων
  pinMode(fosAvli, OUTPUT);  
  pinMode(switchHome, INPUT);     // Αρχικοποίηση των εισόδων 
  pinMode(switchAvli, INPUT);
    
  dht.begin();                    // Αρχικοποίηση του αισθητήρα θερμοκρασίας 
  lcd.backlight();                // Ανάβει την οθόνη 
}


void loop() {
  //Διάβασε την θερμοκρασία και την υγρασία 
  //και εμφάνισε τα στην οθόνη
  lcd.setCursor(2,3);  
  lcd.print(dht.readTemperature());
  lcd.setCursor(10,3);  
  lcd.print(dht.readHumidity());

  //Διάβασε τους διακόπτες και εμφάνισε τις αξιες τους
  int sw1 = digitalRead(switchHome);
  int sw2 = digitalRead(switchAvli);
  lcd.setCursor(2,2);
  lcd.print(sw1);
  lcd.setCursor(10,2);
  lcd.print(sw2);

  //Ελεγχος διακόπτη 1
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

  // Έλεγχος διακόπτη 2
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
