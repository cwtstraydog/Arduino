//
// 25Khz signal 
// Currently setup for reverse polarity fan so 99 = 1% and 100 = no PWM Control and 0, 1, and 2 = off
// Attempting to accept input form serial to control fans
//
// To do list
// 
// 
//
//
//

unsigned int dc = 99;  // % duty cycle that you can set yourself 
unsigned long speed = 0;

long t = 0;    
long r1;

unsigned long period = 40;

unsigned int integerValue=0;  // Max value is 65535
char incomingByte;




void setup()
{
  Serial.begin(115200);
  Serial.println("::Start 140721_Fan_PWM_w_serial_input:: Workign On VIsualBasic Interfacing");

  for (int i=2; i< 13; i++) pinMode(i, OUTPUT);

  t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output


}


 
void loop() 
{
  
  // Declarations======================
//    unsigned int dc = 99;  // % duty cycle that you can set yourself 
//    unsigned long speed = 0;

//    long t = 0;    
//    long r1;

//    unsigned long period = 40;

//    unsigned int integerValue=0;  // Max value is 65535
//    char incomingByte;

//End declarations ====================


  // VVVV this the code for fan control VVVVV
  PORTE |= B00001000;  //Turn on pin 5
  delayMicroseconds(t);
  PORTE &= B11110111;  //Turn off pin 5
  delayMicroseconds(period - t);
  // ^^^^ this the code for fan control ^^^^
  
 
   // =========================  Remove this and add math to automatically ramp fan ====================
 if (Serial.available() > 0) {   // something came across serial
 integerValue = 0;         // throw away previous integerValue
 
  // =========================  Remove this and add math to automatically ramp fan ====================
  //  if (dc  >=  3);
  //    dc--;
  //   r1=65000;
    
  while(1)             // force into a loop until 'n' is received
  {
      
 //   r1--;
 //   if (r1 >= 0) break;
 //   if (r1 >= 0) continue;
 
  // VVVV this the code for fan control VVVVV
  t = (40 * dc) /100;    //unit is "us", gives 25kHz PWM output
  PORTE |= B00001000;  //Turn on pin 5
  delayMicroseconds(t);
  PORTE &= B11110111;  //Turn off pin 5
  delayMicroseconds(period - t);
  // ^^^^ this the code for fan control ^^^^
  
  
  // =========================  Remove this and add math to automatically ramp fan ====================
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
  // =========================  Remove this and add math to automatically ramp fan ====================
    }
      Serial.println("IntegerValue");
      Serial.println(integerValue);   // Do something with the value
      Serial.println("  ");
      Serial.println("dc");
      Serial.println(dc);
      Serial.println("  ");
      Serial.println("speed");
      Serial.println(speed);
      Serial.println("  ");
      Serial.println("t");
      Serial.println(t);
  } //This comes back when code body is added back
}




