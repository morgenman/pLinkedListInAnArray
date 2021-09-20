#ifndef ABSTRACTPOOL_H
#define ABSTRACTPOOL_H

/**
 * Pure virtual functions (= 0) mean the class is abstract (cannot be
 * instantiated). This class must be extended for use with all of
 * these functions implemented in the inheriting type. The virtual
 * functions (the overriding ones you write) can be called through a
 * reference or pointer to an AbstractPool that is instantiated with
 * the subclass.
 */
class AbstractPool {
 public:
  using NodePtr = int;
  constexpr static NodePtr nullNodePtr = -1;

  /**
   * Return a NodePtr at a new node.
   *
   * @return a NodePtr for a valid Node if one is available;
   * nullNodePtr otherwise.
   */
  virtual NodePtr newNode() = 0;

  /**
   * Release a NodePtr back to the pool.
   *
   * @param curr NodePtr indicating the node to return
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  virtual void deleteNode(NodePtr curr) = 0;

  /**
   * Return the data in the given node.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the data (character) in the given node.
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  virtual char data(NodePtr curr) = 0;

  /**
   * Set the data is the given node to the given value.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the new (after setting) data in the node
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  virtual char data(NodePtr curr, char ch) = 0;

  /**
   * Return the next NodePtr in the given node.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the next NodePtr in the given node.
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  virtual NodePtr next(NodePtr curr) = 0;

  /**
   * Set the data is the given node to the given value.
   *
   * @param curr NodePtr indicating the node that is to be dereferenced
   * @return the new (after setting) next NodePtr in the node
   * @throws std::invalid_argument if curr is out of range or nullNodePtr
   */
  virtual NodePtr next(NodePtr curr, NodePtr next) = 0;

  /**
   * Set tracing to the given value. When tracing, every new or delete
   * is logged to stderr.
   *
   * @param traceOn boolean whether trace should be set on or off.
   * @return the new value of the trace flag.
   */
  virtual bool trace(bool traceOn) = 0;

  /**
   * Print out state of the free list.
   */
  virtual void showFreeList() = 0;

  /**
   * Print the nodes in use for the current list.
   *
   * @param head first element in the list; must be on
   * the range nullNodePtr to maximum number of nodes - 1.
   * @requirement must be implemented using recursion
   */
  virtual void nodes(NodePtr head) = 0;
};

#endif /* ABSTRACTPOOL_H */
