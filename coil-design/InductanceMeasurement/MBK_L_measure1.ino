

boolean buttonState = false;
int x = 0;
int index = 0;

void setup() {
   pinMode(2, INPUT);
   pinMode(9, OUTPUT);
   Serial.begin(115200);
}

void loop() {

  buttonState = digitalRead(2);
  if(buttonState){  
    analogWrite(5,255);
    digitalWrite(9,true);
    for(index = 0;index < 30;index++){
      x = analogRead(A4);
//      Serial.print(log(float(x) - 643.0));
      Serial.print(x);
      Serial.print(",");
    }
    analogWrite(5,0);
    Serial.println();
    digitalWrite(9,false);
    delay(300);  
  }
}
