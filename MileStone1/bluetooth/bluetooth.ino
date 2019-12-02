#include <SoftwareSerial.h>

SoftwareSerial HC_05(8,9); //Rx, Tx



char x = 0;
void setup() 
{ 
 HC_05.begin(9600);  
 Serial.begin(9600); 
} 
void loop() 
{ 
 if (Serial.available()){
   x = Serial.read();
    HC_05.write(x);
 }
 delay(1000);
}  
