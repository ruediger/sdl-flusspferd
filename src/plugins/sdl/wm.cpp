// -*- mode:c++; -*- vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:enc=utf-8:
/*
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
#include "wm.hpp"
#include "Surface.hpp"

#include <flusspferd/create.hpp>

#include <SDL.h>

using namespace flusspferd;
namespace sdl {
namespace {
	int wm_toggle_fullscreen(Surface &surface) {
    return SDL_WM_ToggleFullScreen(surface.surface);
  }

  void wm_set_icon(Surface &surface) {
    SDL_WM_SetIcon(surface.surface, 0x0);
  }

  int wm_grab_input(int mode) {
    return (int)SDL_WM_GrabInput((SDL_GrabMode)mode);
  }
}
	void load_wm(flusspferd::object &sdl) {
		create_native_function(sdl, "WMSetCaption", &::SDL_WM_SetCaption);
    create_native_function(sdl, "WMToggleFullScreen", &sdl::wm_toggle_fullscreen);
    create_native_function(sdl, "WMSetIcon", &sdl::wm_set_icon);
    create_native_function(sdl, "WMIconifyWindow", &::SDL_WM_IconifyWindow);
    sdl.define_property("GRAB_QUERY", value((int)SDL_GRAB_QUERY));
    sdl.define_property("GRAB_OFF", value((int)SDL_GRAB_OFF));
    sdl.define_property("GRAB_ON", value((int)SDL_GRAB_ON));
    create_native_function(sdl, "WMGrabInput", &sdl::wm_grab_input);
	}
}
