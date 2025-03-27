# NOKIA 5110 Readme

## Table of contents

  * [Overview](#overview)
  * [Hardware](#hardware)
  * [Software](#software)
    * [File system](#file-system)
  * [Output](#output)

## Overview

* Name: NOKIA_5110
* Description:

0. C++ Library for Nokia 5110 LCD, PCD8544 Driver. 84 x 48 pixels.
1. Invert colour, rotate, sleep, contrast bias control supported.
2. Bitmaps supported.
3. Hardware SPI

* Author: Gavin Lyons


## Hardware

The Nokia 5110 is a basic graphic LCD screen for lots of applications.
GPIO function on RPI, 5 Nokia 5110 LCD lines SPI bus.
The user can use any GPIO for reset, data/command line
and chip select. Clock and data are tied to hardware interface chosen. 
The driver chip is PCD8544.

Example file set up :

const uint mosi_pin = 19;
const uint sck_pin = 18;
const uint cs_pin = 17;
const uint res_pin = 3;
const uint dc_pin = 2;

| PICO pin(HW SPI) | Nokia 5110 LCD |
| ------ | ------ | ------ |
| sclk pin GPIO 18 (spi0) | LCD_CLK Pin 5 clock in |
| mosi pin GPIO 19 (spi0) | LCD_DIN Pin 4 data in |
| DC pin GPIO 2 | LCD_DC Pin 3 data/command|
| CS pin GPIO 17 | LCD_CE Pin 2 chip enable |
| Reset pin GPIO 3 | LCD_RST Pin 1 reset|

Connect Nokia 5110 VCC(pin 6)to 3.3V.
The user may have to adjust LCD contrast and bias settings,
to the screen at hand for optimal display.
A resistor or potentiometer can be connected between (Nokia LCD)
GND(pin8) and LIGHT(pin7) to switch on /off backlight and adjust brightness.

[Nokia 5110 LCD dataSheet ](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)

[![ image nokia ](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/NOKIA2.jpg)](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/NOKIA2.jpg)

## Software

### File system

Example files 

| Filepath | File Function | SPI |
| ---- | ---- | ---- |
| hello | Basic use case | HW |
| text_graphics_functions | Text & Graphics & Function testing | HW |
| bitmap | Bitmaps tests | HW |
| framerate_test | Frame rate per second test | HW |


## Output

Example output.

[![output image](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/nokiagraph1.jpg)](https://github.com/gavinlyonsrepo/pic_18F47K42_projects/blob/master/images/nokiagraph1.jpg)
