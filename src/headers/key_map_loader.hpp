#pragma once

#include "key_map_node.hpp"
#include <string>

KeyMapNode* load_key_map(std::string &file_name);

void grab_master(std::string keys);
