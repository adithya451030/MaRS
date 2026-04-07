unsigned long previousMillis = 0; // Stores last time LED state changed

unsigned long interval = 1000; // Time interval for ON/OFF

int timedelay = 500;

int state = 1; // Keeps track of which step we are in

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis(); // current time

  if (currentMillis - previousMillis >= interval)// Check if required time has passed
  {
    previousMillis = currentMillis; // Save current time for next comparison

    switch (state)
    {
      case 1: // STEP 1: Turn LEDs ON
      
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);
      
        interval = 1000; // stay ON for 1 second
        timedelay = 500; // Resets timedelay after running more than one time
        state = 2;       // move to next step
        break;

      case 2: // STEP 2: Turn LEDs OFF
      
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);

        interval = timedelay; // wait for timedelay
        timedelay += 500;     // increase delay for next time
        state = 3;
        break;

      case 3: // STEP 3: Turn LEDs ON again
      
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);

        interval = 1000;
        state = 4;
        break;

      case 4: // STEP 4: Turn LEDs OFF again
      
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);

        interval = timedelay; // increased delay again
        timedelay += 500;
        state = 5;
        break;

      case 5: // STEP 5: Turn LEDs ON third time
      
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, HIGH);

        interval = 1000;
        state = 6;
        break;

      case 6: // STEP 6: Final OFF
      
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);

        interval = 1000;
        state = 1; // restart sequence from beginning
        break;
    }
  }
}
