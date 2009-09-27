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
#include "sdl-key.hpp"

#include <flusspferd/create.hpp>
#include <flusspferd/class_description.hpp>

#include <SDL.h>

using namespace flusspferd;

namespace sdl {
namespace {
	char const *get_key_name(int key) {
    return SDL_GetKeyName((SDLKey)key);
  }

  int get_app_state() {
    return SDL_GetAppState();
  }

  int event_state(int type, int state) {
    return event_state(type, state);
  }

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   ActiveEvent,
   (constructor_name, "ActiveEvent")
   (constructible, false)
   (full_name, "sdl.ActiveEvent")
   (properties,
    ("type", getter, get_type)
    ("gain", getter, get_type)
    ("state", getter, get_state)))
  {
    SDL_ActiveEvent event;
  public:
    int get_type()  { return event.type; }
    int get_gain()  { return event.gain; }
    int get_state() { return event.state; }

    ActiveEvent(flusspferd::object const &self, SDL_ActiveEvent const &e)
      : base_type(self), event(e)
    { }

    static ActiveEvent &create(SDL_ActiveEvent const &e) {
      return flusspferd::create_native_object<ActiveEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Keysym,
   (constructor_name, "Keysym")
   (constructible, false)
   (full_name, "sdl.Keysym")
   (properties,
    ("scancode", getter, get_scancode)
    ("sym", getter, get_sym)
    ("mod", getter, get_mod)
    ("unicode", getter, get_unicode)))
  {
    SDL_keysym k;
  public:
    int get_scancode() { return k.scancode; }
    int get_sym()      { return k.sym; }
    int get_mod()      { return k.mod; }
    int get_unicode()  { return k.unicode; }

    Keysym(flusspferd::object const &self, SDL_keysym const &k)
      : base_type(self), k(k)
    { }

    static Keysym &create(SDL_keysym const &k) {
      return flusspferd::create_native_object<Keysym>(object(), k);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   KeyboardEvent,
   (constructor_name, "KeyboardEvent")
   (constructible, false)
   (full_name, "sdl.KeyboardEvent")
   (properties,
    ("type", getter, get_type)
    ("state", getter, get_state)
    ("keysym", getter, get_keysym)))
  {
    SDL_KeyboardEvent event;
  public:
    int    get_type()    { return event.type; }
    int    get_state()   { return event.state; }
    Keysym &get_keysym() { return Keysym::create(event.keysym); }

    KeyboardEvent(flusspferd::object const &o, SDL_KeyboardEvent const &e)
      : base_type(o), event(e)
    { }

    static KeyboardEvent &create(SDL_KeyboardEvent const &e) {
      return flusspferd::create_native_object<KeyboardEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (MouseMotionEvent,
   (constructor_name, "MouseMotionEvent")
   (constructible, false)
   (full_name, "sdl.MouseMotionEvent")
   (properties,
    ("type", getter, get_type)
    ("state", getter, get_state)
    ("x", getter, get_x)
    ("y", getter, get_y)
    ("xrel", getter, get_xrel)
    ("yrel", getter, get_yrel)))
  {
    SDL_MouseMotionEvent e;
  public:

    int get_type() { return e.type; }
    int get_state() { return e.state; }
    int get_x() { return e.x; }
    int get_y() { return e.y; }
    int get_xrel() { return e.xrel; }
    int get_yrel() { return e.yrel; }

    MouseMotionEvent(flusspferd::object const &self, SDL_MouseMotionEvent const &e)
      : base_type(self), e(e)
    { }

    static MouseMotionEvent &create(SDL_MouseMotionEvent const &e) {
      return flusspferd::create_native_object<MouseMotionEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   MouseButtonEvent,
   (constructor_name, "MouseButtonEvent")
   (constructible, false)
   (full_name, "sdl.MouseButtonEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("button", getter, get_button)
    ("state", getter, get_state)
    ("x", getter, get_x)
    ("y", getter, get_y)))
  {
    SDL_MouseButtonEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_button() { return event.button; }
    int get_state() { return event.state; }
    int get_x() { return event.x; }
    int get_y() { return event.y; }

    MouseButtonEvent(flusspferd::object const &self, SDL_MouseButtonEvent const &event)
      : base_type(self), event(event)
    { }

    static MouseButtonEvent &create(SDL_MouseButtonEvent const &e) {
      return flusspferd::create_native_object<MouseButtonEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyAxisEvent,
   (constructor_name, "JoyAxisEvent")
   (constructible, false)
   (full_name, "sdl.JoyAxisEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("axis", getter, get_axis)
    ("value", getter, get_value)))
  {
    SDL_JoyAxisEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_axis() { return event.axis; }
    int get_value() { return event.value; }

    JoyAxisEvent(flusspferd::object const &self, SDL_JoyAxisEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyAxisEvent &create(SDL_JoyAxisEvent const &e) {
      return flusspferd::create_native_object<JoyAxisEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyButtonEvent,
   (constructor_name, "JoyButtonEvent")
   (constructible, false)
   (full_name, "sdl.JoyButtonEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("button", getter, get_button)
    ("state", getter, get_state)
    ))
  {
    SDL_JoyButtonEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_button() { return event.button; }
    int get_state() { return event.state; }

    JoyButtonEvent(flusspferd::object const &self, SDL_JoyButtonEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyButtonEvent &create(SDL_JoyButtonEvent const &e) {
      return flusspferd::create_native_object<JoyButtonEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyHatEvent,
   (constructor_name, "JoyHatEvent")
   (constructible, false)
   (full_name, "sdl.JoyHatEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("hat", getter, get_hat)
    ("value", getter, get_value)
    ))
  {
    SDL_JoyHatEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_hat() { return event.hat; }
    int get_value() { return event.value; }

    JoyHatEvent(flusspferd::object const &self, SDL_JoyHatEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyHatEvent &create(SDL_JoyHatEvent const &e) {
      return flusspferd::create_native_object<JoyHatEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   JoyBallEvent,
   (constructor_name, "JoyBallEvent")
   (constructible, false)
   (full_name, "sdl.JoyBallEvent")
   (properties,
    ("type", getter, get_type)
    ("which", getter, get_which)
    ("ball", getter, get_ball)
    ("xrel", getter, get_xrel)
    ("yrel", getter, get_yrel)
    ))
  {
    SDL_JoyBallEvent event;
  public:
    int get_type() { return event.type; }
    int get_which() { return event.which; }
    int get_ball() { return event.ball; }
    int get_xrel() { return event.xrel; }
    int get_yrel() { return event.yrel; }

    JoyBallEvent(flusspferd::object const &self, SDL_JoyBallEvent const &event)
      : base_type(self), event(event)
    { }

    static JoyBallEvent &create(SDL_JoyBallEvent const &e) {
      return flusspferd::create_native_object<JoyBallEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   ResizeEvent,
   (constructor_name, "ResizeEvent")
   (constructible, false)
   (full_name, "sdl.ResizeEvent")
   (properties,
    ("type", getter, get_type)
    ("w", getter, get_w)
    ("h", getter, get_h)
    ))
  {
    SDL_ResizeEvent event;
  public:
    int get_type() { return event.type; }
    int get_w() { return event.w; }
    int get_h() { return event.h; }

    ResizeEvent(flusspferd::object const &self, SDL_ResizeEvent const &event)
      : base_type(self), event(event)
    { }

    static ResizeEvent &create(SDL_ResizeEvent const &e) {
      return flusspferd::create_native_object<ResizeEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   ExposeEvent,
   (constructor_name, "ExposeEvent")
   (constructible, false)
   (full_name, "sdl.ExposeEvent")
   (properties,
    ("type", getter, get_type)
    ))
  {
    SDL_ExposeEvent event;
  public:
    int get_type() { return event.type; }

    ExposeEvent(flusspferd::object const &self, SDL_ExposeEvent const &event)
      : base_type(self), event(event)
    { }

    static ExposeEvent &create(SDL_ExposeEvent const &e) {
      return flusspferd::create_native_object<ExposeEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   QuitEvent,
   (constructor_name, "QuitEvent")
   (constructible, false)
   (full_name, "sdl.QuitEvent")
   (properties,
    ("type", getter, get_type)
    ))
  {
    SDL_QuitEvent event;
  public:
    int get_type() { return event.type; }

    QuitEvent(flusspferd::object const &self, SDL_QuitEvent const &event)
      : base_type(self), event(event)
    { }

    static QuitEvent &create(SDL_QuitEvent const &e) {
      return flusspferd::create_native_object<QuitEvent>(object(), e);
    }
  };

  FLUSSPFERD_CLASS_DESCRIPTION
  (
   Event,
   (constructor_name, "Event")
   (constructible, false)
   (full_name, "sdl.Event")
   (properties,
    ("type", getter, get_type)
    ("active", getter, get_active)
    ("key", getter, get_key)
    ("motion", getter, get_motion)
    ("button", getter, get_button)
    ("jaxis", getter, get_jaxis)
    ("jball", getter, get_jball)
    ("jhat", getter, get_jhat)
    ("jbutton", getter, get_jbutton)
    ("resize", getter, get_resize)
    ("expose", getter, get_expose)
    ("quit", getter, get_quit)
    /* TODO
    user     User defined event (see SDL_UserEvent)
    syswm    Undefined window manager event (see SDL_SysWMEvent)
    */
    ))
  {
    SDL_Event event;
  public:

    int get_type() {
      return event.type;
    }
    ActiveEvent &get_active() {
      return ActiveEvent::create(event.active);
    }
    KeyboardEvent &get_key() {
      return KeyboardEvent::create(event.key);
    }
    MouseMotionEvent &get_motion() {
      return MouseMotionEvent::create(event.motion);
    }
    MouseButtonEvent &get_button() {
      return MouseButtonEvent::create(event.button);
    }
    JoyAxisEvent &get_jaxis() {
      return JoyAxisEvent::create(event.jaxis);
    }
    JoyBallEvent &get_jball() {
      return JoyBallEvent::create(event.jball);
    }
    JoyHatEvent &get_jhat() {
      return JoyHatEvent::create(event.jhat);
    }
    JoyButtonEvent &get_jbutton() {
      return JoyButtonEvent::create(event.jbutton);
    }
    ResizeEvent &get_resize() {
      return ResizeEvent::create(event.resize);
    }
    ExposeEvent &get_expose() {
      return ExposeEvent::create(event.expose);
    }
    QuitEvent &get_quit() {
      return QuitEvent::create(event.quit);
    }
#if 0
    UserEvent &get_user() {
      return UserEvent::create(event.user);
    }
    SysWMEvent &get_syswm() {
      return SysWMEvent::create(event.syswm);
    }
#endif

    Event(flusspferd::object const &self, SDL_Event const &e)
      : base_type(self), event(e)
    { }

    static Event &create(SDL_Event const &e) {
      return flusspferd::create_native_object<Event>(object(), e);
    }
  };

  object poll_event() {
    SDL_Event event;
    int i = SDL_PollEvent(&event);
    if(i == 0) {
      return object();
    }
    else {
      return Event::create(event);
    }
  }

  object wait_event() {
    SDL_Event event;
    int i = SDL_WaitEvent(&event);
    if(i == 0) {
      return object();
    }
    else {
      return Event::create(event);
    }
  }

  int get_mod_state() {
    return SDL_GetModState();
  }
  void set_mod_state(int s) {
    SDL_SetModState((SDLMod)s);
  }

  object get_mouse_state() {
    int x, y;
    int ret = SDL_GetMouseState(&x, &y);
    object state(flusspferd::create_object());
    state.set_property("state", ret);
    state.set_property("x", x);
    state.set_property("y", y);
    return state;
  }

  object get_relative_mouse_state() {
    int x, y;
    int ret = SDL_GetRelativeMouseState(&x, &y);
    object state(flusspferd::create_object());
    state.set_property("state", ret);
    state.set_property("x", x);
    state.set_property("y", y);
    return state;
  }
}
	void load_events(object &sdl) {
		sdl.define_property("key", key_object());
    sdl.define_property("kmod", mod_object());
    create_native_function(sdl, "enableUNICODE", &::SDL_EnableUNICODE);
    create_native_function(sdl, "enableKeyRepeat", &::SDL_EnableKeyRepeat);
    create_native_function(sdl, "getKeyName", &sdl::get_key_name);
    sdl.define_property("APPMOUSEFOCUS", value((int)SDL_APPMOUSEFOCUS));
    sdl.define_property("APPINPUTFOCUS", value((int)SDL_APPINPUTFOCUS));
    sdl.define_property("APPACTIVE", value((int)SDL_APPACTIVE));
    create_native_function(sdl, "getAppState", &sdl::get_app_state);
#if 0
    create_native_function(sdl, "startTextInput", &::SDL_StartTextInput);
    create_native_function(sdl, "stopTextInput", &::SDL_StopTextInput);
#endif
    sdl.define_property("IGNORE", value((int)SDL_IGNORE));
    sdl.define_property("ENABLE", value((int)SDL_ENABLE));
    sdl.define_property("QUERY", value((int)SDL_QUERY));
    create_native_function(sdl, "eventState", &sdl::event_state);
    load_class<sdl::ActiveEvent>(sdl);
    load_class<sdl::KeyboardEvent>(sdl);
    load_class<sdl::MouseMotionEvent>(sdl);
    load_class<sdl::MouseButtonEvent>(sdl);
    load_class<sdl::JoyAxisEvent>(sdl);
    load_class<sdl::JoyBallEvent>(sdl);
    load_class<sdl::JoyHatEvent>(sdl);
    load_class<sdl::JoyButtonEvent>(sdl);
    load_class<sdl::ResizeEvent>(sdl);
    load_class<sdl::ExposeEvent>(sdl);
    load_class<sdl::QuitEvent>(sdl);
    load_class<sdl::Event>(sdl);
    sdl.define_property("ACTIVEEVENT", value((int)SDL_ACTIVEEVENT));
    sdl.define_property("KEYDOWN", value((int)SDL_KEYDOWN));
    sdl.define_property("KEYUP", value((int)SDL_KEYUP));
    sdl.define_property("MOUSEMOTION", value((int)SDL_MOUSEMOTION));
    sdl.define_property("MOUSEBUTTONDOWN", value((int)SDL_MOUSEBUTTONDOWN));
    sdl.define_property("MOUSEBUTTONUP", value((int)SDL_MOUSEBUTTONUP));
    sdl.define_property("JOYAXISMOTION", value((int)SDL_JOYAXISMOTION));
    sdl.define_property("JOYBALLMOTION", value((int)SDL_JOYBALLMOTION));
    sdl.define_property("JOYHATMOTION", value((int)SDL_JOYHATMOTION));
    sdl.define_property("JOYBUTTONDOWN", value((int)SDL_JOYBUTTONDOWN));
    sdl.define_property("JOYBUTTONUP", value((int)SDL_JOYBUTTONUP));
    sdl.define_property("VIDEORESIZE", value((int)SDL_VIDEORESIZE));
    sdl.define_property("VIDEOEXPOSE", value((int)SDL_VIDEOEXPOSE));
    sdl.define_property("QUIT", value((int)SDL_QUIT));
    sdl.define_property("USEREVENT", value((int)SDL_USEREVENT));
    sdl.define_property("SYSWMEVENT", value((int)SDL_SYSWMEVENT));
    create_native_function(sdl, "pollEvent", &sdl::poll_event);
    create_native_function(sdl, "waitEvent", &sdl::wait_event);
    create_native_function(sdl, "getModState", &sdl::get_mod_state);
    create_native_function(sdl, "setModState", &sdl::set_mod_state);
    create_native_function(sdl, "pumpEvents", &::SDL_PumpEvents);
    create_native_function(sdl, "getMouseState", &sdl::get_mouse_state);
    create_native_function(sdl, "getRelativeMouseState", &sdl::get_relative_mouse_state);
    create_native_function(sdl, "joystickEventState", &::SDL_JoystickEventState);
	}
}
