int setpoint01;
int setpoint02;
int setpoint03;
int F1seq=0;
int F2seq=0;
int F3seq=0;
int F1seqHour=0;
int F2seqHour=0;
int F3seqHour=0;
int years=0;
int months=0;
int weeks=0;
int days=0;
int hours=0;
int minutes=0;
unsigned long seconds=0;
unsigned long msec=0;
int TCHourTrack01=0;
int TCHourCount01=0;
int TCHourTrack02=0;
int TCHourCount02=0;
int TCHourTrack03=0;
int TCHourCount03=0;
int dc03;

int TCMinuteTrack01=0;
int TCMinuteCount01=0;
int TCMinuteTrack02=0;
int TCMinuteCount02=0;
int TCMinuteTrack03=0;
int TCMinuteCount03=0;
int F1seqMinute=0;
int F2seqMinute=0;
int F3seqMinute=0;

int tempPin3 = A3;    //Cabinet

int HPumpRelay1Pin22=22;  //hot pump on=low off =high
int HeaterRelay2Pin23=23;  //heater on=low heater off=high
int HPumpRelay=0;            //hot pump off=0 on =1
int HeaterRelay=0;          //heater off=0 on=1


int CPumpRelay3Pin24=24;  //Cold pump on-off relay
int CRedirectRelay4Pin25;  //Redirects cold water flow from cabinet cooling coil to fermenters
int CPumpRelay=0;          //flag for pump off=0 on=1
int CPRedirect=0;          //Flag for redirect recirculate=0 flow=1

void setup(void) {
    Serial.begin(115200);
Serial.print(" Set up begin test of Lager sequence");
    Serial.println(0,0);
    
    pinMode(CPumpRelay3Pin24, OUTPUT);  //Cold pump on-off relay
    pinMode(CRedirectRelay4Pin25, OUTPUT);  //Redirects cold water flow from cabinet cooling coil to fermenters
    pinMode(HPumpRelay1Pin22, OUTPUT);  //hot pump on=low off =high
    pinMode(HeaterRelay2Pin23,OUTPUT);  //heater on=low heater off=high
}


void loop(void) {
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

/*
d=58=8
r=43=30
d=43=84
r=35=96
d=35=24
r=68=48
d=68=48
hold=68=ever
*/





   
if (TCMinuteTrack01==0) {TCMinuteTrack01=minutes;}

  if (TCMinuteTrack01!=minutes) { //It is a different Minute||a Minute has past
    ++TCMinuteCount01;              //count the minutes that have passed
    TCMinuteTrack01=minutes;     // new 
    Serial.println(0,0);
    delay(1000);
    
   }

Serial.print("Begin Fermenter control");
    Serial.println(0,0);
    Serial.print("Track = ");
    Serial.print(TCMinuteTrack01);
    Serial.println(0,0);
    Serial.print("Count = ");
    Serial.print(TCMinuteCount01);
        Serial.println(0,0);
    Serial.print("F1seq = ");
    Serial.print(F1seq);
        Serial.println(0,0);
        Serial.print("Setpoint = ");
        Serial.print(setpoint01);
        Serial.println(0,0);
        delay(1000);
    
   if ((TCMinuteCount01<10) && (F1seqMinute==0)) { //Start fermenter temp control #1 every 10 minutes
        F1seqMinute=1;
     Serial.print("Minute count < 10 ");
         Serial.println(0,0);
   }
   
   if (TCHourCount01==10) {  // Fermentation temp check
     ++F1seqMinute;
     TCMinuteCount01=0;
     /*
     int tempPin3 = A3;    //Cabinet

int HPumpRelay1Pin22=22;  //hot pump on=low off =high
int HeaterRelay2Pin23=23;  //heater on=low heater off=high
int HPumpRelay=0;            //hot pump off=0 on =1
int HeaterRelay=0;          //heater off=0 on=1


int CPumpRelay3Pin24=24;  //Cold pump on-off relay
int CRedirectRelay4Pin25;  //Redirects cold water flow from cabinet cooling coil to fermenters
int CPumpRelay=0;          //flag for pump off=0 on=1
int CPRedirect=0;          //Flag for redirect recirculate=0 flow=1

     */
     //cabinet temp?     tempPin3
     // is pump on?

if ((tempPin3>70) && (CPumpRelay=0)) {
digitalWrite(CPumpRelay3Pin24, LOW);  //turning pump
digitalWrite(CRedirectRelay4Pin25, LOW);  //redirecting to reserver
CPumpRelay=1;              //pump on=1
CPRedirect=1;          //rediectred to reserver
}

     if (tempPin3>70) {dc03=204;}                      //80% fan
     if ((tempPin3<69.99)&& (tempPin3>67)){dc03=128;}  //50% fan
     if ((tempPin3<66.99)&& (tempPin3>65)){dc03=77;}   //30% fan

   }
     /* 
we need a minute counter to 10
we need to check that a fermentor is installed
we need to get a temp
we need to check the temp against the setpoint
we need to manage if the pumps or heaters are on allready
cabinet profile01
  we are shooting for the cabinet to be around 65º
    >70º fan to 80% and be sure the pump is running
    <69.99º and >67º fan at 50% 
    <66.99º and >65º fan 30%
    <64.99º and >62º fan 0%

*/


     
       if (5==5)  { //Fermenter installed check

     //fermenter01installed ?  
       //fermenter01 temp?
     //fermenter02installed ?  
       //fermenter02 temp?
     //fermenter03installed ?  
       //fermenter03 temp?
   }

} //end loop 
