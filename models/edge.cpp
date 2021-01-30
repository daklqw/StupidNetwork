#include "edge.h"

sn_real_t Edge::getScale() const
{
    return scale;
}

void Edge::setScale(const sn_real_t &value)
{
    scale = value;
}

void Edge::addScale(const sn_real_t & value)
{
    scale += value;
}

Node *Edge::getHead() const
{
    return head;
}

void Edge::setHead(Node *value)
{
    head = value;
}

Node *Edge::getTail() const
{
    return tail;
}

void Edge::setTail(Node *value)
{
    tail = value;
}

sn_real_t Edge::getDerivative() const
{
    return derivative;
}

void Edge::setDerivative(const sn_real_t & value)
{
    derivative = value;
}

void Edge::addDerivative(const sn_real_t & value)
{
    derivative += value;
}

Edge::Edge()
{
    head = tail = nullptr;
    scale = 0;
    reset();
}

Edge::Edge(Node * _head, Node * _tail)
{
    head = _head;
    tail = _tail;
    scale = 0;
    reset();
}

Edge::Edge(Node * _head, Node * _tail, sn_real_t _scale)
{
    head = _head;
    tail = _tail;
    scale = _scale;
    reset();
}

void Edge::reset()
{
    derivative = 0;
}
