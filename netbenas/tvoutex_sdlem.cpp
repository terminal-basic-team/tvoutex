/*
 * Terminal-BASIC is a lightweight BASIC-like language interpreter
 * Copyright (c) 2017,2018 Andrey V. Skvortsov
 * Copyright (C) 2019,2020 Terminal-BASIC team
 *     <https://bitbucket.org/%7Bf50d6fee-8627-4ce4-848d-829168eedae5%7D/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "TVoutEx.h"

#ifdef SDL_DEBUG

#include <SDL2/SDL.h>
#include <stdexcept>

#include "bytearray.hpp"
#include "utility/Font6x8.h"
#include "utility/Font8x8.h"

#define SDL_ASSERT(a) { if (!(a)) throw std::runtime_error(SDL_GetError()); }

static SDL_Window *window = nullptr;
static const uint8_t scale = 3;
static SDL_Renderer *renderer = nullptr;
static SDL_Thread *sdlThreadObject = nullptr;
static SDL_mutex *_lock = nullptr;
static SDL_cond *_cond = nullptr;

static bool _initialized = false;

static void
drawPoint(uint16_t x, uint16_t y)
{
	const uint16_t xs = x*scale+scale;
	const uint16_t ys = y*scale+scale;
	for (uint16_t _x = x*scale; _x<xs; ++_x)
		for (uint16_t _y=y*scale; _y<ys; ++_y)
			SDL_ASSERT(SDL_RenderDrawPoint(renderer, _x, _y) == 0);
}

int
TVoutEx::_sdlThread(void*)
{
	SDL_ASSERT(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) == 0);
	
	SDL_ASSERT((window = SDL_CreateWindow("TERMINAL BASIC", 100,100,
	    scale*TVoutEx::_instance->hres(),
	    scale*TVoutEx::_instance->vres(), 0)) != nullptr);
	
	SDL_ASSERT((renderer = SDL_CreateRenderer(window, -1, 0)) != nullptr);
	SDL_ASSERT(SDL_RenderClear(renderer) == 0);
	SDL_ASSERT(SDL_AddTimer(17, TVoutEx::_sdlTimerCallback, nullptr) != 0);
		
	_initialized = true;
	
	while (true) {
		SDL_ASSERT(SDL_LockMutex(_lock) == 0);
		SDL_ASSERT(SDL_CondWait(_cond, _lock) == 0);
		SDL_ASSERT(SDL_UnlockMutex(_lock) == 0);
		update();
	}
}

void
TVoutEx::_initSDL()
{
	SDL_ASSERT((sdlThreadObject = SDL_CreateThread(TVoutEx::_sdlThread,
	    "SDL THREAD", nullptr)) != nullptr);
	SDL_ASSERT((_lock = SDL_CreateMutex()) != nullptr);
	SDL_ASSERT((_cond = SDL_CreateCond()) != nullptr);
	while (!_initialized)
		SDL_Delay(1);
}

void
TVoutEx::update()
{
	SDL_ASSERT(SDL_SetRenderDrawColor(renderer, 0,0,0,255) == 0);
	SDL_ASSERT(SDL_RenderClear(renderer) == 0);
	SDL_ASSERT(SDL_SetRenderDrawColor(renderer, 255,255,255,255) == 0);
	
	for (uint8_t y=0; y<TVoutEx::_instance->vres(); ++y) {
		for (uint8_t x=0; x<TVoutEx::_instance->hres(); ++x) {
				if (TVoutEx::_instance->getPixel(x,y) == WHITE)
					drawPoint(x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

uint32_t
TVoutEx::_sdlTimerCallback(uint32_t interval, void*)
{
	if (vbiHook != nullptr)
		(*vbiHook)();
	
	SDL_ASSERT(SDL_LockMutex(_lock) == 0);
	SDL_ASSERT(SDL_CondBroadcast(_cond) == 0);
	SDL_ASSERT(SDL_UnlockMutex(_lock) == 0);
	
	return interval;
}

#endif // SDL_DEBUG
