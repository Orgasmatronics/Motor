/*
simple program to get time domain response to a pulse


Aleister Crowley liscense: do what thou wilt shall be the whole of the law
*/

int pulseLength = 25;//ms
boolean buttonState = false;
int numPoints = 500; //number of points
int deltaT = 1;
int x0 = 0;

void setup(){
    Serial.begin(115200);
    x0 = analogRead(A5);
}

void loop(){
  
  buttonState = digitalRead(2);
  if(buttonState){
    analogWrite(5,255);
    delay(pulseLength);
    analogWrite(5,0);
    delay(1);
    int index = 0;
    int x[numPoints];
    for(index = 0;index < numPoints;index++){
      x[index] = analogRead(A5)  - x0;
      delay(deltaT);
    }
    for(index = 0;index < numPoints;index++){
      Serial.print(x[index]);
      Serial.print("  ");
    }
    Serial.println();
    delay(500);
    }
    
  }
    
    
    
    
