# 🚗 Smart Parking System with ESP8266 & RFID

This project is an **IoT-based Smart Parking System** using **ESP8266, RFID, and MySQL** to monitor and manage parking slots. It detects parking availability using sensors, stores data in a **MySQL database**, and provides real-time updates on an **LCD display**.

## 🚀 Features
- **RFID-based access control** for entry & exit.
- **Live parking slot monitoring** using infrared sensors.
- **ESP8266 WiFi connectivity** for real-time database updates.
- **MySQL & PHP backend** to store and manage data.
- **LCD display** for status updates.
- **Automated gate control** using servo motors.
- **Payment system** with balance checking.

---

## 🛠️ Hardware Requirements
- **ESP8266** (NodeMCU)
- **RFID Readers (MFRC522)**
- **RFID Cards**
- **Servo Motors** (for automated gates)
- **Infrared Sensors** (for detecting cars)
- **LCD 20x4** (with I2C module)
- **Power Supply & Jumper Wires**

---

## 🖥️ Software Requirements
- **Arduino IDE** (with ESP8266 board package)
- **XAMPP** (for MySQL & Apache)
- **Postman** (for API testing)

---

## 🔧 Setup & Installation

### 1️⃣ **ESP8266 Firmware (Arduino Code)**
Upload the **ESP8266 entry & exit codes** using Arduino IDE.

### 2️⃣ **Database Setup**
1. Create a database **`smart_parking_system`** in MySQL.
2. Import the provided **`smart_parking.sql`** file.
3. Ensure **Apache & MySQL** are running on XAMPP.

### 3️⃣ **Backend API (PHP)**
- Place the **PHP files** inside **`htdocs/smart_parking/`** (XAMPP).
- Modify **`db.php`** with your MySQL credentials.
- Start the Apache server.

### 4️⃣ **ESP8266 WiFi Configuration**
Modify the **WiFi credentials** inside **ESP8266 code**:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* server = "http://YOUR_SERVER_IP/smart_parking/";
📡 API Endpoints
🟢 1. Insert Parking Data
URL: GET /insert.php?sensor_data=1,0,1,0,1,0
Purpose: Saves sensor readings into the database.
Response:

json
Copy
Edit
{"status":"success", "message":"Data inserted successfully"}
🟢 2. Get Parking Slot Status
URL: GET /get_parking_status.php
Purpose: Retrieves the latest parking availability.
Response:

json
Copy
Edit
{
  "status": "success",
  "data": {
    "sensor1": "1",
    "sensor2": "0",
    "sensor3": "1",
    "sensor4": "0",
    "sensor5": "1",
    "sensor6": "0"
  },
  "free": 3,
  "taken": 3
}
🟢 3. Entry Processing
URL: POST /parking.php?action=entry&uid=10867A51
Purpose: Logs an entry transaction and starts parking time.
Response:

json
Copy
Edit
{"status":"success", "message":"Entry recorded successfully"}
🟢 4. Exit Processing
URL: POST /parking.php?action=exit&uid=10867A51
Purpose: Logs an exit transaction, calculates cost, and updates balance.
Response:

json
Copy
Edit
{
  "status": "success",
  "message": "Exit recorded successfully",
  "cost": 200,
  "duration": 5,
  "balance": 1800
}
🏛️ Database Schema (MySQL)
Table: customers
Column	Type	Description
id	INT (AUTO)	Unique ID
uid	VARCHAR(20)	RFID Card ID
name	VARCHAR(50)	Customer Name
balance	INT	Account Balance (Frw)
Table: transactions
Column	Type	Description
id	INT (AUTO)	Unique Transaction ID
uid	VARCHAR(20)	RFID Card ID
entry_time	DATETIME	Time of Parking Entry
exit_time	DATETIME	Time of Parking Exit
duration	INT	Duration in Minutes
cost	INT	Amount Charged (Frw)
Table: sensor_readings
Column	Type	Description
id	INT (AUTO)	Unique ID
sensor1	INT (1/0)	Parking Slot 1
sensor2	INT (1/0)	Parking Slot 2
sensor3	INT (1/0)	Parking Slot 3
sensor4	INT (1/0)	Parking Slot 4
sensor5	INT (1/0)	Parking Slot 5
sensor6	INT (1/0)	Parking Slot 6
Table: test1 (Parking Summary)
Column	Type	Description
id	INT (AUTO)	Unique ID
park_id	INT	Parking Lot ID
free	INT	Total Free Slots
taken	INT	Total Taken Slots

🎯 Future Improvements
Mobile App Integration 📱
Payment via Mobile Money 💰
Camera-based License Plate Recognition 🎥

🤝 Contribution & Support
Fork the repository and submit PRs.

Report issues under GitHub Issues.

For support, contact tuyisengeemmanuel1999@gmail.com or open a discussion.



🚀 Made with ❤️ by Emmanuel TUYISENGE
