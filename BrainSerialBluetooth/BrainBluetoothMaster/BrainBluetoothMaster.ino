#include <Brain.h>
#include<SoftwareSerial.h>

Brain brain(Serial);
SoftwareSerial HC_05(10, 11); // RX | TX 
int send= 0;
void setup() {
    // Start the hardware serial.
    
    HC_05.begin(9600); 
    HC_05.write("1");
    Serial.begin(9600);
 
    
}

void loop() {
   
 
    if (brain.update()) {
        send = brain.readAttention();
        if (brain.readSignalQuality()){
           Serial.println("HELMET NOT ON");
        }
        if(send > 45){
          HC_05.write(2);
        }
        else HC_05.write(1);
          
        Serial.println(brain.readErrors());
        Serial.println(brain.readCSV());
    }

    Serial.write(1);
    delay(1000);
    Serial.write(2);

   
}
