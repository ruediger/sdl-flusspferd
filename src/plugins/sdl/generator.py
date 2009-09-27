# This generator was used to wrap some Event classes

def build_wrapper(name, elements):
    print "FLUSSPFERD_CLASS_DESCRIPTION"
    print "("
    print name + ","
    print "(constructor_name, \"" + name + "\")"
    print "(constructible, false)"
    print "(full_name, \"sdl." + name + "\")"
    print "(properties,"
    for i in elements:
        print "  (\"" + i + "\", getter, get_" + i + ")"
    print "))\n{"
    print "  SDL_" + name + " event;"
    print "public:"
    for i in elements:
        print "  int get_" + i + "() { return event." + i + "; }"
    print ""
    print "  " + name + "(flusspferd::object const &self, SDL_" + name + " const &event)"
    print "    : base_type(self), event(event)"
    print "  { }"
    print ""
    print "  static " + name + " &create(SDL_" + name + " const &e) {"
    print "    return flusspferd::create_native_object<" + name + ">(object(), e);"
    print "  }"
    print "};"


def build_wrapper_(elements, name):
    build_wrapper(name, elements)

#print ""
#build_wrapper_(["type", "which", "button", "state" ], "JoyButtonEvent")
#print ""
#build_wrapper_(["type", "which", "hat", "value"], "JoyHatEvent")
#print ""
#build_wrapper_(["type", "which", "ball", "xrel", "yrel"], "JoyBallEvent")
print ""
build_wrapper_(["type","w", "h"], "ResizeEvent")
print ""
build_wrapper_(["type"], "ExposeEvent")
print ""
build_wrapper_(["type"], "QuitEvent")
print ""
