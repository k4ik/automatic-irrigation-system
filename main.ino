#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define SENSOR_UMIDADE_SOLO_PINO A0
#define RELE_IRRIGACAO_PINO 3

LiquidCrystal lcd(12, 11, 5, 4, 7, 2);

bool irrigar = false;

void setup() {
    Serial.begin(9600);
    pinMode(RELE_IRRIGACAO_PINO, OUTPUT);
    pinMode(SENSOR_UMIDADE_SOLO_PINO, INPUT);
    
    digitalWrite(RELE_IRRIGACAO_PINO, HIGH);
    lcd.begin(16, 2);
    lcd.print("Iniciando...");
    delay(2000);
    lcd.clear();
}

void loop() {
    controlarIrrigacao();
}

void controlarIrrigacao() {
    irrigar = digitalRead(SENSOR_UMIDADE_SOLO_PINO);
    
    lcd.setCursor(0, 0);
    if (irrigar) {
        digitalWrite(RELE_IRRIGACAO_PINO, LOW); 
        lcd.print("Umidade baixa ");
        lcd.setCursor(0, 1);
        lcd.print("Irrigando...   ");
        Serial.println("Irrigando...");
    } else {
        digitalWrite(RELE_IRRIGACAO_PINO, HIGH); 
        lcd.print("Umidade alta  ");
        lcd.setCursor(0, 1);
        lcd.print("Solo Ok       ");
        Serial.println("Solo Ok");
    }

    delay(500); 
}
