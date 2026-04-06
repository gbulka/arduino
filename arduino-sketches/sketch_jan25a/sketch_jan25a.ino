// LCD:
// https://forbot.pl/blog/kurs-arduino-wyswietlacz-tekstowy-lcd-id4263

// Czujnik temp/wilg:
// DHT11: https://botland.com.pl/content/140-arduino-i-obsluga-czujnika-temperatury-i-wilgotnosci-dht11

#include <LiquidCrystal.h>  //Dołączenie bilbioteki
#include <dht11.h>


#define DHT11PIN 12  //przypisanie pinu 2 Arduino jako odczyt z sensora

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  //Informacja o podłączeniu nowego wyświetlacza
dht11 dht;

struct Measurement {
  int Check;
  float Temp;
  float Humd;
};

const char demoText[] = "Hello World!";
byte textLen;
const unsigned int scrollDelay = 200;
const byte lcdCols = 16;

void setup() {
  lcd.begin(16, 2);  //Deklaracja typu

  Serial.begin(115200);  //inicjalizacja monitora szeregowego
  Serial.println("Program testowy DHT11");
  Serial.println();


  textLen = sizeof(demoText) - 1;
  //lcd.init();
  //lcd.backlight();
  lcd.print(demoText);
  //delay(demoDelay);
}

void loop() {
  Measurement measurement = measureTempAndHumd();
  printMeasurement(measurement);
  delay(2000);
};

Measurement measureTempAndHumd() {

  int check = dht.read(DHT11PIN);
  Measurement result = { check, dht.temperature, dht.humidity };

  Serial.print("Stan sensora: ");
  switch (result.Check) {
    case DHTLIB_OK:
      Serial.println("OK");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Błąd sumy kontrolnej");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Koniec czasu oczekiwania - brak odpowiedzi");
      break;
    default:
      Serial.println("Nieznany błąd");
      break;
  }

  Serial.print("Wilgotnosc (%): ");  //wyświetlenie wartości wilgotności
  Serial.print(result.Humd, 2);
  Serial.print("\t");
  Serial.print("Temperatura (C): ");  //wyświetlenie temperatury
  Serial.println(result.Temp, 2);

  return result;
};

void printMeasurement(Measurement measurement) {

  String line1 = "Wilg:   " + String(measurement.Humd, 1) + " %";
  String line2 = "Temp:   " + String(measurement.Temp, 1) + "'C";

  displayOnLcd(line1, line2);
};

void displayOnLcd(String line1, String line2) {
  lcd.setCursor(0, 0);  //Ustawienie kursora
  lcd.print(line1);     //Wyświetlenie tekstu
  lcd.setCursor(0, 1);  //Ustawienie kursora
  lcd.print(line2);     //Wyświetlenie tekstu
};
