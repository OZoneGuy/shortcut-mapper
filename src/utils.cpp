#include "headers/utils.hpp"
#include <ctime>
#include <sys/syslog.h>
#include <string>

void write_log(int priority, const std::string &msg){
  std::time_t time = std::time(nullptr);
  syslog(priority, "%s: %s", std::ctime(&time), msg.c_str());
}

KeyCode keycode_from_string(Display *dpy, const std::string &key){
  return XKeysymToKeycode(dpy, XStringToKeysym(key.c_str()));
}

char char_from_keycode(const XEvent &ev){
  return XKeysymToString(XLookupKeysym((XKeyEvent *)&ev, 0))[0];
}

string str_from_key_code(const XEvent &ev) {
  return XKeysymToString(XLookupKeysym((XKeyEvent *)&ev, 0));
}
