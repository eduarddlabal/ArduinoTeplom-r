#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define ONEWIRE_PIN 5
#define DHT_PIN 6
#define MODE_CHANGE 3
#define HELP_MODE 9

int modeButtonState = 0;
int helpButtonState = 0;
int mode = 1;
bool help = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONEWIRE_PIN);
DallasTemperature sensors(&oneWire);
DHT dht(DHT_PIN, DHT11);

void checkDallasSensors();
void checkModeChangeButtons();
void showDataOnLCD(float TS1, float TS2, float HS2);

void setup()
{
  lcd.init();      // inicializace lcd
  lcd.backlight(); // zapnuti podsviceni displeje
  lcd.setCursor(5, 0);

  lcd.print("EDCS"); // vypis informaci o autorovi
  lcd.setCursor(1, 1);
  lcd.print("Comp. systems");
  delay(2000);

  lcd.clear();

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
  checkDallasSensors();
  sensors.requestTemperatures(); // vyzadani teploty od Dallas senzoru

  checkModeChangeButtons();

  float temperature_Dallas = sensors.getTempCByIndex(0);
  float temperature_DHT = dht.readTemperature();
  float humidity_DHT = dht.readHumidity();
  Serial.println("temp 18S20=");
  Serial.print(temperature_Dallas);
  Serial.println("temp DHT11=");
  Serial.print(humidity_DHT);
  Serial.println("hum DHT11=");
  Serial.print(temperature_DHT);

  showDataOnLCD(temperature_Dallas, temperature_DHT, humidity_DHT);
}

void checkDallasSensors()
{
  if (sensors.getDS18Count() == 0)
  {
    lcd.setCursor(3, 0);
    lcd.print("CHYBA");

    exit(0);
  }
}

void checkModeChangeButtons()
{
  helpButtonState = digitalRead(HELP_MODE);
  if (helpButtonState == HIGH)
  {
    lcd.clear();
    if (help == false)
    {
      help = true;
    }
    else
    {
      help = false;
    }
    mode = 1;
  }

  modeButtonState = digitalRead(MODE_CHANGE);
  if (modeButtonState == HIGH)
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
}

void showDataOnLCD(float TS1, float TS2, float HS2)
{
  if (help != true)
    switch (mode)
    {
    case 1:
      // vypis teploty z 18S20
      lcd.setCursor(3, 0);
      lcd.print("Teplota S1:");
      lcd.setCursor(4, 1);
      lcd.print(TS1);
      lcd.setCursor(9, 1);
      lcd.print(" ˚C");
      break;

    case 2:
      // vypis teploty z DHT11
      lcd.setCursor(3, 0);
      lcd.print("Teplota S2:");
      lcd.setCursor(4, 1);
      lcd.print(TS2);
      lcd.setCursor(9, 1);
      lcd.print(" ˚C");
      break;

    case 3:
      // vypis vlhkosti z DHT11
      lcd.setCursor(4, 0);
      lcd.print("Vlhkost:");
      lcd.setCursor(4, 1);
      lcd.print(HS2);
      lcd.setCursor(9, 1);
      lcd.print(" %");
      break;

    default:
      break;
    }

  else if (help == true) // zbytečné informace, příprava na možnou další funkcionalitu
    switch (mode)
    {
    case 1:
      // autor
      lcd.setCursor(2, 0);
      lcd.print("ED Comp. sys.");
      lcd.setCursor(2, 1);
      lcd.print("www.edcs.cz");
      delay(50);

      break;

    case 2:
      // github
      lcd.setCursor(3, 0);
      lcd.print("github.com");
      lcd.setCursor(1, 1);
      lcd.print("/eduarddlabal");
      delay(50);
      break;

    case 3:
      // licence
      lcd.setCursor(4, 0);
      lcd.print("Licence");
      lcd.setCursor(4, 1);
      lcd.print("WTFPL 2");
      delay(50);
      break;

    default:
      break;
    }
}