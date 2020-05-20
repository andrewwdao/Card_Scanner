# Attendance Checking System for students of Can Tho University

[![Latest release](https://img.shields.io/github/v/release/minhan74/Card_Scanner?include_prereleases)](https://github.com/minhan74/Card_Scanner/releases/latest)
[![Release Date](https://img.shields.io/github/release-date-pre/minhan74/Card_Scanner)](https://github.com/minhan74/Card_Scanner/releases/latest/)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE) <!-- [![License](https://img.shields.io/github/license/minhan74/Card_Scanner.svg)](LICENSE) -->
[![Size](https://img.shields.io/github/repo-size/minhan74/Card_Scanner)](https://github.com/minhan74/Card_Scanner/)

## Download

```bash
git clone --recursive https://github.com/minhan74/Card_Scanner.git
git submodule update --init --recursive
```

This project includes two main components:

* A Card Reader Device
* A Web Server

## Card Reader Device

This device is designed for reading student card, indicates student information and save these information into SD card. The device can connect to a server (locally or globally) to manipulate student's attendance information.

### Hardware

#### Cover

Designed using Fusion360.

Created by 3D printing and laser cutting.

#### PCB

Designed in Altium 18.

Manufactured in china.

### Embedded software

Microcontroller: ESP32 DEV KIT V1

Run on both core of an ESP32 using FreeRTOS. Compiled by ESP-IDF with Arduino core as a component.

* ESP-IDF version: 3.2
* Compiler version: 5.2.0
* Arduino components version: 1.0.2

## Web Server

Written in PHP 7.4.6

Based on:

* Xampp v7.4.6
* Lavarel framework 5.6.22

## Documentation

* **[Full Report]**: This project is also a school scientific research, you can have a look of it here. (in Vietnamese)
* **[Hardware files]**: ready-to-print parts of the cover and PCB.
* **[ESP32 - Flash Instruction]**: Instruction on how to flash a ready-to-use binary file to esp32.
* **[ESP32 - Prepare Developing Environment]**: Guidance on how to prepare an appropriate developing environment for esp32.
* **[Web server - How to use]**: How to use the web server.
* **[Web server - Create localhost server]**: How to create a localhost server for locally use.
* **[Web server - Create globalhost server]**: How to create a globalhost server for internet use.

## Sponsor by

* Msc. Khac-Nguyen Nguyen, Can Tho University. <nknguyen@ctu.edu.vn>
* Can Tho University school scientific research fund.

## Supervised by

* Assoc. Prof. Chi-Ngon Nguyen, Can Tho University. <ncngon@ctu.edu.vn>
* Dr. Chanh-Nghiem Nguyen, Can Tho University. <ncnghiem@ctu.edu.vn>
* Msc. Khac-Nguyen Nguyen, Can Tho University. <nknguyen@ctu.edu.vn>

 (c) 2019 Quang-Thong Duong-Pham <baronvn7197@gmail.com> - Quang-Nhut Tran <nhut1202@gmail.com> - Minh-An Dao <minhan7497@gmail.com> - Can Tho University.

<!-- Links -->
[Full Report]:https://bit.ly/DMA-undergrad
[Hardware files]: /hardware/
[ESP32 - Flash Instruction]: /docs/[ESP32]flash_ready-to-use_binary.md
[ESP32 - Prepare Developing Environment]: /docs/[ESP32]prepare_developing_environment.md
[Web server - How to use]: /docs/[Web_server]How_to_use_web_server.md
[Web server - Create localhost server]: /docs/[Web_server]Create_localhost_server.md
[Web server - Create globalhost server]:[Web_server]Create_globalhost_server.md
