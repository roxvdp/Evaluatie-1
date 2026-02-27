#include <Wire.h>               
#include <LiquidCrystal.h>      
#include <Adafruit_BMP280.h>    
#include <DHT.h>


// === DHT11 ===
#define DHTPIN 7              // Data-pin DHT11
#define DHTTYPE DHT11         // DHT11
DHT dht(DHTPIN, DHTTYPE);


// === BMP280 ===
Adafruit_BMP280 bmp;


// LiquidCrystal (rs, E, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);



void setup() {
  Serial.begin(9600);     // Voor debug (optioneel)
  

  // Start LCD
  lcd.begin(16, 2);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Secondje!");
  

  // Start DHT
  dht.begin();
  

// Start BMP280
if (!bmp.begin(0x76)) {
  lcd.clear();
  lcd.print("BMP280 niet gevonden!");
  while (1);
}


delay(2000);
lcd.clear();
}



void loop() {

  float binnenTemp = dht.readTemperature();     // (binnen: DHT11)
  float buitenTemp = bmp.readTemperature();     // (buiten: BMP280)

  // Check op foute metingen
  if (isnan(binnenTemp)) {
    binnenTemp = -99.9;
  }
  if (isnan(buitenTemp)) {
    buitenTemp = -99.9;
  }


  // LCD
  lcd.setCursor(0, 0);
  lcd.print("Binnen: ");
  lcd.print(binnenTemp, 1);
  lcd.print(" C     ");

  lcd.setCursor(0, 1);
  lcd.print("Buiten: ");
  lcd.print(buitenTemp, 1);
  lcd.print(" C     ");

  delay(2000);
}