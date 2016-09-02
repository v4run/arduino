/*
 * Sound detection.
 */

int soundDPin = 8;
int soundAPin = A0;
int ledPin = 13;

void setup() {
  pinMode(soundDPin, INPUT);
  pinMode(ledPin, OUTPUT);
//  Serial.begin(9600);
}

void loop() {
//  int statusD = digitalRead(soundDPin);
  int statusA = analogRead(soundAPin);
  if (statusA < 510) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
