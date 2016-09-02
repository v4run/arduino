/*
 * Ultrasolic sensor(HC-SR04) + Nokia 3110 display
 * 
 * HC-SR04
 * -------
 * VCC  - 5v
 * Gnd  - GND
 * Echo - 9
 * Trig - 8
 * 
 * Display
 * -------
 * GND   - GND
 * BL    - 3.3v
 * VCC   - 3.3v
 * CLK   - 3 
 * DIN   - 4
 * DC    - 5
 * CE    - 7
 * RST   - 6
 */
#include <PCD8544.h>

const int echoPin = 9;
const int trigPin = 8;

static PCD8544 lcd;
int distance = 0, maximum = 0, minimum = 10000;

void setup() {
  lcd.begin(84, 48);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
}

long ping() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void loop() {
  static int i = 0;
  delay(100);                                                 
  long cm = microsecondsToCentimeters(ping());
  if (cm == 0 || cm > 400) {
    return;
  }
  if (distance != cm) {
    distance = cm;
    lcd.setCursor(0, 0);
    lcd.clearLine();
    lcd.print(distance);
    lcd.print("cm");
  }
  if (cm > maximum) {
    maximum = cm;
    lcd.setCursor(0, 1);
    lcd.clearLine();
    lcd.print("Max:");
    lcd.print(maximum);
    lcd.print("cm");
  }
  if (cm < minimum) {
    minimum = cm;
    lcd.setCursor(0, 2);
    lcd.clearLine();
    lcd.print("Min:");
    lcd.print(minimum);
    lcd.print("cm");
  }
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
