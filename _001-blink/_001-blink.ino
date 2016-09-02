/*
 * My first project. Blink onboard led.
 */

 int ledPin = 13;

 void setup() {
  // Initialize pins as outputs
  pinMode(ledPin, OUTPUT);
 }

 void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
 }
 
