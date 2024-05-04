#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12,11,5,4,3,2);

byte temp[8] = {
  B00110,
  B00100,
  B00110,
  B00100,
  B01110,
  B01110,
  B00000,
};

byte hum[8] = {
  B00100,
  B00100,
  B01110,
  B01110,
  B10111,
  B10111,
  B01110,
};

void setup() {
  lcd.begin(16,2);
  lcd.home();
  lcd.print("starting...");
  lcd.createChar(0, temp);
  lcd.createChar(1, hum);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {

  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.print(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


  lcd.clear();
  lcd.home();
  // lcd.print(F("Temp: "));
  lcd.write(byte(0));
  lcd.print(t);
  lcd.print(" ");
  lcd.write(byte(1));
  lcd.print(h);
  lcd.print("%");

}