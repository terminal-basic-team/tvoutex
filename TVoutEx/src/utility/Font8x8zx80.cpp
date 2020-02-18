/*
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

#include "Font8x8zx80.hpp"

PROGMEM const unsigned char Font8x8zx80[256*8+3] = {
8,8,32,
// 32 Space
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
// 33 Exclamation mark (!), not in zx80
0b00000000,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00000000,
0b00001000,
0b00000000,
// 34 Quatation mark (")
0b00000000,
0b00010100,
0b00010100,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
// 35 Number sign (#), not in zx80
0b00000000,
0b00000000,
0b00010100,
0b00111110,
0b00010100,
0b00111110,
0b00010100,
0b00000000,
// 36 Dollar sign ($)
0b00000000,
0b00001000,
0b00111110,
0b01001000,
0b00111110,
0b00001001,
0b00111110,
0b00001000,
// 37 Percent sign (%), not in zx80
0b00000000,
0b01100010,
0b01100100,
0b00001000,
0b00010000,
0b00100110,
0b01000110,
0b00000000,
// 38 Ampersand (&), not in zx80
0b00000000,
0b00111100,
0b01000010,
0b00111000,
0b01000101,
0b01000010,
0b00111101,
0b00000000,
// 39 Apostrophe ('), not in zx80
0b00000000,
0b00001000,
0b00001000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
// 40 Left parenthesis ( ( )
0b00000000,
0b00000100,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00000100,
0b00000000,
// 41 Right parenthesis ( ) )
0b00000000,
0b00010000,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00010000,
0b00000000,
// 42 Asterisk (*)
0b00000000,
0b00000000,
0b00101010,
0b00011100,
0b00001000,
0b00011100,
0b00101010,
0b00000000,
// 43 Plus sign (+)
0b00000000,
0b00000000,
0b00001000,
0b00001000,
0b00111110,
0b00001000,
0b00001000,
0b00000000,
// 44 Comma (,)
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00001000,
0b00001000,
0b00010000,
// 45 Hyphen-minus (-)
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00111110,
0b00000000,
0b00000000,
0b00000000,
// 46 Full stop (.)
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00001100,
0b00001100,
0b00000000,
// 47 Slash (/)
0b00000000,
0b00000000,
0b00000010,
0b00000100,
0b00001000,
0b00010000,
0b00100000,
0b00000000,
// 48 Zero (0)
0b00000000,
0b00011100,
0b00100010,
0b01000001,
0b01000001,
0b00100010,
0b00011100,
0b00000000,
// 49 One (1)
0b00000000,
0b00001100,
0b00010100,
0b00000100,
0b00000100,
0b00000100,
0b00011110,
0b00000000,
// 50 Two (2)
0b00000000,
0b00111110,
0b01000001,
0b00000001,
0b00111110,
0b01000000,
0b01111111,
0b00000000,
// 51 Three (3)
0b00000000,
0b00111110,
0b01000001,
0b00000110,
0b00000001,
0b01000001,
0b00111110,
0b00000000,
// 52 Four (4)
0b00000000,
0b00001100,
0b00010100,
0b00100100,
0b01000100,
0b01111111,
0b00000100,
0b00000000,
// 53 Five (5)
0b00000000,
0b01111111,
0b01000000,
0b01111110,
0b00000001,
0b01000001,
0b00111110,
0b00000000,
// 54 Six (6)
0b00000000,
0b00111110,
0b01000000,
0b01111110,
0b01000001,
0b01000001,
0b00111110,
0b00000000,
// 55 Seven (7)
0b00000000,
0b01111111,
0b00000001,
0b00000010,
0b00000100,
0b00001000,
0b00001000,
0b00000000,
// 56 Eight (8)
0b00000000,
0b00111110,
0b01000001,
0b00111110,
0b01000001,
0b01000001,
0b00111110,
0b00000000,
// 57 Nine (9)
0b00000000,
0b00111110,
0b01000001,
0b01000001,
0b00111111,
0b00000001,
0b00111110,
0b00000000,
// 58 Colon (:)
0b00000000,
0b00000000,
0b00000000,
0b00001000,
0b00000000,
0b00000000,
0b00001000,
0b00000000,
// 59 Semicolon (;)
0b00000000,
0b00000000,
0b00001000,
0b00000000,
0b00000000,
0b00001000,
0b00001000,
0b00010000,
// 60 Less-then (<)
0b00000000,
0b00000000,
0b00000100,
0b00001000,
0b00010000,
0b00001000,
0b00000100,
0b00000000,
// 61 Equals (=)
0b00000000,
0b00000000,
0b00000000,
0b00111110,
0b00000000,
0b00111110,
0b00000000,
0b00000000,
// 62 Greater-then (>)
0b00000000,
0b00000000,
0b00010000,
0b00001000,
0b00000100,
0b00001000,
0b00010000,
0b00000000,
// 63 Quatation mark (?)
0b00000000,
0b00111110,
0b01000001,
0b00000110,
0b00001000,
0b00000000,
0b00001000,
0b00000000,
// 64 At sign (@), not in zx80
0b00000000,
0b00111110,
0b01000001,
0b01011101,
0b01011101,
0b01000101,
0b00111100,
0b00000000,
// 65 A
0b00000000,
0b00111110,
0b01000001,
0b01000001,
0b01111111,
0b01000001,
0b01000001,
0b00000000,
// 66 B
0b00000000,
0b01111110,
0b01000001,
0b01111110,
0b01000001,
0b01000001,
0b01111110,
0b00000000,
// 67 C
0b00000000,
0b00011110,
0b00100001,
0b01000000,
0b01000000,
0b00100001,
0b00011110,
0b00000000,
// 68 D
0b00000000,
0b01111100,
0b01000010,
0b01000001,
0b01000001,
0b01000010,
0b01111100,
0b00000000,
// 69 E
0b00000000,
0b01111111,
0b01000000,
0b01111100,
0b01000000,
0b01000000,
0b01111111,
0b00000000,
// 70 F
0b00000000,
0b01111111,
0b01000000,
0b01111100,
0b01000000,
0b01000000,
0b01000000,
0b00000000,
// 71 G
0b00000000,
0b00011110,
0b00100001,
0b01000000,
0b01000111,
0b00100001,
0b00011110,
0b00000000,
// 72 H
0b00000000,
0b01000001,
0b01000001,
0b01111111,
0b01000001,
0b01000001,
0b01000001,
0b00000000,
// 73 I
0b00000000,
0b00111110,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00111110,
0b00000000,
// 74 J
0b00000000,
0b00000010,
0b00000010,
0b00000010,
0b01000010,
0b00100010,
0b00011100,
0b00000000,
// 75 K
0b00000000,
0b01000010,
0b01000100,
0b01111000,
0b01000100,
0b01000010,
0b01000001,
0b00000000,
// 76 L
0b00000000,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01000000,
0b01111111,
0b00000000,
// 77 M
0b00000000,
0b01000001,
0b01100011,
0b01010101,
0b01001001,
0b01000001,
0b01000001,
0b00000000,
// 78 N
0b00000000,
0b01100001,
0b01010001,
0b01001001,
0b01000101,
0b01000011,
0b01000001,
0b00000000,
// 79 O
0b00000000,
0b00111110,
0b01000001,
0b01000001,
0b01000001,
0b01000001,
0b00111110,
0b00000000,
// 80 P
0b00000000,
0b01111110,
0b01000001,
0b01000001,
0b01111110,
0b01000000,
0b01000000,
0b00000000,
// 81 Q
0b00000000,
0b00111110,
0b01000001,
0b01000001,
0b01001001,
0b01000101,
0b00111110,
0b00000000,
// 82 R
0b00000000,
0b01111110,
0b01000001,
0b01000001,
0b01111110,
0b01000100,
0b01000010,
0b00000000,
// 83 S
0b00000000,
0b00111110,
0b01000000,
0b00111110,
0b00000001,
0b01000001,
0b00111110,
0b00000000,
// 84 T
0b00000000,
0b01111111,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00000000,
// 85 U
0b00000000,
0b01000001,
0b01000001,
0b01000001,
0b01000001,
0b01000001,
0b00111110,
0b00000000,
// 86 V
0b00000000,
0b01000001,
0b01000001,
0b01000001,
0b00100010,
0b00010100,
0b00001000,
0b00000000,
// 87 W
0b00000000,
0b01000001,
0b01000001,
0b01000001,
0b01001001,
0b01010101,
0b00100010,
0b00000000,
// 88 X
0b00000000,
0b00100001,
0b00010010,
0b00001100,
0b00001100,
0b00010010,
0b00100001,
0b00000000,
// 89 Y
0b00000000,
0b01000001,
0b00100010,
0b00011100,
0b00001000,
0b00001000,
0b00001000,
0b00000000,
// 90 Z
0b00000000,
0b01111111,
0b00000010,
0b00000100,
0b00001000,
0b00010000,
0b01111111,
0b00000000,
// 91 Left bracket ([), not in zx80
0b00000000,
0b00001100,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00001100,
0b00000000,
// 92 Tilde (~), not in zx80
0b00000000,
0b00000000,
0b00000000,
0b00010000,
0b00101010,
0b00000100,
0b00000000,
0b00000000,
// 93 Right bracket (]), not in zx80
0b00000000,
0b00011000,
0b00001000,
0b00001000,
0b00001000,
0b00001000,
0b00011000,
0b00000000,
// 94 Caret (^), not in zx80
0b00000000,
0b00001000,
0b00010100,
0b00100010,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
// 95 Underscore (_), not in zx80
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b01111111,
0b00000000
};