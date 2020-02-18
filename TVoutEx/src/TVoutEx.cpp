/*
 * Copyright (c) 2010 Myles Metzer
 * Copyright (c) 2017,2018 Andrey V. Skvortsov
 * Copyright (C) 2019,2020 Terminal-BASIC team
 *     <https://bitbucket.org/%7Bf50d6fee-8627-4ce4-848d-829168eedae5%7D/>
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

/* A note about how Color is defined for this version of TVout
 *
 * Where ever choosing a color is mentioned the following are true:
 * 	BLACK	=0
 *	WHITE	=1
 *	INVERT	=2
 *	All others will be ignored.
 */

#if USE_STRINGH_FUNCS
#include <string.h>
#include <stdbool.h>
#include <math.h>
#endif
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>

#include "TVoutEx.h"

#if TVOUT_DEBUG
#include "seriallight.hpp"
#endif

#if TVOUT_DEBUG
#include "seriallight.hpp"
#endif

#ifdef swap
#undef swap
#endif
template <typename T>
void swap(T &r, T &l)
{
	T buf = r;
	r = l;
	l = buf;
}

TVoutEx *TVoutEx::_instance = NULL;

/* Inline version of set_pixel that does not perform a bounds check
 * This function will be replaced by a macro.
 */
inline void
sp(uint8_t x, uint8_t y, char c)
{
	if (c == 1)
		display.screen[(x / 8) + (y * display.hres)] |= 0x80 >> (x & 7);
	else if (c == 0)
		display.screen[(x / 8) + (y * display.hres)] &= ~0x80 >> (x & 7);
	else
		display.screen[(x / 8) + (y * display.hres)] ^= 0x80 >> (x & 7);
} // end of sp

void
TVoutEx::Font::setRawFont(const uint8_t *rawFont)
{
	font = rawFont;
}

const uint8_t*
TVoutEx::Font::rawFont() const
{
	return font;
}

uint8_t
TVoutEx::Font::width() const
{
	return pgm_read_byte(font);
}

uint8_t
TVoutEx::Font::height() const
{
	return pgm_read_byte(font+1);
}

TVoutEx::TVoutEx() :
screen(nullptr),
_cursorState(false), _lockCursor(false),
_cursorCounter(10), _currentColor{WHITE, BLACK}
{
}

TVoutEx::~TVoutEx()
{
}

TVoutEx::Error_t
TVoutEx::begin(VideMode_t mode, uint8_t x, uint8_t y, uint8_t *buffer)
{
#if TVOUT_DEBUG
	SerialL.println(__PRETTY_FUNCTION__);
	SerialL.print(x), SerialL.write(' '), SerialL.println(y), SerialL.println();
#endif
	
	if (_instance != NULL)
		return MULTIPLE_INSTANCES;
	_instance = this;
	
	// check if x is divisable by 8
	if ((x % 8) != 0)
		return NOT_A_POWER_OF_2;
	x = x / 8;
	
	screen = buffer;
	if (screen == nullptr)
		return NULL_BUFFER;

	cursor_x = cursor_y = 0;

	renderSetup(mode, x, y, screen);
	clearScreen();
	vbiHook = vBlank;
	
#if SDL_DEBUG
	_initSDL();
#endif
	return NO_ERROR;
}

/* Stop video render and free the used memory.
 */
void
TVoutEx::end()
{
	_instance = NULL;
	TIMSK1 = 0;
	vbiHook = emptyFunction;
}

/* Fill the screen with some color.
 *
 * Arguments:
 *	color:
 *		The color to fill the screen with.
 *		(see color note at the top of this file)
 */
void
TVoutEx::fill(Color_t color)
{
	switch (color) {
	case BLACK:
		cursor_x = 0;
		cursor_y = 0;
#if USE_STRINGH_FUNCS
		memset(display.screen, 0, display.size());
#else
		for (int i = 0; i < (display.hres) * display.vres; i++)
			display.screen[i] = 0;
#endif
		break;
	case WHITE:
		cursor_x = 0;
		cursor_y = 0;
#if USE_STRINGH_FUNCS
		memset(display.screen, 0xFF, display.size());
#else
		for (int i = 0; i < (display.hres) * display.vres; i++)
			display.screen[i] = 0xFF;
#endif
		break;
	case INVERT:

		for (int i = 0; i < display.hres * display.vres; i++)
			display.screen[i] = ~display.screen[i];
		break;
	default:
		break;
	}
}

/* Gets the Horizontal resolution of the screen
 *
 * Returns:
 *	The horizonal resolution.
 */
uint8_t
TVoutEx::hres() const
{
	return display.hres * 8;
}

/* Gets the Vertical resolution of the screen
 *
 * Returns:
 *	The vertical resolution
 */
uint8_t
TVoutEx::vres() const
{
	return display.vres;
}

char
TVoutEx::charLine() const
{
	return (display.hres * 8) / _font.width();
}

/* Delay for x frames, exits at the end of the last display line.
 * delay_frame(1) is useful prior to drawing so there is little/no flicker.
 *
 * Arguments:
 *	x:
 *		The number of frames to delay for.
 */
void
TVoutEx::delay_frame(unsigned int x)
{
	int stop_line = (int) (display.start_render +
	    (display.vres * (display.vscale_const + 1))) + 1;
	while (x) {
		while (display.scanLine != stop_line);
		while (display.scanLine == stop_line);
		--x;
	}
} // end of delay_frame

/* Get the time in ms since begin was called.
 * The resolution is 16ms for NTSC and 20ms for PAL
 *
 * Returns:
 *	The time in ms since video generation has started.
 */
unsigned long
TVoutEx::millis()
{
	if (display.lines_frame == _NTSC_LINE_FRAME) {
		return display.frames * _NTSC_TIME_SCANLINE * _NTSC_LINE_FRAME / 1000;
	} else {
		return display.frames * _PAL_TIME_SCANLINE * _PAL_LINE_FRAME / 1000;
	}
} // end of millis

/* force the number of times to display each line.
 *
 * Arguments:
 *	sfactor:
 *		The scale number of times to repeate each line.
 */
void
TVoutEx::force_vscale(char sfactor)
{
	delay_frame(1);
	display.vscale_const = sfactor - 1;
	display.vscale = sfactor - 1;
}

/* force the output start time of a scanline in micro seconds.
 *
 * Arguments:
 *	time:
 *		The new output start time in micro seconds.
 */
void
TVoutEx::force_outstart(uint8_t time)
{
	delay_frame(1);
	display.output_delay = ((time * _CYCLES_PER_US) - 1);
}

/* force the start line for active video
 *
 * Arguments:
 *	line:
 *		The new active video output start line
 */
void
TVoutEx::force_linestart(uint8_t line)
{
	delay_frame(1);
	display.start_render = line;
}

void
TVoutEx::setPixel(uint8_t x, uint8_t y)
{
	if ((x >= display.hres * 8) || (y >= display.vres))
		return;
	sp(x, y, _currentColor[0]);
}

/* Set the color of a pixel
 *
 * Arguments:
 *	x:
 *		The x coordinate of the pixel.
 *	y:
 *		The y coordinate of the pixel.
 *	c:
 *		The color of the pixel
 *		(see color note at the top of this file)
 */
void
TVoutEx::setPixel(uint8_t x, uint8_t y, Color_t c)
{
	_currentColor[0] = c;
	setPixel(x, y);
} // end of set_pixel

/* get the color of the pixel at x,y
 *
 * Arguments:
 *	x:
 *		The x coordinate of the pixel.
 *	y:
 *		The y coordinate of the pixel.
 *
 * Returns:
 *	The color of the pixel.
 *	(see color note at the top of this file)
 *
 * Thank you gijs on the arduino.cc forum for the non obviouse fix.
 */
Color_t
TVoutEx::getPixel(uint8_t x, uint8_t y)
{
	if (x >= display.hres * 8 || y >= display.vres)
		return BLACK;
	if (display.screen[x / 8 + y * display.hres] & (0x80 >> (x & 7)))
		return WHITE;
	return BLACK;
} // end of get_pixel

void
TVoutEx::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	setPosition(x0, y0);
	drawLineTo(x1, y1);
}

/* Draw a line from one point to another
 *
 * Arguments:
 *	x0:
 *		The x coordinate of point 0.
 *	y0:
 *		The y coordinate of point 0.
 *	x1:
 *		The x coordinate of point 1.
 *	y1:
 *		The y coordinate of point 1.
 *	c:
 *		The color of the line.
 *		(see color note at the top of this file)
 */

/* Patched to allow support for the Arduino Leonardo */
void
TVoutEx::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, Color_t c)
{
	_currentColor[0] = c;
	drawLine(x0, y0, x1, y1);
} // end of draw_line

void
TVoutEx::drawLineTo(uint8_t x1, uint8_t y1)
{
	if (x1 >= display.hres * 8
	 || y1 >= display.vres)
		return;
	if (_currentPosition[0] == x1)
		drawColumn(_currentPosition[0], _currentPosition[1], y1);
	else if (_currentPosition[1] == y1)
		drawRow(_currentPosition[1], _currentPosition[0], x1);
	else {
		int e;
		signed int dx, dy, j, temp;
		signed char s1, s2, xchange;
		signed int x, y;

		x = _currentPosition[0];
		y = _currentPosition[1];

		//take absolute value
		if (x1 < _currentPosition[0]) {
			dx = _currentPosition[0] - x1;
			s1 = -1;
		} else if (x1 == _currentPosition[0]) {
			dx = 0;
			s1 = 0;
		} else {
			dx = x1 - _currentPosition[0];
			s1 = 1;
		}

		if (y1 < _currentPosition[1]) {
			dy = _currentPosition[1] - y1;
			s2 = -1;
		} else if (y1 == _currentPosition[1]) {
			dy = 0;
			s2 = 0;
		} else {
			dy = y1 - _currentPosition[1];
			s2 = 1;
		}

		xchange = 0;

		if (dy > dx) {
			temp = dx;
			dx = dy;
			dy = temp;
			xchange = 1;
		}

		e = ((int) dy << 1) - dx;

		for (j = 0; j <= dx; j++) {
			sp(x, y, _currentColor[0]);

			if (e >= 0) {
				if (xchange == 1) x = x + s1;
				else y = y + s2;
				e = e - ((int) dx << 1);
			}
			if (xchange == 1)
				y = y + s2;
			else
				x = x + s1;
			e = e + ((int) dy << 1);
		}
	}
	setPosition(x1, y1);
}

void
TVoutEx::drawRow(uint8_t line, uint16_t x0, uint16_t x1, Color_t c)
{
	Color_t col = _currentColor[0];
	_currentColor[0] = c;
	drawRow(line, x0, x1);
	_currentColor[0] = col;
} // end of draw_row

void
TVoutEx::drawRow(uint8_t line, uint16_t x0, uint16_t x1)
{
	uint8_t lbit, rbit;

	if (x0 == x1)
		setPixel(x0, line, _currentColor[0]);
	else {
		if (x0 > x1) {
			lbit = x0;
			x0 = x1;
			x1 = lbit;
		}
		lbit = 0xff >> (x0 & 7);
		x0 = x0 / 8 + display.hres*line;
		rbit = ~(0xff >> (x1 & 7));
		x1 = x1 / 8 + display.hres*line;
		if (x0 == x1) {
			lbit = lbit & rbit;
			rbit = 0;
		}
		if (_currentColor[0] == WHITE) {
			screen[x0++] |= lbit;
			while (x0 < x1)
				screen[x0++] = 0xff;
			screen[x0] |= rbit;
		} else if (_currentColor[0] == BLACK) {
			screen[x0++] &= ~lbit;
			while (x0 < x1)
				screen[x0++] = 0;
			screen[x0] &= ~rbit;
		} else if (_currentColor[0] == INVERT) {
			screen[x0++] ^= lbit;
			while (x0 < x1)
				screen[x0++] ^= 0xff;
			screen[x0] ^= rbit;
		}
	}
}

void
TVoutEx::drawColumn(uint8_t row, uint16_t y0, uint16_t y1)
{
	unsigned char bit;
	int byte;

	if (y0 == y1)
		setPixel(row, y0, _currentColor[0]);
	else {
		if (y1 < y0) {
			bit = y0;
			y0 = y1;
			y1 = bit;
		}
		bit = 0x80 >> (row & 7);
		byte = row / 8 + y0 * display.hres;
		if (_currentColor[0] == WHITE) {
			while (y0 <= y1) {
				screen[byte] |= bit;
				byte += display.hres;
				y0++;
			}
		} else if (_currentColor[0] == BLACK) {
			while (y0 <= y1) {
				screen[byte] &= ~bit;
				byte += display.hres;
				y0++;
			}
		} else if (_currentColor[0] == INVERT) {
			while (y0 <= y1) {
				screen[byte] ^= bit;
				byte += display.hres;
				y0++;
			}
		}
	}
}

/* Fill a column from one point to another
 *
 * Argument:
 *	row:
 *		The row that fill will be performed on.
 *	y0:
 *		edge 0 of the fill.
 *	y1:
 *		edge 1 of the fill.
 *	c:
 *		the color of the fill.
 *		(see color note at the top of this file)
 */
void
TVoutEx::drawColumn(uint8_t row, uint16_t y0, uint16_t y1, Color_t c)
{
	Color_t col = _currentColor[0];
	_currentColor[0] = c;
	drawColumn(row, y0, y1);
	_currentColor[0] = col;
}

void
TVoutEx::drawEllipse(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	int16_t x0 = x, y0 = y, x1 = x+w, y1 = y+h;
	
	/* rectangular parameter enclosing the ellipse */
	int32_t a = w, b = h, b1 = h & 1; /* diameter */
	float dx = 4 * (1.0 - a) * b*b, dy = 4 * (b1 + 1) * a*a; /* error increment */
	float err = dx + dy + b1 * a*a, e2; /* error of 1.step */

	x1 = x0 + w;
	y0 += (b + 1) / 2;
	y1 = y0 - b1; /* starting pixel */
	a = 8 * a*a;
	b1 = 8 * b*b;

	do {
		setPixel(x1, y0); /*   I. Quadrant */
		setPixel(x0, y0); /*  II. Quadrant */
		setPixel(x0, y1); /* III. Quadrant */
		setPixel(x1, y1); /*  IV. Quadrant */
		e2 = 2 * err;
		if (e2 <= dy) {
			y0++;
			y1--;
			err += dy += a;
		} /* y step */
		if (e2 >= dx || 2 * err > dy) {
			x0++;
			x1--;
			err += dx += b1;
		} /* x step */
	} while (x0 <= x1);

	while (y0 - y1 <= h) { /* too early stop of flat ellipses a=1 */
		setPixel(x0 - 1, y0); /* -> finish tip of ellipse */
		setPixel(x1 + 1, y0++);
		setPixel(x0 - 1, y1);
		setPixel(x1 + 1, y1--);
	}
}

void
TVoutEx::drawEllipse(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, Color_t c)
{
	_currentColor[0] = c;
	drawEllipse(x0, y0, w, h);
}

void
TVoutEx::drawRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h)
{
	if ((w == 0) || (h == 0))
		return;
	if ((w == 1) && (h == 1))
		setPixel(x0, y0);
	else if (w == 1)
		drawColumn(x0, y0, y0+h-1);
	else if (h == 1)
		drawRow(y0, x0, y0+w-1);
	else {
		swap(_currentColor[0], _currentColor[1]);
		if (_currentColor[1] != NOT_A_COLOR) {
			for (unsigned char i = y0; i < y0 + h; i++)
				drawRow(i, x0, x0 + w);
		}
		swap(_currentColor[0], _currentColor[1]);

		drawLine(x0, y0, x0 + w, y0);
		drawLine(x0, y0, x0, y0 + h);
		drawLine(x0 + w, y0, x0 + w, y0 + h);
		drawLine(x0, y0 + h, x0 + w, y0 + h);
	}
}

/* draw a rectangle at x,y with a specified width and height
 *
 * Arguments:
 *	x0:
 *		The x coordinate of upper left corner of the rectangle.
 *	y0:
 *		The y coordinate of upper left corner of the rectangle.
 *	w:
 *		The widht of the rectangle.
 *	h:
 *		The height of the rectangle.
 *	c:
 *		The color of the rectangle.
 *		(see color note at the top of this file)
 *	fc:
 *		The fill color of the rectangle.
 *		(see color note at the top of this file)
 *		default =-1 (no fill)
 */
void
TVoutEx::drawRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, Color_t c, Color_t fc)
{
	_currentColor[0] = c, _currentColor[1] = fc;
	drawRect(x0, y0, w, h);
} // end of draw_rect

/* draw a circle given a coordinate x,y and radius both filled and non filled.
 *
 * Arguments:
 * 	x0:
 *		The x coordinate of the center of the circle.
 *	y0:
 *		The y coordinate of the center of the circle.
 *	radius:
 *		The radius of the circle.
 *	c:
 *		The color of the circle.
 *		(see color note at the top of this file)
 *	fc:
 *		The color to fill the circle.
 *		(see color note at the top of this file)
 *		defualt  =-1 (do not fill)
 */
void
TVoutEx::drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, Color_t c, Color_t fc)
{
	_currentColor[0] = c, _currentColor[1] = fc;
	drawCircle(x0, y0, radius);
} // end of draw_circle



void
TVoutEx::drawCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	uint8_t pyy = y, pyx = x;

	//there is a fill color
	if (_currentColor[1] != NOT_A_COLOR)
		drawRow(y0, x0 - radius, x0 + radius, _currentColor[1]);

	sp(x0, y0 + radius, _currentColor[0]);
	sp(x0, y0 - radius, _currentColor[0]);
	sp(x0 + radius, y0, _currentColor[0]);
	sp(x0 - radius, y0, _currentColor[0]);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		//there is a fill color
		if (_currentColor[1] != NOT_A_COLOR) {
			//prevent double draws on the same rows
			if (pyy != y) {
				drawRow(y0 + y, x0 - x, x0 + x, _currentColor[1]);
				drawRow(y0 - y, x0 - x, x0 + x, _currentColor[1]);
			}
			if (pyx != x && x != y) {
				drawRow(y0 + x, x0 - y, x0 + y, _currentColor[1]);
				drawRow(y0 - x, x0 - y, x0 + y, _currentColor[1]);
			}
			pyy = y;
			pyx = x;
		}
		sp(x0 + x, y0 + y, _currentColor[0]);
		sp(x0 - x, y0 + y, _currentColor[0]);
		sp(x0 + x, y0 - y, _currentColor[0]);
		sp(x0 - x, y0 - y, _currentColor[0]);
		sp(x0 + y, y0 + x, _currentColor[0]);
		sp(x0 - y, y0 + x, _currentColor[0]);
		sp(x0 + y, y0 - x, _currentColor[0]);
		sp(x0 - y, y0 - x, _currentColor[0]);
	}
}


/* place a bitmap at x,y where the bitmap is defined as {width,height,imagedata....}
 *
 * Arguments:
 *	x:
 *		The x coordinate of the upper left corner.
 *	y:
 *		The y coordinate of the upper left corner.
 *	bmp:
 *		The bitmap data to print.
 *	i:
 *		The offset into the image data to start at.  This is mainly used for fonts.
 *		default	=0
 *	width:
 *		Override the bitmap width. This is mainly used for fonts.
 *		default =0 (do not override)
 *	height:
 *		Override the bitmap height. This is mainly used for fonts.
 *		default	=0 (do not override)
 */
void
TVoutEx::bitmap(uint8_t x, uint8_t y, const uint8_t* bmp,
    uint16_t i, uint8_t width, uint8_t lines)
{
	uint8_t temp, lshift, rshift, save, xtra;
	uint16_t si = 0;

	rshift = x & 7;
	lshift = 8 - rshift;
	if (width == 0) {
		width = pgm_read_byte(bmp+i);
		i++;
	}
	if (lines == 0) {
		lines = pgm_read_byte(bmp+i);
		i++;
	}

	if (width & 7) {
		xtra = width & 7;
		width = width / 8;
		width++;
	} else {
		xtra = 8;
		width = width / 8;
	}

	for (uint8_t l = 0; l < lines; l++) {
		si = (y + l) * display.hres + x / 8;
		if (width == 1)
			temp = 0xff >> (rshift + xtra);
		else
			temp = 0;
		save = screen[si];
		screen[si] &= ((0xff << lshift) | temp);
		temp = pgm_read_byte(bmp+(i++));
		screen[si++] |= temp >> rshift;
		for (uint16_t b = i + width - 1; i < b; i++) {
			save = screen[si];
			screen[si] = temp << lshift;
			temp = pgm_read_byte(bmp+i);
			screen[si++] |= temp >> rshift;
		}
		if (rshift + xtra < 8)
			screen[si - 1] |= (save & (0xff >> (rshift + xtra))); //test me!!!
		if (rshift + xtra - 8 > 0)
			screen[si] &= (0xff >> (rshift + xtra - 8));
		screen[si] |= temp << lshift;
	}
} // end of bitmap

void
TVoutEx::setColor(Color_t c)
{
	_currentColor[0] = c;
}

void
TVoutEx::setColor(Color_t c, Color_t b)
{
    _currentColor[0] = c, _currentColor[1] = b;
}

void TVoutEx::setFill(Color_t c)
{
	_currentColor[1] = c;
}

void
TVoutEx::setPosition(uint8_t x, uint8_t y)
{
	if (x >= display.hres * 8)
		x = display.hres * 8 - 1;
	if (y >= display.vres)
		y = display.vres - 1;
	_currentPosition[0] = x, _currentPosition[1] = y;
}

void
TVoutEx::setCursorVisible(bool newVal)
{
	while (_lockCursor);
	_lockCursor = true;
	restore_cursor();
	if (newVal)
		vbiHook = vBlank;
	else
		vbiHook = emptyFunction;
	_lockCursor = false;
}

/* shift the pixel buffer in any direction
 * This function will shift the screen in a direction by any distance.
 *
 * Arguments:
 *	distance:
 *		The distance to shift the screen
 *	direction:
 *		The direction to shift the screen the direction and the integer values:
 *		UP		=0
 *		DOWN	=1
 *		LEFT	=2
 *		RIGHT	=3
 */
void
TVoutEx::shift(uint8_t distance, Direction_t direction)
{
	uint8_t *src;
	uint8_t *dst;
	uint8_t *end;
	uint8_t shift;
	uint8_t tmp;
	const uint16_t diff = distance * display.hres;
	
	switch (direction) {
	case UP:
		dst = display.screen;
		src = display.screen + diff;
		end = display.screen + display.vres * display.hres;
#if TVOUT_DEBUG
		SerialL.println(intptr_t(end), HEX);
		SerialL.println(intptr_t(end-src), HEX);
#endif
#if USE_STRINGH_FUNCS
		memmove(dst, src, intptr_t(end)-intptr_t(src));
		memset(end - diff, 0, diff);
#else
		while (src < end) {
			*dst = *src;
			*src = 0;
			dst++;
			src++;
		}
#endif
		break;
	case DOWN:
		dst = display.screen + display.vres * display.hres - 1;
		src = dst - diff;
		end = display.screen;
#if USE_STRINGH_FUNCS
		memmove(end+diff, end, display.size()-diff);
		memset(end, 0, diff);
#else
		while (src >= end) {
			*dst = *src;
			*src = 0;
			dst--;
			src--;
		}
#endif
		break;
	case LEFT:
		shift = distance & 7;

		for (uint8_t line = 0; line < display.vres; line++) {
			dst = display.screen + display.hres*line;
			src = dst + distance / 8;
			end = dst + display.hres - 2;
			while (src <= end) {
				tmp = 0;
				tmp = *src << shift;
				*src = 0;
				src++;
				tmp |= *src >> (8 - shift);
				*dst = tmp;
				dst++;
			}
			tmp = 0;
			tmp = *src << shift;
			*src = 0;
			*dst = tmp;
		}
		break;
	case RIGHT:
		shift = distance & 7;

		for (uint8_t line = 0; line < display.vres; line++) {
			dst = display.screen + display.hres - 1 + display.hres*line;
			src = dst - distance / 8;
			end = dst - display.hres + 2;
			while (src >= end) {
				tmp = 0;
				tmp = *src >> shift;
				*src = 0;
				src--;
				tmp |= *src << (8 - shift);
				*dst = tmp;
				dst--;
			}
			tmp = 0;
			tmp = *src >> shift;
			*src = 0;
			*dst = tmp;
		}
		break;
	}
} // end of shift

/* set the vertical blank function call
 * The function passed to this function will be called one per frame. The function should be quickish.
 *
 * Arguments:
 *	func:
 *		The function to call.
 */
void
TVoutEx::set_vbi_hook(void (*func)())
{
	vbiHook = func;
} // end of set_vbi_hook

/* set the horizonal blank function call
 * This function passed to this function will be called one per scan line.
 * The function MUST be VERY FAST(~2us max).
 *
 * Arguments:
 *	funct:
 *		The function to call.
 */
void
TVoutEx::set_hbi_hook(void (*func)())
{
	hbiHook = func;
} // end of set_bhi_hook

/* Simple tone generation
 *
 * Arguments:
 *	frequency:
 *		the frequency of the tone
 * courtesy of adamwwolf
 */
void
TVoutEx::tone(unsigned int frequency)
{
	tone(frequency, 0);
} // end of tone

/* Simple tone generation
 *
 * Arguments:
 *	frequency:
 *		the frequency of the tone
 *	duration_ms:
 *		The duration to play the tone in ms
 * courtesy of adamwwolf
 */
void
TVoutEx::tone(unsigned int frequency, unsigned long duration_ms)
{
	if (frequency == 0)
		return;

#if defined(__AVR_ATmega32U4__)
#define TIMER 0
#else
#define TIMER 2
#endif
	//this is init code
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2A |= _BV(WGM21);
	TCCR2B |= _BV(CS20);
	//end init code

	//most of this is taken from Tone.cpp from Arduino
	uint8_t prescalarbits = 0b001;
	uint32_t ocr = 0;

	DDR_SND |= _BV(SND_PIN); //set pb3 (digital pin 11) to output

	//we are using an 8 bit timer, scan through prescalars to find the best fit
	ocr = F_CPU / frequency / 2 - 1;
	prescalarbits = 0b001; // ck/1: same for both timers
	if (ocr > 255) {
		ocr = F_CPU / frequency / 2 / 8 - 1;
		prescalarbits = 0b010; // ck/8: same for both timers

		if (ocr > 255) {
			ocr = F_CPU / frequency / 2 / 32 - 1;
			prescalarbits = 0b011;
		}

		if (ocr > 255) {
			ocr = F_CPU / frequency / 2 / 64 - 1;
			prescalarbits = TIMER == 0 ? 0b011 : 0b100;
			if (ocr > 255) {
				ocr = F_CPU / frequency / 2 / 128 - 1;
				prescalarbits = 0b101;
			}

			if (ocr > 255) {
				ocr = F_CPU / frequency / 2 / 256 - 1;
				prescalarbits = TIMER == 0 ? 0b100 : 0b110;
				if (ocr > 255) {
					// can't do any better than /1024
					ocr = F_CPU / frequency / 2 / 1024 - 1;
					prescalarbits = TIMER == 0 ? 0b101 : 0b111;
				}
			}
		}
	}
	TCCR2B = prescalarbits;

	if (duration_ms > 0)
		remainingToneVsyncs = duration_ms * 60 / 1000; //60 here represents the framerate
	else
		remainingToneVsyncs = -1;

	// Set the OCR for the given timer,
	OCR2A = ocr;
	//set it to toggle the pin by itself
	TCCR2A &= ~(_BV(COM2A1)); //set COM2A1 to 0
	TCCR2A |= _BV(COM2A0);
} // end of tone

/* Stops tone generation
 */
void
TVoutEx::noTone()
{
	TCCR2B = 0;
	PORT_SND &= ~(_BV(SND_PIN)); //set pin 11 to 0
} // end of noTone

void
TVoutEx::selectFont(const uint8_t *f)
{
	_font.setRawFont(f);
}

/*
 * print an 8x8 char c at x,y
 * x must be a multiple of 8
 */
void
TVoutEx::printChar(uint8_t x, uint8_t y, unsigned char c)
{
	const uint8_t offset = pgm_read_byte(_font.rawFont() + 2);
	c -= offset;
	bitmap(x, y, _font.rawFont(), (c*_font.height()) + 3, _font.width(), _font.height());
}

void
TVoutEx::incTxtline()
{
	if (cursor_y > (display.vres - 2*_font.height())) {
#if TVOUT_DEBUG
		SerialL.println(__PRETTY_FUNCTION__);
		dump();
#endif
		shift(_font.height(), UP);
	} else
		cursor_y += _font.height();
}

void
TVoutEx::write(uint8_t c)
{
#if TVOUT_DEBUG
	SerialL.write(c);
#endif
	_lockCursor = true;
	switch (c) {
	case '\0': //null
		break;
	case '\n': //line feed
		restore_cursor();
		incTxtline();
		break;
	case 8: //backspace
		restore_cursor();
		if (cursor_x > 0)
			cursor_x -= _font.width();
		else if (cursor_y>0) {
			cursor_x = hres() - _font.width();
			cursor_y -= _font.height();
		} else
			break;
		printChar(cursor_x, cursor_y, ' ');
		break;
	case '\r': //carriage return !?!?!?!VT!?!??!?!
		restore_cursor();
		cursor_x = 0;
		break;
	case '\t':
		write(' ');
		break;
	default:
		printChar(cursor_x, cursor_y, c);
		if (cursor_x >= (hres() - _font.width())) {
			restore_cursor();
			setCursor(0, cursor_y);
			incTxtline();
		} else
			cursor_x += _font.width();
	}
	_lockCursor = false;
}

void
TVoutEx::vBlank()
{
	Color_t col; // Color to draw cursor
	// If was begin() and cursor is not locked by the non-interrupt code
	if (_instance != NULL && !_instance->_lockCursor) {
		// Count down cursor blank interrupt counter
		if (--_instance->_cursorCounter == 0)
			_instance->_cursorCounter = CURSOR_BLINK_PERIOD;
		else
			return;
		_instance->_cursorState = !_instance->_cursorState;
		if (_instance->_cursorState)
			col = WHITE;
		else
			col = BLACK;
		_instance->drawRow(_instance->cursor_y+
		    _instance->_font.height()-1, _instance->cursor_x,
		    _instance->cursor_x+_instance->_font.width(), col);
	}
}

void
TVoutEx::setCursor(uint8_t x, uint8_t y)
{
	cursor_x = x;
	cursor_y = y;
}

void
TVoutEx::setCursorCharPosition(uint8_t x, uint8_t y)
{
	cursor_x = x*_font.width();
	cursor_y = y*_font.height();
}

void
TVoutEx::restore_cursor()
{
	if (_cursorState) {
		_cursorState = false;
		drawRow(cursor_y+_instance->_font.height()-1, cursor_x,
                    cursor_x+_instance->_font.width(), BLACK);
	}
}

void
TVoutEx::setCursorX(uint8_t x)
{
	_lockCursor = true;
	restore_cursor();
	cursor_x = _font.width() * x;
	_lockCursor = false;
}

uint8_t
TVoutEx::getCursorX() const
{
	return cursor_x / _font.width();
}

#if TVOUT_DEBUG
void
TVoutEx::dump()
{
	SerialL.println(__PRETTY_FUNCTION__);
	SerialL.print("This:      "), SerialL.println(intptr_t(this));
	SerialL.print("Instance:  "), SerialL.println(intptr_t(_instance));
	SerialL.print("Cursor:    "), SerialL.print(cursor_x), SerialL.write(' '),
	    SerialL.println(cursor_y);
	SerialL.print("Cursor lock:"), SerialL.println(_lockCursor);
	SerialL.print("VBI:"), SerialL.println(intptr_t(vbiHook));
	SerialL.print("HBI:"), SerialL.println(intptr_t(hbiHook));
}
#endif

#ifdef UNIT_TEST

static uint8_t vbuf[TVoutEx::bufferSize(32, 32)+2];
static TVoutEx tvOut;

void
setup()
{
	Serial.begin(115200);
	Serial.println(__PRETTY_FUNCTION__);
	
	tvOut.begin(PAL, 32, 32, vbuf+1);
	tvOut.selectFont(font8x8);
        
	tvOut.shift(1, DOWN);
}

void
loop()
{
	if (Serial.available())
		tvOut.write(Serial.read());
}
#endif

