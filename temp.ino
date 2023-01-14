//pulselength = map(degrees, 0, 180, SERVOMIN, SERVOMAX);

 //pwm.setPWM(servonum, 0, pulselen);



 void updateServoPos(int target1, int target2, int target3, char leg){
  if (leg == 'l'){
    plHipL = map((hipLOffset - target1), 0, 180, SERVOMIN, SERVOMAX);
    plKneeL = map((kneeLOffset - target2), 0, 180, SERVOMIN, SERVOMAX);
    plAnkleL = map((2*ankleLOffset - target3), 0, 180, SERVOMIN, SERVOMAX);
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
}