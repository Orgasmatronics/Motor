# -*- coding: utf-8 -*-
"""
Created on Wed Sep 02 15:37:01 2015

@author: Dr. Xtreme


plot and fit data from pulse drive of a motor

load PulseDataButton onto arduino, code follows:

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
    delay(35);
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


"""

import serial
from pylab import *
import numpy as np
from scipy.optimize import curve_fit

SERIAL_PORT = "com4"#PC

ser = serial.Serial( SERIAL_PORT, timeout=10.0 )
ser.setBaudrate(115200)

        
x = ser.readline()
ser.close()
y = stringToArray(x)
y = np.array(y)

y = 2*3.3*y/1.023
t = linspace(0,500,499)
popt, pcov = curve_fit(ringDown, t, y)
print("f = %0.2f Hz" %abs(popt[3]))
print("A = %0.2f mV" %abs(popt[2]))
z = ringDown(t,popt[0],popt[1],popt[2],popt[3])

plot(t,y,'o',t,z)
xlabel("time [ms]")
ylabel("coil voltage [mV]")


def stringToArray(string):
    substring = ''
    array = []
    for index in range(len(string)-4):
        if string[index].isdigit() or string[index] == '-':
            substring = substring + string[index]
        if string[index].isspace() and string[index - 1].isspace():
            array.append(int(substring))
            substring = ''     
    return array

def ringDown(t,lifetime,phase,amplitude,frequency):
    return amplitude*exp(-t/lifetime)*sin(2*pi*frequency*t*0.001 + phase)

