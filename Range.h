int trigPin = 14; // D5
int echoPin = 12; // D6

void range_init() { 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

double get_range() { 
  double duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = duration / 58;
  Serial.print(distance); 
  Serial.println(" cm"); 
  return distance;
}
