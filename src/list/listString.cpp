#include "listString.h"

#include <iostream>
#include <stdexcept>
using namespace std;

AbstractPool* ListString::pool = nullptr;

void ListString::setPool(AbstractPool* thePool) {
  AbstractPool* temp = pool;
  pool = thePool;
  // Moved stuff around to be able to reinitialize liststring
  if (temp != nullptr) {
    throw logic_error("ListString memory pool being reset.");
  }
}

ListString::ListString() : head{AbstractPool::nullNodePtr} {
  if (pool == nullptr) throw logic_error("ListString memory pool never set.");
}

ListString::ListString(const string& strValue)
    : head{AbstractPool::nullNodePtr} {
  for (auto ch : strValue) {
    append(ch);
  }
}

ListString::ListString(ListString& original) : head{AbstractPool::nullNodePtr} {
  for (ListString::NodePtr curr = original.head;
       curr != ListString::nullNodePtr; curr = pool->next(curr)) {
    append(pool->data(curr));
  }
}

void ListString::swap(ListString& other) { std::swap(head, other.head); }

ListString::ListString(ListString&& original)
    : head{AbstractPool::nullNodePtr} {
  this->swap(original);
}

using std::swap;
ListString& ListString::operator=(ListString rhs) {
  this->swap(rhs);
  return *this;
}

void ListString::clean(NodePtr& listToClean) {
  while (listToClean != nullNodePtr) {
    NodePtr bye = listToClean;
    listToClean = pool->next(listToClean);
    pool->deleteNode(bye);
  }
}

ListString::~ListString() { clean(head); }

int ListString::length() const {
  int len = 0;
  for (NodePtr curr = head; curr != nullNodePtr; curr = pool->next(curr)) ++len;
  return len;
}

bool ListString::isEmpty() const { return length() == 0; }

void ListString::append(char ch) {
  // Gracefully handle running out of nodes. Prevents segfaults
  if (pool->free() < 1) {
    cout << "Error: No nodes left in pool. Halting operation." << endl;
  } else {
    NodePtr newNode = pool->newNode();
    pool->data(newNode, ch);
    pool->next(newNode, nullNodePtr);

    if (isEmpty())
      head = newNode;
    else {
      pool->next(lastNode(), newNode);
    }
  }
}

ListString::NodePtr ListString::lastNode() {
  NodePtr last = nullNodePtr;
  // This loop is beautiful Dr. Ladd
  for (NodePtr curr = head; curr != nullNodePtr;
       last = curr, curr = pool->next(curr))
    ;  // empty on purpose
  return last;
}

ostream& operator<<(ostream& out, const ListString& string) {
  for (ListString::NodePtr curr = string.head; curr != ListString::nullNodePtr;
       curr = string.pool->next(curr))
    out << string.pool->data(curr);
  return out;
}

bool ListString::isLetter(char in) {
  if ((in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z')) return true;
  return false;
}

bool ListString::isVowel(char in) {
  switch (in) {
    case 65:   // A
    case 69:   // E
    case 73:   // I
    case 79:   // O
    case 85:   // U
    case 97:   // a
    case 101:  // e
    case 105:  // i
    case 111:  // o
    case 117:  // u
      return true;
    default:
      return false;
  }
}

void ListString::trace(bool traceOn) { pool->trace(traceOn); }
void ListString::freeList() { pool->showFreeList(); }
void ListString::nodes() { pool->nodes(head); }

void ListString::igpayAtinlay() {
  // i is iterator
  NodePtr i = head;
  // pivot is going to be the new head
  NodePtr pivot = head;
  // parent is the node that points at the pivot
  NodePtr parent = head;
  // tail is the last node (which will soon point to the old head)
  NodePtr tail = head;
  // rotated keeps track of if a rotation has occured
  bool rotated = false;
  // stop stops once the next node is a nullNodePtr
  bool stop = false;

  // Only piglatin-alize if the first character is alphabetic
  if (isLetter(pool->data(head))) {
    // Loop until end of word
    while (!stop) {
      // If a vowel has been seen, rotated will be True
      if (!rotated && isVowel(pool->data(i))) {
        rotated = true;
        pivot = i;
      }
      // If at the end of the string, stop the while loop. Set tail
      if (pool->next(i) == nullNodePtr) {
        stop = true;
        tail = i;
      }
      // If not end of string, set parent to i and advance i. If we rotated,
      // stop advancing parent.
      if (!stop) {
        if (!rotated) parent = i;
        i = pool->next(i);
      }
    }
    // If the vowel was the first character, it wasn't truely rotated
    if (rotated && (pivot != head)) {
      // point the tail at the head
      pool->next(tail, head);
      // point the parent of the pivot at nullNodePtr
      pool->next(parent, nullNodePtr);
      // new head is pivot
      head = pivot;
      append('a');
      append('y');
    } else {
      append('w');
      append('a');
      append('y');
    }
  }
}

string ListString::getWord() {
  string out;
  NodePtr temp = head;
  temp--;
  do {
    temp++;
    out.append(1, pool->data(temp));
  } while (pool->next(temp) != nullNodePtr);
  return out;
}
