# SSD1315 README

![ OLED ](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI/blob/main/extras/image/device.jpg)

## Table of contents

* [Overview](#overview)
* [Test](#test)
* [Software](#software)
  * [I2C](#i2c)
  * [Bitmaps](#bitmaps)
* [Screenshots](#screenshots)

## Overview

* Name : SSD1306_OLED_RPI
* Description :

0. Library to support the I2C  OLED Display Module
   driven by the SSD1315 controller for the Raspberry PI PICO rp2040
1. Invert color, rotate, sleep, scroll and contrast control.
2. Can support both I2C ports. IC20 or IC21 selected by user.
3. Tested on 128x64 & 64x32 display size. ONLY tested on 128x64 display size.

* Author: Gavin Lyons

* Developed on Toolchain:

1. Raspberry pi PICO RP2040
2. SDK(2.1.0) C++20
3. compiler G++ for arm-none-eabi((15:10.3-2021.07-4)
4. CMAKE(VERSION 3.18) , VScode(1.84.2)
5. Linux Mint 22.1


## Test

There are  example files included. User picks the one they want
by editing the CMakeLists.txt :: add_executable(${PROJECT_NAME}  section. Comment in one path and one path only.

| Filename | File Function | Screen Size |
| ---- | ---- | ---- |
| hello | Basic use case | 128x64 |
| bitmap | Shows use of bitmaps | 128x64 |
| text_graphics_functions |text, graphics, functionality: scroll, rotate etc | 128x64 |
| I2C_test | I2C interface testing | 128x64 |

## Software

### I2C

Hardware I2C.

1. I2C Address is set by default to  0x3C(your module could be different,
	user can change argument passed into "OLEDbegin" method).

2. Can support both I2C ports. IC20 or IC21 selected by user.

3. I2C Clock rate can be a passed into in the "OLEDbegin" method as a argument in Kilo hertz.

| Frame rate per second example file results  | I2C clock rate KiloHetrz |
| --- | --- |
| 5 | 100 |
| 12 | 400 |

4. The user must also specify the data and clk lines which are linked to the interface used

In all the examples the I2C is set up for ::
Address 0x3C , Interface I2C1 , Clock speed 100Khz, Data pin GPIO 18, Clock pin GPIO 19 .

### Bitmaps

There is a few different ways of displaying bitmaps,

| Num | Method | Data addressing | Note |
| ------ | ------ | ------ | ------ |
| 1 | OLEDBitmap() | Horizontal | Writes directly to screen , no buffer used. |
| 2 | drawBitmap() | Vertical | default, setDrawBitmapAddr(true) |
| 3 | drawBitmap() | Horizontal | setDrawBitmapAddr(false) |

Bitmap functions will return an error code in event of an error.
A horizontal addressed Bitmap's width MUST be divisible by 8. eg,
for a bitmap with width=88 and height=48. Bitmap excepted size = (88/8) * 48 = 528 bytes.
A vertically addressed Bitmap's height MUST be divisible by 8.
Bitmaps can be turned to data [here at link](https://github.com/gavinlyonsrepo/Guardian_LTSM)
See example file "bitmap" for implementation of bitmaps.
