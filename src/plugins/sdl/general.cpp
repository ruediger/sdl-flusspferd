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
#include "general.hpp"

#include "flusspferd/create.hpp"

#include <SDL.h>

using namespace flusspferd;

namespace sdl {
	namespace {
		void quit() {
			SDL_Quit();
		}

		void error(int err) {
			SDL_Error((SDL_errorcode)err);
		}

		object sdl_version() {
			SDL_version v;
			SDL_VERSION(&v);
			object ver(flusspferd::create_object());
			ver.set_property("major", v.major);
			ver.set_property("minor", v.minor);
			ver.set_property("patch", v.patch);
			return ver;
		}

		object linked_version() {
			SDL_version const *v = SDL_Linked_Version();
			if(!v) {
				std::string const what = std::string("SDL_Linked_Version: ") + SDL_GetError();
				throw flusspferd::exception(what.c_str());
			}
			object ver(flusspferd::create_object());
			ver.set_property("major", v->major);
			ver.set_property("minor", v->minor);
			ver.set_property("patch", v->patch);
			return ver;
		}
	}

	void load_general(flusspferd::object &sdl) {
		// General
    sdl.define_property("INIT_TIMER", value(SDL_INIT_TIMER));
    sdl.define_property("INIT_AUDIO", value(SDL_INIT_AUDIO));
    sdl.define_property("INIT_VIDEO", value(SDL_INIT_VIDEO));
    sdl.define_property("INIT_CDROM", value(SDL_INIT_CDROM));
    sdl.define_property("INIT_JOYSTICK", value(SDL_INIT_JOYSTICK));
    sdl.define_property("INIT_EVERYTHING", value(SDL_INIT_EVERYTHING));
    sdl.define_property("INIT_NOPARACHUTE", value(SDL_INIT_NOPARACHUTE));
    sdl.define_property("INIT_EVENTTHREAD", value(SDL_INIT_EVENTTHREAD));
    create_native_function(sdl, "init", &::SDL_Init);
    create_native_function(sdl, "initSubSystem", &::SDL_InitSubSystem);
    create_native_function(sdl, "quit", &sdl::quit);
    create_native_function(sdl, "quitSubSystem", &::SDL_QuitSubSystem);
    sdl.define_property("ENOMEM", value((int)SDL_ENOMEM));
    sdl.define_property("EFREAD", value((int)SDL_EFREAD));
    sdl.define_property("EFWRITE", value((int)SDL_EFWRITE));
    sdl.define_property("EFSEEK", value((int)SDL_EFSEEK));
    sdl.define_property("UNSUPPORTED", value((int)SDL_UNSUPPORTED));
    sdl.define_property("LASTERROR", value((int)SDL_LASTERROR));
    create_native_function(sdl, "error", &sdl::error);
    create_native_function(sdl, "getError", &::SDL_GetError);
    create_native_function(sdl, "clearError", &::SDL_ClearError);
    create_native_function(sdl, "wasInit", &::SDL_WasInit);
    create_native_function(sdl, "version", &sdl::sdl_version);
    create_native_function(sdl, "linkedVersion", &sdl::linked_version);
	}
}
