const int LED_OUT_PIN = 13;
const int CAP_OUT_PIN = 4;
const int CAP_IN_PIN = 9;
long capState = LOW;
const unsigned long MEASURE_ERROR = 0xffffffff;

void setup() {
  pinMode(LED_OUT_PIN, OUTPUT);
  pinMode(CAP_OUT_PIN, OUTPUT);
  pinMode(CAP_IN_PIN, INPUT);
  digitalWrite(CAP_OUT_PIN, capState);
  Serial.begin(115200);
  measureCapMicros(); // do this once so things are settled
}

void loop() {
  unsigned long capTime = measureCapMicros();
  Serial.println(capTime);
}

void toggleState() {
  capState = capState == LOW ? HIGH : LOW;
}


// NB: this isn't the best way to do this if you have other stuff going on - 
// setting up a timer and interrupt will be much more robust
unsigned long measureCapMicros() {
  unsigned long started, stopped;
  toggleState();
  started = micros();
  digitalWrite(CAP_OUT_PIN, capState);
  while(digitalRead(CAP_IN_PIN) != capState) {
    // wait for input to settle
  }
  stopped = micros();
  if(stopped - started < MEASURE_ERROR) {
    return (unsigned int)(stopped - started);
  }
  else {
    // we wrapped around, too lazy to do the right math
    return MEASURE_ERROR;
  }
}
   
