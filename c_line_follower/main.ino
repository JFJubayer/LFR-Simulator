void lineFollow(){
  if(isStopped){
    brake();
    return;
  }

  // Active Non-Blocking 90-Degree Left Turn
  if(navState == STATE_TURN_LEFT){
    wheel(-spinSpeed, spinSpeed);
    turnTicks++;
    bool centerFound = !isInverted ? 
      (digitalRead(sensorPins[3]) == LOW || digitalRead(sensorPins[4]) == LOW) :
      (digitalRead(sensorPins[3]) == HIGH || digitalRead(sensorPins[4]) == HIGH);

    if(turnTicks > 10 && centerFound){
      brake();
      navState = STATE_NORMAL;
      turnTicks = 0;
      prevError = 0;
    }
    return;
  }

  // Active Non-Blocking 90-Degree Right Turn
  if(navState == STATE_TURN_RIGHT){
    wheel(spinSpeed, -spinSpeed);
    turnTicks++;
    bool centerFound = !isInverted ? 
      (digitalRead(sensorPins[3]) == LOW || digitalRead(sensorPins[4]) == LOW) :
      (digitalRead(sensorPins[3]) == HIGH || digitalRead(sensorPins[4]) == HIGH);

    if(turnTicks > 10 && centerFound){
      brake();
      navState = STATE_NORMAL;
      turnTicks = 0;
      prevError = 0;
    }
    return;
  }

  int error = readSensor();

  // CASE 0: End Box Termination Pad
  if(error == END_BOX){
    isStopped = true;
    brake();
    return;
  }

  // CASE 1: Dashed Line Gap (Track 3) or Broken Line Gap (Track 2) or Acute Apex
  if(error == LINE_LOST){
    // If line lost while turning sharply (|prevError| > 15), this is an acute apex!
    if(abs(prevError) > 15){
      if(lastSensor == 1){
        wheel(-spinSpeed, spinSpeed);
      } else {
        wheel(spinSpeed, -spinSpeed);
      }
      return;
    }

    // Otherwise, it's a dashed line gap or straight broken line!
    gapCounter++;
    if(gapCounter <= GAP_LIMIT){
      // Gap-Ride: Dead-reckon along current trajectory (maintains arc for curved dashed line)
      int arcTrim = prevError * 2;
      wheel(leftBaseSpeed + arcTrim, rightBaseSpeed - arcTrim);
      return;
    }

    // Gap limit exceeded -> Active in-place search spin
    if(lastSensor == 1){
      wheel(-spinSpeed, spinSpeed);
    }
    else if(lastSensor == 2){
      wheel(spinSpeed, -spinSpeed);
    }
    else{
      wheel(0, 0);
    }
    return;
  }

  // Reset gap counter when line is detected
  gapCounter = 0;

  // CASE 2: Full Cross, T-Junction, or Perpendicular Branch
  if(error == INTERSECTION_T_OR_CROSS){
    // Left-Hand Priority Rule: Pivot Left at Cross / T-junction
    navState = STATE_TURN_LEFT;
    turnTicks = 0;
    wheel(-spinSpeed, spinSpeed);
    return;
  }

  // CASE 3: 90-Degree Left Corner
  if(error == INTERSECTION_LEFT){
    navState = STATE_TURN_LEFT;
    turnTicks = 0;
    wheel(-spinSpeed, spinSpeed);
    return;
  }

  // CASE 4: 90-Degree Right Corner
  if(error == INTERSECTION_RIGHT){
    navState = STATE_TURN_RIGHT;
    turnTicks = 0;
    wheel(spinSpeed, -spinSpeed);
    return;
  }

  // CASE 5: Normal Tracking with Dynamic Deceleration (Acute Angles & Zig-Zags)
  int absErr = abs(error);
  int curLBase = leftBaseSpeed - (absErr * 2);
  int curRBase = rightBaseSpeed - (absErr * 2);
  if(curLBase < minBaseSpeed) curLBase = minBaseSpeed;
  if(curRBase < minBaseSpeed) curRBase = minBaseSpeed;

  float P = kp * error;
  float D = kd * (error - prevError);
  int delSpeed = (int)(P + D);

  wheel(curLBase + delSpeed, curRBase - delSpeed);
  prevError = error;
}
