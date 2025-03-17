#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <Servo.h>
int Client = 2;
Servo myservo;
// WiFi credentials
const char* ssid = "Monchel";         // Replace with your WiFi SSID
const char* password = "Monchel1";     // Replace with your WiFi password

// Server URL
const char* serverUrl = "http://192.168.43.52/smart_parking/parking.php";

// MFRC522 connections
#define RST_PIN 16
#define SS_PIN 15
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Built-in LED pin
const int ledPin = LED_BUILTIN;
int pos;
void setup() {
  // Initialize serial monitor
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize SPI and MFRC522
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID Reader initialized.");

  // Configure LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn off LED initially

  myservo.attach(2);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
          lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Exit Gate");
        lcd.setCursor(5, 2);
        lcd.print("Thank you!");
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Check if the card can be read
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Read the UID and convert it to a string without colons
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uid += "0"; // Add leading zero for single-digit HEX values
    }
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase(); // Convert to uppercase

  // Print UID to serial monitor
  Serial.println("Card UID: " + uid);

  // Send UID to server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    
    // Start HTTP connection
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // POST data
    String postData = "uid=" + uid + "&action=exit";
    int httpResponseCode = http.POST(postData);

    // Process server response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server Response: " + response);

      // Parse JSON response
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (error) {
        Serial.println("JSON Parsing Failed!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Error Parsing");
        lcd.setCursor(0, 1);
        lcd.print("Try Again");
        return;
      }

      // Extract values
      String status = doc["status"].as<String>();
      String message = doc["message"].as<String>();
      int balance = doc["balance"].as<int>();
      String name = doc["name"].as<String>();
      int cost = doc["cost"].as<int>();
      int duration = doc["duration"].as<int>();

     if (message == "Insufficient balance. Please recharge.") {
         // Display on LCD
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print(name);
      lcd.setCursor(0, 1); 
      lcd.print("Insufficient balance");
      lcd.setCursor(0, 2);
      lcd.print("Balance: " + String(balance) + " Rwf");
    }
    else if(message == "Customer not found"){
        lcd.clear();
        lcd.setCursor(1, 1);
        lcd.print("Customer not found");
      }
        else if(message == "No active entry found."){
        lcd.clear();
        lcd.setCursor(1, 1);
        lcd.print("You didn't Entry !");
      }
      
    else  if (message == "Exit recorded successfully.") {
         // Display on LCD
      lcd.clear();   
      lcd.setCursor(0, 0); 
      lcd.print(name); 
      lcd.setCursor(0, 1);
      lcd.print("Parked Time: " + String(duration) + "min");
      lcd.setCursor(0, 2);
      lcd.print("Cost:" + String(cost)+"f Bal:" + String(balance)+"f" );

    delay(100);

  
      // for servor
    for (pos = 0; pos <= 180; pos += 4){
      myservo.write(pos);
      delay(0.05);
    }
    delay(5000);
    for (pos = 180; pos >= 0; pos -= 4) {  
    myservo.write(pos);                  
    delay(0.05);                           
    } 
    }


      // Light LED for successful response
      digitalWrite(ledPin, LOW);
      delay(1000);
      digitalWrite(ledPin, HIGH);
    } else {
      Serial.println("Error in HTTP request: " + String(httpResponseCode));
    }

    // End HTTP connection
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }

  // Halt PICC to allow subsequent scans
  mfrc522.PICC_HaltA();

  // Small delay to avoid multiple readings
  delay(2000);
}