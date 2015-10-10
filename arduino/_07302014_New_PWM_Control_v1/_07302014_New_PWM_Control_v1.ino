
// 07/31/2014 Trying for better resoltuion of duty cycle
//
// 
////===============Old CodeVVV
// unsigned int dc = 99;  // % duty cycle that you can set yourself 
unsigned long speed = 0;


// unsigned long period = 40;

unsigned int integerValue=0;  // Max value is 65535
char incomingByte;
////===============Old Code^^^

void setup()
{
  // configure hardware timer1 to generate a fast PWM on OC2B (Arduino digital pin 3)
  // set pin high on overflow, clear on compare match with OCR2B
  DDRB = B00111111;  // digital pins -,-,13,12,11,10,9,8

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B = 0x01;  // select timer1 clock as 16 MHz I/O clock / 64 = 250 kHz
  OCR1A = 249;  // top/overflow value is 249 => produces a 1000 Hz PWM
  OCR1B = 255;  // set the PWM to 50% duty cycle



   Serial.begin(115200);
  Serial.println(" :: Start :07-31-2014 13.30: Ver XXX.00.01 'Using Timer Phase Shift PWM code'");

}

void loop()
{
  
  
  
 
      // PORTB = B00111000;   // turns on 13,12,11; turns off 10,9,8
 
  
 if (Serial.available() > 0) {   // something came across serial
  integerValue = 0;         // throw away previous integerValue
 
    
  while(1)             // force into a loop until 'n' is received
  {
      

 
  // VVVV this the code for fan control VVVVV
    
  // ^^^^ this the code for fan control ^^^^
  
  
  
    incomingByte = Serial.read();
    //Serial.println("Incoming Byte");
    //Serial.println(incomingByte); //trying to see into the caos
     if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
     if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
     integerValue *= 10;  // shift left 1 decimal place
     // convert ASCII to integer, add, and shift left 1 decimal place
    integerValue = ((incomingByte - 48) + integerValue);
     speed = integerValue;
     // dc =speed;
  
    }              //========== Debug Stuff VVVVVV
      //Serial.println("IntegerValue");
      //Serial.println(integerValue);   // Do something with the value
      //Serial.println("  ");
      Serial.println("dc");
      //================= Serial.println(dc);
      //Serial.println("  ");
      //Serial.println("speed");
      //Serial.println(speed);
      //Serial.println("  ");
      //Serial.println("t");
      //Serial.println(t);
  } 
  ////================Old Code
}
