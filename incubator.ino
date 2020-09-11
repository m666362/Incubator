#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x38, 16, 2);

//DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float humidity;
float temperature;
float heatIndex;

// Light
#define bulb 4
int bulbState = LOW;

void setup()
{
  // initialize the LCD
  Serial.begin(9600);

  // LCD
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(3, 1);
  lcd.print("Incubator!");
  Serial.println(F("Lcd test!"));
  delay(1000);
  lcd.clear();

  //dht11
  dht.begin();
  Serial.println(F("DHT11 test!"));

  // Bulb
  pinMode(bulb, OUTPUT);
}

void loop()
{
  delay(2000);
  lcd.clear();
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) {
    Serial.print("Sensor not working");
    Serial.println();
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Sensor is not");
    lcd.setCursor(4, 1);
    lcd.print("Working!");
  } else {
    heatIndex = dht.computeHeatIndex(temperature, humidity, false);
    if (temperature <= 37.7) {
      bulbState = HIGH;
      digitalWrite(bulb, bulbState);
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print(" %");
      Serial.println();
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.print(" °C");
      Serial.println();
      Serial.print("Heat index: ");
      Serial.print(heatIndex);
      Serial.println();
      //
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.setCursor(8, 0);
      lcd.print(temperature);
      lcd.setCursor(0, 1);
      lcd.print("Humi: ");
      lcd.setCursor(8, 1);
      lcd.print(humidity);
    } else {
      bulbState = LOW;
      digitalWrite(bulb, bulbState);

    }
  }
}
