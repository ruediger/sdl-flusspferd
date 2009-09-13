// -*- mode:c++; coding:utf-8; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2; -*- vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:enc=utf-8:
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

#include "flusspferd/class.hpp"
#include "flusspferd/create.hpp"
#include "flusspferd/modules.hpp"
#include "flusspferd/security.hpp"
#include "flusspferd/class_description.hpp"

#include <cassert>

#include <SDL.h>

using namespace flusspferd;

namespace sdl {
  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Surface,
   (constructor_name, "Surface")
   (constructible, false)
   (full_name, "sdl.Surface")
   (properties,
    ("flags", getter, get_flags)
    ("width", getter, get_width)
    ("w", getter, get_width)
    ("height", getter, get_height)
    ("h", getter, get_height)
    ("pitch", getter, get_pitch)
    ("refcount", getter_setter, (get_refcount, set_refcount)))
   )
  {
  public:
    SDL_Surface *surface;

    Uint32 get_flags() {
      assert(surface);
      return surface->flags;
    }
    // TODO PixelFormat
    int get_width() {
      assert(surface);
      return surface->w;
    }
    int get_height() {
      assert(surface);
      return surface->h;
    }
    Uint16 get_pitch() {
      assert(surface);
      return surface->pitch;
    }
    // TODO pixels
    // TODO clip_rect
    int get_refcount() {
      assert(surface);
      return surface->refcount;
    }
    void set_refcount(int r) {
      assert(surface);
      surface->refcount = r;
    }

    Surface(flusspferd::object const &self, SDL_Surface *surface)
      : base_type(self), surface(surface)
    { }
  };

  void quit() {
    SDL_Quit();
  }

  FLUSSPFERD_LOADER_SIMPLE(sdl) {
    local_root_scope scope;

    sdl.define_property("INIT_TIMER", value(SDL_INIT_TIMER));
    sdl.define_property("INIT_AUDIO", value(SDL_INIT_AUDIO));
    sdl.define_property("INIT_VIDEO", value(SDL_INIT_VIDEO));
    sdl.define_property("INIT_CDROM", value(SDL_INIT_CDROM));
    sdl.define_property("INIT_JOYSTICK", value(SDL_INIT_JOYSTICK));
    sdl.define_property("INIT_EVERYTHING", value(SDL_INIT_EVERYTHING));
    sdl.define_property("INIT_NOPARACHUTE", value(SDL_INIT_NOPARACHUTE));
    sdl.define_property("INIT_EVENTTHREAD", value(SDL_INIT_EVENTTHREAD));

    create_native_function(sdl, "init", &::SDL_Init);
    create_native_function(sdl, "quit", &sdl::quit);
    create_native_function(sdl, "get_error", &::SDL_GetError);

    load_class<sdl::Surface>(sdl);
  }
}
