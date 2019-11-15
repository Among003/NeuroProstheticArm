/*   
HC05 - Bluetooth AT-Command mode  
modified on 10 Feb 2019 
by Saeed Hosseini 
https://electropeak.com/learn/ 
*/ 
#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(10, 11); // RX | TX 
int flag = 0; 
int LED = 8; 
void setup() 
{   
 Serial.begin(9600); 
 MyBlue.begin(9600); 
 MyBlue.write("1");
 pinMode(LED, OUTPUT); 
 Serial.println("Ready to connect\nDefualt password is 1234 or 000"); 
} 
void loop() 
{ 
 if (MyBlue.available()){
    Serial.println("begin read");
    flag = MyBlue.read()-48; 
    Serial.println(flag);
    MyBlue.write("20");
 }
  Serial.println(flag);
 Serial.println("Flag check");
 
 if (flag == 1) 
 { 
   digitalWrite(LED, HIGH); 
   Serial.println("LED On"); 
 } 
 else if (flag == 0) 
 { 
   digitalWrite(LED, LOW); 
   Serial.println("LED Off"); 
  
  
 } 

delay(1000);


}  
