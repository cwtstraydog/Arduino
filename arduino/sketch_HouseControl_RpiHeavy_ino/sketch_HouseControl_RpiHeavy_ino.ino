
/*===============VVV Notes VVV
Programer//designer John Emig
9/15/2015
                      ::    Mission Statement    //    Accomplishments    ::
                      Same as older one ceptin Raspberry Pi send setpoints and all Ardi does is control pumps and fans
                based on temp reads and input form raspberry pi.
    The unit reads from all 16 thermocouples
    Controls 4 fans
    Controls 16 relays    
      There are control pins that indicate if a device is installed 
      3 device pins for fermenters
      1 signal pin is stir plate is installed
      1 signal pin if Time Machine is installed
      3 fermenters each can have a generic Ale profile or Lager profile depending on signal pins

      
=====================       WHAT IS NEEDED       ======================


record temps

    send data points to raspberry as a data logger and graph builder

=======================================================================

                   //Relay controls 14\\

Hflow        Relay 1,2      pin22,23 Pump=22 and Valves=23
Cflow        Relay 3,4      pin24,25  Valves=24 and Pump=25
F1 HC        Relay 5, 6     pin26,27 cold valves=26 and Hot valves=27
F2 HC        Relay 7, 8     pin28,29 cold valves=28 and Hot valves=29
F3 HC        Relay 9, 10    pin30,31 cold valves=30 and Hot valves=31
Stir plate   Relay 11       pin32 StirRelay11pin32
Time.        Relay 12       pin33 TimeRelay12pin33
Lights       Relay 13,14    pin34,35 Indoor back corner=34  Outdoor over door=35 Connect to Raspberry Pi
Arduino      Relay 15       pin39 (RebootArdPin39Relay15 )
Raspberry Pi Relay 16       pin40 (RebootRpiePin40Relay16)

Tempf0=House down
Tempf1=House up
        Will averg these 2 

Tempf2=Out Left
Tempf3=Out Right
        Will averg these 2 
        and keep house averg within 20-15 of outside averg

Tempf4=Cabinet
Tempf5=Ferm01
Tempf6=Ferm02
Tempf7=Ferm03

Tempf8=Fridge
        **Warning** **Warning** **Warning** the Fridge is warming. There may have been a power outage.
        
Tempf9=Beer
        **Warning** **Warning** **Warning**


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



*/

#define aref_voltage 5

//===================== VVV Strings For Status Reading Commands VVV
int RebootArdPin39Relay15=39;
int RebootRpiePin40Relay16=40;

//===================== ^^^ Strings For Status Reading Commands ^^^


//===================== VVV Time Keeping Stuff VVV
int years=0;
int months=0;
int weeks=0;
int days=0;
int hours=0;
int minutes=0;
unsigned long seconds=0;
unsigned long msec=0;
int pin48=48; //used as a signal pin to display up time and status
//===================== ^^^ Time Keeping Stuff ^^^

//==============VVV Relay Control VVV========
int iLightRelay13Pin34=34;  //indoor light control
int oLightRelay14Pin35=35;  //outdoor light control
//===============^^^ Relay Control ^^^

//===================== VVV Time Machine Control Stuff VVV
int pin53 = 53;   //signal to turn on
int TimeRelay12Pin33=33;
unsigned long motor01;
unsigned long fan01;
long motor01time=0;
unsigned long rest01;
int motorminutes;
int motor01minutes;
//===================== ^^^ Time Machine Control Stuff ^^^


//===================== VVV Stir Plate Control VVV
int pin52 = 52;  //signal to turn on
int StirRelay11Pin32=32;
int fan02=0;
int motor02=0;
int stirmotorminutes;
int motor02minutes;
long motor02time=0;
unsigned long rest02;
//===================== ^^^ Stir Plate Control ^^^


//===================== VVV Fan Control Stuff VVV
unsigned int integerValue=0;  // Max value is 65535
char incomingByte;            // Fan Control Stuff
int dc01;
int dc02;
int dc03;
int dc04;
//===================== ^^^ Fan Control Stuff ^^^

//===================== VVV Temp Read Stuff VVV
int tempPin0 = A0;    //Fermentation 1
int tempPin1 = A1;    //Fermentation 2
int tempPin2 = A2;    //Fermentation 3
int tempPin3 = A3;    //Cabinet
int tempPin4 = A4;    //Temp Control Stuff
int tempPin5 = A5;    //Temp Control Stuff
int tempPin6 = A6;    //Temp Control Stuff
int tempPin7 = A7;    //Temp Control Stuff
int tempPin8 = A8;    //Temp Control Stuff
int tempPin9 = A9;    //Temp Control Stuff
int tempPin10 = A10;  //Temp Control Stuff
int tempPin11 = A11;  //Temp Control Stuff
int tempPin12 = A12;  //Temp Control Stuff
int tempPin13 = A13;  //Temp Control Stuff
int tempPin14 = A14;  //Temp Control Stuff
int tempPin15 = A15;  //Temp Control Stuff

long tempReading0;  //Temp Control Stuff
long tempReading1;  //Temp Control Stuff
long tempReading2;  //Temp Control Stuff
long tempReading3;  //Temp Control Stuff
long tempReading4;  //Temp Control Stuff
long tempReading5;  //Temp Control Stuff
long tempReading6;  //Temp Control Stuff
long tempReading7;  //Temp Control Stuff
long tempReading8;  //Temp Control Stuff
long tempReading9;  //Temp Control Stuff
long tempReading10;  //Temp Control Stuff
long tempReading11;  //Temp Control Stuff
long tempReading12;  //Temp Control Stuff
long tempReading13;  //Temp Control Stuff
long tempReading14;  //Temp Control Stuff
long tempReading15;  //Temp Control Stuff
long sec;  //Temp Control Stuff

float avgTemp0;  //Temp Control Stuff
float avgTemp1;  //Temp Control Stuff
float avgTemp2;  //Temp Control Stuff
float avgTemp3;  //Temp Control Stuff
float avgTemp4;  //Temp Control Stuff
float avgTemp5;  //Temp Control Stuff
float avgTemp6;  //Temp Control Stuff
float avgTemp7;  //Temp Control Stuff
float avgTemp8;  //Temp Control Stuff
float avgTemp9;  //Temp Control Stuff
float avgTemp10;  //Temp Control Stuff
float avgTemp11;  //Temp Control Stuff
float avgTemp12;  //Temp Control Stuff
float avgTemp13;  //Temp Control Stuff
float avgTemp14;  //Temp Control Stuff
float avgTemp15;  //Temp Control Stuff

double tempF0;
double tempF1;
double tempF2;
double tempF3;
double tempF4;
double tempF5;
double tempF6;
double tempF7;
double tempF8;
double tempF9;

double tempC0;
double tempC1;
double tempC2;
double tempC3;
double tempC4;
double tempC5;
double tempC6;
double tempC7;
double tempC8;
double tempC9;

double mv0;
double mv1;
double mv2;
double mv3;
double mv4;
double mv5;
double mv6;
double mv7;
double mv8;
double mv9;
//===================== ^^^ Temp Read Stuff ^^^


//===================== VVV Temp Control Stuff VVV
int OutsideLeft;
int OutsideRight;
int InsideUp;
int InsideDown;
int FridgeSetpoint;
int CoolerSetpoint;

//===================== ^^^ Temp Control Stuff ^^^
int UnknownSetpoint1;
int UnknownSetpoint2;
int UnknownSetpoint3;
int UnknownSetpoint4;
int UnknownSetpoint5;
int UnknownSetpoint6;
int Device1;
int Device2;
int Device3;
int Device4;
int Device5;
int Device6;
int Device7;
int Device8;
int Device9;
int Device10;
int Device11;
int Device12;
int Device13;
int Device14;
int Device15;
int Device16;
int Device17;
int Device18;
int Device19;
int Device20;
              //=== Flags ===VVV
      


int cabcooler;          //cabinet needs cooling turns on cold pump
int cabheater;          //cabinet needs cooling turns on hot pump
int ferm01cooler;       //Fermenter 1 needs cooling turns on cold pump
int ferm01heater;       //Fermenter 1 needs Warming turns on hot pump
int ferm02cooler;       //Fermenter 2 needs cooling turns on cold pump
int ferm02heater;       //Fermenter 2 needs Warming turns on hot pump
int ferm03cooler;       //Fermenter 3 needs cooling turns on cold pump
int ferm03heater;       //Fermenter 3 needs Warming turns on hot pump

              //=== Flags ===^^

        //=== Command Control Pins ===VVV

int Command01Pin44=44;
int Command02Pin45=45;
int Command03Pin46=46;
int Command04Pin47=47;

        //=== Command Control Pins ===^^^

//=== Fermnetation temp control ===VVV

int HPumpRelay1Pin22=22;
int HeaterRelay2Pin23=23;
int HPumpRelay=0;

int CPumpRelay3Pin24=24;
int CRedirectRelay4Pin25=25;
int CPumpRelay=0;

int Ferm1CRelay5Pin26=26;  //turns on 
int Ferm1HRelay6Pin27=27;
int Ferm01Cold;
int Ferm01Hot;
      
int Ferm2CRelay7Pin28=28;
int Ferm2HRelay8Pin29=29;
int Ferm02Cold;
int Ferm02Hot;

int Ferm3CRelay9Pin30=30;
int Ferm3HRelay10Pin31=31;
int Ferm03Cold;
int Ferm03Hot;



int TCHourTrack01;
int TCHourCount01;
int TCHourTrack02;
int TCHourCount02;
int TCHourTrack03;
int TCHourCount03;

int setpoint01;
int setpoint02;
int setpoint03;
int F1seq=0;
int F2seq=0;
int F3seq=0;
int F1seqHour=0;
int F2seqHour=0;
int F3seqHour=0;

int cab;
int sp01up;
int sp01Down;
int sp02up;
int sp02Down;
int sp03up;
int sp03Down;
int cabup;
int cabdown;
            //=== Fermnetation temp control ===^^^

//===================== ^^^ Temp Control Stuff ^^^
 
void setup(void) {

  Serial.begin(115200);
  Serial.println(" :: Start :08-03-2015 15:15 : Ver XXX.01.75 ");
  Serial.println(" ::  F3 Hour Lag Fixed  :: ");
  Serial.println(" :::: ");
  Serial.println(" :::: ");
  Serial.println(" :::: ");
  Serial.println(" :::: ");
 
 //=== Fan Config () ===VVV

       TCCR1B = TCCR1B & 0b11111000 | 0x01;
       TCCR2B = TCCR2B & 0b11111000 | 0x01;
       TCCR3B = TCCR3B & 0b11111000 | 0x01;
       TCCR4B = TCCR4B & 0b11111000 | 0x01;


  pinMode(12, OUTPUT); //Enable the pin that timer1 controls
  pinMode(9, OUTPUT); //Enable the pin that timer2 controls
  pinMode(2, OUTPUT); //Enable the pin that timer3 controls
  pinMode(7, OUTPUT); //Enable the pin that timer4 controls

 //=== Fan Config () ===^^^
 
//=== Stir Plate    //    Time Maching ===VVV
pinMode(pin53,INPUT); //signal to turn on time machine motor
digitalWrite(pin53,HIGH);
pinMode(pin52,INPUT); //signal to turn stir plate motor
digitalWrite(pin52,HIGH);
pinMode(pin48,INPUT); //used as a signal pin to display uptime and status
digitalWrite(pin48,HIGH);

pinMode(TimeRelay12Pin33, OUTPUT); //relay contol pin for time machine
pinMode(StirRelay11Pin32, OUTPUT); //relay control pin for stir plate
digitalWrite(TimeRelay12Pin33, HIGH); //relay contol pin for time machine
digitalWrite(StirRelay11Pin32, HIGH); //relay control pin for stir plate

//=== Stir Plate    //    Time Maching ===^^^

//=== Lighting Control ===VVV
pinMode(iLightRelay13Pin34, OUTPUT); //indoor light control
pinMode(oLightRelay14Pin35, OUTPUT);  //outdoor light control
digitalWrite(iLightRelay13Pin34, HIGH); //indoor light control
digitalWrite(oLightRelay14Pin35, HIGH);  //outdoor light control
//=== Lighting Control ===^^^

//=== Controller Power ===VVV
pinMode(RebootArdPin39Relay15, OUTPUT);
digitalWrite(RebootArdPin39Relay15, HIGH);
pinMode(RebootRpiePin40Relay16, OUTPUT);
digitalWrite(RebootRpiePin40Relay16, HIGH);
//=== Controller Power ===^^^


//=== Fermenter temp control ===VVV

//=== Fermenter #1 control ===VVV

pinMode(Ferm1CRelay5Pin26=26, OUTPUT); //controls valves for fermenter 1 cooling
pinMode(Ferm1HRelay6Pin27=27, OUTPUT); //controls valves for fermenter 1 heating 
digitalWrite(Ferm1CRelay5Pin26=26, HIGH); //controls valves for fermenter 1 cooling
digitalWrite(Ferm1HRelay6Pin27=27, HIGH); //controls valves for fermenter 1 heating 
//=== Fermenter #1 control ===^^^

//=== Fermenter #2 control ===VVV

pinMode(Ferm2CRelay7Pin28=28, OUTPUT); //controls valves for fermenter 2 cooling
pinMode(Ferm2HRelay8Pin29=29, OUTPUT); //controls valves for fermenter 2 heating 
digitalWrite(Ferm2CRelay7Pin28=28, HIGH); //controls valves for fermenter 2 cooling
digitalWrite(Ferm2HRelay8Pin29=29, HIGH); //controls valves for fermenter 2 heating 
//=== Fermenter #2 control ===^^^

//=== Fermenter #3 control ===VVV

pinMode(Ferm3CRelay9Pin30=30, OUTPUT); //controls valves for fermenter 3 cooling
pinMode(Ferm3HRelay10Pin31=31, OUTPUT); //controls valves for fermenter 3 heating 
digitalWrite(Ferm3CRelay9Pin30=30, HIGH); //controls valves for fermenter 3 cooling
digitalWrite(Ferm3HRelay10Pin31=31, HIGH); //controls valves for fermenter 3 heating 
//=== Fermenter #3 control ===^^^

//=== Fermenter cabinet control ===VVV
pinMode(HPumpRelay1Pin22=22, OUTPUT);  //Pump On-Off Relay
pinMode(HeaterRelay2Pin23=23, OUTPUT);  //Heater On-Off Relay
digitalWrite(HPumpRelay1Pin22=22, HIGH);  //Pump On-Off Relay
digitalWrite(HeaterRelay2Pin23=23, HIGH);  //Heater On-Off Relay
pinMode(CPumpRelay3Pin24=24, OUTPUT);  //Cold pump on-off relay
pinMode(CRedirectRelay4Pin25=25, OUTPUT);  //Redirects cold water flow from cabinet cooling coil to fermenters
digitalWrite(CPumpRelay3Pin24=24, HIGH);  //Cold pump on-off relay
digitalWrite(CRedirectRelay4Pin25=25, HIGH);  //Redirects cold water flow from cabinet cooling coil to fermenters
//=== Fermenter cabinet control ===^^^

//=============^^^ Fermenter temp control ^^^===========



//=== Command Pin Setup 4 bit 15 commands ===VVV
pinMode(Command01Pin44, INPUT);  //this and the other 3 (total 4) to be used as signal for recieving commands
pinMode(Command02Pin45, INPUT);  //this and the other 3 (total 4) to be used as signal for recieving commands
pinMode(Command03Pin46, INPUT);  //this and the other 3 (total 4) to be used as signal for recieving commands
pinMode(Command04Pin47, INPUT);  //this and the other 3 (total 4) to be used as signal for recieving commands
//=== Command Pin Setup 4 bit 15 commands ===^^^




  OCR1B = 125;  //time machine motor fan
  OCR2B = 125;  //Stir plate motor fan
  OCR3B = 125;  //cabinet fan (blow over cooling coils
  OCR4B = 125;

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10); // init timer1 configure for fast PWM 
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20); // init timer2 configure for fast PWM 
  TCCR3A = _BV(COM3A1) | _BV(COM3B1) | _BV(WGM30); // init timer3 configure for fast PWM
  TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(WGM40); // init timer4 configure for fast PWM

} //End Void Setup

void loop(void) {
  //Curent fan in use is positive polarity so 255= high and 1= low;
    
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
 if (digitalRead(pin48)==HIGH) { 
    Serial.println(0,0);
    Serial.println(0,0);
    Serial.print("Unit has been up and running for: "); 
    Serial.print(years);Serial.print (" Years ");Serial.print(months);Serial.print(" Months ");Serial.print(weeks);Serial.print(" Weeks ");Serial.print(days);Serial.print(" Days ");Serial.print(hours);Serial.print(" Hours ");Serial.print(minutes);Serial.print(" Min ");Serial.print(seconds);Serial.print(" Sec ");  
    Serial.println(0,0);
    Serial.println(0,0);
    Serial.print("setpoint01 = "); Serial.print(setpoint01);
    Serial.println(0,0);
    Serial.print("setpoint02 = "); Serial.print(setpoint02);
    Serial.println(0,0);
    Serial.print("setpoint03 = "); Serial.print(setpoint03);
    Serial.println(0,0);
    Serial.println(0,0);
    Serial.print("tempF0 = "); Serial.print(tempF0);
    Serial.println(0,0);
    Serial.print("tempF1 = "); Serial.print(tempF1);
    Serial.println(0,0);
    Serial.print("tempF2 = "); Serial.print(tempF2);
    Serial.println(0,0);
    Serial.print("tempF3 = "); Serial.print(tempF3);
    Serial.println(0,0);
    Serial.print("tempF4 = "); Serial.print(tempF4);
    Serial.println(0,0);
    Serial.print("tempF5 = "); Serial.print(tempF5);
    Serial.println(0,0);
    Serial.print("tempF6 = "); Serial.print(tempF6);
    Serial.println(0,0);
    Serial.print("tempF7 = "); Serial.print(tempF7);
    Serial.println(0,0);
    Serial.print("tempF8 = "); Serial.print(tempF8);
    Serial.println(0,0);
    Serial.print("tempF9 = "); Serial.print(tempF9);
    Serial.println(0,0);
    Serial.println(0,0);
    Serial.print("tempC0 = "); Serial.print(tempC0);
    Serial.println(0,0);
    Serial.print("tempC1 = "); Serial.print(tempC1);
    Serial.println(0,0);
    Serial.print("tempC2 = "); Serial.print(tempC2);
    Serial.println(0,0);
    Serial.print("tempC3 = "); Serial.print(tempC3);
    Serial.println(0,0);
    Serial.print("tempC4 = "); Serial.print(tempC4);
    Serial.println(0,0);
    Serial.print("tempC5 = "); Serial.print(tempC5);
    Serial.println(0,0);
    Serial.print("tempC6 = "); Serial.print(tempC6);
    Serial.println(0,0);
    Serial.print("tempC7 = "); Serial.print(tempC7);
    Serial.println(0,0);
    Serial.print("tempC8 = "); Serial.print(tempC8);
    Serial.println(0,0);
    Serial.print("tempC9 = "); Serial.print(tempC9);
    Serial.println(0,0);
    Serial.println(0,0);
    Serial.print("dc01 = "); Serial.print(dc01);
    Serial.println(0,0);
    Serial.print("dc02 = "); Serial.print(dc02);
    Serial.println(0,0);
    Serial.print("dc03 = "); Serial.print(dc03);
    Serial.println(0,0);
    Serial.print("dc04 = "); Serial.print(dc04);
    Serial.println(0,0);
    Serial.println(0,0);
    Serial.print("sp01up = ");Serial.print(sp01up);
    Serial.println(0,0);
    Serial.print("sp01Down = ");Serial.print(sp01Down);
    Serial.println(0,0);
    Serial.print("sp02up = ");Serial.print(sp02up);
    Serial.println(0,0);
    Serial.print("sp02Down = ");Serial.print(sp02Down);
    Serial.println(0,0);
    Serial.print("sp03up = ");Serial.print(sp03up);
    Serial.println(0,0);
    Serial.print("sp03Down = ");Serial.print(sp03Down);
    Serial.println(0,0);
    Serial.print("cabup = ");Serial.print(cabup);
    Serial.println(0,0);
    Serial.print("cabdown = ");Serial.print(cabdown);
    Serial.println(0,0);
    Serial.println(0,0);
    // added 08/12/2015
  
}

/*

                For i = 1 To 10
                    StatusBarArray(arrayindexer1) = 'stuff to be stored into ararray
                    arrayindexer1 = arrayindexer1 + 1
                Next
                arrayindexer1=0
*/

//============== Display Stus Button Code =====^^^

  OCR1B = dc01;//time machine motor fan
  OCR2B = dc02;//Stir plate motor fan
  OCR3B = dc03;//cabinet fan (blow over cooling coils
  OCR4B = dc04;// available fan controler
  
            //=== Temp Reading Code ===VVV    
  for(int i = 0; i < 400; i++) {  // 400 reads then average them out
          delay(50);
    tempReading0 += analogRead(tempPin0);  // Reading thermal from TC1
          delay(50);
    tempReading1 += analogRead(tempPin1);  // Reading thermal from TC2
          delay(50);
    tempReading2 += analogRead(tempPin2);  // Reading thermal from TC3
          delay(50);
    tempReading3 += analogRead(tempPin3);  // Reading thermal from TC4
          delay(50);
    tempReading4 += analogRead(tempPin4);  // Reading thermal from TC5
          delay(50);
    tempReading5 += analogRead(tempPin5);  // Reading thermal from TC6
          delay(50);
    tempReading6 += analogRead(tempPin6);  // Reading thermal from TC7
          delay(50);
    tempReading7 += analogRead(tempPin7);  // Reading thermal from TC8
          delay(50);
    tempReading8 += analogRead(tempPin8);  // Reading thermal from TC9
          delay(50);
    tempReading9 += analogRead(tempPin9);  // Reading thermal from TC10
          delay(50);
  } //this takes 3 minutes and 40.6 seconds to process
  
  avgTemp0 = tempReading0 / 400;  //Averageing the reads out
  avgTemp1 = tempReading1 / 400;  //Averageing the reads out
  avgTemp2 = tempReading2 / 400;  //Averageing the reads out
  avgTemp3 = tempReading3 / 400;  //Averageing the reads out
  avgTemp4 = tempReading4 / 400;  //Averageing the reads out
  avgTemp5 = tempReading5 / 400;  //Averageing the reads out
  avgTemp6 = tempReading6 / 400;  //Averageing the reads out
  avgTemp7 = tempReading7 / 400;  //Averageing the reads out
  avgTemp8 = tempReading8 / 400;  //Averageing the reads out
  avgTemp9 = tempReading9 / 400;  //Averageing the reads out
 
   mv0 = avgTemp0 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv1 = avgTemp1 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv2 = avgTemp2 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv3 = avgTemp3 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv4 = avgTemp4 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv5 = avgTemp5 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv6 = avgTemp6 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv7 = avgTemp7 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv8 = avgTemp8 * ((aref_voltage * 1000) / 1024); //millivolts per temp
   mv9 = avgTemp9 * ((aref_voltage * 1000) / 1024); //millivolts per temp
    
   tempC0 = mv0 / 20;  //converting milli volts to ºC
   tempC1 = mv1 / 20;  //converting milli volts to ºC
   tempC2 = mv2 / 20;  //converting milli volts to ºC
   tempC3 = mv3 / 20;  //converting milli volts to ºC
   tempC4 = mv4 / 20;  //converting milli volts to ºC
   tempC5 = mv5 / 20;  //converting milli volts to ºC
   tempC6 = mv6 / 20;  //converting milli volts to ºC
   tempC7 = mv7 / 20;  //converting milli volts to ºC
   tempC8 = mv8 / 20;  //converting milli volts to ºC
   tempC9 = mv9 / 20;  //converting milli volts to ºC
   
   tempF0 = (tempC0 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF1 = (tempC1 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF2 = (tempC2 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF3 = (tempC3 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF4 = (tempC4 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF5 = (tempC5 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF6 = (tempC6 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF7 = (tempC7 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF8 = (tempC8 / 5 * 9) + 32.0;    //Converting ºC to ºF
   tempF9 = (tempC9 / 5 * 9) + 32.0;    //Converting ºC to ºF
  
delay(10);  //wait .01 second

 tempReading0 = 0;
 tempReading1 = 0;
 tempReading2 = 0;
 tempReading3 = 0;
 tempReading4 = 0;
 tempReading5 = 0;
 tempReading6 = 0;
 tempReading7 = 0;
 tempReading8 = 0;
 tempReading9 = 0;
                                  //=== Fermenter Temp Control Code ===\\===VVV 

            //=== Ferm 3 Lager Profile ===^^^
                                  //=== Fermenter Temp Control Code ===\\===^^^
                                  
                                  
                                  //=== Time Machine Code ===\\===VVV
 if (digitalRead(pin53)==HIGH) {
 //=== turn on motor and fan ===\\===VVVV
    if (fan01==0) {
      dc01=80;   //fan speed 
      fan01=1;   //flag fan on
      motor01=1;
      digitalWrite(TimeRelay12Pin33, LOW);  //motor relay to on  
      Serial.println(0,0);  
      Serial.print("Starting TM Fan and Motor. Fan PWM 80");      
    }
            //=== Keeping track of on time ===VVV
    if (fan01==1) {
      if (motorminutes != minutes) { //xxx
      motorminutes=minutes; //xxx
      ++motor01minutes;
      motor01minutes=motor01minutes+3.33;
      }
    }
      //=== Keeping track of on time ===^^^
      
    if ((motor01minutes>=60) && (motor01==1)) { //shut down motor ramp fan to 80%
      digitalWrite(TimeRelay12Pin33, HIGH);  //motor relay to off
      dc01=129;            //fan set to 80%
      motor01=2;
      Serial.println(0, 0);   
      Serial.print ("TM Motor off, fan PWM on 129. Minutes at 60");  
    }
    
    if ((motor01minutes>=64) && (motor01==2)) { //motor has been off and fan has been at 80% for 3 minutes 
      dc01=10;                //shut off fan
      motor01=3;
      Serial.println(0, 0);  
      Serial.print ("TM Fan off and rest period. Fan PWM set at 10. Minutes at 64");  
    }

    if ((motor01minutes>=72) && (motor01==3)) {  //re-set all we have rested for 5 
     fan01=0;
     motor01=0;
     motor01minutes=0;
      Serial.println(0, 0);  
      Serial.print ("TM Motor has rested. Fan cooled motor and rested. Now restarting. Minutes 72");       
    }
  }  
                                    //=== Time Machine Code ===\\===^^^
                                    
                                  //=== Stir Plate Code ===\\===VVV
 if (digitalRead(pin52)==HIGH) {  
    //=== turn on motor and fan ===\\===VVVV
  if (fan02==0) {
    dc02=80;   
    fan02=1;   
    motor02=1;
    digitalWrite(StirRelay11Pin32, LOW); 
    Serial.println(0,0);  
    Serial.print("Starting SP Fan and Stir Motor dc=80");  
    }
//=== Time Keeping stuff ===VVV
     if (fan02==1) {
      if (stirmotorminutes != minutes) { //xxx
      stirmotorminutes=minutes;  //xxx
      ++motor02minutes;
      motor02minutes=motor02minutes+3.33;
      }
    }
//=== Time Keeping stuff ===^^^

  //=== Turn off motor === and make cooling off time \\===VVV
    if ((motor02minutes>=60) && (motor02==1)) { //shut down motor ramp fan to 80%
      digitalWrite(StirRelay11Pin32, HIGH);  //motor relay to off
      dc02=129;                             //fan set to 80%
      motor02=2;
    Serial.println(0, 0);   
    Serial.print ("Stir Motor off, fan PWM on 129. Minutes at 60");  
    }
        
  //=== Has Rested === reset for restart\\===VVV
  if ((motor02minutes>=64) && (motor02==2)){ //motor has been off and fan has been at 80% for 3 minutes 
      dc02=10;                //shut off fan
      motor02=3;      
      Serial.println(0, 0);  
      Serial.print ("Stir Motor Fan off and rest period. Fan PWM set at 10. Minutes at 64");  
    }
  
   if ((motor02minutes>=72) && (motor02==3)) {  //re-set all we have rested for 5 
     fan02=0;
     motor02=0;
     motor02minutes=0;
     Serial.print ("Stir Motor Motor has rested. Fan cooled motor and rested. Now restarting. Minutes 72");       
       }                         //=== Stir Plate Code ===\\===^^^
 }
/* if a signal pin is high or an "X" count serial spits out all measured point

                  //Relay controls 14\\

Hflow        Relay 1,2      pin22,23 Pump=22 and Valves=23
Cflow        Relay 3,4      pin24,25  Pump=24 and Valves=25
F1 HC        Relay 5, 6     pin26,27 cold valves=26 and Hot valves=27
F2 HC        Relay 7, 8     pin28,29 cold valves=28 and Hot valves=29
F3 HC        Relay 9, 10    pin30,31 cold valves=30 and Hot valves=31
Stir plate   Relay 11       pin32 StirRelay11pin32
Time.        Relay 12       pin33 TimeRelay12pin33
Lights       Relay 13,14    pin34,35 Indoor back corner=34  Outdoor over door=35 Connect to Raspberry Pi
*********Cabinet HC   Relay 15, 16   pin39,40 cold valves=39 and Hot valves=40



Tempf0=House down
Tempf1=House up
        Will averg these 2 

Tempf2=Out Left
Tempf3=Out Right
        Will averg these 2 
        and keep house averg within 20-15 of outside averg
        
        
Tempf4=Cabinet
Tempf5=Ferm01
Tempf6=Ferm02
Tempf7=Ferm03

Tempf8=Fridge
        **Warning** **Warning** **Warning** the Fridge is warming. There may have been a power outage.
        
Tempf9=Beer
        **Warning** **Warning** **Warning**
*/

/*
==============================================================
                Getting inputs for temp control
==============================================================
Setpoints coming from Rpi

setpoint01, setpoint02, setpoint03, cab, OutsideLeft, OutsideRight, InsideUp, InsideDown, FridgeSetpoint, CoolerSetpoint
1Unknown, 2Unknown, 3Unknown, 4Unknown, 5Unknown, 6Unknown


==============================================================
                End Getting inputs for temp control
==============================================================


*/
while (Serial.available() > 0) { // force into a loop until 'n' is received

// =========== Parse input into integers ===========VVV    
    setpoint01=Serial.parseInt();
    setpoint02=Serial.parseInt();
    setpoint03=Serial.parseInt();
    cab=Serial.parseInt();
    OutsideLeft=Serial.parseInt();
    OutsideRight=Serial.parseInt();
    InsideUp=Serial.parseInt();
    InsideDown=Serial.parseInt();
    FridgeSetpoint=Serial.parseInt();
    CoolerSetpoint=Serial.parseInt();
    UnknownSetpoint1=Serial.parseInt();
    UnknownSetpoint2=Serial.parseInt();
    UnknownSetpoint3=Serial.parseInt();
    UnknownSetpoint4=Serial.parseInt();
    UnknownSetpoint5=Serial.parseInt();
    UnknownSetpoint6=Serial.parseInt();
    Device1=Serial.parseInt();
    Device2=Serial.parseInt();
    Device3=Serial.parseInt();
    Device4=Serial.parseInt();
    Device5=Serial.parseInt();
    Device6=Serial.parseInt();
    Device7=Serial.parseInt();
    Device8=Serial.parseInt();
    Device9=Serial.parseInt();
    Device10=Serial.parseInt();
    Device11=Serial.parseInt();
    Device12=Serial.parseInt();
    Device13=Serial.parseInt();
    Device14=Serial.parseInt();
    Device15=Serial.parseInt();
    Device16=Serial.parseInt();
    Device17=Serial.parseInt();
    Device18=Serial.parseInt();
    Device19=Serial.parseInt();
    Device20=Serial.parseInt();
// =========== Parse input into integers ===========^^^    





// =========== Finish input of serial port command ===========VVV
if (Serial.read() == '\n') {}
// =========== Finish input of serial port command ===========^^^


//=== Temp Control Boundaries ===VVV
    sp01up = setpoint01+3;
    sp01Down= setpoint01-3;
    sp02up = setpoint02+3;
    sp02Down= setpoint02-3;
    sp03up = setpoint03+3;
    sp03Down= setpoint03-3;
    cabup=68;
    cabdown=50;
//=== Temp Control Boundaries ===^^^

//=== Cabinet Control Code ===VVV
                      //=== need fan control in cabinet ===
if ((Device1==1)||(Device2==1)||(Device3==1)) {
   if (tempF4>cabup) { // Make cabinet cooler
      digitalWrite(CRedirectRelay4Pin25, HIGH); //Run redirection through cabinet coils.
      cabcooler=1;    //We need the pump on
      cabheater=0;
      dc03=180;          //cabinet fan (blow over cooling coils)
   }    //make it cool
   
      if (tempF4<cabdown) { // make cabinet hotter
         digitalWrite(HeaterRelay2Pin23, HIGH);     // Run Redirection through cabinet coils
         cabheater=1;     //We need the heater
         cabcooler=0;
         dc03=180;          //cabinet fan (blow over cooling coils)         
   }    //make it hot
   
      if ((tempF4>cabdown) && (tempF4<cabup)) { //turn all off
         digitalWrite(CRedirectRelay4Pin25, HIGH); //Do not Run redirection through cabinet coils.
         digitalWrite(HeaterRelay2Pin23, HIGH);     //Do not Run Redirection through cabinet coils
         cabcooler=0;   // cabinet does not need the pump
         cabheater=0;   //Cabinet does not need the pump
         dc03=25;          //cabinet fan (blow over cooling coils) Turned Off
      }    //within the boundaries
}

//=== Cabinet Control Code ===^^^


//=== Fermenter 1 Control Code ===VVV
if (Device1==1) { //Fermenter is  installed we are controling the temps
    if (tempF5>sp01up) {        //make it cool
    // 1.) turn on pump 2.) turn on valves for redirection 3.) Open Flow to ferm 
      digitalWrite(CRedirectRelay4Pin25, LOW); //Turn off cabinet coils and Run through fermenter coils. for test low
      digitalWrite(Ferm1CRelay5Pin26, LOW);  //turns on cold water flow
      digitalWrite(Ferm1HRelay6Pin27, HIGH); //Close heater valves to fermenter coils
      ferm01cooler=1;
      ferm01heater=0;
    }    //make it cool
    
    if (tempF5<sp01Down) {
      // 1.) turn on pump 2.) turn off cabnit redirection 3.) open flow to fermentation
      digitalWrite(HeaterRelay2Pin23, LOW); //Turn off cabinet redirection
      digitalWrite(Ferm1HRelay6Pin27, LOW); //open heater valves to fermenter coils
      digitalWrite(Ferm1CRelay5Pin26, HIGH);  //turns off cold water flow
      ferm01heater=1;
      ferm01cooler=0;
    }      //make it hot
    
    if ((tempF5<sp01up) && (tempF5>sp01Down)) { //within upper (hot) and lower (cold) turn off fermenter coils
      digitalWrite(Ferm1HRelay6Pin27, HIGH); //stop Hot flow to fermenter 1
      digitalWrite(Ferm1CRelay5Pin26, HIGH); //stop Cold flow to fermenter 1
      ferm01heater=0;
      ferm01cooler=0;
    }    //within the boundaries
}
//=== Fermenter 1 Control Code ===^^^

//=== Fermenter 2 Control Code ===VVV
  if (Device2==1) { //Fermenter is  installed we are controling the temps
  
    if (tempF6 > sp02up) {     //make it cool
    // 1.) turn on pump 2.) turn on valves for redirection 3.) Open Flow to ferm 
      digitalWrite(CRedirectRelay4Pin25, LOW); //Turn off cabinet coils and Run through fermenter coils.
      digitalWrite(Ferm2CRelay7Pin28, LOW);  //turns on cold water flow
      digitalWrite(Ferm2HRelay8Pin29, HIGH); //Close heater valves to fermenter coils
      ferm02cooler=1;
      ferm02heater=0;
    }       //make it cool
    
    if (tempF6<sp02Down) {
     // 1.) turn on pump 2.) turn off cabnit redirection 3.) open flow to fermentation
      digitalWrite(HeaterRelay2Pin23, LOW); //Turn off cabinet redirection
      digitalWrite(Ferm2HRelay8Pin29, LOW); //open heater valves to fermenter coils
      digitalWrite(Ferm2CRelay7Pin28, HIGH);  //turns off cold water flow
      ferm02heater=1;
      ferm02cooler=0;
    }       //make it hot
    
    if ((tempF6<sp02up) && (tempF6>sp02Down)) {
      digitalWrite(Ferm2HRelay8Pin29, HIGH); //stop Hot flow to fermenter 1
      digitalWrite(Ferm2CRelay7Pin28, HIGH); //stop Cold flow to fermenter 1
      ferm02heater=0;
      ferm02cooler=0;
    }    //within the boundaries
 }

//=== Fermenter 2 Control Code ===^^^



//=== Fermenter 3 Control Code ===VVV
  if (Device3==1) { //Fermenter is  installed we are controling the temps
    
    if (tempF7>sp03up) {    //make it cool
    // 1.) turn on pump 2.) turn on valves for redirection 3.) Open Flow to ferm 
      digitalWrite(CRedirectRelay4Pin25, LOW); //Turn off cabinet coils and Run through fermenter coils.
      digitalWrite(Ferm3CRelay9Pin30, LOW);  //turns on cold water flow
      digitalWrite(Ferm3HRelay10Pin31, HIGH); //Close heater valves to fermenter coils
      ferm03cooler=1;
      ferm03heater=0;
    }       //make it cool
    
    if (tempF7<sp03Down) {  //make it hot
    // 1.) turn on pump 2.) turn off cabnit redirection 3.) open flow to fermentation
      digitalWrite(HeaterRelay2Pin23, LOW); //Turn off cabinet redirection
      digitalWrite(Ferm3HRelay10Pin31, LOW); //open heater valves to fermenter coils
      digitalWrite(Ferm3CRelay9Pin30, HIGH);  //turns off cold water flow
      ferm03heater=1;
      ferm03cooler=0;    
    }       //make it hot
    
    if ((tempF7<sp03up) && (tempF7>sp03Down)) {
      digitalWrite(Ferm3HRelay10Pin31, HIGH); //stop Hot flow to fermenter 1
      digitalWrite(Ferm3CRelay9Pin30, HIGH); //stop Cold flow to fermenter 1
      ferm03heater=0;
      ferm03cooler=0;
    }    //within the boundaries
}

//=== Fermenter 3 Control Code ===^^^

//=== Turning on or off the pumps ===VVV
      Ferm01Cold=cabcooler+ferm01cooler+ferm02cooler+ferm03cooler;
      Ferm01Hot=cabheater+ferm01heater+ferm02heater+ferm03heater;

      if (Ferm01Cold!=0) {  //someone needs the pump
         digitalWrite(CPumpRelay3Pin24, LOW); //turn on cold pump
          dc03=180;
      }
      
      if (Ferm01Cold==0) { // no one needs pump
         digitalWrite(CPumpRelay3Pin24, HIGH); //turn off cold pump
         dc03=25;
      }      
      
      if (Ferm01Hot!=0) {  //someone needs the pump
         digitalWrite(HPumpRelay1Pin22, LOW); // turn on hot pump
         dc03=180;
      }
      
      if (Ferm01Hot==0) {  // no one needs pump
         digitalWrite(HPumpRelay1Pin22, HIGH); // turn off hot pump
         dc03=25;
      }      



      /*

//=== Turning on or off the pumps ===^^^

//=== Fermenter Control Code ===^^^


// === Command  ===VVV
From RPi perspective

0000 Nothing

Read
0001 Status
0010 tempf
0011 tempc
0100 Setpoint
0101 Sequence 
0110 Alarm
0111 Open
1000 Open
1001 Open
1010 Open
1011 Open
1100 Open
1101 Open
1110 Reboot Arduino
1111 Reboot Pi

//===================== VVV Strings For Status Reading Commands VVV
String Sequences;
String TemperF;
String TemperC;
String SetPoints1;
String Alarm;
String Fanns;

//===================== ^^^ Strings For Status Reading Commands ^^^


  if ((Command04Pin47=high)|| (Command03Pin46=high)|| (Command02Pin45=high)|| (Command01Pin44=high)) {
      if (Command04Pin47=low)&& (Command03Pin46=low)&& (Command02Pin45=low)&& (Command01Pin44=high) {  //0001  Status
        Serial.print(years);Serial.print(",");Serial.print(months);Serial.print(",");
        Serial.print(weeks);Serial.print(",");Serial.print(days);Serial.print(",");
        Serial.print(hours);Serial.print(",");Serial.print(minutes);Serial.println(0,0);
      } //0001  Status
 
      if (Command04Pin47=low)&& (Command03Pin46=low)&& (Command02Pin45=high)&& (Command01Pin44=low) {  //0010 Temp F
        Serial.print(tempF0);Serial.print(",");Serial.print(tempF1);Serial.print(",");
        Serial.print(tempF2);Serial.print(",");Serial.print(tempF3);Serial.print(",");
        Serial.print(tempF4);Serial.print(",");Serial.print(tempF5);Serial.print(",");
        Serial.print(tempF6);Serial.print(",");Serial.print(tempF7);Serial.print(",");
        Serial.print(tempF8);Serial.print(",");Serial.print(tempF9);Serial.println(0,0);
      } //0010  TempF
 
      if (Command04Pin47=low)&& (Command03Pin46=low)&& (Command02Pin45=High)&& (Command01Pin44=high) {  //0011 Temp C

        Serial.print(tempC0);Serial.print(",");Serial.print(tempC1);Serial.print(",");
        Serial.print(tempC2);Serial.print(",");Serial.print(tempC3);Serial.print(",");
        Serial.print(tempC4);Serial.print(",");Serial.print(tempC5);Serial.print(",");
        Serial.print(tempC6);Serial.print(",");Serial.print(tempC7);Serial.print(",");
        Serial.print(tempC8);Serial.print(",");Serial.print(tempC9);Serial.println(0,0);
      } //0011  TempC

      if (Command04Pin47=low)&& (Command03Pin46=high)&& (Command02Pin45=low)&& (Command01Pin44=low) { // 0100 Setpoint
        Serial.print(setpoint01);Serial.print(",");
        Serial.print(setpoint02);Serial.print(",");
        Serial.print(setpoint03);Serial.println(0,0);
      } //0100  Setpoint
 
      if (Command04Pin47=low)&& (Command03Pin46=high)&& (Command02Pin45=low)&& (Command01Pin44=high) { //0101  Sequence
        Serial.print(F1seq);Serial.print(",");
        Serial.print(F2seq);Serial.print(",");
        Serial.print(F3seq);Serial.println(0,0);               
      } //0101  Sequence
 
      if (Command04Pin47=low)&& (Command03Pin46=high)&& (Command02Pin45=high)&& (Command01Pin44=low) {  //0110  Alarms } //0110  Alarms
 
      if (Command04Pin47=low)&& (Command03Pin46=high)&& (Command02Pin45=high)&& (Command01Pin44=high) { //0111  Open } //0111 Open
 
      if (Command04Pin47=high)&& (Command03Pin46=low)&& (Command02Pin45=low)&& (Command01Pin44=low)   { //1000  Open } //1000 Open
 
      if (Command04Pin47=high)&& (Command03Pin46=low)&& (Command02Pin45=low)&& (Command01Pin44=high)  { //1001  Open } //1001 Open
 
      if (Command04Pin47=high)&& (Command03Pin46=low)&& (Command02Pin45=high)&& (Command01Pin44=low)  { //1010  Open } //1010 Open
  
      if (Command04Pin47=high)&& (Command03Pin46=low)&& (Command02Pin45=high)&& (Command01Pin44=high) { //1011  Open } //1011 Open
 
      if (Command04Pin47=high)&& (Command03Pin46=high)&& (Command02Pin45=low)&& (Command01Pin44=low)  { //1100  Open } //1100 Open
   
      if (Command04Pin47=high)&& (Command03Pin46=high)&& (Command02Pin45=low)&& (Command01Pin44=high) { //1101  Open } //1101 Open
 
      if (Command04Pin47=high)&& (Command03Pin46=high)&& (Command02Pin45=high)&& (Command01Pin44=low) { //1110  Reboot Arduino
         digitalWrite(RebootArdPin39Relay15, LOW);
      } //1110 Reboot Arduino
 
      if (Command04Pin47=high)&& (Command03Pin46=high)&& (Command02Pin45=high)&& (Command01Pin44=high){ //1111  Reboot Pi
         digitalWrite(RebootRpiePin40Relay16, LOW);
      } //1111 Reboot Pi


  } //end of command code if statement

// === Command  ===^^^

*/

}

}//== End Of Void Loop ===




