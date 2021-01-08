#pragma once

#include "key_map_node.hpp"
#include <string>

#define KEY_MAP_TEMPLATE "/usr/share/shortcut-mapper/key-map"

KeyMapNode* load_key_map(std::string &file_name, char &code, unsigned int &mods);

void grab_master(std::string keys, char &code, unsigned int &mods);
