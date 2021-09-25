/**
 *  See memoryPool.h for block comment
 */

#include "memoryPool.h"

#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

MemoryPool::MemoryPool() {
  head = 0;
  arrSize = sizeof(array) / sizeof(array[0]);
  for (int i = arrSize - 1; i >= 0; i--) {
    free.push(i);
    set(i, 0, nullNodePtr);
  }
}

void MemoryPool::set(NodePtr index, char ch, NodePtr next) {
  array[index].data = ch;
  array[index].next = next;
}

MemoryPool::node MemoryPool::get(NodePtr index) { return array[index]; }

void MemoryPool::print(const char* in) { cout << in << endl; }
void MemoryPool::print(const char* in, bool arr) {
  cout << in << endl;
  if (arr) {
    cout << "Current state of array: " << endl;
    cout << "Node\t"
         << "|\t"
         << "Value\t"
         << "|\t"
         << "Next" << endl;
    for (int i = 0; i < 15; i++) {
      cout << i << "\t"
           << "|\t*" << array[i].data << "*\t"
           << "|\t*" << array[i].next << "*" << endl;
      cout.flush();
    }
  }
}

MemoryPool::NodePtr MemoryPool::newNode() {
  if (!free.empty()) {
    int index = free.top();
    free.pop();
    if (traceOn)
      print(("Giving new node upon request. Node " + to_string(index) +
             " will be returned")
                .c_str());
    return index;
  } else {
    if (traceOn) print("No free nodes to give.");
    return nullNodePtr;
  }
}

void MemoryPool::deleteNode(NodePtr curr) {
  if (traceOn) print(("Deleting node " + to_string(curr)).c_str());
  free.push(curr);
}

char MemoryPool::data(NodePtr curr) {
  if (traceOn)
    print(("Returning node " + to_string(curr) + ", which is set to " +
           get(curr).data)
              .c_str());
  return get(curr).data;
}

char MemoryPool::data(NodePtr curr, char ch) {
  if (traceOn) print(("Setting node " + to_string(curr) + " to " + ch).c_str());
  set(curr, ch, get(curr).next);
  return get(curr).data;
}

MemoryPool::NodePtr MemoryPool::next(NodePtr curr) {
  if (traceOn)
    print(("Returning the node that node  " + to_string(curr) +
           " points to, which is " + to_string(array[curr].next))
              .c_str());
  return array[curr].next;
}

MemoryPool::NodePtr MemoryPool::next(NodePtr curr, NodePtr next) {
  if (traceOn)
    print(("Setting node " + to_string(curr) + " to point towards node " +
           to_string(next))
              .c_str());
  set(curr, get(curr).data, next);
  return get(curr).next;
}

bool MemoryPool::trace(bool traceOn) {
  MemoryPool::traceOn = traceOn;
  if (traceOn)
    print("Trace On");
  else
    print("Trace Off");
  return MemoryPool::traceOn;
}

void MemoryPool::showFreeList() {
  if (traceOn) print("\n", true);
  cout << "Free node stack:" << endl << endl;
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
  if (traceOn)
    print(("Traversing through nodes from index " + to_string(head) +
           " until pointing at a nullNodePtr")
              .c_str());
  node i = get(head);
  stringstream ln1;
  ln1 << "\t";
  stringstream ln2;
  ln2 << "\t";
  while (i.next != nullNodePtr) {
    ln1 << "[" << head << "]->";
    ln2 << " " << i.data << "   ";
    i = get(++head);
  }
  cout << ln1.str() << "[" << head << "]" << endl;
  cout << ln2.str() << " " << i.data << " " << endl;
}
