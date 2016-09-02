/*
 * Toggle led on alternate detection
 */
int ledPin = 13;
int proxySensorPin = 8;
boolean lastValue = LOW;
boolean ledOn = false;

void setup() {
  pinMode(proxySensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int value = digitalRead(proxySensorPin);
  if (value == HIGH && lastValue == LOW) {
    ledOn = !ledOn;
  }
  digitalWrite(ledPin, ledOn);
  lastValue = value;
}

