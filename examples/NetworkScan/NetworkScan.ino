/*
 * WiFlyHQ Example NetworkScan.ino
 *
 * This sketch shows how you can scan for networks.
 *
 * (c) 2014, Arno Moonen.
 */

#include <WiFlyHQ.h>

WiFly wifly;

void setup()
{
  char buf[32];

  Serial.begin(9600);
  while(!Serial);
  Serial.println(F("START"));
  Serial1.begin(9600);
  if (!wifly.begin(&Serial1, &Serial)) {
    Serial.println(F("FAILED"));
    terminal();
  }

  scan();
}

void loop()
{
  terminal();
}

void scan() {
  Serial.print(F("SCAN\t"));
  Serial.println(wifly.performScan(), DEC);

  uint8_t ch;
  uint8_t rssi;
  uint8_t sec;
  uint16_t capa;
  uint8_t wpa;
  uint8_t wps;
  uint8_t mac[6];
  char ssid[33];

  while(wifly.getNextScanResult(&ch,&rssi,&sec,&capa,&wpa,&wps,mac,ssid) > 0) {
    Serial.println(F("--- --- --- ---"));
    Serial.print(F("SSID\t"));
    Serial.println(ssid);
    Serial.print(F("MAC\t"));
    for(uint8_t x = 0; x < 6; x++) {
      if(mac[x] <= 0x0F) {
        Serial.print('0');
      }
      Serial.print(mac[x], HEX);
    }
    Serial.println();
    Serial.print(F("CHAN\t"));
    Serial.println(ch, DEC);
    Serial.print(F("RSS\t-"));
    Serial.println(rssi, DEC);
    Serial.print(F("CAP\t"));
    Serial.println(capa, HEX);
    Serial.print(F("WPA\t"));
    Serial.println(wpa, HEX);
    Serial.print(F("WPS\t"));
    Serial.println(wps, HEX);
  }
  Serial.println(F("--- --- --- ---"));
  wifly.endScan();
  Serial.println();
  
}

/* Connect the WiFly serial to the serial monitor. */
void terminal()
{
  while (1) {
    if (wifly.available() > 0) {
      Serial.write(wifly.read());
    }

    if (Serial.available() > 0) {
      wifly.write(Serial.read());
    }
  }
}

