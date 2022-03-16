
void testRunning(void) {

  if (heatMode == "pulse" && (sampleN < heatLengthSamples - 1)){
        analogWrite(pwmPin, Voltage*multiplier);
    
  } else if (heatMode == "saw" && (sampleN < heatLengthSamples - 1)){
    
  } else if (heatMode == "saw" && (sampleN < heatLengthSamples - 1)){
    float phase = 0.0;
    float twopi = M_PI * 2;
    
  }

  if ((sampleN > heatLengthSamples - 1) && (heatOn == true)) { // turns the heater off after heatLength samples
    analogWrite(pwmPin, 0);
    // Serial.println("heateroff");
    heatOn = false;
  }
  if (sampleN > sampleLengthSamples - 1) { // stops the timer and reset the samples
    acdc.end();
    sampling = false;
    waitComplete = false;
    bufferPrinted = false;
    counterIncreased = false;
  }
}

void testNrunning(void) {
  if (bufferPrinted == false) {
    printBuffer();
  }
  if (counterIncreased == false) {
    increaseCounter();
  }
  if (waitComplete == false) {
    checkWait(time2wait);
  }
  if (waitComplete == true) {
    if ((purgeIncreased == false) && (voltageIncreased == false) && (r < repeats + 1)) { // starts and repeats the same test
      sampling = true;
      acdc.begin(record, UsamplingRate);
      heatOn = true;
    } else if (voltageIncreased == true) { //increases the voltage and repeats the loop
      voltageIncreased = false;
      waitComplete = false;
      time2wait = waitV;
      //   Serial.println("waitv");
      waitor.begin(counter, 1000000);
    }
    else if (purgeIncreased == true) {
      purgeIncreased = false;
      waitComplete = false;
      time2wait = waitP;
      //   Serial.println("waitP");
      waitor.begin(counter, 1000000);
    }
  }
}
void increaseCounter(void) {

  if (r < repeats) {
    r++;
    printStatus();
    counterIncreased = true;
  } else if ((Voltage * multiplier < Vmax * multiplier)) {
    Voltage++;
    r = 1;
    printStatus();
    voltageIncreased = true;
    counterIncreased = true;

  } else if (p < purges) {
    p++;
    r = 1;
    Voltage = Vmin;
    printStatus();
    counterIncreased = true;
    purgeIncreased = true;
  } else {
    program = false;
  }
}
