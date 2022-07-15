#include "stepper.h"

#define LIMIT_SWITCH1 2
#define LIMIT_SWITCH2 3
#define LIMIT_SWITCH3 18

int motor_counter = 0, motor_pulse_width = 1;
int speed = 400;
volatile int32_t position_counter = 0;
int32_t set_position[3] = {0, 0, 0};
int32_t prev_position[3] = {0, 0, 0};
bool pulse_high = 0;

int stepper_index = 0;

Stepper stepper1(10, 5, 4);
Stepper stepper2(11, 6, 5);
Stepper stepper3(12, 7, 6);

//unsigned long elapsed_time;

ISR(TIMER1_COMPA_vect) {//counter overflows
  stepper1.stepperPulseGen();
  stepper2.stepperPulseGen();
  stepper3.stepperPulseGen();
  TCNT1 = 0;
}

void reached_limit1() {
  stepper1.homing();
  detachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH1));
}

void reached_limit2() {
  stepper2.homing();
  detachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH2));
}

void reached_limit3() {
  stepper3.homing();
  detachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH3));
}

void setup() {
  //stepper motor timer every 100us
  TCCR1A = 0; TCCR1B = 0; TCCR1B |= (1 << CS10);  TIMSK1 |= (1 << OCIE1A);  OCR1A = 319;
  //PID controller refresh timer @ 250Hz
  //TCCR2A = 0; TCCR2B = 0; TCCR2B |= (1 << CS22) | (1 << CS21);  TIMSK2 |= (1 << TOIE2); TCNT2 = 6;

  pinMode(LIMIT_SWITCH1, INPUT);
  pinMode(LIMIT_SWITCH2, INPUT);
  pinMode(LIMIT_SWITCH3, INPUT);

  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH1), reached_limit1, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH2), reached_limit2, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH3), reached_limit3, FALLING);

  Serial.begin(115200);
  Serial.println("Each rod moves upwards for 2 sec");
  stepper1.setSpeed(400);
  stepper2.setSpeed(400);
  stepper3.setSpeed(400);

  delay(4000);

  Serial.println("Each rod starts homing until reaches their own limit");
  stepper1.setSpeed(-400);
  stepper2.setSpeed(-400);
  stepper3.setSpeed(-400);
  while (!stepper1.homed || !stepper2.homed || !stepper3.homed);
}

void loop() {
  if (Serial.available() > 0) {
    prev_position[0] = set_position[0];
    prev_position[1] = set_position[1];
    prev_position[2] = set_position[2];
    set_position[0] = Serial.parseInt();
    set_position[1] = Serial.parseInt();
    set_position[2] = Serial.parseInt();

    while (Serial.available()) Serial.read();
  }
  //  Serial.print("Stepper ");
  //  Serial.print(stepper_index + 1);
  //  Serial.print(" set position: ");
  //  Serial.print(set_position[stepper_index]);
  //  Serial.print("\tPosition");
  //  if (stepper_index == 0)
  //    Serial.println(stepper1.position_counter);
  //  else if (stepper_index == 1)
  //    Serial.println(stepper2.position_counter);
  //  else if (stepper_index == 2)
  //    Serial.println(stepper3.position_counter);
  stepper1.movePositionAccel(prev_position[0], set_position[0], 20000);
  stepper2.movePositionAccel(prev_position[1], set_position[1], 20000);
  stepper3.movePositionAccel(prev_position[2], set_position[2], 20000);

  Serial.print("Rod 1 position: ");
  Serial.print(stepper1.position_counter);
  Serial.print('\t');
  Serial.print("Rod 2 position: ");
  Serial.print(stepper2.position_counter);
  Serial.print('\t');
  Serial.print("Rod 3 position: ");
  Serial.println(stepper3.position_counter);


  //  stepper1.movePosition(set_position[0]);
  //  stepper2.movePosition(set_position[1]);
  //  stepper3.movePosition(set_position[2]);

  //stepper2.setSpeed(400);
}
