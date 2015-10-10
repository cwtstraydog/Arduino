// Sketch 07-11-2014
// Based on code from http://forum.arduino.cc/index.php/topic,17353.0.html
// this is using a gas detector to control fan speed.





const int propPin = 0;
const int methPin = 1;
const int carbPin = 2;
const int propFan = 6;
unsigned char speed;
unsigned int low = 1;
unsigned int high = 10;
unsigned int baseTime = 10;
int propIn, methIn, carbIn;

  
void setup() {
  Serial.begin(9600); 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}  

void loop() {
  
  char str[7];
                    
  propIn = analogRead(propPin);
  methIn = analogRead(methPin);
  carbIn = analogRead(carbPin);  
  
  sprintf(str, "%04d", propIn);
  Serial.print(str);

  sprintf(str, "%04d", methIn);
  Serial.print(str);

  sprintf(str, "%04d", carbIn);  
  Serial.print(str); 




  
  int inByte = Serial.read();  
  
  switch(inByte){
     case 'a':
       for (int i = 1; i < 1000; i++){
         digitalWrite(4,LOW);
         delayMicroseconds(90);
         digitalWrite(4,HIGH);
         delayMicroseconds(10);                
       }       
       break;
    
     case 'b':
       for (int i = 1; i < 1000; i++){
         digitalWrite(4,LOW);
         delayMicroseconds(65);
         digitalWrite(4,HIGH);
         delayMicroseconds(35);                
       }       
       break;
        
     case 'c':
       for (int i = 1; i < 1000; i++){
         digitalWrite(4,LOW);
         delayMicroseconds(35);
         digitalWrite(4,HIGH);
         delayMicroseconds(65);                
       }              
       break;
     
     case 'd':
       for (int i = 1; i < 1000; i++){
         digitalWrite(4,LOW);
         delayMicroseconds(10);
         digitalWrite(4,HIGH);
         delayMicroseconds(90);                
       }       
       break;
     
     case 'e':
       for (int i = 1; i < 1000; i++){
         digitalWrite(3, LOW);
         delayMicroseconds(90);
         digitalWrite(3, HIGH);
         delayMicroseconds(10);                
       }       
       break;
       
     case 'f':
       for (int i = 1; i < 1000; i++){
         digitalWrite(3,LOW);
         delayMicroseconds(65);
         digitalWrite(3,HIGH);
         delayMicroseconds(35);                
       }       
       break;
       
     case 'g':
       for (int i = 1; i < 1000; i++){
         digitalWrite(3,LOW);
         delayMicroseconds(35);
         digitalWrite(3,HIGH);
         delayMicroseconds(65);  
       }     
       break;
       
     case 'h':
       for (int i = 1; i < 1000; i++){
         digitalWrite(3,LOW);
         delayMicroseconds(10);
         digitalWrite(3,HIGH);
         delayMicroseconds(90);      
       } 
       break;
       
     case 'i':
       for (int i = 1; i < 1000; i++){
         digitalWrite(2,LOW);
         delayMicroseconds(90);
         digitalWrite(2,HIGH);
         delayMicroseconds(10);  
       }     
       break;
       
     case 'j':
       for (int i = 1; i < 1000; i++){
         digitalWrite(2,LOW);
         delayMicroseconds(65);
         digitalWrite(2,HIGH);
         delayMicroseconds(35);   
       }    
       break;
       
     case 'k':
       for (int i = 1; i < 1000; i++){
         digitalWrite(2,LOW);
         delayMicroseconds(35);
         digitalWrite(2,HIGH);
         delayMicroseconds(65);   
       }    
       break;
       
     case 'l':
       for (int i = 1; i < 1000; i++){
         digitalWrite(2,LOW);
         delayMicroseconds(10);
         digitalWrite(2,HIGH);
         delayMicroseconds(90);    
       }   
       break;
     
     case 'm':
       tone(13, 500, 1000);       
       break;
       
     default:
       if (propIn || methIn || carbIn > 500){         
         tone(13, 500, 1000);
       }
       int propFan = map(propIn, 0, 1023, 1, 9);
       
       for (int i = 1; i < 1000; i++){
         digitalWrite(4,LOW);
         delayMicroseconds(low*10);
         digitalWrite(4,HIGH);
         delayMicroseconds(high*10);                
       }
       
       speed = propFan;
       low = speed;
       high = baseTime - speed;             
  }
} 
