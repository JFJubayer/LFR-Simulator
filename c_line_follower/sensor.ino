int readSensor(){
  int sumS = 0;
  int sumWS = 0;
  bool s[NUM_SENSORS];

  // Auto-inversion filter (Track 2 inverted section)
  int rawLowCount = 0;
  for(int i = 0; i < NUM_SENSORS; i++){
    if(digitalRead(sensorPins[i]) == LOW) rawLowCount++;
  }

  // If 6 or 7 sensors read LOW (meaning surface is mostly black) for consecutive cycles:
  if(rawLowCount >= 6 && rawLowCount < NUM_SENSORS){
    invertFilter++;
    if(invertFilter > 15){
      isInverted = true;
    }
  } else if(rawLowCount <= 2){
    invertFilter--;
    if(invertFilter < -15){
      isInverted = false;
    }
  } else {
    invertFilter = 0;
  }

  for(int i = 0; i < NUM_SENSORS; i++){
    // Normal track: Black tape absorbs IR -> reads LOW (active-low)
    // Inverted track: White line reflects IR -> reads HIGH
    if(!isInverted){
      s[i] = (digitalRead(sensorPins[i]) == LOW);
    } else {
      s[i] = (digitalRead(sensorPins[i]) == HIGH);
    }

    if(s[i]){
      sumS++;
      sumWS += (i + 1) * 10;
    }
  }

  // 1. Line Lost / Dashed Gap
  if(sumS == 0){
    return LINE_LOST;
  }

  // 2. End Stop Pad (all sensors black for extended period)
  if(sumS == NUM_SENSORS){
    stopBoxCounter++;
    if(stopBoxCounter > 25){
      return END_BOX;
    }
    return INTERSECTION_T_OR_CROSS;
  } else {
    stopBoxCounter = 0;
  }

  // 3. Full Cross, T-Junction, or Perpendicular Intersection
  if(sumS >= 6){
    return INTERSECTION_T_OR_CROSS;
  }

  // 4. 90-Degree Left Turn (Leftmost sensors tripped)
  if(s[0] && s[1] && !s[6] && !s[7]){
    return INTERSECTION_LEFT;
  }

  // 5. 90-Degree Right Turn (Rightmost sensors tripped)
  if(s[6] && s[7] && !s[0] && !s[1]){
    return INTERSECTION_RIGHT;
  }

  // 6. Standard Proportional Tracking
  int linePos = sumWS / sumS;
  int error = linePos - 45;

  // Track which side of center the line was last detected
  if(error < 0){
    lastSensor = 1; // Left side
  } else if(error > 0){
    lastSensor = 2; // Right side
  }

  return error;
}
