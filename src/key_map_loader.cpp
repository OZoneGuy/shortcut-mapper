#include "headers/key_map_loader.hpp"
#include "headers/key_map_node.hpp"
#include "headers/utils.hpp"
#include <X11/X.h>
#include <stdexcept>
#include <sys/syslog.h>
#include <syslog.h>
#include <sstream>
#include <string>
#include <fstream>
#include <X11/Xlib.h>

using std::invalid_argument;
using std::istringstream;
using std::string;

KeyMapNode *load_key_map(string &file_name) {
  std::ifstream file(file_name);

  if (!file.is_open()) {
    write_log(LOG_ERR,
              string("Could not open file at: ") + file_name);
    return nullptr;
  }
  string line;
  KeyMapNode *key_map = new KeyMapNode('\0');
  while (getline(file, line)) {
    if (line == "") // empty line
      continue;
    string keys;
    istringstream iss(line);
    iss >> keys;
    if (keys[0] == '#') // comment line
      continue;

    // Register master hotkey
    if (keys == "Master:") {
      iss >> keys;

      Display *dpy;
      int i = 0;
      unsigned int mods = 0;
      char code = '\0';
      bool failed = false;
      while (i < keys.size()){
        if (i == keys.size() - 1) {
          code = keys[i];
          break;
        }
        if (keys[i] == 'C') {
          if (i + 2 < keys.size() && keys[i + 1] == '-')
            mods |= ControlMask;
          else {
            failed = true;
            break;
          }
        }
        if (keys[i] == 'A') {
          if (i + 2 < keys.size() && keys[i + 1] == '-')
            mods |= Mod1Mask;
          else {
            failed = true;
            break;
          }
        }
        if (keys[i] == 'S') {
          if (i + 2 < keys.size() && keys[i + 1] == '-')
            mods |= Mod4Mask;
          else {
            failed = true;
            break;
          }
        }
      }
      if (failed) {
        write_log(LOG_WARNING,
                  string("Bad Master Key at character: ") + std::to_string(i) +
                  string("\tDefaulting to C-S-k."));
        code = 'k';
        mods = ControlMask | Mod4Mask;
      }
      if (NULL == (dpy = XOpenDisplay(0))) {
        write_log(LOG_ERR, "Failed to acquire display.");
        exit(1);
      }
      XGrabKey(dpy, keycode_from_string(dpy, std::to_string(code)), mods,
               DefaultRootWindow(dpy), 0, GrabModeAsync, GrabModeAsync);
      continue;
    }

    // register key string
    string cmd;
    iss >> cmd;
    try {
      key_map->add(keys, cmd);
    } catch (const invalid_argument& error) {
      write_log(LOG_ERR, error.what());
    }
  }
  return key_map;
}
