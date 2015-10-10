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
Serial.print(" Set up begin test of Lager sequence");
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


 
if (TCHourTrack03==0) {TCHourTrack03=hours;}

  if (TCHourTrack03!=hours) { //It is a diferent hour||an hour has past
    ++TCHourCount03;
    TCHourTrack03=hours; 
    Serial.println(0,0);
    delay(1000);
    //++F3seqHour;
   }
 //Lager Ferm03      
  if (5==5)  { //Begin Lager
Serial.print("Begin Lager");
    Serial.println(0,0);
    Serial.print("Track = ");
    Serial.print(TCHourTrack03);
    Serial.println(0,0);
    Serial.print("Count = ");
    Serial.print(TCHourCount03);
        Serial.println(0,0);
    Serial.print("F3seq = ");
    Serial.print(F3seq);
        Serial.println(0,0);
        Serial.print("Setpoint = ");
        Serial.print(setpoint03);
        Serial.println(0,0);
        delay(1000);
    
   if ((TCHourCount03<8) && (F3seq==0)) { //start sequence 03 Lager#1
     F3seq=1;
     setpoint03=58;     
     Serial.print("hour count < 24 ");
         Serial.println(0,0);
   }
   
   if ((TCHourCount03==8) && (F3seq==1)) {  //dwell 1 68º
     // when tchour03 = 24 we are done with F3seq(1) and we need to we need to ramp
     // and to ramp we need to change setpoint03 -1º every 6 hours
     F3seq=2;
     TCHourCount03=0;
   }
   if ((TCHourCount03==6) && (F3seq==2)) {  //time to ramp -1º every 2 hours 15 times
Serial.println(0,0);
Serial.print("Ramp -1 deg every 2 hours");
Serial.println(0,0);
Serial.print("TCHourCount03 = ");
Serial.print(TCHourCount03);
Serial.println(0,0);
     TCHourCount03=0;
     --setpoint03;
     ++F3seqHour;
       if (F3seqHour==15) {
       F3seq=3;
       F3seqHour=0;
       TCHourCount03=0;
Serial.println(0,0);
Serial.print(" Ramp complete ");
       }    //SEQ2 (ramp) has finished
   }    //ramp is complet
   
    if ((TCHourCount03==84) && (F3seq==3)) {    // dwell 2 62º
      F3seq=4;
      TCHourCount03=0;
      Serial.println(0,0);
Serial.print(" 62 deg 84 hour Dwell complete ");
      Serial.println(0,0);
    }
//========ramp 2 to 72º
    if ((TCHourCount03==9) && (F3seq==4)) {  //time to ramp -1º every 12 hours 8 times to 72º
         TCHourCount03=0;
         --setpoint03;
         ++F3seqHour;
         Serial.println(0,0);
Serial.print("Ramp +1 deg every 12 hours");
Serial.println(0,0);
           if (F3seqHour==8) {
           F3seq=5;
           F3seqHour=0;
           TCHourCount03=0;
           }    //SEQ4 (ramp) has finished
     }    //ramp is complete
    if ((TCHourCount03==24) && (F3seq==5)) {    // dwell @ 35º for 24 hours
      F3seq=6;
      TCHourCount03=0;
      Serial.print("Lager Sequence is done");
    }
    //========ramp 3 to 68º
    if ((TCHourCount03==2) && (F3seq==6)) {  //time to ramp +1.5º every 2 hours 33 times to 72º
         TCHourCount03=0;
         setpoint03+1.5;
         ++F3seqHour;
         Serial.println(0,0);
Serial.print("Ramp +1 deg every 12 hours");
Serial.println(0,0);
           if (F3seqHour==33) {
           F3seq=7;
           F3seqHour=0;
           TCHourCount03=0;
           }    //SEQ (ramp) has finished
     }    //ramp is complete

  }  // End Lager #2

}
