//This code contains the implementation of Cryptography Part 2: Hashing Data using SHA256
//Hashing ensures data integrity by generating a fixedlength hash from input data. 
//Here’s how to implement SHA256 hashing in Arduino IDE:

#include <SHA256.h> // Include the SHA256 library

SHA256 sha256; // Create an instance of the SHA256 class
byte hash[32]; // Buffer to store the resulting hash (SHA256 produces a 32-byte hash)

void setup() {
    Serial.begin(9600); // Initialize serial communication at 9600 baud
    Serial.println("Enter a message to hash:");
}

void loop() {
    if (Serial.available() > 0) {
        // Read the message from the Serial Monitor
        String message = Serial.readStringUntil('\n'); // Read until a newline
        int messageLength = message.length(); // Get the length of the message

        // Print message length
        Serial.print("Message Length: ");
        Serial.println(messageLength);

        // Prepare a byte array for the message
        byte* messageBytes = new byte[messageLength + 1]; // +1 for null terminator
        message.getBytes(messageBytes, messageLength + 1); // Convert String to byte array

        // Compute SHA256 hash
        sha256.reset(); // Reset the SHA256 object
        sha256.update(messageBytes, messageLength); // Update with the message
        sha256.finalize(hash, sizeof(hash)); // Finalize and compute the hash

        // Output the hash in both uppercase and lowercase
        Serial.println("SHA256 Hash (Lowercase):");
        printHash(hash, false); // Print in lowercase

        Serial.println("SHA256 Hash (Uppercase):");
        printHash(hash, true); // Print in uppercase

        delete[] messageBytes; // Free dynamically allocated memory
        Serial.println("Enter a message to hash:");
    }
}

void printHash(byte* hash, bool uppercase) {
    for (int i = 0; i < 32; i++) {
        if (uppercase) {
            if (hash[i] < 16) Serial.print("0"); // Print leading zero for values less than 16
            Serial.print(hash[i], HEX); // Print each byte of the hash in hexadecimal format
        } else {
            if (hash[i] < 16) Serial.print("0"); // Print leading zero for values less than 16
            Serial.print(hash[i] < 10 ? char('0' + hash[i]) : char('a' + hash[i] - 10)); // Lowercase output
        }
        Serial.print(" "); // Add space for better readability
    }
    Serial.println(); // New line after printing the hash
}

