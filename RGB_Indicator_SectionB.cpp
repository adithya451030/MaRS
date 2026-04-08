long time;               // Stores pulse duration
int distance;            // Stores calculated distance

unsigned long previousMillis = 0; // For previous time recording
int ledState = 0;        // LED ON/OFF state for blinking
int sensorValue = 0;     // Stores potentiometer value

void setup()
{
  pinMode(9, OUTPUT); // Set trigger as output
  pinMode(8, INPUT);  // Set echo as input

  pinMode(3, OUTPUT); // RGB Red pin
  pinMode(5, OUTPUT); // RGB Green pin
  pinMode(6, OUTPUT); // RGB Blue pin

  Serial.begin(9600); // Start serial communication
}

void loop()
{
  // Ultrasonic signal generation
  digitalWrite(9, LOW);        // Ensure LOW
  delayMicroseconds(2);              // Small delay

  digitalWrite(9, HIGH);       // Send pulse
  delayMicroseconds(10);   
  digitalWrite(9, LOW);        // Stop pulse

  time = pulseIn(8, HIGH);     // Measure echo time
  distance = time * 0.034 / 2;       // Convert to distance in cm

  // Potentiometer reading
  int potValue = analogRead(A0);     // Read analog value
  int threshold = (potValue / 10)+10;// Set adjustable threshold

  // Display values
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm  | Threshold: ");
  Serial.println(threshold);

  unsigned long currentMillis = millis(); // Current time

  // Brightness control
  sensorValue = analogRead(A0);     // Read potentiometer again
  int val = sensorValue / 4;        // Convert to PWM range (0–255)

  //  LOGIC
  if (distance > threshold)
  {
    // FAR → Green LED
    analogWrite(3, 0);     // Red OFF
    analogWrite(5, val);   // Green ON
    analogWrite(6, 0);     // Blue OFF
  }
  else if (distance > threshold / 2)
  {
    // MEDIUM → Yellow LED
    analogWrite(3, val);   // Red ON
    analogWrite(5, val);   // Green ON
    analogWrite(6, 0);     // Blue OFF
  }
  else if (distance > 5)
  {
    // NEAR → Red LED
    analogWrite(3, val);   // Red ON
    analogWrite(5, 0);     // Green OFF
    analogWrite(6, 0);     // Blue OFF
  }
  else
  {
    // VERY CLOSE → Blinking Red
    if (currentMillis - previousMillis >= 150) // Check time interval
    {
      previousMillis = currentMillis; // Update time
      ledState = 1 - ledState;

      if (ledState)
      {
        analogWrite(3, val); // Red ON
        analogWrite(5, 0);
        analogWrite(6, 0);
      }
      else
      {
        analogWrite(3, 0); // All OFF
        analogWrite(5, 0);
        analogWrite(6, 0);
      }
    }
  }
}
