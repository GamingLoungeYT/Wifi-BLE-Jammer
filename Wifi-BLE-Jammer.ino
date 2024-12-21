#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFi.h>
#include <esp_wifi.h>

#define CE1_PIN 16
#define CSN1_PIN 15
#define CE2_PIN 22
#define CSN2_PIN 21

RF24 nrf24_1(CE1_PIN, CSN1_PIN);
RF24 nrf24_2(CE2_PIN, CSN2_PIN);

uint8_t wifiChannel = 1;

const uint8_t nrfChannels[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  initRFModules();
}

void loop() {

  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  uint8_t nrfChannel1 = nrfChannels[(wifiChannel - 1) % 6];
  uint8_t nrfChannel2 = nrfChannels[6 + ((wifiChannel - 1) % 6)];

  nrf24_1.setChannel(wifiChannel);
  nrf24_2.setChannel(wifiChannel);

  sendNoisePacket(nrf24_1, "Module 1");
  sendNoisePacket(nrf24_2, "Module 2");

  wifiChannel++;
  if (wifiChannel > 12) wifiChannel = 1;
}

void initRFModules() {
  if (!nrf24_1.begin()) {
    Serial.println("nRF24L01+ Module 1 initialization failed!");
    while (1);
  }
  nrf24_1.setAutoAck(false);
  nrf24_1.setRetries(0, 0); 
  nrf24_1.setPALevel(RF24_PA_MAX);

  if (!nrf24_2.begin()) {
    Serial.println("nRF24L01+ Module 2 initialization failed!");
    while (1);
  }
  nrf24_2.setAutoAck(false);
  nrf24_2.setRetries(0, 0); 
  nrf24_2.setPALevel(RF24_PA_MAX);
}

void sendNoisePacket(RF24& nrf, const char* moduleName) {
  uint8_t noisePacket[32];
  memset(noisePacket, 0xFF, sizeof(noisePacket));

  nrf.startWrite(noisePacket, sizeof(noisePacket), false);
  Serial.printf("Noise sent on %s: Wi-Fi channel %d (nRF channel %d)\n", 
                moduleName, wifiChannel, nrf.getChannel());

  delay(5);
  nrf.stopListening();
}
