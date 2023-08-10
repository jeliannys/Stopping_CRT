const int analogPin = A0;  // Analog input pin
float slope, intercept;   // Declaring slope and intercept globally

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(analogPin, INPUT);  // Set analog pin as input
  
  // Calibrate pH and analog values for solutions 1 and 2
  Calibrate();
}

void loop() {
  static bool solution3Calibrated = false;
  
  if (!solution3Calibrated) {
    // Prompt user to place pH probe in solution 3
    Serial.println("Place the pH probe in solution 3 and press Enter");
    waitForEnter();  // Wait for user to press Enter

    solution3Calibrated = true;
  }

  // Read analog voltage for solution 3
  float voltage3 = analogRead(analogPin) * 0.0048828125;  // Convert analog reading to voltage
  delay(1000);  // Delay for stability

  // Calculate the pH value for solution 3 using the linear relationship
  float pH3 = slope * voltage3 + intercept;

  // Output the pH value for solution 3
  Serial.print("pH value for solution 3: ");
  Serial.println(pH3, 2);  // Print pH value with 2 decimal places
}

void Calibrate() {
  float pH1, pH2;           // User-inputted pH values
  float voltage1, voltage2; // Corresponding analog voltage values

  // Prompt user to place pH probe in solution 1
  Serial.println("Place the pH probe in solution 1 and press Enter");
  waitForEnter();  // Wait for user to press Enter

  // Prompt user for pH value 1
  Serial.println("Enter pH value 1:");
  while (!Serial.available()) {}  // Wait for input
  pH1 = Serial.parseFloat();     // Read pH value from serial monitor

  // Read analog voltage for solution 1
  voltage1 = analogRead(analogPin) * 0.0048828125;  // Convert analog reading to voltage
  delay(100);  // Delay for stability

  // Prompt user to place pH probe in solution 2
  Serial.println("Place the pH probe in solution 2 and press Enter");
  waitForEnter();  // Wait for user to press Enter

  // Prompt user for pH value 2
  Serial.println("Enter pH value 2:");
  while (!Serial.available()) {}  // Wait for input
  pH2 = Serial.parseFloat();     // Read pH value from serial monitor

  // Read analog voltage for solution 2
  voltage2 = analogRead(analogPin) * 0.0048828125;  // Convert analog reading to voltage
  delay(100);  // Delay for stability

  // Calculate the slope and intercept of the linear relationship
  slope = (pH2 - pH1) / (voltage2 - voltage1);
  intercept = pH1 - slope * voltage1;
}

void waitForEnter() {
  while (true) {
    while (Serial.available()) {
      Serial.read();  // Clear the serial buffer
    }
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        break;
      }
    }
  }
}