#include "headers/key_mapper.hpp"
#include "headers/key_map_loader.hpp"
#include "headers/key_map_node.hpp"
#include "headers/utils.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/syslog.h>

using std::cout;
using std::endl;
using std::string;

string config_file;
string log_file;

KeyMapNode *keyMapTree;

static Display *dpy;
static XEvent ev;
static char *s;
static unsigned int kc;

int main(int argc, char *argv[]) {

  //////////////////////////////  Handle Option ////////////////////////////////
  if (argc > 1)
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "-h")) {
        // print help
        cout
            << "Usage:" << endl
            << "\t"
            << "-c FILE_NAME"
            << "\t"
            << R"(Specify config file location. Defaults to "$HOME/.config/key_mapper/key_map", or "$XDG_CONFIG_HOME/key_mapper/key_map" if 'XDG_CONFIG_HOME' is set.)"
            << "\n"
            << "\t"
            << "-l FILE_NAME"
            << "\t"
            << "Specify log file location. Defaults to /var/log/?"
            << "\n"
            << "\t"
            << "-h"
            << "\t\t"
            << "Print this help message." << endl;
        exit(0);
      } else if (strcmp(argv[i], "-c")) {
        i++;
        config_file = argv[i];
      } else if (strcmp(argv[i], "-l")) {
        i++;
        log_file = argv[i];
      }
    }

  //////////////////////////////  Initialisation  //////////////////////////////
  openlog("key_mapper", LOG_CONS | LOG_PID, LOG_USER);

  // initialise display
  if (NULL == (dpy = XOpenDisplay(0))) {
    write_log(LOG_ERR, "Failed to acquire display.");
    exit(1);
  }

  ////////////////////////////////  Load Keys //////////////////////////////////
  if (config_file
          .empty()) { // config file has not been specified using '-c' option
    char *XDG_CONF =
        getenv("XDG_CONFIG_HOME"); // Get the default config location
    if (XDG_CONF == NULL) // 'XDG_CONFIG_HOME' is not set, use default location
      config_file = string(getenv("HOME")) + "/.config/key_mapper/key_map";
    else
      config_file = string(XDG_CONF) + "key_mapper/key_map";
  }

  char code;
  unsigned mods;
  keyMapTree = load_key_map(config_file, code, mods); // Load key map
  if (keyMapTree == nullptr ||
      keyMapTree->empty()) { // Check for empty config or failed load
    write_log(LOG_WARNING, "Empty key map");
    return 0;
  }

  ////////////////////////////// Listen to events //////////////////////////////
  // Listen to master key bind
  XGrabKey(dpy, keycode_from_string(dpy, string(1, code)), mods,
           DefaultRootWindow(dpy), 0, GrabModeAsync, GrabModeAsync);
  while (true) {
    XNextEvent(dpy, &ev);
    switch (ev.type) {
    case KeyPress:
      handle_keyboard(keyMapTree);
      break;
    }
  }

  //////////////////////////////////  Ending  //////////////////////////////////
  closelog();
  return 0;
}

void handle_keyboard(KeyMapNode *keyMap) {
  // grab keyboard
  XGrabKeyboard(dpy, DefaultRootWindow(dpy), false, GrabModeAsync,
                GrabModeAsync, CurrentTime);

  bool cont = true;
  KeyMapNode *curNode = keyMapTree;
  while (cont) {
    XNextEvent(dpy, &ev);
    switch (ev.type) {
    case KeyPress: // get key press

      // if user presses escape, stop listening and release keyboard
      if (keycode_from_string(dpy, "Escape") == ev.xkey.keycode) {
        cont = false;
        break;
      }

      // Get next node from key press
      curNode = curNode->get(char_from_keycode(ev));

      // check if node is null
      if (curNode != nullptr) {

        // if it has a command, execute command
        if (curNode->hasCmd)
          system(("setsid -f " + curNode->cmd)
                     .c_str()); // execute shell command as a new process
        if (curNode->empty())   // if there are no more possible keys, stop
          cont = false;
      } else {
        cont = false;
      }
      break;
    case Expose: // Honestly, not sure. This was advised by SO
      while (XCheckTypedEvent(dpy, Expose, &ev)) /* empty body */
        ;
      break;
    default:
      break;
    }
  }

  // Release keyboard
  XUngrabKeyboard(dpy, CurrentTime);
}
