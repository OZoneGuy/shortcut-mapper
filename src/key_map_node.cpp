#include "headers/key_map_node.hpp"
#include <stdexcept>
#include <string>

using std::invalid_argument;
using std::string;

KeyMapNode::KeyMapNode(const char &key) : key(key), cmd(""), hasCmd(false) {}
KeyMapNode::KeyMapNode(const char &key, const string &cmd)
    : key(key), cmd(cmd), hasCmd(true) {}

bool KeyMapNode::has(const char &key) {
  auto keyStoke = nextKeys.find(key);
  if (keyStoke != nextKeys.end())
    return keyStoke->second->hasCmd;

  return false;
}

void KeyMapNode::add(const string &keySeq, const string &cmd) {
  if (keySeq.size() == 1) {
    if (has(keySeq[0]))
      throw invalid_argument("Key string command already defined");
    nextKeys.emplace(keySeq[0], new KeyMapNode(keySeq[0], cmd));
  } else {
    auto search = nextKeys.find(keySeq[0]);
    if (search == nextKeys.end()) {
      auto newKey = nextKeys.emplace(keySeq[0], new KeyMapNode(keySeq[0]));
      (*newKey.first).second->add(keySeq.substr(1),
                                  cmd);
    } else {
      (*search).second->add(keySeq.substr(1),
                            cmd);
    }
  }
}

KeyMapNode* KeyMapNode::get(const char &key) {
  auto search = nextKeys.find(key);
  if (search == nextKeys.end())
    return nullptr;
  else
    return search->second;
}
