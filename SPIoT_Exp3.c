// Simulate temperature and light sensor data

// Defining constants for temperature range and light intensity threshold
const float MIN_TEMP_C = 15.0;  // Minimum temperature in Celsius
const float MAX_TEMP_C = 35.0;  // Maximum temperature in Celsius
const int LIGHT_THRESHOLD = 400; // Threshold for light intensity

// Global variables
float temperature;         // Variable to hold temperature in Celsius
float temperatureF;       // Variable to hold temperature in Fahrenheit
int lightIntensity;       // Variable to hold light intensity
String lightStatus;       // Variable to hold the status of light intensity

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Initialize sensor values
  initializeSensors();
}

void loop() {
  // Generate random temperature between 15°C and 35°C
  temperature = random(MIN_TEMP_C * 10, MAX_TEMP_C * 10) / 10.0; // Random temperature

  // Generate random light intensity between 0 and 1023
  lightIntensity = random(0, 1024); // Simulate light intensity

  // Manipulate sensor data
  temperatureF = (temperature * 9.0 / 5.0) + 32; // Convert Celsius to Fahrenheit
  lightStatus = (lightIntensity < LIGHT_THRESHOLD) ? "LOW" : "HIGH"; // Determine light status

  // Print the data to the serial monitor
  printSensorData();

  // Delay for 2 seconds before the next reading
  delay(2000);
}

// Function to initialize sensors (can be expanded for future use)
void initializeSensors() {
  // Placeholder for any sensor initialization code
  Serial.println("Initializing sensors...");
  delay(500);
}

// Function to print sensor data to the serial monitor
void printSensorData() {
  Serial.print("Temperature (C): ");
  Serial.print(temperature);
  Serial.print(" | Temperature (F): ");
  Serial.print(temperatureF);
  Serial.print(" | Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.print(" | Light Status: ");
  Serial.println(lightStatus);
}
