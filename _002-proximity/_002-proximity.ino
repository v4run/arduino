int ledPin = 13;
int proxySensorPin = 8;

void setup() {
  pinMode(proxySensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int value = digitalRead(proxySensorPin);
  if (value == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

