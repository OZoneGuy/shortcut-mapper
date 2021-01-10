#pragma once

#include "key_map_node.hpp"
#include <string>

/**
 * The template file location
 */
#define KEY_MAP_TEMPLATE "/usr/share/shortcut-mapper/key-map"

/**
 * @brief      Loads the key map from the given file.
 *
 * @details    Load the key map from the given file and return it as a pointer.
 * If the file could not be opened or if it doesn't exist it will copy the
 * template file to the give file location, creating any directories as
 * required. It also returns the character and mods/masks for the master key
 * bind through the parameters `code` and `mods`
 *
 * @param      file_name: string = The name of the file to read, absolute path.
 *
 * @param[out] code: char = The character used for the master key bind
 *
 * @param[out] mods: unsigned int = The Key mods/masks used for the master key
 * bind.
 *
 * @return     KeyMapNode*
 */
KeyMapNode *load_key_map(std::string &file_name, char &code,
                         unsigned int &mods);

/**
 * @brief      Set `code` and `mods` from the string `keys`
 *
 * @details    Set `code` character and `mods` using the `keys` string as
 * described in the documentation for the master key
 *
 * @param      keys: string = The key binding string to parse
 *
 * @param      code: char = The key to listen to
 *
 * @param      mods: unsigned int = The mods/masks for the key.
 *
 * @return     void
 */
void grab_master(std::string keys, char &code, unsigned int &mods);
