//  Sketch 07-12-2014 EmigJ
// This is modified code from "http://forum.arduino.cc/index.php/topic,17353.0.html"
//
// input from serial controls fan speed 1-10 "10 = 100%" "1 = 10%" "0 = 100%"
//
// TO DO
//
// greater resolution 
// some math to ramp the speed 
//

unsigned int high = 1;
unsigned int baseTime = 10;
unsigned int low = 99;
unsigned int speed = 0;
// unsigned int dc = 99; //duty cycle setable
//long t = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println("start PWM_W_Input_Control");
  
//  for (int i=2; i< 13; i++) pinMode(i, OUTPUT);
  
//   t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output
}



void loop()
{
  
    digitalWrite(5,LOW);
    delayMicroseconds(low*10);
    digitalWrite(5,HIGH);
    delayMicroseconds(high*10);

    if (Serial.available()){
      speed = Serial.read()// - 48;
      low = speed;
      high = baseTime - speed;
      Serial.println("high");
      Serial.println(high);
      Serial.println("speed");
      Serial.println(speed);
      Serial.println("basetime");
      Serial.println(baseTime);
      Serial.println("LOW");
      Serial.println(LOW);
    }
  }
