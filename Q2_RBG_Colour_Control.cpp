unsigned long previousMillis = 0; // Stores the time that any changes happen before
int ledState = 0;        // LED ON/OFF state for blinking
int sensorValue = 0;     // Stores potentiometer value

void setup()
{
  pinMode(A0, INPUT);        // Set analog pin for sensor input

  pinMode(11, OUTPUT);       // Red channel of RGB LED (PWM)
  pinMode(10, OUTPUT);       // Green channel of RGB LED (PWM)
  pinMode(9, OUTPUT);        // Blue channel of RGB LED (PWM)

  pinMode(13, OUTPUT);       // Normal LED for blinking
}

void loop()
{
  sensorValue = analogRead(A0);   // Read sensor value (0–1023)

  int val = sensorValue / 4;      // Used for color transitions

  analogWrite(11, val);           // Red increases with sensor value
  analogWrite(10, 255 - val);     // Green decreases (inverse relation)
  analogWrite(9, val / 2);        // Blue increases slowly (half intensity)

  unsigned long currentMillis = millis(); // Get current time

  int interval = 50 + (sensorValue / 2);  // // Adds a minimum delay to prevent very fast blinking. 50 is added for better results

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;  // Update last ON/OFF time

    ledState = 1 - ledState;         // LED state (0 <-> 1)
    digitalWrite(13, ledState);      // Apply state to LED
  }
}
