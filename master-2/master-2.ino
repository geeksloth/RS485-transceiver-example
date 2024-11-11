#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 0;


//  use a 2nd Serial port.
RS485 rs485(&Serial2, sendPin, deviceID);


//  times of last requests.
uint32_t lastT = 0;
uint32_t lastH = 0;


//  for receiving (must be global)
uint8_t ID;
uint8_t arr[32];
uint8_t len;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RS485_LIB_VERSION: ");
  Serial.println(RS485_LIB_VERSION);

  Serial2.begin(38400);
}


void loop()
{
  if (millis() - lastT >= 3000)
  {
    lastT = millis();
    char msg[] = "Get Temperature";
    rs485.send(1, (uint8_t *)msg, strlen(msg));
    Serial.print("SEND: ");
    Serial.println(msg);
  }

  if (millis() - lastH >= 7000)
  {
    lastH = millis();
    char msg[] = "Get Humidity";
    rs485.send(1, (uint8_t *)msg, strlen(msg));
    Serial.print("SEND: ");
    Serial.println(msg);
  }

  if (rs485.receive(ID, arr, len))
  {
    arr[len] = 0;
    Serial.print("RECV:\t");
    Serial.print(ID);
    Serial.print("\t");
    Serial.println((char*) arr);
  }
}