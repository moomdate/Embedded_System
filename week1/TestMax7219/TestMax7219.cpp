#include <SPI.h>
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 1
#define CS_PIN D8
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

void setup() {
  Serial.begin(115200); // For debugging output
  ledMatrix.init();
  ledMatrix.setIntensity(4); // range is 0-15
  ledMatrix.clear();
  ledMatrix.commit(); // commit send buffer to the displays
}

void loop() {
  SendData2MAX7129(1, 0xff);
  delay(500);
  SendData2MAX7129(1, 0);
  delay(500);
}

//===================================================
// ##SegPosition >> 87654321 ##SegData >> tabcdefg
//===================================================
void SendData2MAX7129(byte SegPosition, byte SegData)
{ digitalWrite(CS_PIN, LOW);
  SPI.transfer (SegPosition);
  SPI.transfer (SegData);
  digitalWrite (CS_PIN, HIGH);
}

