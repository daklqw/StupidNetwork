#include "node.h"
#include "edge.h"
#include "../utility/mathematics.h"


sn_real_t Node::getW() const
{
    return totalW;
}

void Node::setW(const sn_real_t &value)
{
    totalW = value;
}

void Node::addW(const sn_real_t & value)
{
    totalW += value;
}

void Node::addInEdge(Edge * edge)
{
    inEdges.push_back(edge);
}

void Node::addOutEdge(Edge * edge)
{
    outEdges.push_back(edge);
}

void Node::activate()
{
    activatedW = activationFunc(totalW);
}

sn_real_t Node::getActivatedW() const
{
    return activatedW;
}

const std::vector<Edge *> & Node::getOutEdges() const
{
    return outEdges;
}

size_t Node::getDegree() const
{
    return degree;
}

void Node::decreaseDegree()
{
    --degree;
}

void Node::reset()
{
    totalW = offset;
    activatedW = 0;
    resetDerivative();
}

void Node::resetDegree(int mode = Node::INDEGREE)
{
    degree = mode == Node::INDEGREE ? inEdges.size() : outEdges.size();
}

void Node::resetDerivative()
{
    derivative = 0;
}

sn_real_t Node::getOffset() const
{
    return offset;
}

void Node::setOffset(const sn_real_t & value)
{
    offset = value;
}

void Node::addOffset(const sn_real_t & value)
{
    offset += value;
}

sn_real_t Node::getDerivative() const
{
    return derivative;
}

void Node::setDerivative(const sn_real_t & value)
{
    derivative = value;
}

void Node::addDerivative(const sn_real_t & value)
{
    derivative += value;
}

std::vector<Edge *> Node::getInEdges() const
{
    return inEdges;
}

Node::Node()
{
    offset = 0;
    reset();
}
