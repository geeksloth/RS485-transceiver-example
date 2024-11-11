#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 0;     //  0 for master, 1 - 31 for slaves
const uint8_t targetID = 2;     // target's ID
uint32_t lastCommand = 0;
int counter = 0;

RS485 rs485(&Serial2, sendPin, deviceID);

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() {
    if (rs485.available() > 0) {                // check if rs485 is being used by some other device
        String text = (String)rs485.readString();
        if (text.startsWith(String(deviceID))) {      // some client is connecting to the master
            Serial.print("received: ");
            Serial.println(text);
            rs485.flush();
            delay(100);
        }
    }
    
    if (millis() - lastCommand >= 1000) {       // send a command every 10 seconds
        lastCommand = millis();
        String cmd = String(targetID);
        cmd += ",";
        cmd += String(counter);         // send a command to the slave id 1
        cmd += ",";
        cmd += "I'm MEGA Master.";
        counter++;
        while (rs485.available());              // wait until rs485 is not being used
        delay(100);
        rs485.flush();
        rs485.print(cmd);
        delay(100);
        Serial.print("sent: ");
        Serial.println(cmd);
    }
}