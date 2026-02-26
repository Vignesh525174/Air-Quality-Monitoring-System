#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int mq135Pin = A0;
int ledPin   = 7;
int buzzer   = 8;
int threshold = 250;   // adjust if needed

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  int airValue = analogRead(mq135Pin);
  Serial.println(airValue);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 10);
  display.print("Air Value: ");
  display.print(airValue);

  display.setCursor(0, 30);

  if (airValue > threshold) {
    display.print("Status: POOR");
    digitalWrite(ledPin, HIGH);     //  LED ON
    digitalWrite(buzzer, HIGH);     //  BUZZER ON
  } else {
    display.print("Status: GOOD");
    digitalWrite(ledPin, LOW);      // LED OFF
    digitalWrite(buzzer, LOW);      // BUZZER OFF
  }

  display.display();
  delay(1000);
}
