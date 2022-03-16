void checkSerial(void) {

  static int val = 0;
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9') // is it a number?
    {
      val = val * 10 + ch - '0'; // yes, accumulate the value
    }
    else if (ch == 'v')
    {
      if ((val <= 20) & (val >= 0)) {
        val = val * multiplier;
        Serial.println(val);
        analogWrite(pwmPin, val);
        val = 0;
      }
    }
    else if (ch == 'm') // MANUAL
    {
      manual = true;
    }
    else if (ch == 'p') // PROGRAM
    {
      program = true;
      createFile();
      writeHeader();
     
    }
    else if (ch == 's') // STOP
    {
      manual = false;
      program = false;
      val = 0;
      analogWrite(pwmPin, val);
      Reset();
    }
    else if (ch == 'r') // RESET
    {
      val = 0;
      analogWrite(pwmPin, val);
      Reset();
    }
    else if (ch == 'd') {
    
  }
}
