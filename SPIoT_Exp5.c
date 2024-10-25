// Define the pins for each color
const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 4;

// Define the timing intervals (in milliseconds)
const unsigned long redDuration = 5000;       // Duration for red light
const unsigned long yellowDuration = 2000;    // Duration for yellow light
const unsigned long greenDuration = 5000;     // Duration for green light
const unsigned long yellowBlinkInterval = 500; // Blinking interval for yellow

// State variables
unsigned long previousMillis = 0;
int currentState = 0; // 0: Red, 1: Yellow, 2: Green
bool yellowBlinkState = LOW; // Yellow light blink state

// Function to initialize pin modes
void initializePins() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

// Function to update the traffic light state
void updateTrafficLight() {
  unsigned long currentMillis = millis();

  // Control the traffic light based on the current state
  switch (currentState) {
    case 0: // Red Light
      digitalWrite(redPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);

      // Transition to yellow after red duration
      if (currentMillis - previousMillis >= redDuration) {
        previousMillis = currentMillis;
        currentState = 1; // Move to yellow
      }
      break;

    case 1: // Blinking Yellow Light
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);

      // Toggle yellow light blinking
      if (currentMillis - previousMillis >= yellowBlinkInterval) {
        yellowBlinkState = !yellowBlinkState; // Toggle yellow light
        digitalWrite(yellowPin, yellowBlinkState);
        previousMillis = currentMillis;
      }

      // Move to next state after yellow duration
      if (currentMillis - previousMillis >= yellowDuration) {
        currentState = 2; // Move to green
        previousMillis = currentMillis; // Update previousMillis for green light
      }
      break;

    case 2: // Green Light
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, HIGH);

      // Transition back to red after green duration
      if (currentMillis - previousMillis >= greenDuration) {
        previousMillis = currentMillis;
        currentState = 0; // Reset to red
      }
      break;
  }
}

void setup() {
  initializePins(); // Initialize the pins
  previousMillis = millis(); // Store the initial time
}

void loop() {
  updateTrafficLight(); // Continuously update the traffic light state
}
