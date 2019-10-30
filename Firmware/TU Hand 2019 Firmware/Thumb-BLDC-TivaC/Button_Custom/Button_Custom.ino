/*
  Button
 
 Trying to turn my Brushless motor - 9/16
 
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = PUSH2;     // the number of the pushbutton pin
const int buttonPin1 = PUSH1;     // the number of the pushbutton pin

const int ledPin =  GREEN_LED;      // the number of the LED pin
const int ledPin1 =  BLUE_LED;      // the number of the LED pin
const int ledPin2 =  RED_LED;      // the number of the LED pin


int oscPin = PB_5;    // oscilloscope connection


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton2 status
int buttonState1 = 0;         // variable for reading the pushbutton1 status


void setup() {
  // initialize the LED pins as an output:
  pinMode(ledPin, OUTPUT);      
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);        

  // initialize the pushbutton2 pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);     
    // initialize the pushbutton1 pin as an input:
  pinMode(buttonPin1, INPUT_PULLUP);     
}

void loop(){
  // read the state of the pushbutton2 value:
  buttonState = digitalRead(buttonPin);
  // read the state of the pushbutton1 value:
  buttonState1 = digitalRead(buttonPin1);

  // check if the pushbutton1 is pressed.
  // if it is, the inner loop activates.
  // if it is not, the inner loop deactivates and waits.
 if (buttonState1 == LOW) {     
    //run inner loop:    
      // check if the pushbutton2 is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin, LOW); 
  
         analogWrite(oscPin, 100);  //PWM DUTY CYCLE: ~30% of 255 
         delay(2); 

  } 
  else {
    // turn LED ON:
    digitalWrite(ledPin1, LOW); 
    digitalWrite(ledPin, HIGH); 
    
     analogWrite(oscPin, 50);   //PWM DUTY CYCLE LOW (STARTUP) ~20% of 255 --- CURRENTLY WORKS W 12 V Source only!!!
    delay(2); 
  }
  } 
  else {
    // wait:
          analogWrite(oscPin, 0); //PWM DUTY CYCLE OFF: 0% of 255
digitalWrite(ledPin, LOW); 
digitalWrite(ledPin1, LOW); 
digitalWrite(ledPin2, LOW); 


     if (buttonState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin2, HIGH);  
         analogWrite(oscPin, 250);   //PWM DUTY CYCLE HIGH ~97% of 255

  } 
    delay(2); 
  }
}
