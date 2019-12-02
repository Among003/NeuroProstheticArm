#include <Brain.h>
#include<SoftwareSerial.h>

Brain brain(Serial);
SoftwareSerial HC_05(8, 9); // RX | TX 
int send= 0;
void setup() {
    // Start the Software serial.
    HC_05.begin(9600); 
    Serial.begin(9600);
}

void loop() {
 
    if (brain.update()) {
        send = brain.readAttention();
        if (brain.readSignalQuality() > 0){
           Serial.println("HELMET NOT ON");
           HC_05.write(100);
        }
        else if(send > 75){
          HC_05.write(3);
        }
        else if (send > 45)
          HC_05.write(2);
        else  HC_05.write(1);

        Serial.println(brain.readErrors());
        Serial.println(brain.readCSV());
    }

   
}
