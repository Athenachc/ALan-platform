//#include <PID_v1.h>

byte pulPin1 = 13;
byte dirPin1 = 12;
byte pulPin2 = 11;
byte dirPin2 = 10;
byte pulPin3 = 9;
byte dirPin3 = 8;

const byte limit1 = 7;
const byte limit2 = 6;
const byte limit3 = 5;

char input;
int wait = 200; //FASTEST = 130!
int wait2 = 300; //slower to aim smoother

void setup() {
  pinMode(pulPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(pulPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(pulPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);

  digitalWrite(limit1, HIGH); //dun use internal pullup resistor
  digitalWrite(limit2, HIGH); //dun use internal pullup resistor
  digitalWrite(limit3, HIGH); //dun use internal pullup resistor

  Serial.begin(9600);
  Serial.println("Start");
  for (int s = 0; s < 50000 && digitalRead(limit1) == HIGH; s++) {
    digitalWrite(dirPin1, HIGH); //Make sure rod 1 is reaching its lowest
    digitalWrite(pulPin1, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin1, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 50000 && digitalRead(limit2) == HIGH; s++) {
    digitalWrite(dirPin2, HIGH); //Make sure rod 2 is reaching its lowest
    digitalWrite(pulPin2, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin2, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 50000 && digitalRead(limit3) == HIGH; s++) {
    digitalWrite(dirPin3, HIGH); //Make sure rod 3 is reaching its lowest
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait);
  }

  /*
    //Increase height (S/200) mm
    for (int s = 0; s < 20000 ; s++) {
      digitalWrite(dirPin1, LOW);
      digitalWrite(dirPin2, LOW);
      digitalWrite(dirPin3, LOW);
      digitalWrite(pulPin1, HIGH);
      digitalWrite(pulPin2, HIGH);
      digitalWrite(pulPin3, HIGH);
      delayMicroseconds(wait);
      digitalWrite(pulPin1, LOW);
      digitalWrite(pulPin2, LOW);
      digitalWrite(pulPin3, LOW);
      delayMicroseconds(wait);
    }*/

  for (int s = 0; s < 250; s++) {//Pitch down 10 deg - 1
    digitalWrite(dirPin3, LOW); //Rod 3 up
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait2); // set rotate speed
    digitalWrite(pulPin3, LOW); // Output low
    delayMicroseconds(wait2); // set rotate speed
  }
  for (int s = 0; s < 3000; s++) {//Pitch down 10 deg - 2
    digitalWrite(dirPin3, LOW); //Rod 3 up
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait); // set rotate speed
    digitalWrite(pulPin3, LOW); // Output low
    delayMicroseconds(wait); // set rotate speed
  }
  for (int s = 0; s < 250; s++) {//Pitch down 10 deg - 3
    digitalWrite(dirPin3, LOW); //Rod 3 up
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait2); // set rotate speed
    digitalWrite(pulPin3, LOW); // Output low
    delayMicroseconds(wait2); // set rotate speed
  }
}

void loop() {

  for (int s = 0; s < 250; s++) {//Roll left 10 deg - part a1
    digitalWrite(dirPin1, LOW); //Rod 1 up
    digitalWrite(dirPin3, HIGH); //Rod 3 down
    digitalWrite(pulPin1, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin1, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait2);
  }
  for (int s = 0; s < 1250; s++) {//Roll left 10 deg - part a2
    digitalWrite(dirPin1, LOW); //Rod 1 up
    digitalWrite(dirPin3, HIGH); //Rod 3 down
    digitalWrite(pulPin1, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin1, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait);
  }

  for (int s = 0; s < 2250; s++) {//Roll left 10 deg - part b1
    digitalWrite(dirPin1, LOW); //Rod 1 up
    digitalWrite(pulPin1, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin1, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 250; s++) {//Roll left 10 deg - part b2
    digitalWrite(dirPin1, LOW); //Rod 1 up
    digitalWrite(pulPin1, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin1, LOW);
    delayMicroseconds(wait2);
  }

  for (int s = 0; s < 250; s++) {//Pitch up 10 deg - part a1
    digitalWrite(dirPin2, LOW); //Rod 2 up
    digitalWrite(dirPin3, HIGH); //Rod 3 down
    digitalWrite(pulPin2, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin2, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait2);
  }
  for (int s = 0; s < 1750; s++) {//Pitch up 10 deg - part a2
    digitalWrite(dirPin2, LOW); //Rod 2 up
    digitalWrite(dirPin3, HIGH); //Rod 3 down
    digitalWrite(pulPin2, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin2, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 1250; s++) { //Pitch up 10 deg - part b1
    digitalWrite(dirPin2, LOW); //Rod 2 up
    digitalWrite(pulPin2, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin2, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 250; s++) { //Pitch up 10 deg - part b2
    digitalWrite(dirPin2, LOW); //Rod 2 up
    digitalWrite(pulPin2, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin2, LOW);
    delayMicroseconds(wait2);
  }
  for (int s = 0; s < 500; s++) {//Roll right 10 deg - part a
    digitalWrite(dirPin1, HIGH); //Rod 1 down
    digitalWrite(dirPin2, LOW); //Rod 2 up
    digitalWrite(dirPin3, LOW); //Rod 3 uP
    digitalWrite(pulPin1, HIGH);
    digitalWrite(pulPin2, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin1, LOW);
    digitalWrite(pulPin2, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait2);
  }
  for (int s = 0; s < 1500; s++) {//Roll right 10 deg - part b
    digitalWrite(dirPin1, HIGH); //Rod 1 down
    digitalWrite(dirPin3, LOW); //Rod 3 up
    digitalWrite(pulPin1, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin1, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 1750; s++) {//Roll right 10 deg - part b1
    digitalWrite(dirPin1, HIGH); //Rod 1 down
    digitalWrite(pulPin1, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin1, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 250; s++) {//Roll right 10 deg - part b2
    digitalWrite(dirPin1, HIGH); //Rod 1 down
    digitalWrite(pulPin1, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin1, LOW);
    delayMicroseconds(wait);
  }
  for (int s = 0; s < 250; s++) {// Return to Pitch down 10 deg - part a1
    digitalWrite(dirPin2, HIGH);//Rod 2 down
    digitalWrite(dirPin3, LOW); //Rod 3 up
    digitalWrite(pulPin2, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin2, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait2);
  }
  for (int s = 0; s < 1250; s++) {// Return to Pitch down 10 deg - part a2
    digitalWrite(dirPin2, HIGH);//Rod 2 down
    digitalWrite(dirPin3, LOW); //Rod 3 up
    digitalWrite(pulPin2, HIGH);
    digitalWrite(pulPin3, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin2, LOW);
    digitalWrite(pulPin3, LOW);
    delayMicroseconds(wait);
  }

  for (int s = 0; s < 2250; s++) {// Return to Pitch down 10 deg - part b1
    digitalWrite(dirPin2, HIGH); //Rod 2 down
    digitalWrite(pulPin2, HIGH);
    delayMicroseconds(wait);
    digitalWrite(pulPin2, LOW);
    delayMicroseconds(wait);
  }
   for (int s = 0; s < 250; s++) {// Return to Pitch down 10 deg - part b2
    digitalWrite(dirPin2, HIGH); //Rod 2 down
    digitalWrite(pulPin2, HIGH);
    delayMicroseconds(wait2);
    digitalWrite(pulPin2, LOW);
    delayMicroseconds(wait2);
  }
}
