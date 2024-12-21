# Wifi/BLE Jammer

This project demonstrates the use of ESP32 and nRF24L01 modules (or E01 modules) to create a Wifi/BLE jammer for educational and experimental purposes. The code is designed to operate on the 2.4GHz spectrum, and support for 433MHz is planned in future updates for applications like car keys.

---

## ⚠️ Disclaimer

This project is for educational purposes only. The use of this tool for unauthorized or malicious activities, such as disrupting legitimate communications, is illegal and unethical. Ensure compliance with all local laws and regulations before proceeding.

---

## Features

- **2.4GHz Band Jammer**: Operates on WiFi/BLE channels.
- **ESP32 Control**: Utilizes the ESP32's Wi-Fi capabilities for jamming.
- **Dual nRF24L01 Modules**: Generates noise packets on multiple channels simultaneously.
- **Modular Design**: Easily extendable to support additional frequencies like 433MHz.

---

## Hardware Requirements

- **ESP32 Board**
- **Two nRF24L01+ Modules** (or E01 modules)
- **Wiring**:
  - CE1_PIN: GPIO 16
  - CSN1_PIN: GPIO 15
  - CE2_PIN: GPIO 22
  - CSN2_PIN: GPIO 21

---

## Software Requirements

1. **Arduino IDE** with the following libraries installed:
   - [RF24 Library](https://github.com/nRF24/RF24)
   - ESP32 Board Package (Install via Arduino Board Manager)

2. Install the ESP32 board package:

---

## Setup Instructions

1. **Wiring**: Connect the nRF24L01 modules to the ESP32 using the specified pins.
2. **Upload Code**:
- Open the provided code in the Arduino IDE.
- Select the appropriate ESP32 board and COM port.
- Compile and upload the code to the ESP32.
3. **Power the Device**: Ensure the ESP32 and nRF24 modules are powered correctly.
4. **Monitor Logs**: Open the Serial Monitor at 115200 baud to view real-time operations.

---

## Code Overview

### Initialization
The `initRFModules()` function initializes both nRF24L01 modules with the following settings:
- Auto acknowledgment disabled.
- Maximum power output.
- No retries for sending packets.

### Main Loop
The main loop cycles through all Wi-Fi channels (1-12) and sends noise packets via the nRF24L01 modules:
- ESP32 sets the current Wi-Fi channel using `esp_wifi_set_channel`.
- Noise packets are sent through each module using the `sendNoisePacket` function.
- After sending on one channel, it increments the channel counter.

### Noise Packet Generation
The `sendNoisePacket` function:
- Fills a 32-byte array with `0xFF`.
- Sends it on the specified channel using the nRF24 module.
- Logs details to the Serial Monitor.

---

## Usage

1. Power on the ESP32 and ensure the nRF24 modules are connected.
2. Monitor the logs in the Serial Monitor to confirm noise is being sent.
3. Modify the `nrfChannels` array in the code to target specific frequencies if needed.

---

## Future Updates

- **433MHz Band Support**: To extend the jammer's capabilities to frequencies used by car keys and other devices.
- **Improved Channel Management**: More precise targeting of channels for specific use cases.

---

## Security and Legal Considerations

- **Responsible Usage**: Ensure you have authorization before using this device.
- **Ethical Compliance**: This tool should only be used in isolated environments or with explicit permission from affected parties.
- **Legal Risks**: Unauthorized jamming can result in severe penalties under local laws.

---

## Acknowledgments

Created by **JoinException**.

- **Libraries Used**:
- [RF24 Library](https://github.com/nRF24/RF24)
- ESP32 Wi-Fi API

For educational purposes and technical exploration only.
