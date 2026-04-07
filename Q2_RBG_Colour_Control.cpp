unsigned long previousMillis = 0; // Stores the time that any changes happen before
int ledState = 0;        // LED ON/OFF state for blinking
int sensorValue = 0;     // Stores potentiometer value

long time;               // Stores pulse duint sensorValue = 0;          // Stores analog input

unsigned long previousMillis = 0; // Stores last time LED ON/OFF
int ledState = 0;                 //ON/OFF state of LED

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

  int interval = 50 + (sensorValue / 2);  // // Adds a minimum delay to prevent very fast blinking

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;  // Update last ON/OFF time

    ledState = 1 - ledState;         // LED state (0 <-> 1)
    digitalWrite(13, ledState);      // Apply state to LED
  }
}ration
int distance;            // Stores calculated distance

void setup()
{
  pinMode(9, OUTPUT); // Set trigger as output
  pinMode(8, INPUT);  // Set echo as input

  pinMode(3, OUTPUT); // RGB Red pin
  pinMode(5, OUTPUT); // RGB Green pin
  pinMode(6, OUTPUT); // RGB Blue pin

  Serial.begin(9600); 
}

void loop()
{
  digitalWrite(9, LOW);        // Ensure LOW
  delayMicroseconds(2);              // Small delay

  digitalWrite(9, HIGH);       // Send pulse
  delayMicroseconds(10);       
  digitalWrite(9, LOW);        // Stop pulse

  time = pulseIn(8, HIGH);     // Measure echo time
  distance = time * 0.034 / 2;       // Convert to distance in cm

  int potValue = analogRead(A0);     // Read analog value
  int threshold = (potValue / 10)+10;// Set adjustable threshold

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm  | Threshold: ");
  Serial.println(threshold);

  unsigned long currentMillis = millis(); // Current time

  sensorValue = analogRead(A0);     // Read potentiometer again
  int val = sensorValue / 4;        // Convert to PWM range (0–255)

  if (distance > threshold)  // FAR → Green LED
  {
    analogWrite(3, 0);  
    analogWrite(5, val);   // Green ON
    analogWrite(6, 0);  
  }
  else if (distance > threshold / 2)    // MEDIUM → Yellow LED
  {
    analogWrite(3, val);   // Red ON
    analogWrite(5, val);   // Green ON
    analogWrite(6, 0);  
  }
  else if (distance > 5) // NEAR → Red LED
  {
    analogWrite(3, val);   // Red ON
    analogWrite(5, 0);  
    analogWrite(6, 0);     
  }
  else // VERY CLOSE → Blinking Red
  {
    if (currentMillis - previousMillis >= 150) // Check time interval
    {
      previousMillis = currentMillis; // Update time
      ledState = 1 - ledState;        // change state

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
