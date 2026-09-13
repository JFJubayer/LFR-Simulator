void initialize(){
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  for(int i = 0; i < NUM_SENSORS; i++){
    pinMode(sensorPins[i], INPUT);
  }

  lastSensor = 0;
  prevError = 0;
  gapCounter = 0;
  stopBoxCounter = 0;
  invertFilter = 0;
  navState = STATE_NORMAL;
  turnTicks = 0;
  isInverted = false;
  isStopped = false;
}
