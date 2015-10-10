
/* 06/25/2015 John Emig
EMESC Fan Lab
Control 10 Fan PWM independantly
06/26/2015
      organised pins and OCR registers into order fan1 - lowest pin

      added serial read parsing code to accept comma deliminated commands from 
      serial port. all ten fan speeds must be entered or remaining duty cycles
      are set to 15 (off)..
      
      
      manually this program works perfectly
      needing windows interface to setup up duty cycles/fan speed

      ======= test commands ========VVV
      30,31,32,33,34,35,36,37,38,39
      ======= test commands ========^^^
      
      ===============^^^ Notes ^^^ */
 


//legacy unknown if needed or not and why screw up a good thing? VVV
unsigned int integerValue=0;  // Max value is 65535
//legacy unknown if needed or not and why screw up a good thing? ^^^



//      ======= Duty Cycle Varibles ========VVV
unsigned int dc0 = 64; //duty cycle zero fan 1
unsigned int dc1 = 64;
unsigned int dc2 = 64;
unsigned int dc3 = 64;
unsigned int dc4 = 64;
unsigned int dc5 = 64;
unsigned int dc6 = 64;
unsigned int dc7 = 64;
unsigned int dc8 = 64;
unsigned int dc9 = 64;
//      ======= Duty Cycle Varibles ========^^^

//      ======= Fan Pin Integers ========VVV
int fan01=2;
int fan02=4;
int fan03=5;
int fan04=6;
int fan05=7;
int fan06=9;
int fan07=10;
int fan08=11;
int fan09=12;
int fan10=13;
//      ======= Fan Pin Integers ========^^^




//legacy unknown if needed or not and why screw up a good thing? VVV
char incomingByte; 
unsigned long speed = 0;
//legacy unknown if needed or not and why screw up a good thing? ^^^


void setup()
{
  
 // Setting                          Prescale_factor
TCCR0A = TCCR0A & 0b11111000 | 0x01; 
TCCR0B = TCCR0B & 0b11111000 | 0x01;  //Original information
TCCR1A = TCCR1A & 0b11111000 | 0x01; 
TCCR1B = TCCR1B & 0b11111000 | 0x01; 
TCCR2A = TCCR2A & 0b11111000 | 0x01; 
TCCR2B = TCCR2B & 0b11111000 | 0x01; 
TCCR3A = TCCR3A & 0b11111000 | 0x01; 
TCCR3B = TCCR3B & 0b11111000 | 0x01; 
TCCR4A = TCCR4A & 0b11111000 | 0x01; 
TCCR4B = TCCR4B & 0b11111000 | 0x01; 


/*
timer 0 (controls pin 13, 4)
timer 1 (controls pin 12, 11)
timer 2 (controls pin 10, 9)
timer 3 (controls pin 5, 3, 2)
timer 4 (controls pin 8, 7, 6)

*/


// =========== Fan Pin Enabling ===========VVV
  pinMode(fan01, OUTPUT);   //Enable the pin 2 that timer3 ch B controls Fan 1
  pinMode(fan02, OUTPUT);   //Enable the pin 4 that timer0 ch B controls Fan 2 
  pinMode(fan03, OUTPUT);   //Enable the pin 5 that timer3 ch A controls Fan 3
  pinMode(fan04, OUTPUT);   //Enable the pin 6 that timer4 ch A controls Fan 4
  pinMode(fan05, OUTPUT);   //Enable the pin 7 that timer4 ch B controls Fan 5
  
  pinMode(fan06, OUTPUT);   //Enable the pin 9 that timer2 ch B controls Fan 6
  pinMode(fan07, OUTPUT);   //Enable the pin 10 that timer2 ch A controls Fan 7
  pinMode(fan08, OUTPUT);   //Enable the pin 11 that timer1 ch B controls Fan 8
  pinMode(fan09, OUTPUT);   //Enable the pin 12 that timer1 ch A controls Fan 9
  pinMode(fan10, OUTPUT);   //Enable the pin 13 that timer0 ch A controls Fan 10
// =========== Fan Pin Enabling ===========^^^
  
// =========== PWM Register presets could be any number just chose these ===========VVV
  OCR3B = 80;   //2  Fan 1
  OCR0B = 80;   //4  Fan 2
  OCR3A = 180;  //5  Fan 3
  OCR4A = 180;  //6  Fan 4
  OCR4B = 80;   //7  Fan 5
  OCR2B = 80;   //9  Fan 6
  OCR2A = 180;  //10 Fan 7
  OCR1A = 180;  //11 Fan 8
  OCR1B = 80;   //12 Fan 9
  OCR0A = 180;  //13 Fan 10
// =========== PWM Register presets could be any number just chose these ===========^^^

  
// =========== PWM Timer configuration ===========VVV  
TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); // init timer0 configure for fast PWM 
TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10); // init timer1 configure for fast PWM 
TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20); // init timer2 configure for fast PWM 
TCCR3A = _BV(COM3A1) | _BV(COM3B1) | _BV(WGM30); // init timer3 configure for fast PWM 
TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(WGM40); // init timer4 configure for fast PWM 
// =========== PWM Timer configuration ===========^^^  




// =========== Serial Port configuration ===========VVV  
  Serial.begin(115200);
  Serial.println(" :: Start :: 10 Fan PWM Ver 001.00.0x '06-26-2015 :: 255 = H :: 1 = L::'");
// =========== Serial Port configuration ===========^^^
}

void loop()
{
  

while (Serial.available() > 0) { // force into a loop until 'n' is received

// =========== Parse input into integers ===========VVV    
    dc0=Serial.parseInt();
    dc1=Serial.parseInt();
    dc2=Serial.parseInt();
    dc3=Serial.parseInt();
    dc4=Serial.parseInt();
    dc5=Serial.parseInt();
    dc6=Serial.parseInt();
    dc7=Serial.parseInt();
    dc8=Serial.parseInt();
    dc9=Serial.parseInt();
// =========== Parse input into integers ===========^^^    

// =========== Ensure Duty Cycle Values ===========VVV    
    if (dc0==0) dc0=15;
    if (dc1==0) dc1=15;
    if (dc2==0) dc2=15;
    if (dc3==0) dc3=15;
    if (dc4==0) dc4=15;
    if (dc5==0) dc5=15;
    if (dc6==0) dc6=15;
    if (dc7==0) dc7=15;
    if (dc8==0) dc8=15;
    if (dc9==0) dc9=15;


    if (dc0>255) dc0=255;
    if (dc1>255) dc1=255;
    if (dc2>255) dc2=255;
    if (dc3>255) dc3=255;
    if (dc4>255) dc4=255;
    if (dc5>255) dc5=255;
    if (dc6>255) dc6=255;
    if (dc7>255) dc7=255;
    if (dc8>255) dc8=255;
    if (dc9>255) dc9=255;
// =========== Ensure Duty Cycle Values ===========^^^

// =========== Input Duty Cycle into PWM registers ===========VVV
  OCR3B = dc0;   //2  Fan 1
  OCR0B = dc1;   //4  Fan 2
  OCR3A = dc2;  //5  Fan 3
  OCR4A = dc3;  //6  Fan 4
  OCR4B = dc4;   //7  Fan 5
  OCR2B = dc5;   //9  Fan 6
  OCR2A = dc6;  //10 Fan 7
  OCR1A = dc7;  //11 Fan 8
  OCR1B = dc8;   //12 Fan 9
  OCR0A = dc9;  //13 Fan 10
// =========== Input Duty Cycle into PWM registers ===========^^^


// =========== Finish input of serial port command ===========VVV
if (Serial.read() == '\n') {}
// =========== Finish input of serial port command ===========^^^


// =========== Debug Stuff Leave for feedback ===========VVV
// Fan 1
      Serial.println(0,0);      
      Serial.print("dc0/Fan 1 = ");
      Serial.print(dc0);
      Serial.println(0,0);      
      Serial.print("OCR3B/Pin 2 = ");
      Serial.print(OCR3B);
      Serial.println(0,0);   
// Fan 2
      Serial.println(0,0);      
      Serial.print("dc1/Fan 2 = ");
      Serial.print(dc1);
      Serial.println(0,0);      
      Serial.print("OCR0B/Pin 4 = ");
      Serial.print(OCR0B);
      Serial.println(0,0);         
// Fan 3
      Serial.println(0,0);      
      Serial.print("dc2/Fan 3= ");
      Serial.print(dc2);
      Serial.println(0,0);      
      Serial.print("OCR3A/Pin 5 = ");
      Serial.print(OCR3A);
      Serial.println(0,0);         
// Fan 4
      Serial.println(0,0);      
      Serial.print("dc3/Fan 4 = ");
      Serial.print(dc3);
      Serial.println(0,0);      
      Serial.print("OCR4A/Pin 6 = ");
      Serial.print(OCR4A);
      Serial.println(0,0);         
// Fan 5
      Serial.println(0,0);      
      Serial.print("dc4/Fan 5= ");
      Serial.print(dc4);
      Serial.println(0,0);      
      Serial.print("OCR4B/Pin 7 = ");
      Serial.print(OCR4B);
      Serial.println(0,0);         
// Fan 6
      Serial.println(0,0);      
      Serial.print("dc5 = ");
      Serial.print(dc5);
      Serial.println(0,0);      
      Serial.print("OCR2B/Pin 9 = ");
      Serial.print(OCR2B);
      Serial.println(0,0);         
// Fan 7
      Serial.println(0,0);      
      Serial.print("dc6 = ");
      Serial.print(dc6);
      Serial.println(0,0);      
      Serial.print("OCR2A/Pin 10 = ");
      Serial.print(OCR2A);
      Serial.println(0,0);         
// Fan 8
      Serial.println(0,0);      
      Serial.print("dc7 = ");
      Serial.print(dc7);
      Serial.println(0,0);      
      Serial.print("OCR1A/Pin 11 = ");
      Serial.print(OCR1A);
      Serial.println(0,0);         
// Fan 9
      Serial.println(0,0);      
      Serial.print("dc8 = ");
      Serial.print(dc8);
      Serial.println(0,0);      
      Serial.print("OCR1B/Pin 12 = ");
      Serial.print(OCR1B);
      Serial.println(0,0);        
// Fan 10
      Serial.println(0,0);      
      Serial.print("dc9 = ");
      Serial.print(dc9);
      Serial.println(0,0);      
      Serial.print("OCR0A/Pin 13 = ");
      Serial.print(OCR0A);
      Serial.println(0,0);   
// =========== Debug Stuff Leave for feedback ===========^^^


  }  //end While Loop 


  } // End Void Loop

