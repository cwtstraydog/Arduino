/* control of fermentation temp Started 4-23-2015
* By John Emig
* 2015
* written for 8 fermentation tanks 
* 2 pumps, 1 hot and 1 cold
* each tank has 4 valves 2 hot, 2 cold
*  (1 in 1 out (hot) 1 in 1 out (cold) so if one is open 
*   so must the other.
* there may come a time that the pumps may have to run continuosly
* then the pump pins will control redirect valves instead
* 04-23-2015 added relay control for thermal sensors
* TCR# controls a relay that connects a tmp37 sensor to the A0 pin
*/ 
unsigned int Status = 99;
char incomingByte;
unsigned int integerValue=0;

////////////////////
#define aref_voltage 3.3
int tempPin = A0;
////////////////////







////////////
long tempReading;
float avgTemp;
///////// TMP37 sensor setup


//22-53
int HpumpPin = 22;                 // Hpump connected to digital pin 22
int CpumpPin = 23;                 // Cpump connected to digital pin 23
//24-31 cold valves 
int Cvalve1Pin = 24;                 // Cvalve1 connected to digital pin 24
int Cvalve2Pin = 25;                 // Cvalve2 connected to digital pin 25
int Cvalve3Pin = 26;                 // Cvalve3 connected to digital pin 26
int Cvalve4Pin = 27;                 // Cvalve4 connected to digital pin 27
int Cvalve5Pin = 28;                 // Cvalve5 connected to digital pin 28
int Cvalve6Pin = 29;                 // Cvalve6 connected to digital pin 29
int Cvalve7Pin = 30;                 // Cvalve7 connected to digital pin 30
int Cvalve8Pin = 31;                 // Cvalve8 connected to digital pin 31
//32-39 Hot Valves
int Hvalve1Pin = 32;                 // HValve1 connected to digital pin 32
int Hvalve2Pin = 33;                 // HValve2 connected to digital pin 33
int Hvalve3Pin = 34;                 // HValve3 connected to digital pin 34
int Hvalve4Pin = 35;                 // HValve4 connected to digital pin 35
int Hvalve5Pin = 36;                 // HValve5 connected to digital pin 36
int Hvalve6Pin = 37;                 // HValve6 connected to digital pin 37
int Hvalve7Pin = 38;                 // HValve7 connected to digital pin 38
int Hvalve8Pin = 39;                 // HValve8 connected to digital pin 39
//41-48 TCR
int TCR1Pin = 41;                 // TCR1 connected to digital pin 41
int TCR2Pin = 42;                 // TCR2 connected to digital pin 42
int TCR3Pin = 43;                 // TCR3 connected to digital pin 43
int TCR4Pin = 44;                 // TCR4 connected to digital pin 44
int TCR5Pin = 45;                 // TCR5 connected to digital pin 45
int TCR6Pin = 46;                 // TCR6 connected to digital pin 46
int TCR7Pin = 47;                 // TCR7 connected to digital pin 47
int TCR8Pin = 48;                 // TCR8 connected to digital pin 48

 




void setup()
{
  
  Serial.begin(115200);
  Serial.println(" :: Start :07-31-2014 13.30: Ver XXX.00.01 'Using Timer Phase Shift PWM code'");
//    analogReference(EXTERNAL);
  //pinMode(Valve-pump, OUTPUT);      // sets the digital pin as output
  
  pinMode(HpumpPin, OUTPUT);                 // sets the Hot pump pin as output
  pinMode(CpumpPin, OUTPUT);                 // sets the cold pump pin as output
//24-31 cold valves 
  pinMode(Cvalve1Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 24
  pinMode(Cvalve2Pin, OUTPUT);                 //sets Cvalve2 connected as output pin 25
  pinMode(Cvalve3Pin, OUTPUT);                 //sets Cvalve3 connected as output pin 26
  pinMode(Cvalve4Pin, OUTPUT);                 //sets Cvalve4 connected as output pin 27
  pinMode(Cvalve5Pin, OUTPUT);                 //sets Cvalve5 connected as output pin 28
  pinMode(Cvalve6Pin, OUTPUT);                 //sets Cvalve6 connected as output pin 29
  pinMode(Cvalve7Pin, OUTPUT);                 //sets Cvalve7 connected as output pin 30
  pinMode(Cvalve8Pin, OUTPUT);                 //sets Cvalve8 connected as output pin 31
//32-39 Hot Valves
  pinMode(Hvalve1Pin, OUTPUT);                 //sets Hvalve1 connected as output pin 32
  pinMode(Hvalve2Pin, OUTPUT);                 //sets Hvalve2 connected as output pin 33
  pinMode(Hvalve3Pin, OUTPUT);                 //sets Hvalve3 connected as output pin 34
  pinMode(Hvalve4Pin, OUTPUT);                 //sets Hvalve4 connected as output pin 35
  pinMode(Hvalve5Pin, OUTPUT);                 //sets Hvalve5 connected as output pin 36
  pinMode(Hvalve6Pin, OUTPUT);                 //sets Hvalve6 connected as output pin 37
  pinMode(Hvalve7Pin, OUTPUT);                 //sets Hvalve7 connected as output pin 38
  pinMode(Hvalve8Pin, OUTPUT);                 //sets Hvalve8 connected as output pin 39
//41-48 TCR
  pinMode(TCR1Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 41
  pinMode(TCR2Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 42
  pinMode(TCR3Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 43
  pinMode(TCR4Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 44
  pinMode(TCR5Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 45
  pinMode(TCR6Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 46
  pinMode(TCR7Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 47
  pinMode(TCR8Pin, OUTPUT);                 //sets Cvalve1 connected as output pin 48
  
}

void loop()
{
 
 
 
 
 
 
  
 
  /////////////////////test code for tmp read
   /////////////////ennd test code for tmp read
  
  digitalWrite(Hvalve1Pin, LOW);   // sets the LED on
    Serial.println("V1 Open");
  delay(1000);                  // waits for a second

  digitalWrite(Hvalve1Pin, HIGH);    // sets the LED off
    Serial.println("V1 Closed");
  delay(1000);                  // waits for a second
  
  
  digitalWrite(Hvalve2Pin, LOW);   // sets the LED on
    Serial.println("V2 Open");
  delay(1000);                  // waits for a second

  digitalWrite(Hvalve2Pin, HIGH);    // sets the LED off
    Serial.println("V2 Closed");
  delay(1000);                  // waits for a second
  
  
  digitalWrite(Hvalve3Pin, LOW);   // sets the LED on
    Serial.println("V3 Open");
  delay(1000);                  // waits for a second

  digitalWrite(Hvalve3Pin, HIGH);    // sets the LED off
    Serial.println("V3 Closed");
  delay(1000);                  // waits for a second
  
  
}
