
// 10/09/2014 Attampting to read Tach Signal and control PWM at same time
//
// 
////===============VVV Notes VVV
////            Pin 4 Is Output
////            Pin 2 Is Input
//  10-09-2014 Combine this final PWM control with Tachometer 
//            reading and display
//  To Do:: add Tach code in the while loop
////===============^^^ Notes ^^^
 



unsigned int integerValue=0;  // Max value is 65535
unsigned int dc = 245;
char incomingByte;
unsigned long speed = 0;

void setup()
{
  
 // Setting                          Prescale_factor
TCCR0B = TCCR0B & 0b11111000 | 0x01; 

  pinMode(4, OUTPUT); //Enable the pin that timer0 controls

  OCR0B = 245;



TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); // init timer0 configure for fast PWM 
  Serial.begin(115200);
  Serial.println(" :: Start :: Ver 001.50.01 '07-31-2014 :: 1 ::H:: - 245 ::L::'");

}

void loop()
{
  
   if (Serial.available() > 0) {   // something came across serial
 integerValue = 0;         // throw away previous integerValue
 OCR0B = dc;
    
  while(1)             // force into a loop until 'n' is received
  {

     incomingByte = Serial.read();
    Serial.println("Incoming Byte");
    Serial.println(incomingByte); //trying to see into the caos
     if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
     if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
     integerValue *= 10;  // shift left 1 decimal place
     // convert ASCII to integer, add, and shift left 1 decimal place
    integerValue = ((incomingByte - 48) + integerValue);
     speed = integerValue;
     dc =speed;
  OCR0B = dc;
    }              //========== Debug Stuff VVVVVV
      //Serial.println("IntegerValue");
      //Serial.println(integerValue);   // Do something with the value
      //Serial.println("  ");
      Serial.println("dc");
      Serial.println(dc);
      //Serial.println("  ");
      //Serial.println("speed");
      //Serial.println(speed);
      //Serial.println("  ");
      //Serial.println("t");
      //Serial.println(t);
  } 
}
