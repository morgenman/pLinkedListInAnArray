/**
 * One line summary
 *
 * Mulitline description describing intent of file
 *
 * @author Dylan C. Morgen
 * @email morgendc203@potsdam.edu
 * @course CIS XXX Course Name
 * @assignment memoryPool.h
 * @due 9/20/2021
 */

#include "abstractPool.h"

class MemoryPool : public AbstractPool {
 public:
  /**
   *
   * @return {NodePtr} :
   */
  NodePtr newNode();

  /**
   *
   * @param  {NodePtr} curr :
   */
  void deleteNode(NodePtr curr);

  /**
   *
   * @param  {NodePtr} curr :
   * @return {char}         :
   */
  char data(NodePtr curr);

  /**
   *
   * @param  {NodePtr} curr :
   * @param  {char} ch      :
   * @return {char}         :
   */
  char data(NodePtr curr, char ch);

  /**
   *
   * @param  {NodePtr} curr :
   * @return {NodePtr}      :
   */
  NodePtr next(NodePtr curr);

  /**
   *
   * @param  {NodePtr} curr :
   * @param  {NodePtr} next :
   * @return {NodePtr}      :
   */
  NodePtr next(NodePtr curr, NodePtr next);

  /**
   *
   * @param  {bool} traceOn :
   * @return {bool}         :
   */
  bool trace(bool traceOn);

  void showFreeList();

  void nodes(NodePtr head);
};
