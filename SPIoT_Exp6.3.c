//This code contains the implementation of Cryptography Part 3: Implementing Secure Communication with TLS
//To ensure secure communication between IoT devices, TLS can be used. 
//The `BearSSL` library in Arduino IDE can be used to establish a secure SSL/TLS connection.

#include <WiFiClientSecure.h> // Include library for secure WiFi connections
#include <BearSSL.h> // Include BearSSL for secure connections

// Replace with your network credentials
const char* ssid = "yourSSID"; // SSID for WiFi
const char* password = "yourPASSWORD"; // Password for WiFi

const char* host = "example.com"; // Server to connect to
WiFiClientSecure client; // Create a secure WiFi client

void setup() {
    Serial.begin(9600); // Initialize serial communication
    connectToWiFi(); // Connect to WiFi
    makeHttpsRequest(); // Make HTTPS request
}

void loop() {
    // No need for repeated actions in loop
}

// Function to connect to WiFi
void connectToWiFi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password); // Start WiFi connection

    unsigned long startTime = millis(); // Start timer for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("."); // Print dots to show progress
        // Check for timeout (10 seconds)
        if (millis() - startTime > 10000) {
            Serial.println("\nConnection timed out!");
            return; // Exit if connection times out
        }
    }
    Serial.println("\nConnected to WiFi!");
}

// Function to make HTTPS GET request
void makeHttpsRequest() {
    client.setInsecure(); // For testing purposes only. Replace with proper certificate verification in production.

    Serial.print("Connecting to ");
    Serial.println(host);

    if (!client.connect(host, 443)) {
        Serial.println("Connection failed!");
        return; // Exit if connection fails
    }

    // Send HTTP GET request
    client.println("GET / HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Connection: close");
    client.println();

    // Read and print the response
    Serial.println("Response:");
    while (client.connected() || client.available()) {
        if (client.available()) {
            String line = client.readStringUntil('\n');
            Serial.println(line); // Print each line of the response
        }
    }

    client.stop(); // Close the connection
    Serial.println("Connection closed.");
}
