

int TemperF[10];

int tempF0;
int tempF1;
int tempF2;
int tempF3;
int tempF4;
int tempF5;
int tempF6;
int tempF7;
int tempF8;
int tempF9;


void setup (void){
 Serial.begin(115200);
  Serial.println(" :: Start :: Array Test");
}
void loop (){

tempF0=1;
 tempF1=2;
 tempF2=3;
 tempF3=4;
 tempF4=5;
 tempF5=6;
 tempF6=7;
 tempF7=8;
 tempF8=9;
 tempF9=10;

TemperF [0]=tempF0;
TemperF [1]=tempF1;
TemperF [2]=tempF2;
TemperF [3]=tempF3;
TemperF [4]=tempF4;
TemperF [5]=tempF5;
TemperF [6]=tempF6;
TemperF [7]=tempF7;
TemperF [8]=tempF8;
TemperF [9]=tempF9;
Serial.println(0,0);
Serial.println(0,0);
        Serial.print(tempF0);Serial.print(",");Serial.print(tempF1);Serial.print(",");
        Serial.print(tempF2);Serial.print(",");Serial.print(tempF3);Serial.print(",");
        Serial.print(tempF4);Serial.print(",");Serial.print(tempF5);Serial.print(",");
        Serial.print(tempF6);Serial.print(",");Serial.print(tempF7);Serial.print(",");
        Serial.print(tempF8);Serial.print(",");Serial.print(tempF9);
Serial.println(0,0);
Serial.println(0,0);
Serial.println("test");
}
