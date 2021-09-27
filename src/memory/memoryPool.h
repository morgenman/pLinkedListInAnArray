/**
 * Implementation of abstractPool
 *
 * @author Dylan C. Morgen
 * @email morgendc203@potsdam.edu
 * @course CIS XXX Course Name
 * @assignment memoryPool.h
 * @due 9/20/2021
 */

#include <stack>

#include "abstractPool.h"

class MemoryPool : public AbstractPool {
 private:
  /**
   * Node Structure
   */
  struct node {
   public:
    char data;
    NodePtr next;
  };
  // This stores the size of the array and is initialized on construction.
  int arrSize;

  // Actual data pool
  node array[100];

  // Trace Support implementation
  bool traceOn = false;

  // Free list implementation. Just a stack of indexes
  std::stack<int> freeList;

  // Set and get functions, created for my own sanity
  void set(NodePtr index, char ch, NodePtr next);
  node get(NodePtr index);

  //
  void print(const char* in);
  void print(const char* in, bool arr);

 public:
  /**
   * MemoryPool constructor.
   *
   */
  MemoryPool();

  /**
   * Return a NodePtr at a new node.
   *
   * @return a NodePtr for a valid Node if one is available;
   * nullNodePtr otherwise.
   */
  NodePtr newNode();

  /**
   * Returns the number of free nodes left
   *
   * @return {int}  : the number of free nodes
   */
  int free();

  /**
   * Release a NodePtr back to the pool.
   *
   * @param curr NodePtr indicating the node to return
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  void deleteNode(NodePtr curr);

  /**
   * Return the data in the given node.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the data (character) in the given node.
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  char data(NodePtr curr);

  /**
   * Set the data is the given node to the given value.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the new (after setting) data in the node (not sure why?)
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  char data(NodePtr curr, char ch);

  /**
   * Return the next NodePtr in the given node.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the next NodePtr in the given node.
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  NodePtr next(NodePtr curr);

  /**
   * Set the data is the given node to the given value.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the new (after setting) next NodePtr in the node
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  NodePtr next(NodePtr curr, NodePtr next);

  /**
   * Set tracing to the given value. When tracing, every new or delete
   * is logged to stderr.
   *
   * @param traceOn boolean whether trace should be set on or off.
   * @return the new value of the trace flag.
   */
  bool trace(bool traceOn);

  /**
   * Print out state of the free list.
   */
  void showFreeList();

  /**
   * Print the nodes in use for the current list.
   *
   * @param head first element in the list; must be on
   * the range nullNodePtr to maximum number of nodes - 1.
   * @requirement must be implemented using recursion
   */
  void nodes(NodePtr head);
};
