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
	FLUSSPFERD_CLASS_DESCRIPTION(
   Joystick,
   (constructor_name, "Joystick")
   (constructible, false)
   (full_name, "sdl.Joystick"))
  {
    SDL_Joystick *joystick;
  public:
    SDL_Joystick *get() {
      assert(joystick);
      return joystick;
    }

    Joystick(flusspferd::object const &self, SDL_Joystick *j)
      : base_type(self), joystick(j)
    { }

    void close() {
      SDL_JoystickClose(joystick);
      joystick = 0x0;
    }

    ~Joystick() {
      if(joystick)
        close();
    }

    static Joystick &create(SDL_Joystick *j) {
      return flusspferd::create_native_object<Joystick>(object(), j);
    }
  };

  Joystick &joystick_open(int index) {
    return Joystick::create(SDL_JoystickOpen(index));
  }

  void joystick_close(Joystick &j) {
    j.close();
  }

  int joystick_index(Joystick &j) {
    return SDL_JoystickIndex(j.get());
  }

  int joystick_num_axes(Joystick &j) {
    return SDL_JoystickNumAxes(j.get());
  }

  int joystick_num_balls(Joystick &j) {
    return SDL_JoystickNumBalls(j.get());
  }

  int joystick_num_hats(Joystick &j) {
    return SDL_JoystickNumHats(j.get());
  }

  int joystick_num_buttons(Joystick &j) {
    return SDL_JoystickNumButtons(j.get());
  }

  int joystick_get_axis(Joystick &j, int axis) {
    return SDL_JoystickGetAxis(j.get(), axis);
  }

  int joystick_get_hat(Joystick &j, int hat) {
    return SDL_JoystickGetHat(j.get(), hat);
  }

  int joystick_get_button(Joystick &j, int button) {
    return SDL_JoystickGetButton(j.get(), button);
  }

  object joystick_get_ball(Joystick &j, int ball) {
    int dx, dy;
    if(SDL_JoystickGetBall(j.get(), ball, &dx, &dy) == -1) {
      return object();
    }
    else {
      object ret(create_object());
      ret.set_property("dx", dx);
      ret.set_property("dy", dy);
      return ret;
    }
  }
}
	void load_joystick(object &sdl) {
		create_native_function(sdl, "numJoysticks", &::SDL_NumJoysticks);
    create_native_function(sdl, "joystickName", &::SDL_JoystickName);
    create_native_function(sdl, "joystickOpened", &::SDL_JoystickOpened);
    create_native_function(sdl, "joystickUpdate", &::SDL_JoystickUpdate);
    load_class<sdl::Joystick>(sdl);
    create_native_function(sdl, "joystickOpen", &sdl::joystick_open);
    create_native_function(sdl, "joystickClose", &sdl::joystick_close);
    create_native_function(sdl, "joystickIndex", &sdl::joystick_index);
    create_native_function(sdl, "joystickNumAxes", &sdl::joystick_num_axes);
    create_native_function(sdl, "joystickNumBalls", &sdl::joystick_num_balls);
    create_native_function(sdl, "joystickNumHats", &sdl::joystick_num_hats);
    create_native_function(sdl, "joystickNumButtons", &sdl::joystick_num_buttons);
    create_native_function(sdl, "joystickGetAxis", &sdl::joystick_get_axis);
    create_native_function(sdl, "joystickGetHat", &sdl::joystick_get_hat);
    create_native_function(sdl, "joystickGetButton", &sdl::joystick_get_button);
    create_native_function(sdl, "joystickGetBall", &sdl::joystick_get_ball);
	}
}
