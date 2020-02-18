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

/**
 * This library provides a simple method for outputting data to a tv
 * from a frame buffer stored in sram.  This implementation is done
 * completly by interupt and will return give as much cpu time to the
 * application as possible.
 */

#ifndef TVOUT_H
#define TVOUT_H

#include <stdint.h>
#include <Arduino.h>
#include <stdlib.h>

#include "VideoGen.h"
#include "spec/HardwareSetup.h"
#include "spec/VideoProperties.h"

#define TVOUT_DEBUG 0
// Use memcpy, memmove, memcpy and memset instead of byte cycles
// It can increase the speed of scrolling operations
#define USE_STRINGH_FUNCS 1

#define CURSOR_BLINK_PERIOD 15

#define NOTCOPYABLE(ClassName)        \
private:                                  \
  ClassName(const ClassName&) = delete;   \
  ClassName(ClassName&&) = delete;        \
  ClassName &operator =(const ClassName&) = delete;

enum Color_t : uint8_t
{
	NOT_A_COLOR = uint8_t(-1),
	BLACK = 0,
	WHITE = 1,
	INVERT = 2
};

enum Direction_t : uint8_t
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

/**
 * TVout.cpp contains a brief expenation of each function.
 */
class TVoutEx final
{
	NOTCOPYABLE(TVoutEx)
public:
        /**
	 * Error codes
	 */
	enum Error_t
	{
		NO_ERROR = 0,
		NOT_A_POWER_OF_2,
		MULTIPLE_INSTANCES,
		NULL_BUFFER,
		OUT_OF_MEMORY
	};
	/**
	 * Raster font
	 */
	class Font
	{
	public:
		void setRawFont(const uint8_t*);
		const uint8_t *rawFont() const;
		uint8_t width() const;
		uint8_t height() const;
	private:
		const uint8_t* font;
	};

	explicit TVoutEx();
	~TVoutEx();

	static TVoutEx *instance()
	{
		return _instance;
	}

	void clearScreen()
	{
		fill(BLACK);
	}

	void invert()
	{
		fill(INVERT);
	}

	/**
	 * @brief Init display with pre-allocated buffer
	 * @param mode PAL or NTSC
	 * @param x Horizontal resolution (must be divisable by 8)
	 * @param y Vertical resolution
	 * @param buf screen buffer pointer
	 * @return code
	 */
	Error_t begin(VideMode_t, uint8_t, uint8_t, uint8_t*);
	/**
	 * @brief Get required buffer size for given resolution
	 * @param x
	 * @param y
	 * @return 
	 */
	static constexpr size_t bufferSize(uint8_t x, uint8_t y)
	{
		return size_t(x / 8) * size_t(y);
	}

	void end();

	//accessor functions
	uint8_t hres() const;
	uint8_t vres() const;
	
	/**
	 * @brief Get the number of characters that will fit on a line
	 *
	 * @return The number of characters that will fit on a text line
	 * starting from x=0. Will return -1 for dynamic width fonts as this
	 * cannot be determined.
	 */
	char charLine() const;

	//flow control functions
	void delay_frame(unsigned int x);
	unsigned long millis();

	//override setup functions
	void force_vscale(char sfactor);
	void force_outstart(uint8_t time);
	void force_linestart(uint8_t line);

	//basic rendering functions
	void setPixel(uint8_t, uint8_t);
	void setPixel(uint8_t x, uint8_t y, Color_t c);
	Color_t getPixel(uint8_t, uint8_t);
	
	void fill(Color_t color);
	void shift(uint8_t distance, Direction_t);
	
	void drawLine(uint8_t, uint8_t, uint8_t, uint8_t);
	void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, Color_t c);
	
	void drawLineTo(uint8_t, uint8_t);
	
	/**
	 * @brief Fill a row from one point to another
	 * 
	 * @param line The row, fill will be performed on.
	 * @param x0 edge 0 of the fill.
	 * @param x1 edge 1 of the fill.
	 */
	void drawRow(uint8_t, uint16_t, uint16_t);
	/**
	 * 
	 * @param line The row, fill will be performed on.
	 * @param x0 edge 0 of the fill
	 * @param x1 edge 1 of the fill
	 * @param c color
	 */
	void drawRow(uint8_t, uint16_t, uint16_t, Color_t);
	
	void drawColumn(uint8_t row, uint16_t y0, uint16_t y1);
	void drawColumn(uint8_t row, uint16_t y0, uint16_t y1, Color_t c);
	
	void drawEllipse(uint8_t, uint8_t, uint8_t, uint8_t);
	void drawEllipse(uint8_t, uint8_t, uint8_t, uint8_t, Color_t);
	
	void drawRect(uint8_t, uint8_t, uint8_t, uint8_t);
	void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, Color_t, Color_t = NOT_A_COLOR);
	
	void drawCircle(uint8_t, uint8_t, uint8_t);
	void drawCircle(uint8_t, uint8_t, uint8_t, Color_t, Color_t = NOT_A_COLOR);
	
	void bitmap(uint8_t, uint8_t, const uint8_t*, uint16_t=0, uint8_t=0, uint8_t=0);
	
	void setColor(Color_t);
        void setColor(Color_t, Color_t);
	
        void setFill(Color_t);
	
	void setPosition(uint8_t, uint8_t);
	
	void setCursorVisible(bool);

	//hook setup functions
	void set_vbi_hook(void (*func)());
	void set_hbi_hook(void (*func)());

	//tone functions
	void tone(unsigned int frequency, unsigned long duration_ms);
	void tone(unsigned int frequency);
	void noTone();

	//The following function definitions can be found in TVoutPrint.cpp
	//printing functions
	void printChar(uint8_t x, uint8_t y, unsigned char c);
	void setCursor(uint8_t, uint8_t);
	void setCursorCharPosition(uint8_t, uint8_t);

	void setCursorX(uint8_t);
	uint8_t getCursorX() const;

	uint8_t
	getCursorY() const
	{
		return (cursor_y);
	}
	void selectFont(const uint8_t*);

	void write(uint8_t);

#if TVOUT_DEBUG
	void dump();
#endif
#ifdef SDL_DEBUG
	static void update();
#endif
private:
#ifdef SDL_DEBUG
	void _initSDL();
	static int _sdlThread(void*);
	static uint32_t _sdlTimerCallback(uint32_t, void*);
#endif
	
	static void vBlank();
	// Implicit singleton instance
	static TVoutEx *_instance;

	void incTxtline();
	
	void restore_cursor();

	// Frame buffer
	uint8_t	*screen;
	// Blinking state of the cursor
	bool	 _cursorState;
	// Cursor state change lock TODO atomic type
	bool	 _lockCursor;
	// sync interrupts between cursor blink cycles
	uint8_t	 _cursorCounter;
	uint8_t	 cursor_x, cursor_y;
	Color_t _currentColor[2];
	uint8_t _currentPosition[2];
	Font	 _font;
};

#endif
