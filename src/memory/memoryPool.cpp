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
  for (int i = arrSize - 1; i >= 0; i--) {
    free.push(i);
    set(i, 0, nullNodePtr);
  }
  print();
}

void MemoryPool::set(NodePtr index, char ch, NodePtr next) {
  array[index].data = ch;
  array[index].next = next;
}

MemoryPool::node MemoryPool::get(NodePtr index) { return array[index]; }

void MemoryPool::print() {
  cout << "Node\t"
       << "|\t"
       << "Value\t"
       << "|\t"
       << "Next" << endl;
  for (int i = 0; i < 15; i++) {
    cout << i << "\t"
         << "|\t*" << (char)array[i].data << "*\t"
         << "|\t*" << array[i].next << "*" << endl;
    cout.flush();
  }
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

void MemoryPool::deleteNode(NodePtr curr) { free.push(curr); }

char MemoryPool::data(NodePtr curr) { return get(curr).data; }

char MemoryPool::data(NodePtr curr, char ch) {
  print();
  set(curr, ch, get(curr).next);
  return get(curr).data;
}

MemoryPool::NodePtr MemoryPool::next(NodePtr curr) { return array[curr].next; }

MemoryPool::NodePtr MemoryPool::next(NodePtr curr, NodePtr next) {
  set(curr, next, get(curr).next);
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
  node i = get(head);
  while (i.next != nullNodePtr) {
    cout << i.next << "\t" << i.next << endl;
    i = get(head++);
  }
}
