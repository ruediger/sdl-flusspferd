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
#include "video.hpp"
#include "Surface.hpp"
#include "rect.hpp"

#include <flusspferd/create.hpp>
#include <flusspferd/create_on.hpp>
#include <flusspferd/create/object.hpp>
#include <flusspferd/create/function.hpp>
#include <flusspferd/class_description.hpp>

#include <SDL.h>

using namespace flusspferd;

namespace sdl {
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

		SDL_PixelFormat *data() { return format; }
		SDL_PixelFormat *get() {
			assert(format);
			return format;
		}

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
      return flusspferd::create<PixelFormat>(bf::make_vector(format));
    }
  };

  PixelFormat &wrap(SDL_PixelFormat *p) {
    return PixelFormat::create(p);
  }
  SDL_PixelFormat *unwrap(PixelFormat &p) {
    return p.data();
  }

  class Surface;

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   PixelData,
   (constructor_name, "PixelData")
   (constructible, false)
   (full_name, "sdl.PixelData")
   (methods,
    ("get", bind, get)
    ("set", bind, set)
    ("getpixel", bind, getpixel)
    ("setpixel", bind, setpixel))
   )
  {
    Uint8 *data_;
  public:
		Uint8 *data() { return data_; }

    int get(int n) {
      assert(data_ && n > 0);
      return data_[n];
    }
    void set(int n, int byte) {
      assert(data_ && n > 0 && byte <= std::numeric_limits<Uint8>::max());
      data_[n] = byte;
    }

    int getpixel(Surface &surface, int x, int y);
    void setpixel(Surface &surface, int x, int y, int color);

    PixelData(flusspferd::object const &self, Uint8 *data)
      : base_type(self), data_(data)
    {
      assert(data);
    }

    static PixelData &create(void *data) {
      return flusspferd::create<PixelData>(bf::make_vector(reinterpret_cast<Uint8*>(data)));
    }
  };

  PixelData &wrap(void *p) {
    return PixelData::create(p);
  }
  void *unwrap(PixelData &p) {
    return reinterpret_cast<void*>(p.data());
  }

  int PixelData::getpixel(Surface &s, int x, int y) {
    assert(s.surface);
    SDL_Surface *surface = s.surface;
    int const bpp = surface->format->BytesPerPixel;
    Uint8 *p = data_ + y * surface->pitch + x * bpp;
    switch (bpp) {
    case 1:
      return *p;
      break;
    case 2:
      return *reinterpret_cast<Uint16*>(p);
      break;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
      break;
    case 4:
      return *reinterpret_cast<Uint32*>(p);
      break;
    default:
      throw flusspferd::exception("getpixel");
    }
  }
  void PixelData::setpixel(Surface &s, int x, int y, int color) {
    assert(s.surface);
    SDL_Surface *surface = s.surface;
    int const bpp = surface->format->BytesPerPixel;
    Uint8 *p = data_ + y * surface->pitch + x * bpp;
    switch(bpp) {
    case 1:
      *p = color;
      break;
    case 2:
      *reinterpret_cast<Uint16*>(p) = color;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (color >> 16) & 0xff;
        p[1] = (color >> 8) & 0xff;
        p[2] = color & 0xff;
      }
      else {
        p[0] = color & 0xff;
        p[1] = (color >> 8) & 0xff;
        p[2] = (color >> 16) & 0xff;
      }
      break;
    case 4:
      *reinterpret_cast<Uint32*>(p) = color;
      break;
   default:
     throw flusspferd::exception("setpixel");
    }
  }

	PixelFormat &Surface::get_format() {
		assert(surface);
		return PixelFormat::create(surface->format);
	}
	PixelData &Surface::get_pixels() {
		assert(surface);
		return PixelData::create(surface->pixels);
	}
	object Surface::get_clip_rect() {
		assert(surface);
		return rect2object(surface->clip_rect);
	}

	Surface &wrap(SDL_Surface *s) {
		return Surface::create(s);
	}
	SDL_Surface *unwrap(Surface &s) {
		return s.surface;
	}

	FLUSSPFERD_CLASS_DESCRIPTION
  (
   Color,
   (constructor_name, "Color")
   (full_name, "sdl.Color")
   (properties,
    ("r", getter_setter, (get_r, set_r))
    ("g", getter_setter, (get_g, set_g))
    ("b", getter_setter, (get_b, set_b)))
   )
  {
  public:
    SDL_Color color;

		SDL_Color &data() { return color; }

    int get_r() { return color.r; }
    void set_r(int r) { color.r = r; }
    int get_g() { return color.g; }
    void set_g(int g) { color.g = g; }
    int get_b() { return color.b; }
    void set_b(int b) { color.b = b; }

    Color(flusspferd::object const &self, SDL_Color const &color)
      : base_type(self), color(color)
    { }
    Color(flusspferd::object const &self, flusspferd::call_context &x)
      : base_type(self)
    {
      if(x.arg.size() == 3) {
        if(!x.arg[0].is_int() || x.arg[1].is_int() || x.arg[2].is_int()) {
          throw flusspferd::exception("Color constructor expected integers");
        }
        color.r = x.arg[0].get_int();
        color.g = x.arg[1].get_int();
        color.b = x.arg[2].get_int();
      }
      else if(x.arg.size() == 1) {
        if(!x.arg[0].is_object() ||
           !flusspferd::is_native<Color>(x.arg[0].get_object()))
        {
          throw flusspferd::exception("Color constructor expects r,g,b or color");
        }
        color = flusspferd::get_native<Color>(x.arg[0].get_object()).color;
      }
      else {
        throw flusspferd::exception("Color constructor expects r,g,b or color");
      }
    }

    static Color &create(SDL_Color const &color) {
      return flusspferd::create<Color>(bf::make_vector(color));
    }
  };

  Color &wrap(SDL_Color const &p) {
    return Color::create(p);
  }
  SDL_Color &unwrap(Color &p) {
    return p.data();
  }

namespace {  
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

  int flip(Surface &surface) {
    return SDL_Flip(surface.surface);
  }

  void update_rect(Surface &screen, int x, int y, int w, int h) {
    SDL_UpdateRect(screen.surface, x, y, w, h);
  }

  int lock_surface(Surface &surface) {
    return SDL_LockSurface(surface.surface);
  }

  void unlock_surface(Surface &surface) {
    SDL_UnlockSurface(surface.surface);
  }

  void free_surface(Surface &surface) {
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
      if(!x.arg[0].is_object() || !flusspferd::is_native<Surface>(x.arg[0].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as first parameter");
      }
      SDL_Surface *src = flusspferd::get_native<Surface>(x.arg[0].get_object()).surface;
      if(!x.arg[1].is_object() || !flusspferd::is_native<Surface>(x.arg[1].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as second parameter");
      }
      SDL_Surface *dest = flusspferd::get_native<Surface>(x.arg[1].get_object()).surface;
      x.result = value(SDL_BlitSurface(src, 0x0, dest, 0x0));
      return;
    }
    else if(x.arg.size() == 4) {
      if(!flusspferd::is_native<Surface>(x.arg[0].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as first parameter");
      }
      SDL_Surface *src = flusspferd::get_native<Surface>(x.arg[0].get_object()).surface;
      if(!x.arg[1].is_object()) {
        throw flusspferd::exception("blitSurface: expected Rect as second parameter");
      }
      SDL_Rect srcrect = object2rect(x.arg[1].get_object());
      if(!flusspferd::is_native<Surface>(x.arg[2].get_object())) {
        throw flusspferd::exception("blitSurface: expected Surface as third parameter");
      }
      SDL_Surface *dest = flusspferd::get_native<Surface>(x.arg[2].get_object()).surface;
      if(!x.arg[3].is_object()) {
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

  int set_colors(Surface &surface, Color &color, int firstcolor, int ncolors) {
    return SDL_SetColors(surface.surface, &color.color, firstcolor, ncolors);
  }

	// TODO
  Surface &create_RGB_surface(int flags, int width, int height, int bpp, int rmask, int gmask, int bmask, int amask) {
    SDL_Surface *surface = SDL_CreateRGBSurface(flags, width, height, bpp, rmask, gmask, bmask, amask);
    if(!surface) {
      std::string const what = std::string("SDL_CreateRGBSurface: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  int set_alpha(Surface &surface, int flags, int alpha) {
    return SDL_SetAlpha(surface.surface, flags, alpha);
  }

  int set_color_key(Surface &surface, int flag, int key) {
    return SDL_SetColorKey(surface.surface, flag, key);
  }

  Surface &display_format(Surface &in) {
    SDL_Surface *surface = SDL_DisplayFormat(in.surface);
    if(!surface) {
      std::string const what = std::string("SDL_DisplayFormat: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  Surface &display_format_alpha(Surface &in) {
    SDL_Surface *surface = SDL_DisplayFormatAlpha(in.surface);
    if(!surface) {
      std::string const what = std::string("SDL_DisplayFormatAlpha: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  Surface &convert_surface(Surface &in, PixelFormat &fmt, int flags) {
    SDL_Surface *surface = SDL_ConvertSurface(in.surface, fmt.format, flags);
    if(!surface) {
      std::string const what = std::string("SDL_ConvertSurface: ") + SDL_GetError();
      throw flusspferd::exception(what.c_str());
    }
    return Surface::create(surface);
  }

  std::string video_driver_name() {
    enum { MAXLEN = 1024 };
    char buffer[MAXLEN];
    return SDL_VideoDriverName(buffer, MAXLEN);
  }

  int map_RGB(PixelFormat &fmt, int r, int g, int b) {
    return SDL_MapRGB(fmt.format, r, g, b);
  }

  int map_RGBA(PixelFormat &fmt, int r, int g, int b, int a) {
    return SDL_MapRGBA(fmt.format, r, g, b, a);
  }

  Color &get_RGB(int pixel, PixelFormat &format) {
    SDL_Color color;
    SDL_GetRGB(pixel, format.format, &color.r, &color.g, &color.b);
    return Color::create(color);
  }

  int save_BMP(Surface &surface, char const *file) {
    return SDL_SaveBMP(surface.surface, file);
  }

  void set_clip_rect(Surface &surface, object const &o) {
    SDL_Rect rect = object2rect(o);
    SDL_SetClipRect(surface.surface, &rect);
  }
  object get_clip_rect(Surface &surface) {
    SDL_Rect rect;
    SDL_GetClipRect(surface.surface, &rect);
    return rect2object(rect);
  }

  int fill_rect(Surface &surface, object const &rect, int color) {
    SDL_Rect r = object2rect(rect);
    return SDL_FillRect(surface.surface, &r, color);
  }
}
  void load_video(flusspferd::object &sdl) {
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
    boost::function< void(call_context &)> blit_surface_ = &sdl::blit_surface;
    create_on(sdl)
      .create<function>("setVideoMode", &sdl::set_video_mode)
      .create<function>("getVideoSurface", &sdl::get_video_surface)
      .create<function>("videoModeOK", &::SDL_VideoModeOK)
      .create<function>("flip", &sdl::flip)
      .create<function>("updateRect", &sdl::update_rect)
      .create<function>("lockSurface", &sdl::lock_surface)
      .create<function>("unlockSurface", &sdl::unlock_surface)
      .create<function>("freeSurface", &sdl::free_surface)
      .create<function>("loadBMP", &sdl::load_BMP)
      .create<function>("saveBMP", &sdl::save_BMP)
      .create<function>("blitSurface", blit_surface_)
      .create<function>("setColors", &sdl::set_colors)
      .create<function>("createRGBSurface", &sdl::create_RGB_surface)
      .create<function>("setAlpha", &sdl::set_alpha)
      .create<function>("setColorKey", &sdl::set_color_key)
      .create<function>("displayFormat", &sdl::display_format)
      .create<function>("displayFormatAlpha", &sdl::display_format_alpha)
      .create<function>("videoDriverName", &sdl::video_driver_name)
      .create<function>("setGamma", &::SDL_SetGamma)
      .create<function>("mapRGB", &sdl::map_RGB)
      .create<function>("mapRGBA", &sdl::map_RGBA)
      .create<function>("getRGB", &sdl::get_RGB)
      .create<function>("setClipRect", &sdl::set_clip_rect)
      .create<function>("getClipRect", &sdl::get_clip_rect)
      .create<function>("fillRect", &sdl::fill_rect);
    load_class<sdl::Surface>(sdl);
    load_class<sdl::PixelFormat>(sdl);
    load_class<sdl::Color>(sdl);
    load_class<sdl::PixelData>(sdl);
    sdl.define_property("SRCALPHA", value(SDL_SRCALPHA));
    sdl.define_property("RLEACCEL", value(SDL_RLEACCEL));
    sdl.define_property("SRCCOLORKEY", value(SDL_SRCCOLORKEY));
  }
}
