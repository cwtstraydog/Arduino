/* 04-30-2015 working code to read from the TMP36F IC
  05-01-2015 add 3 more TMP36F reading
  ------2015 change code to read TMP36F from 1 pin through relay so only one pin is needed
      --why do that?? (Choice is 8(?) TMP times 3 lines each one 24 wires
*/


/* 06/1/2015 Intergrate fan control into Brewhouse control

===============VVV Notes VVV

 06-01-2015 INserted basic code for one PWM channel Need three chanels 

===============^^^ Notes ^^^
*/
#define aref_voltage 5

//===================== VVV Fan Control Stuff VVV

unsigned int integerValue=0;  // Max value is 65535
unsigned int dc = 125;        // Fan Control Stuff
char incomingByte;            // Fan Control Stuff
unsigned long speed = 0;      // Fan Control Stuff

//===================== ^^^ Fan Control Stuff ^^^

//===================== VVV Temp Control Stuff VVV
int tempPin0 = A0;    //Fermentation 1
int tempPin1 = A1;    //Fermentation 2
int tempPin2 = A2;    //Fermentation 3
int tempPin3 = A3;    //Fermentation 4
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

//===================== ^^^ Temp Control Stuff ^^^



//===================== VVV Relay Control Stuff VVV

//===================== ^^^ Relay Control Stuff ^^^
 
void setup(void) {

  Serial.begin(115200);
  Serial.println(" :: Start :04-30-2015 13.30: Ver XXX.00.01 'reading from TMNP3'");
  Serial.println(" :: Start :: Inserted fan control code '06-01-2014 :: 1 ::H:: - 245 ::L::'");
  
 // Setting    For fan control             Prescale_factor
	TCCR0B = TCCR0B & 0b11111000 | 0x01; 

  pinMode(4, OUTPUT); //Enable the pin that timer0 controls

  OCR0B = 125;

  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); // init timer0 configure for fast PWM 





}

void loop(void) {
    OCR0B = dc;
  for(int i = 0; i < 400; i++) {  // 400 reads then average them out
    tempReading0 += analogRead(tempPin0);  // Reading thermal from TC1
/*    delay(1);
    tempReading1 += analogRead(tempPin1);
      delay(1);
    tempReading2 += analogRead(tempPin2);
      delay(1);
    tempReading3 += analogRead(tempPin3);
      delay(1);
    tempReading4 += analogRead(tempPin4);
      delay(1);
    tempReading5 += analogRead(tempPin5);
      delay(1);
    tempReading6 += analogRead(tempPin6);
      delay(1);
    tempReading7 += analogRead(tempPin7);
      delay(1);
    tempReading0 += analogRead(tempPin8);
      delay(1);
    tempReading1 += analogRead(tempPin9);
      delay(1);
    tempReading2 += analogRead(tempPin10);
      delay(1);
    tempReading3 += analogRead(tempPin11);
      delay(1);
    tempReading4 += analogRead(tempPin12);
      delay(1);
    tempReading5 += analogRead(tempPin13);
      delay(1);
    tempReading6 += analogRead(tempPin14);
      delay(1);
    tempReading7 += analogRead(tempPin15);
     */delay(1);  //why i dunno just seemed like the thing to do
  }
  
  avgTemp0 = tempReading0 / 400;  //Averageing the reads out
   /*avgTemp1 = tempReading1 / 400;
    avgTemp2 = tempReading2 / 400;
    avgTemp3 = tempReading3 / 400;
    avgTemp4 = tempReading4 / 400;
    avgTemp5 = tempReading5 / 400;
    avgTemp6 = tempReading6 / 400;
    avgTemp7 = tempReading7 / 400;
    avgTemp0 = tempReading8 / 400;
    avgTemp1 = tempReading9 / 400;
    avgTemp2 = tempReading10 / 400;
    avgTemp3 = tempReading11 / 400;
    avgTemp4 = tempReading12 / 400;
    avgTemp5 = tempReading13 / 400;
    avgTemp6 = tempReading14 / 400;
    avgTemp7 = tempReading15 / 400;
  */
  
  
  double mv0 = avgTemp0 * ((aref_voltage * 1000) / 1024); //millivolts per temp
  /*  double mv1 = avgTemp1 * ((aref_voltage * 1000) / 1024);
    double mv2 = avgTemp2 * ((aref_voltage * 1000) / 1024);
    double mv3 = avgTemp3 * ((aref_voltage * 1000) / 1024);
    double mv4 = avgTemp4 * ((aref_voltage * 1000) / 1024);
    double mv5 = avgTemp5 * ((aref_voltage * 1000) / 1024);
    double mv6 = avgTemp6 * ((aref_voltage * 1000) / 1024);
    double mv7 = avgTemp7 * ((aref_voltage * 1000) / 1024);
    double mv8 = avgTemp8 * ((aref_voltage * 1000) / 1024);
    double mv9 = avgTemp9 * ((aref_voltage * 1000) / 1024);
    double mv10 = avgTemp10 * ((aref_voltage * 1000) / 1024);
    double mv11 = avgTemp11 * ((aref_voltage * 1000) / 1024);
    double mv12 = avgTemp12 * ((aref_voltage * 1000) / 1024);
    double mv13 = avgTemp13 * ((aref_voltage * 1000) / 1024);
    double mv14 = avgTemp14 * ((aref_voltage * 1000) / 1024);
    double mv15 = avgTemp15 * ((aref_voltage * 1000) / 1024);
*/
  double tempC0 = mv0 / 20;  //converting milli volts to ºC
 /*   double tempC1 = mv1 / 20;
    double tempC2 = mv2 / 20;
    double tempC3 = mv3 / 20;
    double tempC4 = mv4 / 20;
    double tempC5 = mv5 / 20;
    double tempC6 = mv6 / 20;
    double tempC7 = mv7 / 20; 
    double tempC8 = mv8 / 20;
    double tempC9 = mv9 / 20;
    double tempC10 = mv10 / 20;
    double tempC11 = mv11 / 20;
    double tempC12 = mv12 / 20;
    double tempC13 = mv13 / 20;
    double tempC14 = mv14 / 20;
    double tempC15 = mv15 / 20;
*/
  double tempF0 = (tempC0 / 5 * 9) + 32.0;    //Converting ºC to ºF
 /* double tempF1 = (tempC1 / 5 * 9) + 32.0;
  double tempF2 = (tempC2 / 5 * 9) + 32.0;
  double tempF3 = (tempC3 / 5 * 9) + 32.0;
  double tempF4 = (tempC4 / 5 * 9) + 32.0;
  double tempF5 = (tempC5 / 5 * 9) + 32.0;
  double tempF6 = (tempC6 / 5 * 9) + 32.0;
  double tempF7 = (tempC7 / 5 * 9) + 32.0;
  double tempF8 = (tempC8 / 5 * 9) + 32.0;
  double tempF9 = (tempC9 / 5 * 9) + 32.0;
  double tempF10 = (tempC10 / 5 * 9) + 32.0;
  double tempF11 = (tempC11 / 5 * 9) + 32.0;
  double tempF12 = (tempC12 / 5 * 9) + 32.0;
  double tempF13 = (tempC13 / 5 * 9) + 32.0;
  double tempF14 = (tempC14 / 5 * 9) + 32.0;
  double tempF15 = (tempC15 / 5 * 9) + 32.0;
*/


Serial.println();
// this is for programing only this will be replaced with RaspPi information later
  Serial.println(0, 0);
  Serial.print("Fermentation 1 ");    Serial.print(tempC0); Serial.print(" C ");
  Serial.println(0, 0);
  Serial.print("Fermentation 1 ");    Serial.print(tempF0); Serial.print(" F ");      
/*Serial.print("Fermentation 5 ");    Serial.print(tempF4); Serial.print(" ºF ");      
Serial.print("Fermentation 6 ");    Serial.print(tempF5); Serial.print(" ºF ");      
Serial.print("Fermentation 7 ");    Serial.print(tempF6); Serial.print(" ºF ");      
Serial.print("Fermentation 8 ");    Serial.print(tempF7); Serial.print(" ºF ");      

    Serial.print(tempF8);
    Serial.print(tempF9);
    Serial.print(tempF10);
    Serial.print(tempF11);
    Serial.print(tempF12);
    Serial.print(tempF13);
    Serial.print(tempF14);
    Serial.print(tempF15);
    Serial.println(" F");

*/  tempReading0 = 0;
    /*tempReading1 = 0;
    tempReading2 = 0;
    tempReading3 = 0;
    tempReading4 = 0;
    tempReading5 = 0;
    tempReading6 = 0;
    tempReading7 = 0;
    tempReading8 = 0;
    tempReading9 = 0;
    tempReading10 = 0;
    tempReading11 = 0;
    tempReading12 = 0;
    tempReading13 = 0;
    tempReading14 = 0;
    tempReading15 = 0;
      */ 
      
 /*========================== VVV Serial input Code for RaspPi Control Later  VVV
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
========================== ^^^ Serial input Code for raspPi Control Later  ^^^
     
    */  
      
  delay(1000);  //wait 1 second

}

