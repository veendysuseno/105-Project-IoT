# 105 IoT Projects Collection

This repository contains 105 IoT (Internet of Things) projects designed to help beginners and advanced users alike explore the world of IoT. Each project focuses on real-world applications using popular microcontrollers such as Arduino, ESP8266, NodeMCU, and Raspberry Pi, with various sensors, modules, and communication technologies.

## Table of Contents

1. [Introduction](#introduction)
2. [Getting Started](#getting-started)
3. [List of Projects](#list-of-projects)
4. [Hardware Requirements](#hardware-requirements)
5. [Software Setup](#software-setup)
6. [How to Use This Repository](#how-to-use-this-repository)
7. [Contributing](#contributing)
8. [License](#license)

## Introduction

This repository provides a comprehensive guide to building IoT-based projects using a wide range of sensors and communication modules. From home automation and environmental monitoring to smart agriculture and health-related projects, this collection covers various domains where IoT is making an impact.

Each project includes:

- A detailed description of the objective and components
- Circuit diagrams
- Source code
- Step-by-step instructions for setting up and running the project

## Getting Started

To begin using the projects in this repository, you will need:

- A microcontroller board (Arduino, ESP8266, ESP32, or Raspberry Pi)
- A working knowledge of basic electronics and programming
- Familiarity with IoT platforms (e.g., Blynk, ThingSpeak, MQTT)

### Prerequisites

Before you begin, ensure that you have the following installed:

- Arduino IDE or PlatformIO for microcontroller programming
- Python for Raspberry Pi-based projects
- Required libraries and drivers (listed in each project folder)

## List of Projects

### Home Automation

1. **Smart Home Control with Blynk**  
   Automate your home appliances using Blynk and NodeMCU.
2. **Voice-Controlled Lights Using Google Assistant**  
   Turn your lights on and off using voice commands with Google Assistant.
3. **IoT Smart Door Lock**  
   Build a Wi-Fi-based smart door lock system using an ESP8266 module.

### Environmental Monitoring

4. **Temperature and Humidity Monitoring with DHT11**  
   Measure and display temperature and humidity data on an LCD screen.
5. **Air Quality Monitoring with MQ-2**  
   Detect gas and smoke levels in the air using an MQ-2 sensor.

### Smart Agriculture

6. **Smart Irrigation System with Soil Moisture Sensor**  
   Automate watering of plants based on real-time soil moisture readings.
7. **IoT-Based Greenhouse Monitoring**  
   Control and monitor temperature, humidity, and light levels in a greenhouse.

### Health Monitoring

8. **Pulse Rate Monitoring with Pulse Sensor and HC-05 Bluetooth**  
   Measure and send real-time heart rate data to a smartphone app.
9. **Smart Medicine Box with Alerts**  
   Remind users to take their medicine at scheduled intervals using an IoT system.

... and many more!

For the full list of 105 projects, please refer to the `Projects.md` file in this repository.

## Hardware Requirements

Each project comes with a detailed list of the components needed, but the general hardware requirements include:

- **Microcontrollers**: Arduino Uno, NodeMCU, ESP8266, ESP32, Raspberry Pi
- **Sensors**: DHT11/DHT22, BMP180, MQ-2, DS18B20, Soil Moisture Sensor, etc.
- **Communication Modules**: nRF24L01, 433 MHz Transmitter Receiver, HC-05 Bluetooth, Wi-Fi Modules
- **Displays**: 16x2 LCD, OLED, TFT Display
- **Actuators**: Relays, Servo Motors, DC Motors
- **Power Supply**: 9V Battery, Power Adapter

Each project folder contains a detailed bill of materials (BoM) specific to that project.

## Software Setup

### Arduino IDE

To program Arduino boards, install the Arduino IDE from the [official website](https://www.arduino.cc/en/software). Install the necessary libraries by navigating to **Sketch > Include Library > Manage Libraries**.

### PlatformIO

For NodeMCU or ESP8266 projects, you can use [PlatformIO](https://platformio.org/) integrated into VS Code. This environment offers better support for ESP-based projects.

### Python for Raspberry Pi

For Raspberry Pi-based projects, ensure Python 3.x is installed. Many projects use popular IoT frameworks and protocols like MQTT and HTTP, which can be installed using pip:

```bash
sudo apt-get install python3-pip
pip3 install paho-mqtt
```

## How to Use This Repository

1. Clone the repository:

```bash
git clone https://github.com/veendysuseno/105-IoT-Projects.git
cd 105-IoT-Projects
```

2. Navigate to the project folder:
   Each project has its own folder containing the necessary code, instructions, and circuit diagrams. You can navigate to a specific project and follow the steps mentioned in the README.md of that project.

3. Upload the code:
   Use the Arduino IDE or PlatformIO to upload the code to your microcontroller.

4. Test the project:
   Follow the wiring diagrams and test the project by connecting the components as per the instructions.

## Contributing

We welcome contributions to enhance and expand the list of projects in this repository. You can contribute by:

- Adding new IoT projects
- Improving the documentation or code for existing projects
- Fixing bugs or optimizing the project code

To contribute, please fork the repository, create a new branch, and submit a pull request. Ensure that your contribution is well-documented and tested.

## License

- This repository is licensed under the MIT License. You are free to use, modify, and distribute this code, provided that proper credit is given to the original authors. <br/>
"# 105-Project-IoT" 
