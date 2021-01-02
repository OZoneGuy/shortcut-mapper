#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <string>

void write_log(int priority, const std::string &msg);

KeyCode keycode_from_string(Display *dpy, const std::string& key);

char char_from_keycode(const XEvent &ev);
