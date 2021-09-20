/**
 *  See memoryPool.h for block comment
 */

#include "memoryPool.h"

MemoryPool::NodePtr MemoryPool::newNode() { return 5; }

void MemoryPool::deleteNode(NodePtr curr) {}

char MemoryPool::data(NodePtr curr) { return 'a'; }

char MemoryPool::data(NodePtr curr, char ch) { return 'a'; }

MemoryPool::NodePtr MemoryPool::next(NodePtr curr) { return 5; }

MemoryPool::NodePtr MemoryPool::next(NodePtr curr, NodePtr next) { return 5; }

bool MemoryPool::trace(bool traceOn) { return false; }

void MemoryPool::showFreeList() {}

void MemoryPool::nodes(NodePtr head) {}
