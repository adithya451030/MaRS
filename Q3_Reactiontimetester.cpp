const int ledPin = 13;
const int buttonPin = 2;

unsigned long previousMillis = 0;
unsigned long randomDelayTime = 0;
unsigned long startTime = 0;

int state = 0;

// For single press detection
int lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

  randomSeed(analogRead(0));

  previousMillis = millis();
  randomDelayTime = random(2000, 5000);
}

void loop() {
  unsigned long currentMillis = millis();
  int currentButtonState = digitalRead(buttonPin);

  switch (state) {
    // STATE 0: WAIT RANDOM TIME
    case 0:
      if (currentButtonState == LOW && lastButtonState == HIGH) {
        Serial.println("Too Early! Wait for LED.");
        previousMillis = currentMillis;
        randomDelayTime = random(2000, 5000);
      }

      if (currentMillis - previousMillis >= randomDelayTime) {
        digitalWrite(ledPin, HIGH);
        startTime = currentMillis;
        state = 1;
      }
      break;
    // STATE 1: WAIT FOR BUTTON PRESS
    case 1:
      if (currentButtonState == LOW && lastButtonState == HIGH) {

        delay(50); // simple debounce

        if (digitalRead(buttonPin) == LOW) {

          unsigned long reactionTime = currentMillis - startTime;

          Serial.print("Reaction Time: ");
          Serial.print(reactionTime);
          Serial.println(" ms");

          digitalWrite(ledPin, LOW);

          previousMillis = currentMillis;
          state = 2;
        }
      }
      break;
    // STATE 2: PAUSE BEFORE NEXT ROUND
    case 2:
      if (currentMillis - previousMillis >= 2000) {
        previousMillis = currentMillis;
        randomDelayTime = random(2000, 5000);
        state = 0;
      }
      break;
  }

  // update last button state (IMPORTANT)
  lastButtonState = currentButtonState;
}
