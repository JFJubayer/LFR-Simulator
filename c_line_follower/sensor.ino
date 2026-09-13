int readSensor(){
  int sumS = 0;
  int sumWS = 0;
  bool sensorReading[NUM_SENSORS];

  for(int i = 0; i < NUM_SENSORS; i++){
    // Active LOW: LOW (0) means line detected
    sensorReading[i] = (digitalRead(sensorPins[i]) == LOW);
    if(sensorReading[i]){
      sumS++;
      sumWS += (i + 1) * 10;
    }
  }

  if(sumS == 0){
    return LINE_LOST;
  }

  int linePos = sumWS / sumS;
  int error = linePos - 45;

  // Track which side of the center the line was last seen on
  if(error < 0){
    lastSensor = 1; // Left side
  } else if(error > 0){
    lastSensor = 2; // Right side
  }

  return error;
}



