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
unsigned long speed = 0;
long t = 0;    

long period = 40;

void setup()
{
  Serial.begin(115200);
  Serial.println("start Fan_PWM_140712_w_serial_input Best Guess");

  for (int i=2; i< 13; i++) pinMode(i, OUTPUT);

  t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output

}

void loop()
{
  PORTE |= B00001000;  //Turn on pin 5
  delayMicroseconds(t);
  PORTE &= B11110111;  //Turn off pin 5
  delayMicroseconds(period - t);

  if (Serial.available()){      //only getting one of a two digit number loop too fast to read two digits
      
      speed = Serial.read() - 48;
      dc = speed;
      //dc = dc--;
      t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output
 
      Serial.println("dc");
      Serial.println(dc);
      Serial.println("speed");
      Serial.println(speed);
      Serial.println("t");
      Serial.println(t);

}
}



