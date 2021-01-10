#pragma once

#include <functional>
#include <map>
#include <string>

/**
 * A tree structure to speed up comparing input strings and finding the
 * corresponding shortcut string.
 */
struct KeyMapNode {
private:
  /**
   * A map mapping characters with the corresponding node in the tree
   */
  std::map<char, KeyMapNode *> nextKeys;
  /**
   * The key of this node.
   */
  const char key;
  /**
   * Shows whether or not this node is a command node/has a command
   */
  bool hasCmd;
  /**
   * The command associated with the node, could be NULL/empty.
   */
  std::string cmd;

public:

  /**
   * @brief      KeyMapNode constructor without a command
   *
   * @details    Constructs a KeyMapNode object without a command
   *
   * @param      key: char = The associated character
   *
   * @return     KeyMapNode
   */
  KeyMapNode(const char &key);
  /**
   * @brief      KeyMapNode constructor with a command.
   *
   * @details    Constructs a KeyMapNode object with a command.
   *
   * @param      key: char = The associated character
   *             cmd: string = The associated command
   *
   * @return     KeyMapNode
   */
  KeyMapNode(const char &key, const std::string &cmd);

  bool has_cmd() const;

  std::string get_cmd() const;

  /**
   * @brief      Returns true if the next 'key' sequence has a command
   *
   * @details    Returns true if there is a following KeyMapNode that has the
   * same key as `key` and has a command
   *
   * @param      key: const char& = the key to check for
   *
   * @return     boolean
   */
  bool has(const char &key);

  /**
   * @brief      Adds a new KeyMapNode with command, if possible.
   *
   * @details    Adds a new KeyMapNode with command `cmd` associated with the
   * string `keyString`. Will try to add the node to the tree. If another node
   * exists with the same string and it has a command then it will fail,  throw
   * `invalid_argument`, and log the string with the command to the system log
   *
   * @param      keyString: string = The key string to associate the command
   * with cmd: string = The shell command to associate with
   *
   * @return     void
   *
   * @throws     std::invalid_argument Thrown if a node with the same string
   * already has a command
   */
  void add(const std::string &keyString, const std::string &cmd);

  /**
   * @brief      Retrieves a pointer to the KeyMapNode with the given character
   *
   * @details    Retrieves a pointer to the KeyMapNode associated with the given
   * character. If no KeyMapNode is associated, then return `nullptr`.
   *
   * @param      key: char = The character to look for
   *
   * @return     KeyMapNode*
   */
  KeyMapNode *get(const char &key);

  /**
   * @brief      Checks if this is a leaf node
   *
   * @details    Returns true if there are no more possible paths, and false
   * otherwise.
   *
   * @return     bool
   */
  const bool empty() { return nextKeys.empty(); }

  bool operator==(const char &key) const { return key == this->key; }
};
