int led1 = 13;                // the led1 is at 13 pin
int led2 = 8;                 // the led2 is at 8 pin
int pir1 = 2;              // the two pir motion sensor are at 2 and 3 pin
int pir2 = 3;              

// intially the motion flag is low 
volatile int motion1 = LOW;    
volatile int motion2 = LOW;

void setup() {
  // initialized LED1 and LED2 as an output
  pinMode(led1, OUTPUT);      
  pinMode(led2, OUTPUT);
  
  // Also, initialized sensor1 and sensor2 as an input
  pinMode(pir1, INPUT);    
  pinMode(pir2, INPUT);

  // attach interrupt to sensor pin, 
  attachInterrupt(digitalPinToInterrupt(pir1), firstMotion, RISING); //two interrputs are attached for the 2 methods
  attachInterrupt(digitalPinToInterrupt(pir2), secondMotion, RISING);
 
  Serial.begin(9600);        // baud rate is 9600
}

void loop(){
  //interrupts are being used 
}

void firstMotion() {     //the 2 methiods are created for the 2 pir motion sensors that check the bool state of the motion
  digitalWrite(led1, !motion1);   
  motion1 = !motion1;              
  if (motion1 == HIGH) { //when motion detected then the message is printed on the serial monnitor
    Serial.println("first pir and led"); 
  } 
  else {
    Serial.println("first motion and led stopped");
  }
}
void secondMotion() {
  digitalWrite(led2, !motion2);   
  motion2 = !motion2;              
  if (motion2 == HIGH) {
    Serial.println("second pir and led");  
  } 
  else {
    Serial.println("second motion and led stopped");
  }
}
