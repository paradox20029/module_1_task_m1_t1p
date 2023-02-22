const int motionPin = 2; // Motion sensor output pin
const int ledPin = 13; // LED pin

volatile bool motionDetected = false; // Flag to indicate if motion is detected
volatile bool ledState = LOW; // Current state of the LED
// the volatile key word suggets that the varibales can change at any time and are modified by the ISR
void setup() {
  pinMode(motionPin, INPUT); //setting up the motion pin and led pin which have been defined above
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motionPin), motionDetectedISR, RISING); //attach interrupt method is used for the interrupt and rising suggests that it is being used for 
  interruptMethod();//interrupt method is called to intialte the interrupt

  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Do nothing in the loop, as we are using interrupts instead
}

void motionDetectedISR() { //this method is the interrupt service routine which is called when the motion is detected 
  motionDetected = true;
  Serial.println("Motion detected!"); // print to serial monitor that the motion is detected
}

void blinkLED() { //this method turns the led on and off depending upon the motion detection
  ledState = !ledState; // Invert the LED state
  digitalWrite(ledPin, ledState);
}

void handleMotionDetection() { //this method blinks led when the motion is detected checked by the timer interrupt
  if (motionDetected) {
    blinkLED(); //calling the method to blink the led
    motionDetected = false; //setting the flag back to false
  }
}

void interruptMethod() { //
  noInterrupts(); // Disable interrupts

  // Set timer1 to run at 2Hz (every 500ms)
  TCCR1A = 0; //these two timer counters have reset
  TCCR1B = 0;
  OCR1A = 15624; // the value comes after calculaing from the formula which suggests that the timer has 2hz of frequency
  TCCR1B |= (1 << WGM12);//wave form genration determines how timer/counter will operate, the timer will count upto value specified in OCR1A
  TCCR1B |= (1 << CS12);//prescaler set to 256 dividing the clock frequency by 256, slows the counter and helpn in counting upto the OCR1A before triggering the interrupt
  TIMSK1 |= (1 << OCIE1A);//this enables the interrupt when the vlaue is reached

  interrupts(); // Enable interrupts
}

ISR(TIMER1_COMPA_vect) { //TIMER1_COMPA_VECT is a predefined macro that specifies the interrupt vector with output compare A of timer1
  handleMotionDetection();//after timer is triggered then ISR calls the handle motion method
  //this ISR method is executed when the interrupt is triggered and microcontroller pauses and jumps to ISR to execute the code inside
}
