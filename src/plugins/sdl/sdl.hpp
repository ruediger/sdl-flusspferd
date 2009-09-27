// -*- mode:c++; -*- vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:enc=utf-8:
/*
Functions to Wrap and Unwrap SDL Handlers.

The MIT License

Copyright (c) 2009 Rüdiger Sonderfeld

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef FLUSSPFERD_PLUGINS_SDL_SDL_HPP
#define FLUSSPFERD_PLUGINS_SDL_SDL_HPP

#include <SDL.h>

namespace sdl {
	// Video:
	class Surface;
	Surface &wrap(SDL_Surface *s);
	SDL_Surface *unwrap(Surface &s);

	class PixelFormat;
	PixelFormat &wrap(SDL_PixelFormat *p);
	SDL_PixelFormat *unwrap(PixelFormat &p);

	class PixelData;
	PixelData &wrap(void *p);
	void *unwrap(PixelData &p);

	class Color;
	Color &wrap(SDL_Color const &p);
	SDL_Color &unwrap(Color &p);

	// Events:
	class ActiveEvent;
	ActiveEvent &wrap(SDL_ActiveEvent const &p);
	SDL_ActiveEvent &unwrap(ActiveEvent &p);

	class Keysym;
	Keysym &wrap(SDL_keysym const &p);
	SDL_keysym &unwrap(Keysym &p);

	class KeyboardEvent;
	KeyboardEvent &wrap(SDL_KeyboardEvent const &p);
	SDL_KeyboardEvent &unwrap(KeyboardEvent &p);

	class MouseMotionEvent;
	MouseMotionEvent &wrap(SDL_MouseMotionEvent const &p);
	SDL_MouseMotionEvent &unwrap(MouseMotionEvent &p);

	class MouseButtonEvent;
	MouseButtonEvent &wrap(SDL_MouseButtonEvent const &p);
	SDL_MouseButtonEvent &unwrap(MouseButtonEvent &p);

	class JoyAxisEvent;
	JoyAxisEvent &wrap(SDL_JoyAxisEvent const &p);
	SDL_JoyAxisEvent &unwrap(JoyAxisEvent &p);

	class JoyButtonEvent;
	JoyButtonEvent &wrap(SDL_JoyButtonEvent const &p);
	SDL_JoyButtonEvent &unwrap(JoyButtonEvent &p);

	class JoyHatEvent;
	JoyHatEvent &wrap(SDL_JoyHatEvent const &p);
	SDL_JoyHatEvent &unwrap(JoyHatEvent &p);

	class JoyBallEvent;
	JoyBallEvent &wrap(SDL_JoyBallEvent const &p);
	SDL_JoyBallEvent &unwrap(JoyBallEvent &p);

	class ResizeEvent;
	ResizeEvent &wrap(SDL_ResizeEvent const &p);
	SDL_ResizeEvent &unwrap(ResizeEvent &p);

	class ExposeEvent;
	ExposeEvent &wrap(SDL_ExposeEvent const &p);
	SDL_ExposeEvent &unwrap(ExposeEvent &p);

	class QuitEvent;
	QuitEvent &wrap(SDL_QuitEvent const &p);
	SDL_QuitEvent &unwrap(QuitEvent &p);

	class Event;
	Event &wrap(SDL_Event const &p);
	SDL_Event &unwrap(Event &p);

	// Joystick:
	class Joystick;
	Joystick &wrap(SDL_Joystick *j);
	SDL_Joystick *unwrap(Joystick &j);
}

#endif
