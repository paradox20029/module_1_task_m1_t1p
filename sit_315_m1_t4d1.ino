const uint16_t t1_load = 0;//these are the counter and comare values
const uint16_t t1_comp = 31250; //the timer has prescaler of 256 and value of 500ms 

int red = 10;  // the pins are defined for the three led
int green = 11; 
int blue = 12;

int PIR1 = 5;  //the pins are defined for the three sensors
int PIR2 = 6; 
int PIR3 = 7; 

int motion1 = LOW; //the intial state of the motion is low
int motion2 = LOW;
int motion3 = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
  
  PCICR |= B00000100;//this activates the port b in the arduino with 1 in the bit zero position
  PCMSK2 |= B11100000; //pin change mask 2 B11100000 is a binary number represented in base 2. 
  //It has a value of 224 in base 10. This binary number has three consecutive 1s starting from the leftmost bit (MSB), 
  //which corresponds to pins PCINT23, PCINT22, and PCINT21 on the microcontroller. 
  //By setting these bits to 1, pin change interrupts will be enabled for these three pins.
  //this sets the CTC mode which means that the counter will count the value upto the top value of the OCCR1A register
  TCCR1B &= ~(1 << WGM13);//this is done to clear the counter
  TCCR1B |= (1 << WGM12); //it sets the WGM12 bit
  
  TCCR1B |= (1 << CS12); //the prescaler is 256 so these are set according to the value
  TCCR1B &= ~(1 << CS11); //they are set to binary  1  0 0 to set the prescaler value to 256
  TCCR1B &= ~(1 << CS10);
  
  TCNT1= t1_load; //the timer counter is set to zero for loading
  OCR1A= t1_comp; //the output comare register has this value as the prescaler is set to 256, store the outcome value  
  TIMSK1 = (1 << OCIE1A); //sets the outcome compare enable interrupt for timer1 to compare match A
  
  sei(); //enables the global interrupts
}

void loop()
{
  delay(1000);
}

ISR(PCINT2_vect) //this method is used for pin change interrupt, the PCINT2_vect is used for port d in arduino which is from D0 to D7
{
  motion1 = digitalRead(PIR1); //When a pin change interrupt occurs on any of the pins in the corresponding Pin Change Mask Register (PCMSK2),
  //the microcontroller jumps to this ISR to execute the code inside.
  motion2 = digitalRead(PIR2);
  motion3 = digitalRead(PIR3);
  
} 

ISR(TIMER1_COMPA_vect)//this is the interrupt service routine
{
  if(motion1 == HIGH) //This is an Interrupt Service Routine (ISR) for the Timer/Counter1 Compare Match A vector (TIMER1_COMPA_vect). 
  //This ISR will be executed when the Timer/Counter1 value matches the value in OCR1A, which is set to a specific value to generate a periodic interrupt.
  {
    Serial.println("first sensor:red");
    digitalWrite(red,HIGH);
  }
  digitalWrite(red,LOW);
  
  if(motion2 == HIGH)
  {
    Serial.println("second sensor:green");
    digitalWrite(green,HIGH); 
  }
  digitalWrite(green,LOW);
  
  if(motion3 == HIGH)
  {
    Serial.println("third sensor:blue");
    digitalWrite(blue,HIGH);
  }
  digitalWrite(blue,LOW);
}
