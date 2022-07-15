byte pulPin1 = 10;
byte dirPin1 = 5;
byte pulPin2 = 11;
byte dirPin2 = 6;
byte pulPin3 = 12;
byte dirPin3 = 7;

const byte limit1 = 2;
const byte limit2 = 3;
const byte limit3 = A4;

char input;
int steps = 10; //200 steps: 0.9mm, 200 steps/revolution

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

  Serial.begin(115200);
  Serial.println("Start");

}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.print("You typed: ");
    Serial.println(input);

    //Reach minimum strokes!
    if (input == 'x' ) {
      digitalWrite(dirPin1, HIGH);
      for (int s = 0; s < 50000 && digitalRead(limit1) == HIGH; s++) {
        digitalWrite(pulPin1, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin1, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }

    if (input == 'y') {
      digitalWrite(dirPin2, HIGH);
      for (int s = 0; s < 50000  && digitalRead(limit2) == HIGH; s++) {
        digitalWrite(pulPin2, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin2, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }

    if (input == 'z' ) {
      digitalWrite(dirPin3, HIGH);
      for (int s = 0; s < 50000 && digitalRead(limit3) == HIGH; s++) {
        digitalWrite(pulPin3, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin3, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }

    //Moving UPWARD!
    if (input == 'a') { //Rod 1 moves upward
      digitalWrite(dirPin1, LOW);
      for (int s = 0; s < 500; s++) {
        digitalWrite(pulPin1, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin1, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }
    if (input == 'b') { //Rod 2 moves upward
      digitalWrite(dirPin2, LOW);
      for (int s = 0; s < 500; s++) {
        digitalWrite(pulPin2, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin2, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }
    if (input == 'c') { //Rod 3 moves upward
      digitalWrite(dirPin3, LOW);
      for (int s = 0; s < 500; s++) {
        digitalWrite(pulPin3, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin3, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }

    //Moving DOWNWARD!
    if (input == 'd') { //Rod 1 moves downward
      digitalWrite(dirPin1, HIGH);
      for (int s = 0; s < 500; s++) {
        digitalWrite(pulPin1, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin1, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }
    if (input == 'e') { //Rod 2 moves downward
      digitalWrite(dirPin2, HIGH);
      for (int s = 0; s < 500; s++) {
        digitalWrite(pulPin2, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin2, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }
    if (input == 'f') { //Rod 3 moves downward
      digitalWrite(dirPin3, HIGH);
      for (int s = 0; s < 500; s++) {
        digitalWrite(pulPin3, HIGH);
        delayMicroseconds(300); // set rotate speed
        digitalWrite(pulPin3, LOW); // Output low
        delayMicroseconds(300); // set rotate speed
      }
    }


  }
}
