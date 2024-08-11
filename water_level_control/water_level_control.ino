
int relay1 = 8;
int relay2 = 7;
int echoPin1 = 9;
int trigPin1 = 10;
int echoPin2 = 11;
int trigPin2 = 12;
float duration1,duration2;
int levelDifference;
int distance1,distance2;
void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 * 0.0343) / 2;
  Serial.print("Distance1: ");
  Serial.println(distance1);
  
  delay(100);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * 0.0343) / 2;
  Serial.print("Distance2: ");
  Serial.println(distance2);

  levelDifference = distance1- distance2; // we will set a threshold by calculating the difference in water level
  delay(50);
  
  if (levelDifference > 1) { // activate pump 1 for pumping water into tank 2
    digitalWrite(relay1, LOW); // low level triggered relay
    digitalWrite(relay2, HIGH);
    delay(1000);   
  } else if(levelDifference < -1) { // activate pump 2 for pumping water into tank 1
    digitalWrite(relay2, LOW); // low level triggered relay
    digitalWrite(relay1, HIGH);
    delay(1000);
  } else {                     // turn off pumps
    digitalWrite(relay1, HIGH); 
    digitalWrite(relay2, HIGH);
    delay(1000);
  }
}
