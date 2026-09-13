void lineFollow(){
  static bool wasLost = false;
  int error = readSensor();

  if(error == LINE_LOST){
    wasLost = true;
    if(lastSensor == 1){
      wheel(-spinSpeed, spinSpeed);
    }
    else if(lastSensor == 2){
      wheel(spinSpeed, -spinSpeed);
    }
    else{
      wheel(0, 0); // Stop safely if line was never detected
    }
  }
  else{
    if(wasLost){
      prevError = error; // Prevent derivative spike upon line reacquisition
      wasLost = false;
    }

    float P = kp * error;
    float D = kd * (error - prevError);
    int delSpeed = (int)(P + D);

    wheel(leftBaseSpeed + delSpeed, rightBaseSpeed - delSpeed);
    prevError = error;
  }
}



