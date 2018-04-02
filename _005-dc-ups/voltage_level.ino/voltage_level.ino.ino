#include <PCD8544.h>

static PCD8544 lcd;

const int UPS_Voltage_Pin = A0;
const int Lamp_Pin = 8;
const int Charger_Relay_Pin = 9;

const float Reference_Voltage = 5.15;
const float Resistor_1 = 98100; // 98.1K resistor
const float Resistor_2 = 9700;  // 9.7K resistor
const float CutoffVoltage = 13.9;
const float LampCutoffVoltage = 11;
const float Denominator = Resistor_2 / (Resistor_1 + Resistor_2);

float Voltage = 0.0;
float PrevVoltage = 0.0;

void setup()
{
    analogReference(DEFAULT);
    lcd.begin(84, 48);
    lcd.setContrast(70);
    pinMode(Charger_Relay_Pin, OUTPUT);
    digitalWrite(Charger_Relay_Pin, HIGH);
    pinMode(UPS_Voltage_Pin, INPUT);
    Serial.begin(9600);
}

void showVoltage(float voltage)
{
    for (int i = 0; i < round(Voltage/CutoffVoltage * 4); i++) {
      lcd.setCursor(0, 5-i);
      lcd.clearLine();
      lcd.print("#");
    }
}

void loop()
{
    float Analog_Read_Value = analogRead(UPS_Voltage_Pin);
    float Input_Voltage = (Analog_Read_Value / 1024) * Reference_Voltage;
    Voltage = Input_Voltage / Denominator;
    if (PrevVoltage != Voltage) {
      showVoltage(Voltage);
    }
    if (PrevVoltage >= LampCutoffVoltage && Voltage < LampCutoffVoltage)
    {
        Serial.println("Voltage fell far below cutoff. Turning bulb off.");
        digitalWrite(Lamp_Pin, LOW);
    }
    if (PrevVoltage < CutoffVoltage && Voltage >= CutoffVoltage)
    {
        Serial.println("Voltage reached cutoff. Turning charger off.");
        digitalWrite(Charger_Relay_Pin, LOW);
    }
    if (PrevVoltage >= CutoffVoltage && Voltage < CutoffVoltage)
    {
        Serial.println("Voltage fell below cutoff. Turning charger on.");
        digitalWrite(Charger_Relay_Pin, HIGH);
    }
    PrevVoltage = Voltage;
}

