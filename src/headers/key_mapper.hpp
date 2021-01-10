#pragma once

#include "key_map_node.hpp"
#include <X11/Xlib.h>
#include <string>

/**
 * @brief      Handle keyboard input for key strings
 *
 * @details    Handles keyboard grabbing and input for shortcut strings. Also
 * responsible for executing the appropriate command.
 *
 * @param      keyMap: KeyMapNode* = The current active KeyMapNode
 *
 * @return     void
 */
void handle_keyboard(KeyMapNode *keyMap);
