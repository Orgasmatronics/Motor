float flow = 10.0; //Minimum frequency [Hz]
float fhigh = 50.0; //Maximum frequency [Hz]
float f = flow;  //current frequency [Hz]
int T = int(1000.0/f);  //period in ms
int pulseTime = 10; //duration of pulse in ms
float knob = 0;

boolean buttonState = false;



void setup() {
  knob = float(analogRead(A2))/1023.0;
  f = flow + knob*(fhigh - flow);
  T = int(1000.0/f);
  Serial.begin(115200);
}

void loop() {  
  int index = 0;
  buttonState = digitalRead(2); //button "off" state control subroutine
  if(buttonState){
    delay(250);
    buttonState = false;
    while(!buttonState){
      delay(1);
      buttonState = digitalRead(2);
    }
    delay(250);
  }    
  
  knob = float(analogRead(A2))/1023.0;
  f = flow + knob*(fhigh - flow);
  T = int(1000.0/f);
  analogWrite(5,255);
  delay(pulseTime);
  analogWrite(5,0);
  T = abs(T - pulseTime);
  delay(T);
  Serial.print(f);
  Serial.print(" Hz");
  Serial.println();
  
}
