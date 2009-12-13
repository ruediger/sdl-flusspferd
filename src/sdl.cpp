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

#include "flusspferd/modules.hpp"
#include "flusspferd/security.hpp"

#include <stdexcept>
#include <cassert>
#include <limits>

#include <SDL.h>

#include "general.hpp"
#include "video.hpp"
#include "wm.hpp"
#include "events.hpp"
#include "mouse.hpp"
#include "joystick.hpp"

using namespace flusspferd;

namespace sdl {
  FLUSSPFERD_LOADER_SIMPLE(sdl) {
    local_root_scope scope;

    load_general(sdl);
    load_video(sdl);
    load_wm(sdl);
    load_events(sdl);
    load_mouse(sdl);
    load_joystick(sdl);
  }
}
