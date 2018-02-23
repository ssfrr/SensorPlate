const int LED_OUT_PIN = 13;
const int OSC_IN_PIN = 2;

volatile unsigned long periodMicros;
volatile unsigned long lastMicros;
volatile unsigned int periodCount = 0;

void setup() {
  pinMode(LED_OUT_PIN, OUTPUT);
  pinMode(OSC_IN_PIN, INPUT);
  Serial.begin(115200);
  lastMicros = micros();
  
  //attachInterrupt(INT0, oscISR, RISING);
  
  // enable INT0 interrupt on change - less overhead than using attachInterrupt()
  EICRA = 0x03;  // enable INT0 for rising edge
  EIMSK = 0x01;  // enable INT0
}

void loop() {
  Serial.print("{periodMicros: ");
  Serial.print(periodMicros);
  Serial.println("}");
  digitalWrite(LED_OUT_PIN, periodMicros > 200 ? HIGH : LOW);
  delay(10);
}


ISR(INT0_vect) {
  unsigned long now = micros();
  ++periodCount;
  if(periodCount == 1) {
    if(now - lastMicros < 10000) {
      // otherwise we probably rolled over, so don't update the period
      periodMicros = now - lastMicros;
    }
    lastMicros = now;
    periodCount = 0;
  }
}
   
