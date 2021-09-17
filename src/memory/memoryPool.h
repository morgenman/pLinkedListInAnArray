#include "abstractPool.h"

class MemoryPool: public AbstractPool{
public:
    NodePtr newNode();

    void deleteNode(NodePtr curr);

    char data(NodePtr curr);

    char data(NodePtr curr, char ch);

    NodePtr next(NodePtr curr);

    NodePtr next(NodePtr curr, NodePtr next);

    bool trace(bool traceOn);

    void showFreeList();

    void nodes(NodePtr head);

};
