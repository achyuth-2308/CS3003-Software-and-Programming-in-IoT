//This code contains the implementation of Cryptography Part 1: AES - Encryption and Decryption

#include <AES.h>    // Include the AES library
#include <Crypto.h> // Include the Crypto library

// Create an instance of the AES128 class
AES128 aes;

// Define a 16-byte encryption key (must be 16 bytes for AES-128)
byte key[16] = {
    0x2b, 0x7e, 0x15, 0x16,
    0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x01, 0x2f,
    0xbf, 0xd5, 0x5b, 0x6e
};

// Define the plaintext (must be 16 bytes for AES block size)
byte plainText[16] = {
    'E', 'x', 'a', 'm',
    'p', 'l', 'e', 'T',
    'e', 'x', 't', '1',
    '2', '3', '4', '!'
};

byte cipherText[16];    // Buffer for the ciphertext
byte decryptedText[16];  // Buffer for the decrypted text

void setup() {
    Serial.begin(9600); // Initialize serial communication at 9600 baud

    // Encrypt the plaintext
    aes.setKey(key, sizeof(key));            // Set the encryption key
    aes.encryptBlock(cipherText, plainText); // Encrypt the plaintext

    // Decrypt the ciphertext
    aes.decryptBlock(decryptedText, cipherText); // Decrypt the ciphertext

    // Output results
    Serial.println("Plaintext:");
    for (int i = 0; i < 16; i++) {
        Serial.print((char)plainText[i]); // Print the original plaintext
    }

    Serial.println("\nCiphertext (Hex):");
    for (int i = 0; i < 16; i++) {
        Serial.print(cipherText[i], HEX); // Print the ciphertext in hexadecimal format
        Serial.print(" "); // Add space for better readability
    }

    Serial.println("\nDecrypted Text:");
    for (int i = 0; i < 16; i++) {
        Serial.print((char)decryptedText[i]); // Print the decrypted text
    }
}

void loop() {
    // Nothing to do here
}
