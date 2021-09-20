/**
 *  See memoryPool.h for block comment
 */

#include "memoryPool.h"

#include <iostream>
#include <stack>
using namespace std;

MemoryPool::MemoryPool() {
  arrSize = sizeof(array) / sizeof(array[0]);
  for (int i = 0; i < arrSize; i++) {
    free.push(i);
  }
}

MemoryPool::NodePtr MemoryPool::newNode() {
  node temp;
  return 5;
}

void MemoryPool::deleteNode(NodePtr curr) {}

char MemoryPool::data(NodePtr curr) { return 'a'; }

char MemoryPool::data(NodePtr curr, char ch) { return 'a'; }

MemoryPool::NodePtr MemoryPool::next(NodePtr curr) { return 5; }

MemoryPool::NodePtr MemoryPool::next(NodePtr curr, NodePtr next) { return 5; }

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

void MemoryPool::nodes(NodePtr head) {}
