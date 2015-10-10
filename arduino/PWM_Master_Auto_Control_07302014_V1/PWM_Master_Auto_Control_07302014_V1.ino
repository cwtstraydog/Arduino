
// 07/30/2014 Trying for better resoltuion of duty cycle
//
// Using old code with timer to test PWM resolution
////===============Old CodeVVV
unsigned int dc = 99;  // % duty cycle that you can set yourself 
unsigned long speed = 0;

long t = 0;    
long r1;

unsigned long period = 40;

unsigned int integerValue=0;  // Max value is 65535
char incomingByte;
////===============Old Code^^^

void setup()
{
  
  // pinMode(9, OUTPUT);



  ////===============Old CodeVVV
   Serial.begin(115200);
  Serial.println(" :: Start :07-30-2014 15.15: Ver XXX.00.01 'Testing Keypad Control' ");
}

void loop()
{

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
     dc = integerValue;
     if dc= 491 then setpin ()
  
    }              //========== Debug Stuff VVVVVV
 
      Serial.println("dc");
      Serial.println(dc);
  } 
 
}
