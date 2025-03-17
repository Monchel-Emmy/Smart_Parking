#include <SoftwareSerial.h>


SoftwareSerial espSerial(2, 3); // RX, TX for ESP8266
int sensorPins[] = {A0, A1, A2, A3, A4, A5}; // Infrared sensors
int sensorValues[6];

void setup() {
  Serial.begin(9600); // For debugging
  espSerial.begin(115200); // Communication with ESP8266
  for (int i = 0; i < 6; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  // Read sensor values
  for (int i = 0; i < 6; i++) {
    sensorValues[i] = analogRead(sensorPins[i]); // Adjust to digitalRead if required
  }

    for (int i = 0; i < 6; i++) {
     Serial.println(sensorValues[i]);
  }
  
  // Format data
  String data = String(sensorValues[0]) + "," + String(sensorValues[1]) + "," +
                String(sensorValues[2]) + "," + String(sensorValues[3]) + "," +
                String(sensorValues[4]) + "," + String(sensorValues[5]);

  // Send data to ESP8266
  espSerial.println(data);
  delay(10000); // Delay 1 second

}

