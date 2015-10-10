//
// 25Khz signal 
// Currently setup for reverse polarity fan so 99 = 1% and 100 = no PWM Control and 0, 1, and 2 = off
// 
//
// To do list
// Make a loop timer that increments (decrements) "dc" from 99 to 3 
// 10 minutes = 600 and an even spread would be increment (decrement) 6.25 seconds between change
//
//
//


unsigned int dc = 99;  // % duty cycle that you can set yourself 
long t = 0;    

long period = 40;
     
void setup()
{
  Serial.begin(115200);
  Serial.println("start Fan_PWM_140711");

  for (int i=2; i< 13; i++) pinMode(i, OUTPUT);

  t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output

}

void loop()
{
 
  PWM_Freq(1000000000,0);
  if (dc >= 3);
  {
  dc--;
  }
  if (dc < 3);
  {
    dc = 99;
}
  
   t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output
   
}


void PWM_Freq(int nn, int dd)
{
  for (int i=2; i< nn; i++) pinMode(i, OUTPUT);
  
   PORTE |= B00001000;  //Turn on pin 5

  delayMicroseconds(t);
  PORTE &= B11110111;  //Turn off pin 5

  delayMicroseconds(period - t);
}	
