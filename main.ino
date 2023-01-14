#include <wire.h>
#include <Adafruit_PWMServoDriver.h>


void updateServoPos(int target1, int target2, int target3, char leg){
  if (leg == 'l'){
    plHipL = map((hipLOffset - target1), 0, 180, SERVOMIN, SERVOMAX);
    plKneeL = map((kneeLOffset - target2), 0, 180, SERVOMIN, SERVOMAX);
    plAnkleL = map((2*ankleLOffset - target3), 0, 180, SERVOMIN, SERVOMAX);
    
    pwm.setPWM(hipL_Pin,0,plHipL);
    pwm.setPWM(KneeL_Pin,0,plKneeL);
    pwm.setPWM(AnkelL_Pin,0,plAnkelL);
    
    //hipL.write(hipLOffset - target1);
    //kneeL.write(kneeLOffset - target2);
    //ankleL.write(2*ankleLOffset - target3);
  }
  else if (leg == 'r'){
    plHipR = map((hipROffset + target1), 0, 180, SERVOMIN, SERVOMAX);
    plKneeR = map((kneeROffset + target2), 0, 180, SERVOMIN, SERVOMAX);
    plAnkleR = map((target3), 0, 180, SERVOMIN, SERVOMAX);
    //hipR.write(hipROffset + target1);
    //kneeR.write(kneeROffset + target2);
    //ankleR.write(target3);
  }

void pos(float x, float z, char leg){
  float hipRad2 = atan(x/z);
  float hipDeg2 = hipRad2 * (180/PI);

  float z2 = z/cos(hipRad2);

  float hipRad1 = acos((sq(l1) + sq(z2) - sq(l2))/(2*l1*z2));
  float hipDeg1 = hipRad1 * (180/PI);
  
  float kneeRad = PI - acos((sq(l1) + sq(l2) - sq(z2))/(2*l1*l2));

  float ankleRad = PI/2 + hipRad2 - acos((sq(l2) + sq(z2) - sq(l1))/(2*l2*z2));
  
  float hipDeg = hipDeg1 + hipDeg2;
  float kneeDeg = kneeRad * (180/PI);
  float ankleDeg = ankleRad * (180/PI);

  updateServoPos(hipDeg, kneeDeg, ankleDeg, leg);  
}

void takeStep(float stepLength, int stepVelocity){
  for (float i = stepLength; i >= -stepLength; i-=0.5){
    pos(i, stepHeight, 'r');
    pos(-i, stepHeight - stepClearance, 'l');
    delay(stepVelocity);
  }

  for (float i = stepLength; i >= -stepLength; i-=0.5){
    pos(-i, stepHeight - stepClearance, 'r');
    pos(i, stepHeight, 'l');
    delay(stepVelocity);
  }
}

void initialize(){
  for (float i = 10.7; i >= stepHeight; i-=0.1){
    pos(0, i, 'l');
    pos(0, i, 'r');
  }
}


void setup(){

Serial.begin(9600);

pwm.begin();
pwm.setPWMFreq(SERVO_FREQ);


pwm.setPWM(0, 0, 0);



delay(5000);
initialize();
}


void loop(){

takeStep(2, 0);

}
