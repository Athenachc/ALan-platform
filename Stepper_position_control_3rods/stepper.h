#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

#define STEP_PORT PORTB

class Stepper {
  public:
    //STEP/DIR and endstop pins
    int step_pin;
    int dir_pin;
    int endstop_pin;
    byte step_port;
    byte step_pin_num;
    //variables for pulse generation
    volatile bool pulse_high = 0;
    volatile int motor_counter = 0, motor_pulse_width = 1;
    //speed and position variables
    int spd;
    volatile int32_t position_counter;
    int32_t set_position;

    volatile bool homed = false;

    //public:
    Stepper(int step, int dir, byte pin_num) {
      //num_stepper++;
      step_pin = step;
      dir_pin = dir;
      step_pin_num = pin_num;
      pinMode(step_pin, OUTPUT);
      pinMode(dir_pin, OUTPUT);
    }
//    Stepper(int step, int dir, byte pin_num, int endstop) {
//      //num_stepper++;
//      step_pin = step;
//      dir_pin = dir;
//      step_pin_num = pin_num;
//      endstop_pin = endstop;
//      pinMode(step_pin, OUTPUT);
//      pinMode(dir_pin, OUTPUT);
//      pinMode(endstop_pin, INPUT);
//    }

    void stepperPulseGen() {
      if (pulse_high) {
        STEP_PORT &= ~(1 << step_pin_num); //set step pin low
        pulse_high = 0;
      }
      else if (motor_counter < motor_pulse_width) motor_counter++;
      else if (motor_counter == motor_pulse_width) {
        STEP_PORT |= 1 << step_pin_num; //set step pin high
        motor_counter = 0; //reset motor_counter
        pulse_high = 1; //change pulse_high
        if (spd > 0)
          position_counter++; //if moving upwards --> increases position_counter
        else
          position_counter--; //if moving downwards --> decreases position_counter
      }
      else motor_counter = 0;
    }

//    void homeStepper() {
//      Serial.println("Moving stepper outward");
//      spd = 400;
//      digitalWrite(dir_pin, spd < 0);
//      if (spd) motor_pulse_width = 5000 / abs(spd);
//      delay(500);
//      Serial.println("Homing stepper");
//      spd = -400;
//      digitalWrite(dir_pin, spd < 0);
//      if (spd) motor_pulse_width = 5000 / abs(spd);
//      while (digitalRead(endstop_pin));
//      spd = 0;
//      digitalWrite(dir_pin, spd < 0);
//      if (spd) motor_pulse_width = 5000 / abs(spd);
//      else motor_pulse_width = -1;
//      homed = true;
//      position_counter = 0;
//      set_position = 0;
//    }

    void homing(){
      homed = true;
      position_counter = 0;
      set_position = 0;
      spd = 0;
      motor_pulse_width = -1;
      Serial.println("homed");
    }
    
    void setSpeed(int speed) {
      spd = speed;
      digitalWrite(dir_pin, spd < 0);
      if (spd) motor_pulse_width = 5000 / abs(spd);
      else motor_pulse_width = -1;
    }

    void movePosition(int32_t position) {
      set_position = position;
      spd = constrain(set_position - position_counter, -400, 400);
      setSpeed(spd);
    }

    void movePositionAccel(int32_t start_position, int32_t end_position, int acceleration_distance) {
      set_position = end_position;
      int target_speed = 500;
      int32_t distance_from_start = abs(position_counter - start_position); //position_counter - prev_position = distance_from_start
      int32_t distance_from_end = abs(end_position - position_counter); //set_position - position_counter = distance_from_end
      int32_t travel_distance = abs(end_position - start_position); //set_position - prev_position = travel_distance
      if (abs(end_position - start_position) < 2 * acceleration_distance) // if moving distance is too short (< 2 acc distance)
        spd = constrain(set_position - position_counter, -300, 300); //range of speed: {-300, 300}
      if (distance_from_end < 1000) { //when the motor almost reached the target position 
        spd = constrain(set_position - position_counter, -200, 200); //switch to P control
      }
      else if (distance_from_start < acceleration_distance) {//start acceleration
        spd = map(distance_from_start, 0, acceleration_distance, 200, target_speed); //speed of "start acc" = its lower bound(0 to acc), upper bound(200 to target spd)
      }
      else if (distance_from_start > acceleration_distance && distance_from_end > acceleration_distance) {//constant spd range
        spd = target_speed;
      }
      else {//start deceleration
        spd = map(distance_from_end, 0, acceleration_distance, 200, target_speed);//speed of "start dec" = its lower bound(0 to acc), upper bound(200 to target spd)
      }
      if (end_position < start_position && distance_from_end >= 1000) spd = -spd; //moving downwards
      setSpeed(spd);
    }
};

#endif
