
// Lachlan Greve //

// Libraries //

#include "ADC_Module.h"
#include "ADC.h"
#include "RingBuffer.h"
#include "IntervalTimer.h"
#include <math.h>
#include "SdFat.h"
#include <SPI.h>
#include <vector>
#include <TimeLib.h>


// Constants //

#define pwmPin A21 //dac_0
#define ledPin 13
#define tempPin 5
#define EOT 4

#define USE_SDIO 1
#define SPI_SPEED SD_SCK_MHZ(50)

const uint8_t chipSelect = SS;

// Test Parameters //
const String Title = "A/P/B (150SCCM) - N (150SCCM) Alternating. Variable Purge Wait 15min - 45min";
const String description = "";


const String heatMode = "pulse"; // pulse, sawt or sine
const int sensors = 4; // the number of sensors on the board
const int sampleTime = 500; // in MS
const int repeats = 5;
const int Vmin = 10; //minimum range of voltage
const int Vmax = 20; //maxmium value of voltage
const int Vinc = 2;
const int waitR = 120;//120; //seconds to wait between repeat tests
const int waitV = 300;//300; //seconds to wait between voltage changes
const int waitP = 900;//900; //seconds to wait for purge
const int bitrateOut = 12;
const int purges = 28;
const int samplingRate = 4000; // (Hz) samples per second
const int heatTime = 75;//75; // 15 ms heat time



const int Teeth = 1;

// For Calculation Dont Change //
const int multiplier = (pow(2, bitrateOut)) / 33; //to convert ADC units to voltage
const int UsamplingRate = 1000000 / samplingRate;
const int sampleLengthSamples = sampleTime * samplingRate / 1000; // convert to miliseconds
const int heatLengthSamples = heatTime * samplingRate / 1000;


// Variables //

volatile uint16_t sampleCounter = 0; //Counts the current sample
volatile uint16_t Voltage = 0;
volatile bool program = false;
volatile bool sampling = false;
volatile bool waitComplete = true;
volatile bool heatOn = false;
volatile bool manual = false;
volatile uint16_t seconds = 0;
volatile uint16_t sampleN = 0;
volatile uint16_t r = 0;
volatile uint16_t time2wait = waitR;
volatile uint16_t p = 1;
volatile bool counterIncreased = false;
volatile bool voltageIncreased = false;
volatile bool purgeIncreased = true;
volatile bool bufferPrinted = true;
volatile uint16_t n = 0;
volatile String  Date = (String(year()) + "" + String(month()) + "" + String(day()) + "" + String(hour()) + "" + String(minute()) + "" + String(second()));

String S1 = "";
String S2 = "";
String S3 = "";
String S4 = "";

SdFatSdioEX sd;

SdFile file;

#define error(msg) sd.errorHalt(F(msg))
#define FILE_BASE_NAME "Data"

  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  char fileName[13] = FILE_BASE_NAME "00.csv";



IntervalTimer waitor, acdc;
// Initialise //

ADC * adc = new ADC();

void setup() {

  setSyncProvider(getTeensy3Time);
  
  Serial.begin(2000000);
  delay(100);

  pinMode(pwmPin, OUTPUT);

  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);

  analogWriteResolution(bitrateOut); //12-bit output level (4096 levels)
  analogWrite(pwmPin, 0);

  while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(100);
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }

  adc->setAveraging(0, ADC_0); // set number of averages
  adc->setResolution(12, ADC_0); // set bits of resolution
  adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED, ADC_0); // change the conversion speed
  adc->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED, ADC_0); // change the sampling speed
  adc->setReference(ADC_REFERENCE::REF_EXT, ADC_0);
  Voltage = Vmin;

  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin()) {
    sd.initErrorHalt();
  }


  Welcome();
}



void loop() {

  checkSerial();
  if (program == true) {
    if (sampling == true) {
      testRunning();
    } else {
      testNrunning();
    }
  }
  if (manual == true)
  {
    writeOut();
  }
    if (!file.sync() || file.getWriteError()) {
    error("write error");
  }
}

  void space();



    
