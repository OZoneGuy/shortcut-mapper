#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <string>

/**
 * @brief      Writes a log message to the system
 *
 * @details    Write a log message to the system log using syslog command
 *
 * @param      priority: int = The log message priority, see `syslog` for
 * details
 *
 * @param      msg: string = The log message
 *
 * @return     void
 */
void write_log(int priority, const std::string &msg);

/**
 * @brief      Get the XKeyCode from the given string
 *
 * @details    Get the keycode corresponding the given string
 *
 * @param      dpy: Display* = A pointer to the Display
   @param      key: string = The key string to get the code of
 *
 * @return     KeyCode
 */
KeyCode keycode_from_string(Display *dpy, const std::string &key);

/**
 * @brief      Get the character corresponding to the given KeyCode
 *
 * @details    Uses XEvent to get the most the KeyCode of the most recent key
 * press. Then gets the corresponding string and returns it in char form. Only
 * works with characters.
 *
 * @param      ev: XEvent = The XEvent containing the reference to the key
 * pressed
 *
 * @return     char
 */
char char_from_keycode(const XEvent &ev);

/**
 * @brief      Get the name of the given key code
 *
 * @details    Uses XEvent to get the most the KeyCode of the most recent key
 * press. Then returns the corresponding string. Similar to `char_from_keycode`
 * but this returns string name of the key code
 *
 * @param      ev: XEvent = The XEvent containing the reference to the key
 * pressed
 *
 * @return     std::string
 */
std::string str_from_key_code(const XEvent &ev);
