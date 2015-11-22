/*
button_simple, Dr. X. Treme September 2015

Simplest possible coil drive program, very important for debugging!!

All this does is turn on the voltage at pin 5 when the button at pin 2 is connected 

Aleister Crowley license: do what thou wilt shall be the whole of the law

*/

  int buttonPin = 2; //define knob pin as analog input A2
  int motorPin = 5;  //define motor pin to be PWM output pin 5
  boolean buttonState = false;//buttonState is state of button 
  int motorSpeed = 0;//motorSpeed is the speed scaled to 255
  
 void setup() {
    pinMode(buttonPin, INPUT);  
    
 }

void loop() {
    buttonState = digitalRead(buttonPin); //read button state
    if(buttonState){
      motorSpeed = 255;
    }
    else{
      motorSpeed = 0;
    }
    analogWrite(motorPin,motorSpeed); //set motor speed based on knob position
}
