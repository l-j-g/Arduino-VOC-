void printBuffer(void) {

  waitor.end();
  acdc.end();
  seconds = 0;
  n = 0;
  file.println(S1);
  file.println(S2);
  file.println(S3);
  file.println(S4);

  //  while (n < sampleLengthSamples) {
  //    Serial.print(S1[n]);
  //    Serial.print(","); //print the delimiter
  //    Serial.print(S2[n]);
  //    Serial.print(","); //print the delimiter
  //    Serial.print(S3[n]);
  //    Serial.print(","); //print the delimiter
  //    Serial.print(S4[n]);
  //    Serial.print(",");
  //    Serial.print(n);
  //    Serial.println(",");
  //    n++;
  //    delayMicroseconds(100);
  //  }
// Serial.print(",");
bufferPrinted = true;
sampleN = 0;
time2wait = waitR;
// Serial.println("wait R");
waitor.begin(counter, 1000000);
}


void writeOut(void) { //Displays sensor readings straight to serial
  Serial.print(analogRead(21));
  Serial.print(",");
  Serial.print(analogRead(20));
  Serial.print(",");
  Serial.print(analogRead(19));
  Serial.print(",");
  Serial.print(analogRead(18));
  Serial.println(",");
}

void createFile(void){

    if (BASE_NAME_SIZE > 6) {
    error("FILE_BASE_NAME too long");
  }
    while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      error("Can't create file name");
    }
  }

    if (!file.open(fileName, O_CREAT | O_WRITE | O_EXCL)) {
    error("file.open");
  }
}
