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
#include <flusspferd/create_on.hpp>
#include <flusspferd/create/object.hpp>
#include <flusspferd/create/function.hpp>

#include <SDL.h>

using namespace flusspferd;
namespace sdl {
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

		SDL_Joystick *data() {
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
      return flusspferd::create<Joystick>(bf::make_vector(j));
    }
  };

  Joystick &wrap(SDL_Joystick *j) {
    return Joystick::create(j);
  }

  SDL_Joystick *unwrap(Joystick &j) {
    return j.data();
  }

namespace {
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
      object ret(create<object>());
      ret.set_property("dx", dx);
      ret.set_property("dy", dy);
      return ret;
    }
  }
}
  void load_joystick(object &sdl) {
    create_on(sdl)
      .create<function>("numJoysticks", &::SDL_NumJoysticks)
      .create<function>("joystickName", &::SDL_JoystickName)
      .create<function>("joystickOpened", &::SDL_JoystickOpened)
      .create<function>("joystickUpdate", &::SDL_JoystickUpdate)
      .create<function>("joystickOpen", &sdl::joystick_open)
      .create<function>("joystickClose", &sdl::joystick_close)
      .create<function>("joystickIndex", &sdl::joystick_index)
      .create<function>("joystickNumAxes", &sdl::joystick_num_axes)
      .create<function>("joystickNumBalls", &sdl::joystick_num_balls)
      .create<function>("joystickNumHats", &sdl::joystick_num_hats)
      .create<function>("joystickNumButtons", &sdl::joystick_num_buttons)
      .create<function>("joystickGetAxis", &sdl::joystick_get_axis)
      .create<function>("joystickGetHat", &sdl::joystick_get_hat)
      .create<function>("joystickGetButton", &sdl::joystick_get_button)
      .create<function>("joystickGetBall", &sdl::joystick_get_ball);
    load_class<sdl::Joystick>(sdl);
  }
}
