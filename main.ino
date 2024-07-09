#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define SENSOR_UMIDADE_SOLO_PINO A0
#define RELE_IRRIGACAO_PINO 3 

#define UMIDADE_SOLO_MINIMA 300
#define UMIDADE_SOLO_MAXIMA 700

LiquidCrystal lcd(12, 11, 5, 4, 7, 2); 

void setup() {
    Serial.begin(9600); 
    pinMode(RELE_IRRIGACAO_PINO, OUTPUT);
    digitalWrite(RELE_IRRIGACAO_PINO, LOW); 
    lcd.begin(16, 2);
    lcd.print("Iniciando...");
    delay(2000);
    lcd.clear();
}

void loop() {
    controlarIrrigacao();
}

void controlarIrrigacao() {
    int umidadeSolo = analogRead(SENSOR_UMIDADE_SOLO_PINO);
    lcd.setCursor(0, 0);
    lcd.print("Umidade: ");
    lcd.print(umidadeSolo);
    lcd.print("    "); 

    Serial.print("Umidade do Solo: ");
    Serial.println(umidadeSolo); 

    if (umidadeSolo < UMIDADE_SOLO_MINIMA) {
        digitalWrite(RELE_IRRIGACAO_PINO, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Irrigando...   ");
        Serial.println("Irrigando..."); 
    } else if (umidadeSolo > UMIDADE_SOLO_MAXIMA) {
        digitalWrite(RELE_IRRIGACAO_PINO, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Solo Ok       ");
        Serial.println("Solo Ok"); 
    } else {
        digitalWrite(RELE_IRRIGACAO_PINO, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Umidade Adeq. ");
        Serial.println("Umidade Adequada"); 
    }

    delay(2000);
}
