//
// TestMax7219_2
//
#include <SPI.h>
#include "LedMatrix.h"

#define NUMBER_OF_DEVICES 1
#define CS_PIN D8
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

void setup() {
  Serial.begin(115200); // For debugging output
  ledMatrix.init();
  ledMatrix.setIntensity(4); // range is 0-15
}

void loop() {
  ledMatrix.clear();
  ledMatrix.commit(); // commit send buffer to the displays
  delay(1000);
  Send2MAX7129(5, 1, 0);
  Send2MAX7129(4, 2, 0);
  Send2MAX7129(3, 3, 1);
  Send2MAX7129(2, 4, 0);
  Send2MAX7129(1, 5, 0);
  delay(1000);
}

//===================================================
//===================================================
void Send2MAX7129(byte SegPosition, byte Value, bool dotDigit)
{ const static byte charTable [] =
  { B01111110, B00110000, B01101101, B01111001,
     B00110011, B01011011, B01011111, B01110000,
     B01111111, B01111011, B01110111, B00011111,
     B00001101, B00111101, B01001111, B01000111
  };
  
  Value = charTable[Value];
  if (dotDigit == 1) Value |= 0x80;
  digitalWrite(CS_PIN, LOW);
  SPI.transfer (SegPosition);
  SPI.transfer (Value);
  digitalWrite (CS_PIN, HIGH);
  Serial.print(Value);
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

