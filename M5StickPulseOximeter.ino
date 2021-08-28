#include <M5StickC.h>
#include "MAX30100_PulseOximeter.h"

PulseOximeter pulseOximeter;
int HR, SPO2 = 0;
long intervalTime = 0;

void setup()
{
  M5.begin();
  if (pulseOximeter.begin()) {
    M5.Lcd.println("Success");
   } else {
    M5.Lcd.println("Failed");
    exit(0);
  }
  pulseOximeter.setOnBeatDetectedCallback(updateBeat);
}

void loop()
{
  M5.update();
  pulseOximeter.update();
  if (millis() - intervalTime > 1000) 
  {
    HR = pulseOximeter.getHeartRate();
    SPO2 = pulseOximeter.getSpO2();
    updateDisplay();
    intervalTime = millis();
  }
}

void updateDisplay()
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(65,6);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print(" "); 
  
  M5.Lcd.setCursor(6,6);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("HR"); 
  M5.Lcd.setCursor(6,28);
  M5.Lcd.setTextSize(6);
  M5.Lcd.printf("%2d", HR);

  M5.Lcd.setCursor(6,88);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("SPO2"); 
  M5.Lcd.setCursor(6,110);
  M5.Lcd.setTextSize(6);
  M5.Lcd.printf("%2d",SPO2);
}

void updateBeat()
{
    M5.Lcd.setCursor(65,6);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.print("@"); 
}
