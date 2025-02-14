//Theme : Pawsome Technology
//Name of The Project : PawPatrol
#include <SoftwareSerial.h>

SoftwareSerial sim800(10, 11); 

#define LDR_PIN 2
#define BUZZER_PIN 3

bool petDetected = false; 

void setup() {
    pinMode(LDR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    sim800.begin(9600) ;
    Serial.begin(9600);
}

void sendSMS() {
    sim800.println("AT+CMGF=1"); 
    delay(1000);
    sim800.println("AT+CMGS=\"+9880458153\""); 
    delay(1000);
    sim800.print("Alert! Your pet crossed the boundary."); 
    delay(1000);
    sim800.write(26); 
    delay(1000);
}

void loop() {
    int sensorState = digitalRead(LDR_PIN); 

    if (sensorState == HIGH && !petDetected) { 
        Serial.println("Pet detected! Sending SMS...");
        digitalWrite(BUZZER_PIN, HIGH); 
        sendSMS();
        petDetected = true; 
    }

    if (sensorState == LOW && petDetected) { 
        Serial.println("Laser restored. Stopping buzzer...");
        digitalWrite(BUZZER_PIN, LOW); 
        petDetected = false; 
    }

    delay(500);
}
