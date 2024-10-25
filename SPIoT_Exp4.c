// Advanced LED Control using Serial Commands

const int ledPin = 13;              // Define the pin for the LED
const unsigned long LED_TIMEOUT = 5000; // Timeout duration for automatic LED turn-off (5 seconds)

unsigned long ledOnTime;             // Variable to track when the LED was turned on
bool ledState = false;               // Variable to track the LED state

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Inform the user about the available commands
  Serial.println("LED Control System Ready.");
  Serial.println("Enter 'LED ON' to turn the LED on or 'LED OFF' to turn it off.");
}

void loop() {
  // Check if data is available to read from the serial port
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read the incoming command
    command.trim(); // Remove any leading or trailing whitespace

    // Process the command
    processCommand(command);
  }

  // Check if the LED is on and if the timeout duration has elapsed
  if (ledState && (millis() - ledOnTime >= LED_TIMEOUT)) {
    turnOffLED(); // Turn off the LED after the timeout
  }
}

// Function to process received commands
void processCommand(String command) {
  if (command.equalsIgnoreCase("LED ON")) { // Turn the LED on
    turnOnLED();
  } else if (command.equalsIgnoreCase("LED OFF")) { // Turn the LED off
    turnOffLED();
  } else {
    Serial.println("Unknown command. Please enter 'LED ON' or 'LED OFF'.");
  }
}

// Function to turn on the LED
void turnOnLED() {
  digitalWrite(ledPin, HIGH); // Set the LED pin HIGH
  ledState = true;             // Update LED state
  ledOnTime = millis();        // Record the time the LED was turned on
  Serial.println("LED is now ON");
}

// Function to turn off the LED
void turnOffLED() {
  digitalWrite(ledPin, LOW); // Set the LED pin LOW
  ledState = false;          // Update LED state
  Serial.println("LED is now OFF");
}
