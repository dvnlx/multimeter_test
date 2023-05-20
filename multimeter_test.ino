#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int piezzoPin = 6;
int buttonPin = 7;
int page = 1;
unsigned long debounceDelay = 200;
const int ohmPin = A0;
int sensorValue = 0;
float Vin = 5;
float Vout = 0;
float Rref = 1000;
float ohms = 0;
float input_voltage = 0.0;
float temp = 0.0;
float voltr1 = 10000.0;
float voltr2 = 2000.0;

void setup()
{
    pinMode(button, INPUT_PULLUP);
    lcd.begin(16, 2);
    lcd.print("Arduino Multimeter");
    lcd.setCursor(0, 1);
    lcd.print("by dvnlx");
    delay(1000);
    lcd.clear();
}

void loop()
{
    if (digitalRead(button) == LOW && (millis() - lastButtonPress >= debounceDelay))
    {
        lastButtonPress = millis();
        page++;
        if (page > 3)
        {
            page = 1;
        }
    }

    switch (page)
    {
    case 1:
        ohmMeter();
        break;
    case 2:
        conductivityTest();
        break;
    case 3:
        VoltMeter();
        break;
    }
    delay(100);
}

void ohmMeter()
{
    lcd.clear();
    lcd.print("Ohms:");
    lcd.setCursor(0, 1);
    sensorValue = analogRead(sensorPin);
    Vout = (Vin * sensorValue) / 1023;
    ohms = Rref * (1 / ((Vin / Vout) - 1));
    lcd.setCursor(0, 1);
    delay(500);
    lcd.print(ohms);
}

void conductivityTest()
{
    lcd.clear();
    lcd.print("Conductivity:");
    sensorValue = analogRead(sensorPin);
    Vout = (Vin * sensorValue) / 1023;
    ohms = Rref * (1 / ((Vin / Vout) - 1));
    lcd.setCursor(0, 1);
    if (ohms < 20)
    {
        lcd.print("True");
        tone(cont, 500);
    }
    else
    {
        lcd.print("False");
    }
}

void VoltMeter()
{
    lcd.clear();
    lcd.print("Volts:");
    lcd.setCursor(0, 1);
    int analog_value = analogRead(A0);
    temp = (analog_value * 5.0) / 1024.0;
    input_voltage = temp / (r2 / (r1 + r2));
    if (input_voltage < 0.1)
    {
        input_voltage = 0.0;
    }
    Serial.print("v= ");
    Serial.println(input_voltage);
    lcd.setCursor(0, 1);
    lcd.print(input_voltage);
}
