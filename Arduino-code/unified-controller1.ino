/*
Crowley license: do what thou wilt shall be the whole of the law
fuck patents, fuck copyright

November 2015

This program is for two mode motor driver: button pulse and smart feedback drive

*/


int mode = 0;
int x = 0;
int x0 = 0;
int threshold = 0;
int sensorPin = A4;    // select the input pin for the potentiometer
int motorPin = 10;
int xold = 0;
int index  = 0;
boolean button3state = false;
boolean button2state = false;
int dataPin = 11;


void setup() {
  Serial.begin(115200);
  x0 = analogRead(sensorPin);   
  pinMode(dataPin, OUTPUT);
}

void loop() {
  
  button3state = digitalRead(3);
  if(button3state){
    mode = mode + 1;
    if(mode > 1){
      mode = 0;
    }
    delay(200); 
  }
  
  switch (mode){
    case 0:
      //push button turns on motor take data
      button2state = digitalRead(2);
      if(button2state){
        analogWrite(motorPin,255);
        digitalWrite(dataPin,HIGH);

      }
      else{
        analogWrite(motorPin,0);
        digitalWrite(dataPin,LOW);
      }
      x = analogRead(sensorPin) - x0;
      Serial.println(x);
      delay(1);
      break;
    case 1:
      //smart pulse drive
      x = analogRead(A4) - x0;
      if(x >= threshold){
       analogWrite(10,255);
       digitalWrite(dataPin,LOW);
      }
      else{
        analogWrite(10,0);
        digitalWrite(dataPin,HIGH);
      }
      Serial.println(x);
      delay(1);    
      break;
    default:
      mode = 0;
  }    
  
  
}
