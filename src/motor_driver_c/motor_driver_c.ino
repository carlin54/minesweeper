// I298N - Right Motor
#define PIN_ENA   6
#define PIN_IN1   22
#define PIN_IN2   23

#define PIN_RRE_A 18
#define PIN_RRE_B 19

volatile byte rightAFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte rightBFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte rightEncoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte rightOldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte rightReading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent


// I298N - Left Motor
#define PIN_ENB   7
#define PIN_IN3   30
#define PIN_IN4   31

#define PIN_LRE_A 20
#define PIN_LRE_B 21

volatile byte leftAFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte leftBFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte leftEncoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte leftOldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte leftReading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent


//Rotart Encoders
#define WHEEL_DIAMETER 3
#define WHEEL_CIRCUMFERENCE (WHEEL_DIAMETER*2*3.14159)
#define RE_TICK_DISTANCE (3*WHEEL_CIRCUMFERENCE)/1000

void setup()
{
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  
  pinMode(PIN_RRE_A,INPUT_PULLUP);
  pinMode(PIN_RRE_B,INPUT_PULLUP);
  attachInterrupt(PIN_RRE_A, pinA(), RISING);
  attachInterrupt(PIN_RRE_B, pinb(), RISING);
  
  
  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  
  pinMode(PIN_RRE_A,INPUT_PULLUP);
  pinMode(PIN_RRE_A,INPUT_PULLUP);
  attachInterrupt(PIN_LRE_A, pinA(), RISING);
  attachInterrupt(PIN_LRE_B, pinb(), RISING);
  
}

void pinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void pinB(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}


float move_x = 0;
float move_y = 1;

void update(){

}

void loop()
{
  
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  
  
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  
  analogWrite(PIN_ENA, 255);
  analogWrite(PIN_ENB, 255); 
 
  delay(2000);
 
 
 
  exit(0);
}
