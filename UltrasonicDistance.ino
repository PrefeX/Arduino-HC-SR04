/*
  Simple program for reading the distance from a HC-SR04 Ultrasonic sensor.
*/

// Assign some more user-friendly names to the pins
const int TRIGGER = 2;
const int ECHO = 3;

long travelTime;
int distance;

void setup() {
  // Configure the pins as inputs or outputs
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  // Enable serial communication
  Serial.begin(9600);

  // Make sure we start with cleared pins
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
}

void loop() {
  Trigger();

  // Record the sounds travel-time in micro-sec
  travelTime = pulseIn(ECHO, HIGH);

  // Calculate the distance
  distance = CalculateDistance(travelTime);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
}

// Activate the sensor for 10µs. Results in a 8-cycle sonic burst
long Trigger() {
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
}

// Calculate the distance based on the signal's traveltime
float CalculateDistance(long travelTime) {

  /*
    Speed of sound:  v = 340m/s  = 0.034cm/µs
    Time:            t = s / v   = travelTime / 0.034  = ?µs
    Distance:        s = t * v
  */

  // We divide it by 2 because we just want the time used for the return, not both ways.
  int _distance = travelTime * 0.034 / 2;

  // Check if the recorded distance is outside what the sensor can read
  if (_distance < 2 || _distance > 400)
    return NULL;
  else
    return _distance;
}
