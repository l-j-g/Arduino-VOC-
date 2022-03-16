
void printStatus(void) {
  file.print("Repeat Number:");
  file.print(",");
  file.print(r);
  file.print(",");
  file.print("Voltage:");
  file.print(",");
  file.print(Voltage);
  file.print(",");
  file.print("Purge Number:");
  file.print(",");
  file.print(p);
  file.print(",");
}

void Reset(void) {

  sampleCounter = 0; //Counts the current sample
  Voltage = Vmin;
  program = false;
  manual = false;
  sampling = false;
  waitComplete = false;
  heatOn = false;
  seconds = 0;
  sampleN = 0;
  r = 0;
  time2wait = waitR;
  p = 0;
  counterIncreased = false;
  voltageIncreased = false;
  purgeIncreased = true;
  seconds = 0;
  acdc.end();
  waitor.end();
  bufferPrinted = true;
  printStatus();
  Welcome();
}

void writeHeader(void){
  
//  file.println("###");
//  file.println("Experiment Title:," + String(Title));
//  file.println("Date:," + Date);
//  file.println("Experiment Description:," + String(description));
//  file.println("Sensors:," + sensors);
//  file.println("Heating Mode:," + heatMode);
//  file.println("Heating Time:," + heatTime);
//  file.println("Sampling Time:," + sampleTime);
//  file.println("Sampling Rate:," + samplingRate);
//  file.println("Repeats:," + repeats);
//  file.println("Repeat Delay (sec):," + waitR);
//  file.println("Heating Mode:," + heatMode);
//  file.println("Voltage Range:," + String(Vmin) + "," + String(Vmax) + ",Increment:," + String(Vinc));
//  file.println("Voltage Increase Delay (sec):" + waitV);
//  file.println("Calibration Points / # of Purges:" + purges);
//  file.println("Purge Delay (sec)" + waitP);
//  file.println("###");
}

void Welcome(void){
  Serial.println("Welcome.");
  Serial.println("'m' = direct sensor output");
  Serial.println("'p' = start programed routine");
  Serial.println("'s' = stop");
  Serial.println("'r' = reset");
  Serial.println("'##v' = set heater voltage (10-20)"); 
  Serial.println(("Current Heater Value:") + Voltage);
}
