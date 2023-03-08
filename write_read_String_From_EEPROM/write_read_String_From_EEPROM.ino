#include <EEPROM.h>

int eepromOffset = 0;

void setup() {
  Serial.begin(9600);

  // Sensor values float
  float t = 32.000;
  float h = 84.750;

  // Write in EEPROM
  String strT = String(t);
  String strH = String(h);
  int str1AddrOffset = writeStringToEEPROM(eepromOffset, strT);
  writeStringToEEPROM(str1AddrOffset, strH);
}

void loop() {

  // Read from EEPROM
  String newStrT;
  String newStrH;
  
  int newStr1AddrOffset = readStringFromEEPROM(eepromOffset, &newStrT);
  readStringFromEEPROM(newStr1AddrOffset, &newStrH);
  
  Serial.println(newStrT);
  Serial.println(newStrH);
}

// ==========================================================================

int writeStringToEEPROM(int addrOffset, const String &strToWrite) {
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
  return addrOffset + 1 + len;
}

int readStringFromEEPROM(int addrOffset, String *strToRead) {
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}
