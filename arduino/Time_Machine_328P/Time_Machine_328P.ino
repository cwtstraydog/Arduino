/*Time Machine/Re-Ager and Stir Plate Control ATmega328p 5v 16Mhz 
John Emig
06/22/2015
Fan Control on timer 1, Pin 5
digital relay control on pin 4 for time machine motor, and Pin 7 for stir plate motor
three thermocouples A0, A1, A2
no thermal couple code not needed at this time

*/




//===================== VVV Time Keeping Stuff VVV
int years=0;
int months=0;
int weeks=0;
int days=0;
int hours=0;
int minutes=0;
unsigned long seconds=0;
unsigned long msec=0;

//===================== ^^^ Time Keeping Stuff ^^^

int pin5=5; //on signal for time machine
int pin6=6; //on signal for stir plate
int pin8=8; //used as a signal pin to display up time and status
int pin9=9; //open input

//===================== VVV Time Machine Control Stuff VVV
int pin3 = 3;   //TM Fan PWM
int TimeRelay1Pin4=4;
int fan01=0;
int motor01=0;
int motorminutes;
int motor01minutes;
//===================== ^^^ Time Machine Control Stuff ^^^

//===================== VVV Stir Plate Control VVV
int pin10 = 10;  //Stir Fan PWM
int StirRelay2Pin7=7;
int fan02=0;
int motor02=0;
int stirmotorminutes;
int motor02minutes;
//===================== ^^^ Stir Plate Control ^^^

//===================== VVV Fan Control Stuff VVV

unsigned int integerValue=0;  // Max value is 65535
char incomingByte;            // Fan Control Stuff


unsigned long speed = 0;      // Fan Control Stuff

int dc01;
int dc02;

//===================== ^^^ Fan Control Stuff ^^^

//===================== VVV Temp Read Stuff VVV
int tempPin0 = A0;    //Thermmocouple 1
int tempPin1 = A1;    //Thermocouple 2
int tempPin2 = A2;    //Thermocouple 3
long tempReading0;  //Temp Control Stuff
long tempReading1;  //Temp Control Stuff
long tempReading2;  //Temp Control Stuff
float avgTemp0;  //Temp Control Stuff
float avgTemp1;  //Temp Control Stuff
float avgTemp2;  //Temp Control Stuff
//===================== ^^^ Temp Read Stuff ^^^

void setup() {
  
  Serial.begin(115200);
  Serial.println(" :: Start :06-22-2015 10:45 : Ver XXX.50.01 ");
  Serial.println(" :: Start :: ");
  Serial.println(" :: Start :: ");
 
 
TCCR1B = TCCR0B & 0b11111000 | 0x01; 
TCCR2B = TCCR0B & 0b11111000 | 0x01; 


  pinMode(pin10, OUTPUT); //Stir Fan PWM 
  pinMode(pin3, OUTPUT); //TM Fan PWM
  
  OCR1B = 245;
  OCR2B = 245;

TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10); // init timer0 configure for fast PWM 
TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20); // init timer0 configure for fast PWM 

 
 
 
 pinMode(pin5,INPUT);  //Signal To turn on TM
  pinMode(pin6,INPUT);  //Signal to turn on Stir
   pinMode(pin8,INPUT); //Signal to display time
    pinMode(pin9,INPUT); //signal to turn on Stir controlled by varible Knob
 pinMode(TimeRelay1Pin4, OUTPUT);  //turn on TM Motor
  pinMode(StirRelay2Pin7, OUTPUT);  //Turn on Stir motor
  
}

void loop() {
  //Current fan in use is positive polarity so 255= high and 1= low;

//============== Time Keeping Code =====VVV
  msec=millis();
  seconds=msec/1000;
  minutes=msec/60000;
  hours=msec/3600000;
  days=msec/86400000;
  weeks=msec/604800000;
  months=msec/2618784000;
  years=msec/3142540800;
  
if (seconds>=60) {seconds = seconds % 60;}
if (minutes>=60) {minutes = minutes % 60;}
if (hours>=24) {hours = hours % 24;}
if (days>=7) {days = days % 7;}
if ((weeks>=4) && (days>=2)) {weeks = 0;}
if (months>=12) {months = months % 12;}
//============== Time Keeping Code =====^^^

//============== Display Stus Button Code =====VVV
//if (digitalRead(pin8)==HIGH) { //Display Status Button
//Serial.println("Unit has been up and running for "); 
//Serial.print(years);Serial.print (" Years ");Serial.print(months);Serial.print(" Months ");Serial.print(weeks);Serial.print(" Weeks ");Serial.print(days);Serial.print(" Days ");Serial.print(hours);Serial.print(" Hours ");Serial.print(minutes);Serial.print(" Min ");Serial.print(seconds);Serial.print(" Sec ");  
//Serial.println(0,0);
 //}
//============== Display Stus Button Code =====^^^



                                  //=== Time Machine Code ===\\===VVV
if (digitalRead(pin5)==HIGH) {  // Turn on Time Machine

   //=== turn on motor and fan ===\\===VVVV
    if (fan01==0) {
      OCR1B=80;   //fan speed 
      fan01=1;   //flag fan on
      motor01=1;
      }

    if (fan01==1) {
      if (motorminutes != minutes) { //xxx
      motorminutes=minutes; //xxx
      ++motor01minutes;
      }
    }
//10/08/2015 motor reliability tests show better reliability with 30mins on instead of 60mins
    if ((motor01minutes==30) && (motor01==1)) { //shut down motor ramp fan to 80%
      digitalWrite(TimeRelay1Pin4, HIGH);  //motor relay to off
      OCR1B=129;            //fan set to 80%
      motor01=2;
      //10/08/2015 added the following 5 'cause the status was flooding the serial port and it did not need to
          if (digitalRead(pin8)==HIGH) { //Display Status Button
            Serial.println("Unit has been up and running for "); 
            Serial.print(years);Serial.print (" Years ");Serial.print(months);Serial.print(" Months ");Serial.print(weeks);Serial.print(" Weeks ");Serial.print(days);Serial.print(" Days ");Serial.print(hours);Serial.print(" Hours ");Serial.print(minutes);Serial.print(" Min ");Serial.print(seconds);Serial.print(" Sec ");  
            Serial.println(0,0);
           }
    }
    
    if ((motor01minutes==33) && (motor01==2)) { //motor has been off and fan has been at 80% for 3 minutes 
      OCR1B=10;                //shut off fan
      motor01=3;
    }

    if ((motor01minutes==38) && (motor01==3)) {  //re-set all we have rested for 5 
     fan01=0;
     motor01=0;
     motor01minutes=0;
    }
 }
                                    //=== Time Machine Code ===\\===^^^
                                    
                                    
                                  //=== Stir Plate Code ===\\===VVV
 if (digitalRead(pin6)==HIGH) {

   //=== turn on motor and fan ===\\===VVVV
  if (fan02==0) {
    OCR2B=80;   
    fan02=1;   
    motor02=1;
    digitalWrite(StirRelay2Pin7, LOW);  
    }

     if (fan02==1) {
      if (stirmotorminutes != minutes) { //xxx
      stirmotorminutes=minutes;  //xxx
      ++motor02minutes;
      }
    }
//10/08/2015 motor reliability tests show better reliability with 30mins on instead of 60mins
    if ((motor02minutes==30) && (motor02==1)) { //shut down motor ramp fan to 80%
      digitalWrite(StirRelay2Pin7, HIGH);  //motor relay to off
      OCR2B=129;                             //fan set to 80%
      motor02=2;
      //10/08/2015 added the following 5 'cause the status was flooding the serial port and it did not need to
          if (digitalRead(pin8)==HIGH) { //Display Status Button
            Serial.println("Unit has been up and running for "); 
            Serial.print(years);Serial.print (" Years ");Serial.print(months);Serial.print(" Months ");Serial.print(weeks);Serial.print(" Weeks ");Serial.print(days);Serial.print(" Days ");Serial.print(hours);Serial.print(" Hours ");Serial.print(minutes);Serial.print(" Min ");Serial.print(seconds);Serial.print(" Sec ");  
            Serial.println(0,0);
           }
    }
    
    if ((motor02minutes==33) && (motor02==2)){ //motor has been off and fan has been at 80% for 3 minutes 
      OCR2B=10;                //shut off fan
      motor02=3;
    }

    if ((motor02minutes==38) && (motor02==3)) {  //re-set all we have rested for 5 
     fan02=0;
     motor02=0;
     motor02minutes=0;

    }                            //=== Stir Plate Code ===\\===^^^
 }
                                   //=== Fan Stir Plate Code ===\\===VVV
                                   /*
                                   The plan is the use the Pwm control for the stirplate motor speed control
                                   Use a varible resitor (VR) to tell the PWM the speed wire the VR as a voltage divider
                                   as the voltage read changes so does the speed.
                                   
                                   o to 5v 0 to 1023
                                   fan speeds are 0 255
                                   .25 pwm per increment
                                   ==========
                                   .05V per increment
                                   ==========
                                   .2v(200mv) = 1 PWM
                                   
                                   */
                                   
                                   
                                   //=== Fan Stir Plate Code ===\\===^^^
}
