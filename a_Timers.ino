void record() {

  if (sampleN < sampleLengthSamples + 1) {
    S1 += analogRead(21) + ",";
    S2 += analogRead(20) + "'";
    S3 += analogRead(19) + ",";
    S4 += analogRead(18) + ",";
    sampleN++;
  }
}

void counter() {

  seconds++;
}

void checkWait(int time2wait) {

  if (seconds > time2wait - 1) {
    waitor.end();
    waitComplete = true;
    seconds = 0;
  }
}
