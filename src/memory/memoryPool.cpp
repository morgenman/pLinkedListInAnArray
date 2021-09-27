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
  arrSize = sizeof(array) / sizeof(array[0]);
  for (int i = arrSize - 1; i >= 0; i--) {
    freeList.push(i);
    set(i, 0, nullNodePtr);
  }
}

void MemoryPool::set(NodePtr index, char ch, NodePtr next) {
  if (index == nullNodePtr || index >= arrSize) {
    throw out_of_range("Index out of Range");
  }
  array[index].data = ch;
  array[index].next = next;
}

MemoryPool::node MemoryPool::get(NodePtr index) {
  if (index == nullNodePtr || index >= arrSize) {
    throw out_of_range("Index out of Range");
  }
  return array[index];
}

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
    for (int i = 0; i < arrSize; i++) {
      cout << i << "\t"
           << "|\t*" << array[i].data << "*\t"
           << "|\t*" << array[i].next << "*" << endl;
      cout.flush();
    }
  }
}

MemoryPool::NodePtr MemoryPool::newNode() {
  if (!freeList.empty()) {
    // Store value at top
    int index = freeList.top();
    // Pop it off (this could be all one function if c++ simply returned when
    // popping)
    freeList.pop();

    if (traceOn)
      print(("Giving new node upon request. Node " + to_string(index) +
             " will be returned")
                .c_str());

    // return said value
    return index;
  } else {
    if (traceOn) print("No free nodes to give.");
    return nullNodePtr;
  }
}

void MemoryPool::deleteNode(NodePtr curr) {
  if (traceOn) print(("Deleting node " + to_string(curr)).c_str());

  // Add the node to the freelist
  freeList.push(curr);
}

char MemoryPool::data(NodePtr curr) {
  if (traceOn)
    print(("Returning node " + to_string(curr) + ", which is set to " +
           get(curr).data)
              .c_str());

  // Return the data stored by node
  return get(curr).data;
}

char MemoryPool::data(NodePtr curr, char ch) {
  if (traceOn) print(("Setting node " + to_string(curr) + " to " + ch).c_str());

  // Set the character stored
  set(curr, ch, get(curr).next);
  // Return the character stored
  return get(curr).data;
}

MemoryPool::NodePtr MemoryPool::next(NodePtr curr) {
  if (traceOn)
    print(("Returning the node that node  " + to_string(curr) +
           " points to, which is " + to_string(array[curr].next))
              .c_str());

  // Return next node index
  return array[curr].next;
}

MemoryPool::NodePtr MemoryPool::next(NodePtr curr, NodePtr next) {
  if (traceOn)
    print(("Setting node " + to_string(curr) + " to point towards node " +
           to_string(next))
              .c_str());

  // Set the node's next pointer
  set(curr, get(curr).data, next);
  // Return the node's next pointer
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
  // Added this for personal sanity reasons
  if (traceOn) print("\n", true);

  cout << "Free node stack:" << endl;

  // temp stack
  stack<int> temp;

  // Load items into temp stack
  while (freeList.empty() == false) {
    temp.push(freeList.top());
    freeList.pop();
  }

  // Move them back, printing as you go
  while (temp.empty() == false) {
    cout << temp.top() << " ";
    freeList.push(temp.top());
    temp.pop();
  }
}

int MemoryPool::free() { return freeList.size(); }

void MemoryPool::nodes(NodePtr head) {
  if (traceOn)
    print(("Traversing through nodes from index " + to_string(head) +
           " until pointing at a nullNodePtr")
              .c_str());

  // stringstreamed into 2 lines so we can have pretty aligned -> diagrams
  stringstream ln1;
  ln1 << "\t";
  stringstream ln2;
  ln2 << "\t";

  // Until end of string
  while (next(head) != nullNodePtr) {
    ln1 << "[" << head << "]->";
    ln2 << " " << data(head) << "   ";
    head = next(head);
  }
  // Need to repeat the command out of the loop in case the string is only one
  // char
  cout << ln1.str() << "[" << head << "]" << endl;
  cout << ln2.str() << " " << data(head) << " " << endl;
}
