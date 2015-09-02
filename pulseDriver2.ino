/*
Most basic resonant drive.  Pulses of duration pulseTime in miliseconds are put out on pin 5, with frequency f in Hertz and period T = 1000.0/f.  Frequency is set by turning a knob that controls the analog input A2.  Many forks will be needed to make the variations of this, but this base program is important as a starting point for a resonant drive motor.  It is also assumed that a button that connects the digital pin "2" to Vcc is connected, with a pull down resistor(see documentation for master beta kit). 

Aleister Crowley license: do what thou wilt shall be the whole of the law
*/

float flow = 10.0; //Minimum frequency [Hz]
float fhigh = 50.0; //Maximum frequency [Hz]
float f = flow;  //current frequency [Hz]
int T = int(1000.0/f);  //period in ms
int pulseTime = 10; //duration of pulse in ms
float knob = 0;//a floating point number from 0 to 1 based on analog input A2

boolean buttonState = false;

void setup() {
  knob = float(analogRead(A2))/1023.0;//analog input is scaled to 1023 maximum, "knob" is scaled to 1.0
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
    while(!buttonState){  //until the user hits the button again, just chill out and do nothing
      delay(1);
      buttonState = digitalRead(2);
    }
    delay(250);
  }    
  
  knob = float(analogRead(A2))/1023.0;  //read the knob again
  f = flow + knob*(fhigh - flow);  //set frequency based on knob (in Hz)
  T = int(1000.0/f); //period in ms
  analogWrite(5,255); //turn on current through coil(assmining drive transistor like master beta kit)
  delay(pulseTime);  //note this global variable declared before setup(), which user might want to change manually
  analogWrite(5,0);  //turn current back off
  T = abs(T - pulseTime);  //time to have current off is total cycle time T minus "on" time pulseTime
  delay(T);  //wait in "off" state (note that this is a different T!)
  Serial.print(f); //send the frequency down the serial line so the user can read it in real time from teh Arduino IDE
  Serial.print(" Hz");
  Serial.println();
  
}
