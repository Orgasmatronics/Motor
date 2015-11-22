/*
Crowley license: do what thou wilt shall be the whole of the law
fuck patents, fuck copyright

November 2015

read from D11, turn on transistor if it's high, off if low

*/


int dataPin = 11;


void setup() {
  pinMode(dataPin, INPUT);
}

void loop() {

  int dataState = digitalRead(dataPin);
  if(dataState != 0){
    analogWrite(10,255);
  }
  else{
    analogWrite(10,0);
  }
  
}
