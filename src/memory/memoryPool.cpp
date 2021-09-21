/**
 *  See memoryPool.h for block comment
 */

#include "memoryPool.h"

#include <iostream>
#include <stack>
using namespace std;

MemoryPool::MemoryPool() {
  head = 0;
  arrSize = sizeof(array) / sizeof(array[0]);
  for (int i = 0; i < arrSize; i++) {
    free.push(i);
  }
  for (int i = 0; i < 15; i++) {
    set(i, 'a' + i, i + 1);
  }
}

void MemoryPool::set(NodePtr index, char ch, NodePtr next) {
  array[index].data = ch;
  array[index].data = next;
}
void MemoryPool::set(NodePtr index, char ch) {
  set(index, ch, get(index).next);
}
void MemoryPool::set(NodePtr index, NodePtr next) {
  set(index, get(index).data, next);
}

MemoryPool::node MemoryPool::get(NodePtr index) { return array[index]; }

MemoryPool::NodePtr MemoryPool::getParentIndex(NodePtr index) {
  int i = head;
  while (array[i].next != nullNodePtr) {
    if (array[i].next == index) return i;
    i++;
  }
  return nullNodePtr;
}

MemoryPool::NodePtr MemoryPool::newNode() {
  if (!free.empty()) {
    int index = free.top();
    free.pop();
    return index;
  } else {
    return nullNodePtr;
  }
}

void MemoryPool::deleteNode(NodePtr curr) {}

char MemoryPool::data(NodePtr curr) { return get(curr).data; }

char MemoryPool::data(NodePtr curr, char ch) {
  set(curr, ch);
  return get(curr).data;
}

MemoryPool::NodePtr MemoryPool::next(NodePtr curr) { return array[curr].next; }

MemoryPool::NodePtr MemoryPool::next(NodePtr curr, NodePtr next) {
  set(curr, next);
  return get(curr).next;
}

bool MemoryPool::trace(bool traceOn) { return false; }

void MemoryPool::showFreeList() {
  // temp stack
  stack<int> temp;

  // Load items into temp stack
  while (free.empty() == false) {
    temp.push(free.top());
    free.pop();
  }

  // Move them back, printing as you go
  while (temp.empty() == false) {
    cout << temp.top() << " ";
    free.push(temp.top());
    temp.pop();
  }
}

void MemoryPool::nodes(NodePtr head) {
  int j = head;
  cout << head;
  node i = get(j);
  while (i.next != nullNodePtr) {
    // cout << i.data << "\t" << i.next << endl;
    j++;
    i = get(j);
  }
}
