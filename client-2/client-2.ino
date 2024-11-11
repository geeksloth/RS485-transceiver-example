#include "Arduino.h"
#include "RS485.h"


const uint8_t sendPin  = 4;
const uint8_t deviceID = 1;


//  use a 2nd Serial port.
RS485 rs485(&Serial2, sendPin, deviceID);


//  for receiving (must be global)
uint8_t ID;
uint8_t buffer[32];
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
  if (rs485.receive(ID, buffer, len))
  {
    buffer[len] = 0;
    Serial.print("RECV: ");
    Serial.println((char*) buffer);

    if (strcmp((char*)buffer, "Get Humidity") == 0)
    {
      int humidity = 50 + random(10);
      sprintf((char*)buffer, "HUM: %d", humidity);
      rs485.send(ID, buffer, strlen((char*)buffer));
    }
    if (strcmp((char*)buffer, "Get Temperature") == 0)
    {
      int temperature = 15 + random(10);
      sprintf((char*)buffer, "TEM: %d", temperature);
      rs485.send(ID, buffer, strlen((char*)buffer));
    }
  }
}
