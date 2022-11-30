#include <Arduino.h>
#include <TMC5160.h>

#define LIMIT_SWITCH1 2
#define LIMIT_SWITCH2 3
#define LIMIT_SWITCH3 18
const uint8_t SPI_CS1 = 48; // CS pin in SPI mode Rod 1
const uint8_t SPI_CS2 = 46; // CS pin in SPI mode Rod 2
const uint8_t SPI_CS3 = 49; // CS pin in SPI mode Rod 3

//const uint8_t SPI_DRV_ENN = 8;  // DRV_ENN pin in SPI mode

volatile bool homed1 = false;
volatile bool homed2 = false;
volatile bool homed3 = false;

unsigned long interval = 300;
unsigned long prev, t_echo = 0;
unsigned long now;

float h; //stroke length
int a = 5000; //amplitude
int b = 150; //periodicity

TMC5160_SPI motor1 = TMC5160_SPI(SPI_CS1); //Use default SPI peripheral and SPI settings.
TMC5160_SPI motor2 = TMC5160_SPI(SPI_CS2); //Use default SPI peripheral and SPI settings.
TMC5160_SPI motor3 = TMC5160_SPI(SPI_CS3); //Use default SPI peripheral and SPI settings.


void reached_limit1() {
  homed1 = true;
  motor1.stop();
  motor1.setCurrentPosition(0);
  detachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH1));
}

void reached_limit2() {
  homed2 = true;
  motor2.stop();
  motor2.setCurrentPosition(0);
  detachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH2));
}

void reached_limit3() {
  homed3 = true;
  motor3.stop();
  motor3.setCurrentPosition(0);
  detachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH3));
}

void setup()
{
  pinMode(LIMIT_SWITCH1, INPUT);
  pinMode(LIMIT_SWITCH2, INPUT);
  pinMode(LIMIT_SWITCH3, INPUT);

  // USB/debug serial coms
  Serial.begin(115200);

  //pinMode(SPI_DRV_ENN, OUTPUT);
  //digitalWrite(SPI_DRV_ENN, LOW); // Active low

  // This sets the motor & driver parameters /!\ run the configWizard for your driver and motor for fine tuning !
  TMC5160::PowerStageParameters powerStageParams; // defaults.
  TMC5160::MotorParameters motorParams;
  motorParams.globalScaler = 98; // Adapt to your driver and motor (check TMC5160 datasheet - "Selecting sense resistors")
  motorParams.irun = 31;
  motorParams.ihold = 16;

  SPI.begin();
  motor1.begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION );
  motor2.begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION );
  motor3.begin(powerStageParams, motorParams, TMC5160::NORMAL_MOTOR_DIRECTION );
  
  // ramp definition
  motor1.setAcceleration(500);
  motor2.setAcceleration(500);
  motor3.setAcceleration(500);
  motor1.setMaxSpeed(400);
  motor2.setMaxSpeed(400);
  motor3.setMaxSpeed(400);

  HomingUp();
  
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH1), reached_limit1, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH2), reached_limit2, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH3), reached_limit3, FALLING);

  HomingDown();
}


void HomingUp() {
  
  // ramp definition
  motor1.setRampMode(TMC5160::VELOCITY_MODE);
  motor2.setRampMode(TMC5160::VELOCITY_MODE);
  motor3.setRampMode(TMC5160::VELOCITY_MODE);
  motor1.setAcceleration(500);
  motor2.setAcceleration(500);
  motor3.setAcceleration(500);
  //motor1.setMaxSpeed(400);
  //motor2.setMaxSpeed(400);
  motor3.setMaxSpeed(400);
  Serial.println("done 400");
  delay(2000);
}

void HomingDown(){
  motor1.setRampMode(TMC5160::VELOCITY_MODE);
  motor2.setRampMode(TMC5160::VELOCITY_MODE);
  motor3.setRampMode(TMC5160::VELOCITY_MODE);
  //motor1.setMaxSpeed(-200);
  //motor2.setMaxSpeed(-200);
  motor3.setMaxSpeed(-200);
  Serial.println("done -200");
}


void altsinmove() {
  motor1.setRampMode(TMC5160::POSITIONING_MODE);
  motor2.setRampMode(TMC5160::POSITIONING_MODE);
  motor3.setRampMode(TMC5160::POSITIONING_MODE);
  if (now - prev >= interval) {
    prev = now;
    h = a * sin(b * now) + a;
    motor1.setTargetPosition(h);
    motor2.setTargetPosition(h);
    motor3.setTargetPosition(h);
    Serial.println(h);

  }
}

void loop()
{

  now = millis();
  //altsinmove();

  if ( now - t_echo > 100 )
  {
    t_echo = now;

    // get the current target position
    float xactual_1 = motor1.getCurrentPosition();
    float vactual_1 = motor1.getCurrentSpeed();
    float xactual_2 = motor2.getCurrentPosition();
    float vactual_2 = motor2.getCurrentSpeed();
    float xactual_3 = motor3.getCurrentPosition();
    float vactual_3 = motor3.getCurrentSpeed();
    //Serial.print("current position 1 : ");
    //Serial.print(xactual_1);
    //Serial.print("\tcurrent speed 1 : ");
    //Serial.println(vactual_1);
    //Serial.print("current position 2 : ");
    //Serial.print(xactual_2);
    //Serial.print("\tcurrent speed 2 : ");
    //Serial.println(vactual_2);
    //Serial.print("current position 3 : ");
    //Serial.print(xactual_3);
    //Serial.print("\tcurrent speed 3 : ");
    //Serial.println(vactual_3);
  }
}
