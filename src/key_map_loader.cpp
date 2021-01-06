#include "headers/key_map_loader.hpp"
#include "headers/key_map_node.hpp"
#include "headers/utils.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/syslog.h>
#include <syslog.h>

using std::invalid_argument;
using std::istringstream;
using std::string;

KeyMapNode *load_key_map(string &file_name) {
  std::ifstream file(file_name);

  // Try opening file
  if (!file.is_open()) {
    // Log failure to open file
    write_log(LOG_ERR, string("Could not open file at: ") + file_name);
    return nullptr;
  }

  string line;
  KeyMapNode *key_map = new KeyMapNode(
      '\0'); // Root node, has no commands and cannot be activated

  while (getline(file, line)) {
    if (line == "") // empty line, skip
      continue;

    string keys; // holds the first non space terminated string, usually holds
                 // the key string
    istringstream iss(line);
    iss >> keys;
    if (keys[0] == '#') // commented line
      continue;

    // Register master hotkey
    if (keys == "Master:") {
      iss >> keys; // Store the master key bind

      grab_master(keys); // grab the key bind
      continue;
    }

    // register key string
    string cmd;
    getline(iss, cmd);   // get the remainder of the line
    cmd = cmd.substr(1); // remove first character, it is a space
    try {
      key_map->add(keys, cmd); // try adding the command to the key tree
    } catch (const invalid_argument &error) {
      write_log(LOG_ERR, error.what());
    }
  }

  // close file
  file.close();

  // Return key map tree
  return key_map;
}

void grab_master(std::string keys) {
  Display *dpy;

  int i = 0;
  unsigned int mods = 0;
  char code = '\0';
  bool failed = false;

  // Get display
  if (NULL == (dpy = XOpenDisplay(0))) {
    write_log(LOG_ERR, "Failed to acquire display.");
    exit(1);
  }

  // Read and parse key bind
  while (i < keys.size()) {

    // there is only one character (remaining)
    if (i == keys.size() - 1) {
      code = keys[i];
      break;
    }

    // Control Key modifier
    if (keys[i] == 'C') {
      if (i + 2 < keys.size() && keys[i + 1] == '-') {
        mods |= ControlMask;
        i += 2;
      } else {
        failed = true;
        break;
      }
    }

    // Alt key modifier
    if (keys[i] == 'A') {
      if (i + 2 < keys.size() && keys[i + 1] == '-') {
        mods |= Mod1Mask;
        i += 2;
      } else {
        failed = true;
        break;
      }
    }

    // Super (Windows) key modifier
    if (keys[i] == 'S') {
      if (i + 2 < keys.size() && keys[i + 1] == '-') {
        mods |= Mod4Mask;
        i += 2;
      } else {
        failed = true;
        break;
      }
    }
  }

  // Failed to parse the key, defaulting master key to C-S-k (Control+Super+k)
  if (failed) {
    write_log(LOG_WARNING, string("Bad Master Key at character: ") +
                               std::to_string(i) +
                               string("\tDefaulting to C-S-k."));
    code = 'k';
    mods = ControlMask | Mod4Mask;
  }

  // Grab key bind
  XGrabKey(dpy, keycode_from_string(dpy, string(1, code)), mods,
           DefaultRootWindow(dpy), 0, GrabModeAsync, GrabModeAsync);
}
