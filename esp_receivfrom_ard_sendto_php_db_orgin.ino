#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "Monchel";
const char* password = "Monchel1";
const char* insertServer = "http://192.168.43.52/smart_parking/insert.php";  // Insert Data
const char* fetchServer = "http://192.168.43.52/smart_parking/get_parking_status.php";  // Fetch Data

WiFiClient client;
LiquidCrystal_I2C lcd(0x27, 20, 4);  // LCD with I2C address 0x27

unsigned long lastFetchTime = 0;
unsigned long lastSendTime = 0;
unsigned long fetchInterval = 1000;  // Fetch status every 10 seconds
unsigned long sendInterval = 1000;    // Send data every 3 seconds

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if it's time to send data (every 3 seconds)
  if (currentMillis - lastSendTime >= sendInterval) {
    if (Serial.available()) {
      // Read CSV data from Serial
      String data = Serial.readStringUntil('\n');
      data.trim(); // Remove whitespace and newline characters

      if (validateCSVData(data)) {
        Serial.println("Received from Arduino: " + data);
        sendParkingData(data);  // Send data
      } else {
        Serial.println("Invalid sensor data format. Expected CSV with 6 binary values.");
      }
    }
    lastSendTime = currentMillis;  // Update the last send time
  }

  // Check if it's time to fetch parking status (every 10 seconds)
  if (currentMillis - lastFetchTime >= fetchInterval) {
    fetchParkingStatus();  // Fetch parking status
    lastFetchTime = currentMillis;  // Update the last fetch time
  }
}

// ✅ Function to validate the CSV sensor data
bool validateCSVData(String data) {
  int count = 0;
  for (unsigned int i = 0; i < data.length(); i++) {
    char c = data[i];
    if (c == '0' || c == '1') {
      continue; // Valid binary character
    } else if (c == ',') {
      count++; // Count commas
    } else {
      return false; // Invalid character
    }
  }
  return (count == 5); // Ensure exactly 5 commas (6 values total)
}

// ✅ Function to send sensor data to the server
void sendParkingData(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    Serial.println("Sending parking data...");

    // Start HTTP connection
    http.begin(client, insertServer);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Send data using POST
    String postData = "sensor_data=" + data;
    int httpResponseCode = http.POST(postData);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server Response: " + response);
    } else {
      Serial.println("Failed to send data. HTTP Error: " + String(httpResponseCode));
    }
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}

// ✅ Function to fetch and display parking status
void fetchParkingStatus() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, fetchServer);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);

      // Parse JSON
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);
      if (!error) {
        String status = doc["status"].as<String>();
        if (status == "success") {
          JsonObject data = doc["data"];

          // Extract parking slot values
          int sensor1 = data["sensor1"];
          int sensor2 = data["sensor2"];
          int sensor3 = data["sensor3"];
          int sensor4 = data["sensor4"];
          int sensor5 = data["sensor5"];
          int sensor6 = data["sensor6"];

          // Total free and taken slots
          int totalFree = doc["free"];
          int totalTaken = doc["taken"];
          // Display on LCD
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("   Parking Slots:");
          lcd.setCursor(0, 1);
          lcd.print("S1:" + String(sensor1 == 1 ? "Fre" : "Ful") + " S2:" + String(sensor2 == 1 ? "Fre" : "Ful") + " S3:" + String(sensor3 == 1 ? "Fre" : "Ful"));
          lcd.setCursor(0, 2);
          lcd.print("S4:" + String(sensor1 == 1 ? "Fre" : "Ful") + " S5:" + String(sensor2 == 1 ? "Fre" : "Ful") + " S6:" + String(sensor3 == 1 ? "Fre" : "Ful"));
          lcd.setCursor(0, 3);
          lcd.print("T.Free=" + String(totalFree) + " T.Taken=" + String(totalTaken));
          
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("No Parking Data");
        }
      } else {
        Serial.println("JSON Parse Error");
      }
    } else {
      Serial.println("Failed to connect to server.");
    }
    http.end();
  }
}
