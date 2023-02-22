int led = 13;                // the pin that the LED is attached to
int sensor = 2;              // the pin that the sensor is attached to
volatile int motion = LOW;    // by default, no motion detected

void setup() {
  pinMode(led, OUTPUT);      // initializing LED as output
  pinMode(sensor, INPUT);    // initializing sensor for input
  attachInterrupt(digitalPinToInterrupt(sensor), motionDetected, RISING);
  // attach interrupt to sensor pin with the motion detector method and rising
  Serial.begin(9600);       
}

void loop(){
  // interrupt is being used loop not needed
}

void motionDetected() {
  digitalWrite(led, !motion);   // toggle LED
  motion = !motion;              // update variable state
  if (motion == HIGH) {
    Serial.println("Motion detected!"); 
  } 
  else {
    Serial.println("no motion");
  }
}
