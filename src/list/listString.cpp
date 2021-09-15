#include "listString.h"
#include <stdexcept>
#include <iostream>
using namespace std;



AbstractPool * ListString::pool = nullptr;

void ListString::setPool(AbstractPool *thePool) {
  if (pool != nullptr)
    throw logic_error("ListString memory pool being reset.");

  pool = thePool;
}

ListString::ListString()
  : head{AbstractPool::nullNodePtr}
{
  if (pool == nullptr)
    throw logic_error("ListString memory pool never set.");
}

ListString::ListString(const string &strValue)
  : head{AbstractPool::nullNodePtr}
{
  for (auto ch : strValue) {
    append(ch);
  }
}

ListString::ListString(ListString & original)
    : head{AbstractPool::nullNodePtr}
{
  for (ListString::NodePtr curr = original.head;
       curr != ListString::nullNodePtr;
       curr = pool->next(curr))
  {
    append(pool->data(curr));
  }
}

void ListString::swap(ListString & other) {
  std::swap(head, other.head);
}

ListString::ListString(ListString && original)
  : head{AbstractPool::nullNodePtr}
{
  this->swap(original);
}

using std::swap;
ListString & ListString::operator=(ListString rhs) {
  this->swap(rhs);
  return *this;
}

void ListString::clean(NodePtr & listToClean) {
  while (listToClean != nullNodePtr) {
    NodePtr bye = listToClean;
    listToClean = pool->next(listToClean);
    pool->deleteNode(bye);
  }
}

ListString::~ListString() {
  clean(head);
}

int ListString::length() const {
  int len = 0;
  for (NodePtr curr = head; curr != nullNodePtr; curr = pool->next(curr))
    ++len;
  return len;
}

bool ListString::isEmpty() const {
  return length() == 0;
}

void ListString::append(char ch) {
  NodePtr newNode = pool->newNode();
  pool->data(newNode, ch);
  pool->next(newNode, nullNodePtr);

  if (isEmpty())
    head = newNode;
  else {
    pool->next(lastNode(), newNode);
  }
}

ListString::NodePtr ListString::lastNode() {
  NodePtr last = nullNodePtr;
  for (NodePtr curr = head; curr != nullNodePtr; last = curr, curr = pool->next(curr))
    ; // empty on purpose
  return last;
}

ostream& operator<<(ostream & out, const ListString& string) {
  for (ListString::NodePtr curr = string.head; curr != ListString::nullNodePtr; curr = string.pool->next(curr))
    out << string.pool->data(curr);
  return out;
}

void ListString::trace(bool traceOn) { pool->trace(traceOn); }
void ListString::freeList() { pool->showFreeList(); }
void ListString::nodes() {
  pool->nodes(head);
}
void ListString::igpayAtinlay() {}
