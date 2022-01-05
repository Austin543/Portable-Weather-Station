//Libraries
#include <DHT.h>;
#include <Wire.h>;
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
float hum;
float temp;

//Create display object
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  dht.begin(); //begin communication with sensor

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
  delay(500);
  display.clearDisplay();
  display.setRotation(2); //flip 180deg
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true); //use cp437 font
}

void loop() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(2000); //Delay 2 sec.

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp(");
  display.print(char(248)); //Character 248 is degree symbol
  display.print("C)  Humidity(%)");
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.println(String(temp, 1) + "  " + String(hum, 1));
  display.drawFastVLine(53, 0, 50, SSD1306_WHITE); //(x, y, length, color)
  display.display();

}
