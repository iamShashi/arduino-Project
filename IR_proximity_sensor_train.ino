
// Author: Ankit Kumar
// Date: 04/03/2015
// Version: 1.0
#include <Servo.h>
Servo myservo;

int pos = 0;
int IRpin = A0;               // IR photodiode on analog pin A0
int IRemitter = 2;            // IR emitter LED on digital pin 2
int ambientIR;                // variable to store the IR coming from the ambient
int obstacleIR;               // variable to store the IR coming from the object
int value[10];                // variable to store the IR values
int distance=0;                 // variable that will tell if there is an obstacle or not
boolean isTrain=false;
void setup(){
  Serial.begin(9600);         // initializing Serial monitor
  myservo.attach(9);
  pinMode(IRemitter,OUTPUT);  // IR emitter LED on digital pin 2
  digitalWrite(IRemitter,LOW);// setup IR LED as off
  pinMode(11,OUTPUT);         // buzzer in digital pin 11
}

void loop(){
  distance = readIR(5);       // calling the function that will read the distance and passing the "accuracy" to it
  Serial.println(distance);   // writing the read value on Serial monitor
  if(distance>30)
  {
    isTrain = true;
  }
  else
  {
    isTrain = false;
  }
  train();                // to indicate the presense of train
  shutter(isTrain);
}

int readIR(int times){
  for(int x=0;x<times;x++){
    digitalWrite(IRemitter,LOW);     //turning the IR LEDs off to read the IR coming from the ambient
    delay(1);                        // minimum delay necessary to read values
    ambientIR = analogRead(IRpin);   // storing IR coming from the ambient
    digitalWrite(IRemitter,HIGH);    //turning the IR LEDs on to read the IR coming from the obstacle
    delay(1);                        // minimum delay necessary to read values
    obstacleIR = analogRead(IRpin);  // storing IR coming from the obstacle
    value[x] = ambientIR-obstacleIR; // calculating changes in IR values and storing it for future average
  }
  
  for(int x=0;x<times;x++){          // calculating the average based on the "accuracy"
    distance+=value[x];
  }
  return(distance/times);            // return the final value
}

void train()
{
  if (distance>30)
  {
    digitalWrite(11,HIGH);          //turning the led on to indicate presence of object
  }
  else
  {  
    digitalWrite(11,LOW);           //turning the led off if no object
    
  }
}
void shutter(boolean check)
{
    if(check==true)
    {
          for(pos;pos<=180;pos+=1)
          {
              myservo.write(pos);             
               delay(10);
            } 
     }
     if(check==false)
    {
          for(pos;pos>=1;pos-=1)
          {
              myservo.write(pos);             
               delay(10);
            } 
     }
  }
