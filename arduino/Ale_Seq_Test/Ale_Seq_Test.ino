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

void setup(void) {
    Serial.begin(115200);
Serial.print(" Set up begin test of ale sequence");
    Serial.println(0,0);
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



 
if (TCHourTrack01==0) {TCHourTrack01=hours;}

  if (TCHourTrack01!=hours) { //It is a diferent hour||an hour has past
    ++TCHourCount01;
    TCHourTrack01=hours; 
    Serial.println(0,0);
    delay(1000);
    //++F1seqHour;
   }
 //Ale Ferm01      
  if (5==5)  { //Begin Ale
Serial.print("Begin ale");
    Serial.println(0,0);
    Serial.print("Track = ");
    Serial.print(TCHourTrack01);
    Serial.println(0,0);
    Serial.print("Count = ");
    Serial.print(TCHourCount01);
        Serial.println(0,0);
    Serial.print("F1seq = ");
    Serial.print(F1seq);
        Serial.println(0,0);
        Serial.print("Setpoint = ");
        Serial.print(setpoint01);
        Serial.println(0,0);
        delay(1000);
    
   if ((TCHourCount01<24) && (F1seq==0)) { //start sequence 01Ale#1
     F1seq=1;
     setpoint01=68;     
     Serial.print("hour count < 24 ");
         Serial.println(0,0);
   }
   
   if ((TCHourCount01==24) && (F1seq==1)) {  //dwell 1 68º
     // when tchour01 = 24 we are done with F1seq(1) and we need to we need to ramp
     // and to ramp we need to change setpoint01 -1º every 6 hours
     F1seq=2;
     TCHourCount01=0;
   }
   if ((TCHourCount01==6) && (F1seq==2)) {  //time to ramp -1º every 6 hours 6 times
Serial.println(0,0);
Serial.print("Ramp -1 deg every 6 hours");
Serial.println(0,0);
Serial.print("TCHourCount01 = ");
Serial.print(TCHourCount01);
Serial.println(0,0);
     TCHourCount01=0;
     --setpoint01;
     ++F1seqHour;
       if (F1seqHour==6) {
       F1seq=3;
       F1seqHour=0;
       TCHourCount01=0;
Serial.println(0,0);
Serial.print(" Ramp complete ");
       }    //SEQ2 (ramp) has finished
   }    //ramp is complet
   
    if ((TCHourCount01==84) && (F1seq==3)) {    // dwell 2 62º
      F1seq=4;
      TCHourCount01=0;
      Serial.println(0,0);
Serial.print(" 62 deg 84 hour Dwell complete ");
      Serial.println(0,0);
    }
//========ramp 2 to 72º
    if ((TCHourCount01==9) && (F1seq==4)) {  //time to ramp +1º every 9 hours 11 times to 72º
         TCHourCount01=0;
         ++setpoint01;
         ++F1seqHour;
         Serial.println(0,0);
Serial.print("Ramp +1 deg every 9 hours");
Serial.println(0,0);
           if (F1seqHour==11) {
           F1seq=5;
           F1seqHour=0;
           TCHourCount01=0;
           }    //SEQ4 (ramp) has finished
     }    //ramp is complete
    if ((TCHourCount01==48) && (F1seq==5)) {    // dwell 3 62º for 48 hours
      F1seq=6;
      TCHourCount01=0;
      Serial.print("Ale Sequence is done");
    }

  }  // End Ale #2

}
