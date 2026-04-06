#define PROXY_TTD 58 // proxy-sensor time-to-distance ratio
#define triggerPin 12
#define echoPin 11
#define minDistance 10 // cm
#define distanceTriggerTimeMiliseconds = 5000

unsigned long distanceExceededMiliseconds = 0;

void setup() {
  Serial.begin (9600);
  pinMode(triggerPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
}

void loop() {
  unsigned long timestamp = millis();
  delay(500);

  long distance = getDistanceCentimeters();  
  if (distance >= minDistance) {
    distanceExceededMiliseconds += timestamp - millis(); // TODO: This number will overflow (go back to zero), after approximately 50 days.
    Serial.print(distance);
    Serial.println(" cm [ALERT!]");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}

int getDistanceCentimeters(){
  long time, distance;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  time = pulseIn(echoPin, HIGH);
  distance = time / PROXY_TTD;
  return distance;
}