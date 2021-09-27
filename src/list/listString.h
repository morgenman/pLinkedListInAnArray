#ifndef LISTSTRING_H
#define LISTSTRING_H

#include <iostream>
#include <string>

#include "abstractPool.h"

class ListString {
 public:
  using NodePtr = AbstractPool::NodePtr;
  constexpr static NodePtr nullNodePtr = AbstractPool::nullNodePtr;

  /**
   * Set the pool to use. Must be run before any ListString are
   * created and can only be called once.
   *
   * @param thePool pointer an an AbstractPool implementation that will provide
   * nodes.
   * @throws logic_error if set a second time.
   */
  static void setPool(AbstractPool *thePool);

  static void trace(bool traceOn);
  static void freeList();

  /**
   * Default constructor; initialized to empty.
   */
  ListString();

  /**
   * Construct with initial value from contents of str.
   *
   * @param str a string of characters to copy into our string
   */
  ListString(const std::string &str);

  /**
   * Copy constructor: copy contents of the original into a new linked
   * list.
   *
   * @param original the ListString to copy
   */
  ListString(ListString &original);

  /**
   * Move constructor: swap contents with original, assuming original
   * will be deleted.
   *
   * @param orignal the ListString that is being robbed of its content.
   */
  ListString(ListString &&original);

  /**
   * Assignment operator. Parameter passed by value on purpose so the
   * lhs can swap with the parameter to get its value.
   *
   */
  ListString &operator=(ListString rhs);

  /**
   * Delete a ListString, returning all Nodes to the Pool.
   */
  virtual ~ListString();

  /**
   * Return the length.
   *
   * @return number of characters stored in the string.
   */
  virtual int length() const;

  /**
   * Is this string empty?
   *
   * @return true if empty, false otherwise.
   */
  virtual bool isEmpty() const;

  /**
   * Append the given character to the end of the string.
   *
   * @param ch the character to append
   */
  virtual void append(char ch);

  virtual void igpayAtinlay();

  virtual void nodes();

  /**
   * Return word as a string. Used in testing function
   *
   * @return {std::string}  :
   */
  std::string getWord();

 private:
  // Static _pointer_ to the class-wide memory pool.  MUST be set
  // before any constructor is called; cannot be reset.
  static AbstractPool *pool;

  /**
   * Tests if a character is alphabetic
   *
   * @param  {char} in : character to test
   * @return {bool}    : true if character is a-Z
   */
  static bool isLetter(char in);

  /**
   * Determines if a character is a vowel
   *
   * @param  {char} in : character to test
   * @return {bool}    : true if vowel
   */
  static bool isVowel(char in);

  /**
   * Swap our guts with the guts of the other string.
   *
   * @param other another ListString with which we will exchange
   * value.
   */
  void swap(ListString &other);

  /**
   * Clean up a linked list by releasing the nodes.
   *
   * @param listToClean points to the list to be released; will be set
   * to nullNodePtr upon return.
   */
  void clean(NodePtr &listToClean);

  /**
   *  Return the NodePtr of the last node in the current list.
   *
   *  @return returns the "address" of the last node or nullNodePtr if
   *  this string's list is empty.
   */
  NodePtr lastNode();

  // The NodePtr pointing at our linked-list content.
  NodePtr head;

  // declaration of at ouput operator for ListString. "friend" means that this
  // external function is permitted to break encapsulation.
  friend std::ostream &operator<<(std::ostream &out, const ListString &string);
};

#endif /* LISTSTRING_H */
