// vim:ts=2:sw=2:expandtab:autoindent:filetype=cpp:
/*
Copyright (c) 2008 Aristid Breitkreuz, Ruediger Sonderfeld

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

#include "flusspferd/io/file_class.hpp"
#include "flusspferd/local_root_scope.hpp"
#include "flusspferd/create.hpp"
#include "flusspferd/string.hpp"
#include "flusspferd/string_io.hpp"
#include "flusspferd/create.hpp"
#include <boost/scoped_array.hpp>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace flusspferd;
using namespace flusspferd::io;

class file_class::impl {
public:
  std::fstream stream;

  static void create(char const *name, boost::optional<int> mode);
};

file_class::file_class(call_context &x)
  : p(new impl)
{
  if (!x.arg.empty()) {
    string name = x.arg[0].to_string();
    open(name.c_str());
  }
}

file_class::~file_class()
{}

void file_class::post_initialize() {
  register_native_method("open", &file_class::open);
  register_native_method("close", &file_class::close);
  register_native_method("readWhole", &file_class::read_whole);
  register_native_method("read", &file_class::read);
  register_native_method("write", &file_class::write);
}

char const *file_class::class_info::constructor_name() {
  return "File";
}

std::size_t file_class::class_info::constructor_arity() {
  return 1;
}

void file_class::class_info::augment_constructor(object constructor) {
  create_native_function(constructor, "create", &impl::create);
}

object file_class::class_info::create_prototype() {
  local_root_scope scope;

  object proto = create_object();

  create_native_method(proto, "open", 1);
  create_native_method(proto, "close", 0);
  create_native_method(proto, "readWhole", 0);
  create_native_method(proto, "read", 1);
  create_native_method(proto, "write", 1);

  return proto;
}

void file_class::open(char const *name) {
  p->stream.open(name);

  if (!p->stream)
    throw exception("Could not open file");
}

void file_class::close() {
  p->stream.close();
}

string file_class::read_whole() {
  std::string data;
  char buf[4096];

  do { 
    p->stream.read(buf, sizeof(buf));
    data.append(buf, p->stream.gcount());
  } while (p->stream);

  return string(data);
}

string file_class::read(unsigned size) {
  if (!size)
    size = 4096;

  boost::scoped_array<char> buf(new char[size + 1]);

  p->stream.read(buf.get(), size);
  buf[p->stream.gcount()] = '\0';

  return string(buf.get());
}

void file_class::write(string const &text) {
  p->stream << text;
}

void file_class::impl::create(char const *name, boost::optional<int> mode) {
  if (creat(name, mode.get_value_or(0666)) < 0)
    throw exception("Could not create file");
}
