/*
 * Measuring the LR time of an inductor in series 
 * with a bias resistor
 * 
 * burning turd bag license
 * 
 * version 2
 * 
 * December 2015
 */



boolean buttonState = false;
int x = 0;
int index = 0;
int numPoints = 30;
int startTime = 0;
int stopTime = 0;
int deltaT = 0;

void setup() {
   pinMode(2, INPUT);
   pinMode(9, OUTPUT);
   Serial.begin(115200);
}

void loop() {
  startTime = micros();  
  analogWrite(5,255);
  digitalWrite(9,true);
  for(index = 0;index < numPoints - 1;index++){
    x = analogRead(A4);
    Serial.print(x);
    Serial.print(",");
  }
  x = analogRead(A4);
  Serial.print(x);
  analogWrite(5,0);
  Serial.println();
  stopTime = micros();
  deltaT = stopTime - startTime;
  //Serial.print(deltaT);
 // Serial.println();
  digitalWrite(9,false);
  delay(100);  
}

