#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT_PIN 6
#define MODE_CHANGE 3
#define HELP_MODE 9

int buttonState = 0;
int button2State = 0;
int mode = 1;
int help = 1;

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(5);
DallasTemperature sensors(&oneWire);
DHT dht(DHT_PIN, DHT11);

void setup()
{
  lcd.init(); // Initialize the LCD I2C display
  lcd.backlight();
  lcd.setCursor(5, 0); // move cursor to   (3, 0)
  lcd.print("EDCS");
  lcd.setCursor(1, 1);
  lcd.print("Comp. systems");
  delay(2000);

  lcd.clear();

  lcd.setCursor(1, 0); // move cursor to   (3, 0)
  lcd.print("Inicializace...");

  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(12);
  dht.begin();
  pinMode(MODE_CHANGE, INPUT);
  pinMode(HELP_MODE, INPUT);
  Serial.println("Setup done");
  lcd.clear();
}

void loop()
{
  sensors.requestTemperatures();

  if (sensors.getDS18Count() == 0)
  {
    lcd.setCursor(3, 0);
    lcd.print("CHYBA");

    exit(0);
  }

  button2State = digitalRead(HELP_MODE);
  if (button2State == HIGH)
  {
    lcd.clear();
    if (help == 1)
    {
      help++;
    }
    else
    {
      help = 1;
    }
    mode = 1;
  }

  buttonState = digitalRead(MODE_CHANGE);
  if (buttonState == HIGH)
  {
    lcd.clear();
    if (mode != 3)
    {
      mode++;
    }
    else
    {
      mode = 1;
    }
    
  }

  float temperature = sensors.getTempCByIndex(0);
  float temperatura_DHT = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print(temperature);
  Serial.print(humidity);
  Serial.print(temperatura_DHT);

  if (help == 1)
  {
    if (mode == 1)
    {
      lcd.setCursor(3, 0);
      lcd.print("Teplota S1:");
      lcd.setCursor(4, 1);
      lcd.print(temperature);
      lcd.setCursor(9, 1);
      lcd.print(" ˚C");
    }
    else if (mode == 2)
    {
      lcd.setCursor(3, 0);
      lcd.print("Teplota S2:");
      lcd.setCursor(4, 1);
      lcd.print(temperatura_DHT);
      lcd.setCursor(9, 1);
      lcd.print(" ˚C");
    }
    else if (mode == 3)
    {
      lcd.setCursor(4, 0);
      lcd.print("Vlhkost:");
      lcd.setCursor(4, 1);
      lcd.print(humidity);
      lcd.setCursor(9, 1);
      lcd.print(" %");
    }
  }

  else if (help == 2)
  {
    if (mode == 1)
    {
      lcd.setCursor(2, 0);
      lcd.print("ED Comp. sys.");
      lcd.setCursor(2, 1);
      lcd.print("www.edcs.cz");
      delay(50);
    }
    else if (mode == 2)
    {
      lcd.setCursor(3, 0);
      lcd.print("github.com");
      lcd.setCursor(1, 1);
      lcd.print("/eduarddlabal");
      delay(50);
    }
    
    else if (mode == 3)
    {
      lcd.setCursor(4, 0);
      lcd.print("Licence");
      lcd.setCursor(4, 1);
      lcd.print("WTFPL 2");
      delay(50);
    }
  }
}