void wheel(int leftSpeed, int rightSpeed){
  // Clamp speed while properly preserving the sign (+ for forward, - for reverse)
  leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
  rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

  // Left Motor (inC, inD, enB)
  if(leftSpeed > 0){
    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);
  }
  else if(leftSpeed < 0){
    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);
  }
  else{
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);
  }

  // Right Motor (inA, inB, enA)
  if(rightSpeed > 0){
    digitalWrite(inB, HIGH);
    digitalWrite(inA, LOW);
  }
  else if(rightSpeed < 0){
    digitalWrite(inB, LOW);
    digitalWrite(inA, HIGH);
  }
  else{
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
  }

  analogWrite(enB, abs(leftSpeed));
  analogWrite(enA, abs(rightSpeed));
}

void brake(){
  // Active dynamic brake (shorts motor terminals to clamp back-EMF)
  digitalWrite(inA, HIGH);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, HIGH);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}





