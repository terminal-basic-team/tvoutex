/*
 * Copyright (c) 2010 Myles Metzer
 * Copyright (c) 2017-2019 Andrey V. Skvortsov
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:

 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Font8x8.h"

PROGMEM const unsigned char font8x8[] = {
8,8,0,
// 0 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
// 1 0x00, 0x3E, 0x41, 0x55, 0x41, 0x55, 0x49, 0x3E,
0b00000000,
0b00111110,
0b01000001,
0b01010101,
0b01000001,
0b01010101,
0b01001001,
0b00111110,
// 2 0x00, 0x3E, 0x7F, 0x6B, 0x7F, 0x6B, 0x77, 0x3E,
0b00000000,
0b00111110,
0b01111111,
0b01101011,
0b01111111,
0b01101011,
0b01110111,
0b00111110,
// 3 0x00, 0x22, 0x77, 0x7F, 0x7F, 0x3E, 0x1C, 0x08,
0x00, 0x22, 0x77, 0x7F, 0x7F, 0x3E, 0x1C, 0x08,
// 4 0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 
0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08,
// 5 0x00, 0x08, 0x1C, 0x2A, 0x7F, 0x2A, 0x08, 0x1C, 
0x00, 0x08, 0x1C, 0x2A, 0x7F, 0x2A, 0x08, 0x1C, 
0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x08, 0x1C, 
0x00, 0x00, 0x1C, 0x3E, 0x3E, 0x3E, 0x1C, 0x00, 
0xFF, 0xFF, 0xE3, 0xC1, 0xC1, 0xC1, 0xE3, 0xFF, 
0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00, 
0xFF, 0xFF, 0xE3, 0xDD, 0xDD, 0xDD, 0xE3, 0xFF, 
0x00, 0x0F, 0x03, 0x05, 0x39, 0x48, 0x48, 0x30, 
0x00, 0x08, 0x3E, 0x08, 0x1C, 0x22, 0x22, 0x1C, 
0x00, 0x18, 0x14, 0x10, 0x10, 0x30, 0x70, 0x60, 
0x00, 0x0F, 0x19, 0x11, 0x13, 0x37, 0x76, 0x60, 
0x00, 0x08, 0x2A, 0x1C, 0x77, 0x1C, 0x2A, 0x08, 
0x00, 0x60, 0x78, 0x7E, 0x7F, 0x7E, 0x78, 0x60, 
0x00, 0x03, 0x0F, 0x3F, 0x7F, 0x3F, 0x0F, 0x03, 
0x00, 0x08, 0x1C, 0x2A, 0x08, 0x2A, 0x1C, 0x08, 
0x00, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x66, 
0x00, 0x3F, 0x65, 0x65, 0x3D, 0x05, 0x05, 0x05, 
0x00, 0x0C, 0x32, 0x48, 0x24, 0x12, 0x4C, 0x30, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 
0x00, 0x08, 0x1C, 0x2A, 0x08, 0x2A, 0x1C, 0x3E, 
0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x1C, 0x1C, 0x1C, 
0x00, 0x1C, 0x1C, 0x1C, 0x7F, 0x3E, 0x1C, 0x08, 
0x00, 0x08, 0x0C, 0x7E, 0x7F, 0x7E, 0x0C, 0x08, 
0x00, 0x08, 0x18, 0x3F, 0x7F, 0x3F, 0x18, 0x08, 
0x00, 0x00, 0x00, 0x70, 0x70, 0x70, 0x7F, 0x7F, 
0x00, 0x00, 0x14, 0x22, 0x7F, 0x22, 0x14, 0x00, 
0x00, 0x08, 0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x7F, 
//0x00, 0x7F, 0x7F, 0x3E, 0x3E, 0x1C, 0x1C, 0x08,
0b00000000,
0b01111111,
0b01111111,
0b00111110,
0b00111110,
0b00011100,
0b00011100,
0b00001000,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 
0x00, 0x36, 0x36, 0x14, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 
0x00, 0x08, 0x1E, 0x20, 0x1C, 0x02, 0x3C, 0x08, 
0x00, 0x60, 0x66, 0x0C, 0x18, 0x30, 0x66, 0x06, 
0x00, 0x3C, 0x66, 0x3C, 0x28, 0x65, 0x66, 0x3F, 
0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 
//0x00, 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60,
0b00000000,
0b01100000,
0b00110000,
0b00011000,
0b00011000,
0b00011000,
0b00110000,
0b01100000,
0x00, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 
0x00, 0x00, 0x36, 0x1C, 0x7F, 0x1C, 0x36, 0x00, 
0x00, 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x60, 
0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 
0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 
0x00, 0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 
0x00, 0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7E, 
0x00, 0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E, 
//0x00, 0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C,
0b00000000,
0b00111100,
0b01100110,
0b00000110,
0b00011100,
0b00000110,
0b01100110,
0b00111100,
0x00, 0x0C, 0x1C, 0x2C, 0x4C, 0x7E, 0x0C, 0x0C, 
0x00, 0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 
0x00, 0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 
0x00, 0x7E, 0x66, 0x0C, 0x0C, 0x18, 0x18, 0x18, 
0x00, 0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 
0x00, 0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 
0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 
0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 
0x00, 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 
0x00, 0x00, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x00, 
0x00, 0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 
0x00, 0x3C, 0x66, 0x06, 0x1C, 0x18, 0x00, 0x18, 
0x00, 0x38, 0x44, 0x5C, 0x58, 0x42, 0x3C, 0x00, 
0x00, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 
0x00, 0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 
0x00, 0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 
//0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7C,
0b00000000,
0b01111100,
0b01100110,
0b01100110,
0b01100110,
0b01100110,
0b01100110,
0b01111100,
0x00, 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7E, 
0x00, 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 
0x00, 0x3C, 0x66, 0x60, 0x60, 0x6E, 0x66, 0x3C, 
0x00, 0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 
0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 
0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x6C, 0x6C, 0x38, 
0x00, 0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 
0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 
0x00, 0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 
0x00, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x63, 0x63, 
0x00, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 
0x00, 0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 
0x00, 0x3C, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x06, 
0x00, 0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 
// 0x00, 0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C,
0b00000000,
0b00111100,
0b01100110,
0b01100000,
0b00111100,
0b00000110,
0b01100110,
0b00111100,
0x00, 0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x18, 
0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3E, 
0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 
0x00, 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 
0x00, 0x63, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x63, 
0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 
0x00, 0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 
0x00, 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 
0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 
0x00, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 
0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 
0x00, 0x0C, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 
0x00, 0x60, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 
0x00, 0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 
0x00, 0x06, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3E, 
0x00, 0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 
// 0x00, 0x1C, 0x36, 0x30, 0x30, 0x7C, 0x30, 0x30,
0b00000000,
0b00011100,
0b00110110,
0b00110000,
0b00110000,
0b01111100,
0b00110000,
0b00110000,
0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x3C, 
0x00, 0x60, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 
0x00, 0x00, 0x18, 0x00, 0x18, 0x18, 0x18, 0x3C, 
0x00, 0x0C, 0x00, 0x0C, 0x0C, 0x6C, 0x6C, 0x38, 
0x00, 0x60, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66, 
0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
0x00, 0x00, 0x00, 0x63, 0x77, 0x7F, 0x6B, 0x6B, 
0x00, 0x00, 0x00, 0x7C, 0x7E, 0x66, 0x66, 0x66, 
0x00, 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 
0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 
0x00, 0x00, 0x3C, 0x6C, 0x6C, 0x3C, 0x0D, 0x0F, 
0x00, 0x00, 0x00, 0x7C, 0x66, 0x66, 0x60, 0x60, 
0x00, 0x00, 0x00, 0x3E, 0x40, 0x3C, 0x02, 0x7C, 
0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x18, 
0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 
0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x3C, 0x18, 
0x00, 0x00, 0x00, 0x63, 0x6B, 0x6B, 0x6B, 0x3E, 
//0x00, 0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66,
0b00000000,
0b00000000,
0b00000000,
0b01100110,
0b00111100,
0b00011000,
0b00111100,
0b01100110,
//0x00, 0x00, 0x00, 0x66, 0x66, 0x3E, 0x06, 0x3C,
0b00000000,
0b00000000,
0b00000000,
0b01100110,
0b01100110,
0b00111110,
0b00000110,
0b00111100,
//0x00, 0x00, 0x00, 0x3C, 0x0C, 0x18, 0x30, 0x3C,
0b00000000,
0b00000000,
0b00000000,
0b00111100,
0b00001100,
0b00011000,
0b00110000,
0b00111100,
//0x00, 0x0E, 0x18, 0x18, 0x30, 0x18, 0x18, 0x0E,
0b00000000,
0b00001110,
0b00011000,
0b00011000,
0b00110000,
0b00011000,
0b00011000,
0b00001110,
//0x00, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18,
0b00000000,
0b00011000,
0b00011000,
0b00011000,
0b00000000,
0b00011000,
0b00011000,
0b00011000,
//0x00, 0x70, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x70,
0b00000000,
0b01110000,
0b00011000,
0b00011000,
0b00001100,
0b00011000,
0b00011000,
0b01110000,
//0x00, 0x00, 0x00, 0x3A, 0x6C, 0x00, 0x00, 0x00,
0b00000000,
0b00000000,
0b00000000,
0b00111010,
0b01101100,
0b00000000,
0b00000000,
0b00000000,
//0x00, 0x08, 0x1C, 0x36, 0x63, 0x41, 0x41, 0x7F,
0b00000000,
0b00001000,
0b00011100,
0b00110110,
0b01100011,
0b01000001,
0b01000001,
0b01111111
};
