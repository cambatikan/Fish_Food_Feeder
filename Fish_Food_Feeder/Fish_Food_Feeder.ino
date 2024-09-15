#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

// Servo motor tanımlaması
Servo servoMotor;     
LiquidCrystal_I2C lcd(0x27,16,2); // LCD ekran tanımlaması

#include <OneWire.h>
#include <DallasTemperature.h>

// Sıcaklık sensörü tanımlamaları
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Zaman ve sıcaklık değişkenleri
int second = 0;
int minute = 0;
int hour = 0;
int i = 0;
int x = 24; // Zaman kontrolü için bir değişken
float timer = 5.55555555556; // Servo hareket gecikmesi
float Celcius = 0; // Sıcaklık değeri

void setup(void) {
  // Servo motor ve LCD ayarları
  servoMotor.attach(9);      // Servo motorun sinyal pini pin 9'a bağlı
  lcd.init();
  
  Serial.begin(9600); 
  sensors.begin(); // Sıcaklık sensörü başlatma
}

void loop(void) { 
  // Mevcut saniyeyi seri ekrana yazdır
  Serial.println((String)second);

  // LCD'yi temizle ve sıcaklık değerini al
  lcd.clear();
  sensors.requestTemperatures(); 
  Celcius = sensors.getTempCByIndex(0);

  // Sıcaklığı LCD'ye yazdır
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  TEMPERATURE  ");
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.print((float)Celcius);
  lcd.print("'C");
  lcd.print("   ");
  
  // 2 saniye bekleme
  delay(2000);

  // Zamanı güncelle
  second = second + 2;
  lcd.clear();

  // Kalan süreyi LCD'ye yazdır
  lcd.setCursor(0, 0);
  lcd.print("REMAINING TIME");
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  // Saniyeyi 1'er 1'er artır ve LCD'de göster
  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);

  delay(1000);
  second++;
  lcd.setCursor(0, 1);
  printTimeToLcd(hour, minute, second);
}

// Zamanın LCD'ye yazdırıldığı fonksiyon
void printTimeToLcd(int x, int y, int z) {
  // Eğer saniye 60'dan büyükse, bir dakika eklenir ve saniye sıfırlanır
  if(z > 60) {
    minute++;
    second = 1;
  }

  // Eğer dakika 60'dan büyükse, bir saat eklenir ve dakika sıfırlanır
  if(y > 60) {
    hour++;
    minute = 1;
  }

  // Eğer saat 24, dakika 60 ve saniye 60 olduğunda servo motor çalıştırılır
  if(x == 24 && y == 60 && z == 60) {
    while (i < 180) {
      i++;
      delay(timer);
      servoMotor.write(i);
    }
    
    while (i > 0) {
      i--;
      delay(timer);
      servoMotor.write(i);
    }

    // Zaman sıfırlanır
    second = 0;
    minute = 0;
    hour = 0;
  }

  // Kalan zaman hesaplaması
  int secResult = 60 - z;
  int minResult = 60 - y;
  int hourResult = 24 - x;

  // LCD'ye kalan süre yazdırılır
  lcd.print((int)(24 - x));
  lcd.print(":");
  lcd.print((int)(60 - y));
  lcd.print(":");
  lcd.print((int)(60 - z)); 
  lcd.print(" TO FEED"); 
}
