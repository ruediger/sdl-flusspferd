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

#include <stdexcept>
#include <cassert>

#include <SDL.h>

// DEBUG(
#include "flusspferd/value_io.hpp"
#include <iostream>
// DEBUG)

using namespace flusspferd;

namespace sdl {
  object rect2object(SDL_Rect const &r) {
    object rect(flusspferd::create_object());
    rect.set_property("h", r.h);
    rect.set_property("w", r.w);
    rect.set_property("x", r.x);
    rect.set_property("y", r.y);
    return rect;
  }

  SDL_Rect object2rect(object const &o) {
    SDL_Rect ret;
    if(!o.has_property("h")) {
      throw flusspferd::exception("Rect: Missing property 'h'");
    }
    else if(!o.has_property("w")) {
      throw flusspferd::exception("Rect: Missing property 'w'");
    }
    else if(!o.has_property("x")) {
      throw flusspferd::exception("Rect: Missing property 'x'");
    }
    else if(!o.has_property("y")) {
      throw flusspferd::exception("Rect: Missing property 'y'");
    }
    ret.h = o.get_property("h").get_int();
    ret.w = o.get_property("w").get_int();
    ret.x = o.get_property("x").get_int();
    ret.y = o.get_property("y").get_int();
    return ret;
  }

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   PixelFormat,
   (constructor_name, "PixelFormat")
   (constructible, false)
   (full_name, "sdl.PixelFormat")
   (properties,
    /* SDL_Palette *palette; */
    ("BitsPerPixel", getter, get_bitspp)
    ("BytesPerPixel", getter, get_bytespp)
    ("Rloss", getter, get_rloss)
    ("Gloss", getter, get_gloss)
    ("Bloss", getter, get_bloss)
    ("Aloss", getter, get_aloss)
    ("Rshift", getter, get_rshift)
    ("Gshift", getter, get_gshift)
    ("Bshift", getter, get_bshift)
    ("Ashift", getter, get_ashift)
    ("Rmask", getter, get_rmask)
    ("Gmask", getter, get_gmask)
    ("Bmask", getter, get_bmask)
    ("Amask", getter, get_amask)
    ("colorkey", getter, get_colorkey)
    ("alpha", getter, get_alpha))
   )
  {
  public:
    SDL_PixelFormat *format;

    int get_bitspp() {
      assert(format);
      return format->BitsPerPixel;
    }
    int get_bytespp() {
      assert(format);
      return format->BytesPerPixel;
    }
    int get_rloss() {
      assert(format);
      return format->Rloss;
    }
    int get_gloss() {
      assert(format);
      return format->Gloss;
    }
    int get_bloss() {
      assert(format);
      return format->Bloss;
    }
    int get_aloss() {
      assert(format);
      return format->Aloss;
    }
    int get_rshift() {
      assert(format);
      return format->Rshift;
    }
    int get_gshift() {
      assert(format);
      return format->Gshift;
    }
    int get_bshift() {
      assert(format);
      return format->Bshift;
    }
    int get_ashift() {
      assert(format);
      return format->Ashift;
    }
    int get_rmask() {
      assert(format);
      return format->Rmask;
    }
    int get_gmask() {
      assert(format);
      return format->Gmask;
    }
    int get_bmask() {
      assert(format);
      return format->Bmask;
    }
    int get_amask() {
      assert(format);
      return format->Amask;
    }
    int get_colorkey() {
      assert(format);
      return format->colorkey;
    }
    int get_alpha() {
      assert(format);
      return format->alpha;
    }

    PixelFormat(flusspferd::object const &self, SDL_PixelFormat *format)
      : base_type(self), format(format)
    {
      assert(format);
    }

    static PixelFormat &create(SDL_PixelFormat *format) {
      return flusspferd::create_native_object<PixelFormat>(object(), format);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
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
    ("clip_rect", getter, get_clip_rect)
    ("refcount", getter_setter, (get_refcount, set_refcount)))
   )
  {
  public:
    SDL_Surface *surface;

    Uint32 get_flags() {
      assert(surface);
      return surface->flags;
    }
    PixelFormat &get_format() {
      assert(surface);
      return PixelFormat::create(surface->format);
    }
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
    object get_clip_rect() {
      assert(surface);
      return rect2object(surface->clip_rect);
    }
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
      return flusspferd::create_native_object<Surface>(object(), surface);
    }
  };

  void quit() {
    SDL_Quit();
  }

  Surface &set_video_mode(int width, int height, int bpp, Uint32 flags) {
    SDL_Surface *surface = SDL_SetVideoMode(width, height, bpp, flags);
    if(!surface) {
      std::string const what = std::string("SDL_SetVideoMode: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  Surface &get_video_surface() {
    return Surface::create(SDL_GetVideoSurface());
  }

  int flip(Surface const &surface) {
    return SDL_Flip(surface.surface);
  }

  void update_rect(Surface const &screen, int x, int y, int w, int h) {
    SDL_UpdateRect(screen.surface, x, y, w, h);
  }

  int lock_surface(Surface const &surface) {
    return SDL_LockSurface(surface.surface);
  }

  void unlock_surface(Surface const &surface) {
    SDL_UnlockSurface(surface.surface);
  }

  void free_surface(Surface const &surface) {
    SDL_FreeSurface(surface.surface);
  }

  Surface &load_BMP(char const *file) {
    SDL_Surface *surface = SDL_LoadBMP(file);
    if(!surface) {
      std::string const what = std::string("SDL_LoadBMP: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  void blit_surface(flusspferd::call_context &x) {
    if(x.arg.size() == 2) {
      std::cerr << "DEBUG: " << x.arg[0] << ' ' << x.arg[1] << std::endl;
      if(!x.arg[0].is_object() || !flusspferd::is_native<Surface>(x.arg[0].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as first parameter");
      }
      SDL_Surface *src = flusspferd::get_native<Surface>(x.arg[0].get_object()).surface;
      if(!x.arg[1].is_object() || !flusspferd::is_native<Surface>(x.arg[1].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as second parameter");
      }
      SDL_Surface *dest = flusspferd::get_native<Surface>(x.arg[1].get_object()).surface;
      std::cerr << "blit\n";
      x.result = value(SDL_BlitSurface(src, 0x0, dest, 0x0));
      std::cerr << "done\n";
      return;
    }
    else if(x.arg.size() == 4) {
      if(!flusspferd::is_native<Surface>(x.arg[0].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as first parameter");
      }
      SDL_Surface *src = flusspferd::get_native<Surface>(x.arg[0].get_object()).surface;
      if(!flusspferd::is_native<Surface>(x.arg[1].get_object())) {
        throw flusspferd::exception("blitSurface: expected Rect as second parameter");
      }
      SDL_Rect srcrect = object2rect(x.arg[1].get_object());
      if(!flusspferd::is_native<Surface>(x.arg[2].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as third parameter");
      }
      SDL_Surface *dest = flusspferd::get_native<Surface>(x.arg[2].get_object()).surface;
      if(!flusspferd::is_native<Surface>(x.arg[3].get_object())) {
        throw flusspferd::exception("blitSurface: expected Rect as fourth parameter");
      }
      SDL_Rect destrect = object2rect(x.arg[3].get_object());
      x.result = value(SDL_BlitSurface(src, &srcrect, dest, &destrect));
      return;
    }
    else {
      throw flusspferd::exception("blitSurface: expected two or four parameter ( blitSurface(from, to) || blitSurface(from, from_rect, to, to_rext) )");
    }
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
    create_native_function(sdl, "getError", &::SDL_GetError);
    sdl.define_property("SWSURFACE", value(SDL_SWSURFACE));
    sdl.define_property("HWSURFACE", value(SDL_HWSURFACE));
    sdl.define_property("ASYNCBLIT", value(SDL_ASYNCBLIT));
    sdl.define_property("ANYFORMAT", value(SDL_ANYFORMAT));
    sdl.define_property("HWPALETTE", value(SDL_HWPALETTE));
    sdl.define_property("DOUBLEBUF", value(SDL_DOUBLEBUF));
    sdl.define_property("FULLSCREEN", value(SDL_FULLSCREEN));
    sdl.define_property("OPENGL", value(SDL_OPENGL));
    sdl.define_property("OPENGLBLIT", value(SDL_OPENGLBLIT));
    sdl.define_property("RESIZABLE", value(SDL_RESIZABLE));
    sdl.define_property("NOFRAME", value(SDL_NOFRAME));
    create_native_function(sdl, "setVideoMode", &sdl::set_video_mode);
    create_native_function(sdl, "getVideoSurface", &sdl::get_video_surface);
    load_class<sdl::Surface>(sdl);
    load_class<sdl::PixelFormat>(sdl);
    create_native_function(sdl, "flip", &sdl::flip);
    create_native_function(sdl, "updateRect", &sdl::update_rect);
    create_native_function(sdl, "lockSurface", &sdl::lock_surface);
    create_native_function(sdl, "unlockSurface", &sdl::unlock_surface);
    create_native_function(sdl, "freeSurface", &sdl::free_surface);
    create_native_function(sdl, "loadBMP", &sdl::load_BMP);
    boost::function< void(call_context &)> blit_surface_ = &sdl::blit_surface;
    create_native_function(sdl, "blitSurface", blit_surface_);
  }
}
