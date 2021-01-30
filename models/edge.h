#ifndef EDGE_H
#define EDGE_H
#include "../base.h"
#include "node.h"

class Edge
{
private:
    Node * head, * tail;
    sn_real_t scale, derivative;
public:
    Edge();
    Edge(Node *, Node *);
    Edge(Node *, Node *, sn_real_t);

    void reset();

    sn_real_t getScale() const;
    void setScale(const sn_real_t &value);
    void addScale(const sn_real_t &value);
    Node *getHead() const;
    void setHead(Node *value);
    Node *getTail() const;
    void setTail(Node *value);
    sn_real_t getDerivative() const;
    void setDerivative(const sn_real_t & value);
    void addDerivative(const sn_real_t & value);
};

#endif // EDGE_H
