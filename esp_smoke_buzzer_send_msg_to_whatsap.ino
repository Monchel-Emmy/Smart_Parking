#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "Monchel";
const char* password = "Monchel1";

#define MQ5_PIN A0       // MQ5 sensor connected to A0
#define BUZZER_PIN D5    // Buzzer connected to D5
int smokeThreshold = 420;
String phoneNumber = "+250780904149";
String apiKey = "6737250";
#define waterPump D4
void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(""); 
  if (httpResponseCode == 200){
    Serial.println("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void sendSensor(){
  int smokeLevel = analogRead(MQ5_PIN); // Read sensor value
  Serial.print("Smoke Level: ");
  Serial.println(smokeLevel);

  if (smokeLevel > smokeThreshold) {
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
    digitalWrite(waterPump, HIGH); // Turn on buzzer
    Serial.println("Smoke detected! Buzzer activated."); 
    String message = "fire detected ";
    sendMessage(message);
    delay(1000); 
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
    digitalWrite(waterPump, LOW); // Turn on buzzer
  }
}

void setup() {
  pinMode(waterPump,OUTPUT);
  pinMode(MQ5_PIN, INPUT);       
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sendSensor();
  delay(2000); 
}


