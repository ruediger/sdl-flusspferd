// -*- mode:c++; -*- vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:enc=utf-8:
/*
Wrapper for SDL_Surface. (Rest of implementation in video.cpp)

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
#ifndef FLUSSPFERD_PLUGINS_SDL_SURFACE_HPP
#define FLUSSPFERD_PLUGINS_SDL_SURFACE_HPP

#include <flusspferd/object.hpp>
#include <flusspferd/class_description.hpp>
#include <cassert>

#include <SDL.h>

namespace sdl {
  namespace bf = boost::fusion;
  class PixelFormat;
  class PixelData;

  FLUSSPFERD_CLASS_DESCRIPTION(
   Surface,
   (constructor_name, "Surface")
   (constructible, false)
   (full_name, "sdl.Surface")
   (properties,
    ("flags", getter, get_flags)
    ("format", getter, get_format)
    ("width", getter, get_width)
    ("w", getter, get_width)
    ("height", getter, get_height)
    ("h", getter, get_height)
    ("pitch", getter, get_pitch)
    ("pixels", getter, get_pixels)
    ("clip_rect", getter, get_clip_rect)
    ("refcount", getter_setter, (get_refcount, set_refcount)))
   )
  {
  public:
    SDL_Surface *surface;

    int get_flags() {
      assert(surface);
      return surface->flags;
    }
    PixelFormat &get_format();
    int get_width() {
      assert(surface);
      return surface->w;
    }
    int get_height() {
      assert(surface);
      return surface->h;
    }
    int get_pitch() {
      assert(surface);
      return surface->pitch;
    }
    PixelData &get_pixels();
		flusspferd::object get_clip_rect();
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
    {
      assert(surface);
    }

    static Surface &create(SDL_Surface *surface) {
      return flusspferd::create<Surface>(bf::make_vector(surface));
    }
  };
}

#endif
