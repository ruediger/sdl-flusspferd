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
#include "sdl-key.hpp"
#include <flusspferd/create.hpp>
#include <flusspferd/create/object.hpp>
#include <SDL.h>

using namespace flusspferd;
namespace sdl {
  object key_object() {
    object key(create<object>());
    key.define_property("BACKSPACE", value((int)SDLK_BACKSPACE));
    key.define_property("TAB", value((int)SDLK_TAB));
    key.define_property("CLEAR", value((int)SDLK_CLEAR));
    key.define_property("RETURN", value((int)SDLK_RETURN));
    key.define_property("PAUSE", value((int)SDLK_PAUSE));
    key.define_property("ESCAPE", value((int)SDLK_ESCAPE));
    key.define_property("SPACE", value((int)SDLK_SPACE));
    key.define_property("EXCLAIM", value((int)SDLK_EXCLAIM));
    key.define_property("QUOTEDBL", value((int)SDLK_QUOTEDBL));
    key.define_property("HASH", value((int)SDLK_HASH));
    key.define_property("DOLLAR", value((int)SDLK_DOLLAR));
    key.define_property("AMPERSAND", value((int)SDLK_AMPERSAND));
    key.define_property("QUOTE", value((int)SDLK_QUOTE));
    key.define_property("LEFTPAREN", value((int)SDLK_LEFTPAREN));
    key.define_property("RIGHTPAREN", value((int)SDLK_RIGHTPAREN));
    key.define_property("ASTERISK", value((int)SDLK_ASTERISK));
    key.define_property("PLUS", value((int)SDLK_PLUS));
    key.define_property("COMMA", value((int)SDLK_COMMA));
    key.define_property("MINUS", value((int)SDLK_MINUS));
    key.define_property("PERIOD", value((int)SDLK_PERIOD));
    key.define_property("SLASH", value((int)SDLK_SLASH));
    key.define_property("0", value((int)SDLK_0));
    key.define_property("1", value((int)SDLK_1));
    key.define_property("2", value((int)SDLK_2));
    key.define_property("3", value((int)SDLK_3));
    key.define_property("4", value((int)SDLK_4));
    key.define_property("5", value((int)SDLK_5));
    key.define_property("6", value((int)SDLK_6));
    key.define_property("7", value((int)SDLK_7));
    key.define_property("8", value((int)SDLK_8));
    key.define_property("9", value((int)SDLK_9));
    key.define_property("COLON", value((int)SDLK_COLON));
    key.define_property("SEMICOLON", value((int)SDLK_SEMICOLON));
    key.define_property("LESS", value((int)SDLK_LESS));
    key.define_property("EQUALS", value((int)SDLK_EQUALS));
    key.define_property("GREATER", value((int)SDLK_GREATER));
    key.define_property("QUESTION", value((int)SDLK_QUESTION));
    key.define_property("AT", value((int)SDLK_AT));
    key.define_property("LEFTBRACKET", value((int)SDLK_LEFTBRACKET));
    key.define_property("BACKSLASH", value((int)SDLK_BACKSLASH));
    key.define_property("RIGHTBRACKET", value((int)SDLK_RIGHTBRACKET));
    key.define_property("CARET", value((int)SDLK_CARET));
    key.define_property("UNDERSCORE", value((int)SDLK_UNDERSCORE));
    key.define_property("BACKQUOTE", value((int)SDLK_BACKQUOTE));
    key.define_property("a", value((int)SDLK_a));
    key.define_property("b", value((int)SDLK_b));
    key.define_property("c", value((int)SDLK_c));
    key.define_property("d", value((int)SDLK_d));
    key.define_property("e", value((int)SDLK_e));
    key.define_property("f", value((int)SDLK_f));
    key.define_property("g", value((int)SDLK_g));
    key.define_property("h", value((int)SDLK_h));
    key.define_property("i", value((int)SDLK_i));
    key.define_property("j", value((int)SDLK_j));
    key.define_property("k", value((int)SDLK_k));
    key.define_property("l", value((int)SDLK_l));
    key.define_property("m", value((int)SDLK_m));
    key.define_property("n", value((int)SDLK_n));
    key.define_property("o", value((int)SDLK_o));
    key.define_property("p", value((int)SDLK_p));
    key.define_property("q", value((int)SDLK_q));
    key.define_property("r", value((int)SDLK_r));
    key.define_property("s", value((int)SDLK_s));
    key.define_property("t", value((int)SDLK_t));
    key.define_property("u", value((int)SDLK_u));
    key.define_property("v", value((int)SDLK_v));
    key.define_property("w", value((int)SDLK_w));
    key.define_property("x", value((int)SDLK_x));
    key.define_property("y", value((int)SDLK_y));
    key.define_property("z", value((int)SDLK_z));
    key.define_property("DELETE", value((int)SDLK_DELETE));
    key.define_property("WORLD_0", value((int)SDLK_WORLD_0));
    key.define_property("WORLD_1", value((int)SDLK_WORLD_1));
    key.define_property("WORLD_2", value((int)SDLK_WORLD_2));
    key.define_property("WORLD_3", value((int)SDLK_WORLD_3));
    key.define_property("WORLD_4", value((int)SDLK_WORLD_4));
    key.define_property("WORLD_5", value((int)SDLK_WORLD_5));
    key.define_property("WORLD_6", value((int)SDLK_WORLD_6));
    key.define_property("WORLD_7", value((int)SDLK_WORLD_7));
    key.define_property("WORLD_8", value((int)SDLK_WORLD_8));
    key.define_property("WORLD_9", value((int)SDLK_WORLD_9));
    key.define_property("WORLD_10", value((int)SDLK_WORLD_10));
    key.define_property("WORLD_11", value((int)SDLK_WORLD_11));
    key.define_property("WORLD_12", value((int)SDLK_WORLD_12));
    key.define_property("WORLD_13", value((int)SDLK_WORLD_13));
    key.define_property("WORLD_14", value((int)SDLK_WORLD_14));
    key.define_property("WORLD_15", value((int)SDLK_WORLD_15));
    key.define_property("WORLD_16", value((int)SDLK_WORLD_16));
    key.define_property("WORLD_17", value((int)SDLK_WORLD_17));
    key.define_property("WORLD_18", value((int)SDLK_WORLD_18));
    key.define_property("WORLD_19", value((int)SDLK_WORLD_19));
    key.define_property("WORLD_20", value((int)SDLK_WORLD_20));
    key.define_property("WORLD_21", value((int)SDLK_WORLD_21));
    key.define_property("WORLD_22", value((int)SDLK_WORLD_22));
    key.define_property("WORLD_23", value((int)SDLK_WORLD_23));
    key.define_property("WORLD_24", value((int)SDLK_WORLD_24));
    key.define_property("WORLD_25", value((int)SDLK_WORLD_25));
    key.define_property("WORLD_26", value((int)SDLK_WORLD_26));
    key.define_property("WORLD_27", value((int)SDLK_WORLD_27));
    key.define_property("WORLD_28", value((int)SDLK_WORLD_28));
    key.define_property("WORLD_29", value((int)SDLK_WORLD_29));
    key.define_property("WORLD_30", value((int)SDLK_WORLD_30));
    key.define_property("WORLD_31", value((int)SDLK_WORLD_31));
    key.define_property("WORLD_32", value((int)SDLK_WORLD_32));
    key.define_property("WORLD_33", value((int)SDLK_WORLD_33));
    key.define_property("WORLD_34", value((int)SDLK_WORLD_34));
    key.define_property("WORLD_35", value((int)SDLK_WORLD_35));
    key.define_property("WORLD_36", value((int)SDLK_WORLD_36));
    key.define_property("WORLD_37", value((int)SDLK_WORLD_37));
    key.define_property("WORLD_38", value((int)SDLK_WORLD_38));
    key.define_property("WORLD_39", value((int)SDLK_WORLD_39));
    key.define_property("WORLD_40", value((int)SDLK_WORLD_40));
    key.define_property("WORLD_41", value((int)SDLK_WORLD_41));
    key.define_property("WORLD_42", value((int)SDLK_WORLD_42));
    key.define_property("WORLD_43", value((int)SDLK_WORLD_43));
    key.define_property("WORLD_44", value((int)SDLK_WORLD_44));
    key.define_property("WORLD_45", value((int)SDLK_WORLD_45));
    key.define_property("WORLD_46", value((int)SDLK_WORLD_46));
    key.define_property("WORLD_47", value((int)SDLK_WORLD_47));
    key.define_property("WORLD_48", value((int)SDLK_WORLD_48));
    key.define_property("WORLD_49", value((int)SDLK_WORLD_49));
    key.define_property("WORLD_50", value((int)SDLK_WORLD_50));
    key.define_property("WORLD_51", value((int)SDLK_WORLD_51));
    key.define_property("WORLD_52", value((int)SDLK_WORLD_52));
    key.define_property("WORLD_53", value((int)SDLK_WORLD_53));
    key.define_property("WORLD_54", value((int)SDLK_WORLD_54));
    key.define_property("WORLD_55", value((int)SDLK_WORLD_55));
    key.define_property("WORLD_56", value((int)SDLK_WORLD_56));
    key.define_property("WORLD_57", value((int)SDLK_WORLD_57));
    key.define_property("WORLD_58", value((int)SDLK_WORLD_58));
    key.define_property("WORLD_59", value((int)SDLK_WORLD_59));
    key.define_property("WORLD_60", value((int)SDLK_WORLD_60));
    key.define_property("WORLD_61", value((int)SDLK_WORLD_61));
    key.define_property("WORLD_62", value((int)SDLK_WORLD_62));
    key.define_property("WORLD_63", value((int)SDLK_WORLD_63));
    key.define_property("WORLD_64", value((int)SDLK_WORLD_64));
    key.define_property("WORLD_65", value((int)SDLK_WORLD_65));
    key.define_property("WORLD_66", value((int)SDLK_WORLD_66));
    key.define_property("WORLD_67", value((int)SDLK_WORLD_67));
    key.define_property("WORLD_68", value((int)SDLK_WORLD_68));
    key.define_property("WORLD_69", value((int)SDLK_WORLD_69));
    key.define_property("WORLD_70", value((int)SDLK_WORLD_70));
    key.define_property("WORLD_71", value((int)SDLK_WORLD_71));
    key.define_property("WORLD_72", value((int)SDLK_WORLD_72));
    key.define_property("WORLD_73", value((int)SDLK_WORLD_73));
    key.define_property("WORLD_74", value((int)SDLK_WORLD_74));
    key.define_property("WORLD_75", value((int)SDLK_WORLD_75));
    key.define_property("WORLD_76", value((int)SDLK_WORLD_76));
    key.define_property("WORLD_77", value((int)SDLK_WORLD_77));
    key.define_property("WORLD_78", value((int)SDLK_WORLD_78));
    key.define_property("WORLD_79", value((int)SDLK_WORLD_79));
    key.define_property("WORLD_80", value((int)SDLK_WORLD_80));
    key.define_property("WORLD_81", value((int)SDLK_WORLD_81));
    key.define_property("WORLD_82", value((int)SDLK_WORLD_82));
    key.define_property("WORLD_83", value((int)SDLK_WORLD_83));
    key.define_property("WORLD_84", value((int)SDLK_WORLD_84));
    key.define_property("WORLD_85", value((int)SDLK_WORLD_85));
    key.define_property("WORLD_86", value((int)SDLK_WORLD_86));
    key.define_property("WORLD_87", value((int)SDLK_WORLD_87));
    key.define_property("WORLD_88", value((int)SDLK_WORLD_88));
    key.define_property("WORLD_89", value((int)SDLK_WORLD_89));
    key.define_property("WORLD_90", value((int)SDLK_WORLD_90));
    key.define_property("WORLD_91", value((int)SDLK_WORLD_91));
    key.define_property("WORLD_92", value((int)SDLK_WORLD_92));
    key.define_property("WORLD_93", value((int)SDLK_WORLD_93));
    key.define_property("WORLD_94", value((int)SDLK_WORLD_94));
    key.define_property("WORLD_95", value((int)SDLK_WORLD_95));
    key.define_property("KP0", value((int)SDLK_KP0));
    key.define_property("KP1", value((int)SDLK_KP1));
    key.define_property("KP2", value((int)SDLK_KP2));
    key.define_property("KP3", value((int)SDLK_KP3));
    key.define_property("KP4", value((int)SDLK_KP4));
    key.define_property("KP5", value((int)SDLK_KP5));
    key.define_property("KP6", value((int)SDLK_KP6));
    key.define_property("KP7", value((int)SDLK_KP7));
    key.define_property("KP8", value((int)SDLK_KP8));
    key.define_property("KP9", value((int)SDLK_KP9));
    key.define_property("KP_PERIOD", value((int)SDLK_KP_PERIOD));
    key.define_property("KP_DIVIDE", value((int)SDLK_KP_DIVIDE));
    key.define_property("KP_MULTIPLY", value((int)SDLK_KP_MULTIPLY));
    key.define_property("KP_MINUS", value((int)SDLK_KP_MINUS));
    key.define_property("KP_PLUS", value((int)SDLK_KP_PLUS));
    key.define_property("KP_ENTER", value((int)SDLK_KP_ENTER));
    key.define_property("KP_EQUALS", value((int)SDLK_KP_EQUALS));
    key.define_property("UP", value((int)SDLK_UP));
    key.define_property("RIGHT", value((int)SDLK_RIGHT));
    key.define_property("LEFT", value((int)SDLK_LEFT));
    key.define_property("INSERT", value((int)SDLK_INSERT));
    key.define_property("HOME", value((int)SDLK_HOME));
    key.define_property("END", value((int)SDLK_END));
    key.define_property("PAGEUP", value((int)SDLK_PAGEUP));
    key.define_property("PAGEDOWN", value((int)SDLK_PAGEDOWN));
    key.define_property("F1", value((int)SDLK_F1));
    key.define_property("F2", value((int)SDLK_F2));
    key.define_property("F3", value((int)SDLK_F3));
    key.define_property("F4", value((int)SDLK_F4));
    key.define_property("F5", value((int)SDLK_F5));
    key.define_property("F6", value((int)SDLK_F6));
    key.define_property("F7", value((int)SDLK_F7));
    key.define_property("F8", value((int)SDLK_F8));
    key.define_property("F9", value((int)SDLK_F9));
    key.define_property("F10", value((int)SDLK_F10));
    key.define_property("F11", value((int)SDLK_F11));
    key.define_property("F12", value((int)SDLK_F12));
    key.define_property("F13", value((int)SDLK_F13));
    key.define_property("F14", value((int)SDLK_F14));
    key.define_property("F15", value((int)SDLK_F15));
    key.define_property("NUMLOCK", value((int)SDLK_NUMLOCK));
    key.define_property("CAPSLOCK", value((int)SDLK_CAPSLOCK));
    key.define_property("SCROLLOCK", value((int)SDLK_SCROLLOCK));
    key.define_property("RSHIFT", value((int)SDLK_RSHIFT));
    key.define_property("LSHIFT", value((int)SDLK_LSHIFT));
    key.define_property("RCTRL", value((int)SDLK_RCTRL));
    key.define_property("LCTRL", value((int)SDLK_LCTRL));
    key.define_property("RALT", value((int)SDLK_RALT));
    key.define_property("LALT", value((int)SDLK_LALT));
    key.define_property("RMETA", value((int)SDLK_RMETA));
    key.define_property("LMETA", value((int)SDLK_LMETA));
    key.define_property("LSUPER", value((int)SDLK_LSUPER));
    key.define_property("RSUPER", value((int)SDLK_RSUPER));
    key.define_property("MODE", value((int)SDLK_MODE));
    key.define_property("COMPOSE", value((int)SDLK_COMPOSE));
    key.define_property("HELP", value((int)SDLK_HELP));
    key.define_property("PRINT", value((int)SDLK_PRINT));
    key.define_property("SYSREQ", value((int)SDLK_SYSREQ));
    key.define_property("BREAK", value((int)SDLK_BREAK));
    key.define_property("MENU", value((int)SDLK_MENU));
    key.define_property("POWER", value((int)SDLK_POWER));
    key.define_property("EURO", value((int)SDLK_EURO));
    key.define_property("UNDO", value((int)SDLK_UNDO));
    return key;
  }

  object mod_object() {
    object mod(create<object>());
    mod.define_property("NONE", value((int)KMOD_NONE));
    mod.define_property("LSHIFT", value((int)KMOD_LSHIFT));
    mod.define_property("RSHIFT", value((int)KMOD_RSHIFT));
    mod.define_property("LCTRL", value((int)KMOD_LCTRL));
    mod.define_property("RCTRL", value((int)KMOD_RCTRL));
    mod.define_property("LALT", value((int)KMOD_LALT));
    mod.define_property("RALT", value((int)KMOD_RALT));
    mod.define_property("LMETA", value((int)KMOD_LMETA));
    mod.define_property("RMETA", value((int)KMOD_RMETA));
    mod.define_property("NUM", value((int)KMOD_NUM));
    mod.define_property("CAPS", value((int)KMOD_CAPS));
    mod.define_property("MODE", value((int)KMOD_MODE));
    mod.define_property("CTRL", value((int)KMOD_CTRL));
    mod.define_property("SHIFT", value((int)KMOD_SHIFT));
    mod.define_property("ALT", value((int)KMOD_ALT));
    mod.define_property("META", value((int)KMOD_META));
    return mod;
  }
}
