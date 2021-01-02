#pragma once

#include <functional>
#include <string>
#include <map>

struct KeyMapNode {
private:

  std::map<char, KeyMapNode*> nextKeys;
  const char key;

public:

  const bool hasCmd;
  const std::string cmd;

  KeyMapNode(const char &key);
  KeyMapNode(const char &key, const std::string &cmd);

  /**
   * @brief      Returns true if the next 'key' sequence has a command
   *
   * @details    Returns true if there is a following KeyMapNode that has the same key as `key` and has a command
   *
   * @param      key: const char& = the key to check for
   *
   * @return     boolean
   */
  bool has(const char &key);
  void add(const std::string &keyString, const std::string &cmd);
  KeyMapNode* get(const char &key);


  bool operator==(const char& key) const {
    return key == this->key;
  }
};
