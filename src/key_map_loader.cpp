#include "headers/key_map_loader.hpp"
#include "headers/key_map_node.hpp"
#include "headers/utils.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/syslog.h>
#include <syslog.h>

using std::invalid_argument;
using std::istringstream;
using std::string;
namespace fs = std::filesystem;

KeyMapNode *load_key_map(string &file_name, char &code, unsigned &mods) {
  std::ifstream file(file_name);

  // Try opening file
  if (!file.is_open()) {
    // Log failure to open file
    write_log(LOG_ERR, "Could not open file at: " + file_name +
                           ". Copying template file.");

    // Create directory
    fs::create_directory(fs::path(file_name).parent_path());

    // copy template to file location
    fs::copy_file(KEY_MAP_TEMPLATE, file_name);

    // reopen file
    file.open(file_name);
  }

  string line;
  KeyMapNode *key_map = new KeyMapNode(
      '\0'); // Root node, has no commands and cannot be activated

  while (getline(file, line)) {
    // empty line, skip
    if (line == "")
      continue;

    // holds the first non space terminated string, usually holds
    // the key string
    string keys;
    istringstream iss(line);
    iss >> keys;

    // commented line
    if (keys[0] == '#')
      continue;

    // Register master hotkey
    if (keys == "Master:") {
      // Store the master key bind
      iss >> keys;

      // grab the key bind
      grab_master(keys, code, mods);
      continue;
    }

    // register key string
    string cmd;
    // get the remainder of the line
    getline(iss, cmd);
    // remove first character, it is a space
    cmd = cmd.substr(1);
    try {
      // try adding the command to the key tree
      key_map->add(keys, cmd);
    } catch (const invalid_argument &error) {
      write_log(LOG_ERR, error.what());
    }
  }

  // close file
  file.close();

  // Return key map tree
  return key_map;
}

void grab_master(std::string keys, char &code, unsigned int &mods) {
  Display *dpy;
  int i = 0;
  code = 0;
  mods = 0;
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
    if (keys[i] == 'M') {
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
}
