#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 31;     //  0 for master, 1 - 31 for slaves
const uint8_t targetID = 0;
uint32_t lastCommand = 0;
int counter = 0;

RS485 rs485(&Serial, sendPin, deviceID);  //  uses default deviceID

void setup() {
  Serial.begin(115200);
}

void loop() {
    if (rs485.available() > 0) {                // check if rs485 is being used by some other device
        String text = (String)rs485.readString();
        if (text.startsWith(String(deviceID))) {      // some client is connecting to the master
            Serial.print("received: ");
            Serial.println(text);
            rs485.flush();
        }
    }
    
    if (millis() - lastCommand >= 1000) {       // send a command every 10 seconds
        lastCommand = millis();
        String cmd = String(targetID);
        cmd += ",";
        cmd += String(counter);         // send a command to the slave id 1
        cmd += ",";
        cmd += "I'm UNO.";
        counter++;
        while (rs485.available());              // wait until rs485 is not being used
        rs485.print(cmd);
        Serial.print("sent: ");
        Serial.println(cmd);
    }
    
}