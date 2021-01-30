#ifndef NODE_H
#define NODE_H
#include "../base.h"
#include <vector>

class Edge;
class Node
{
private:
    sn_real_t totalW, activatedW, offset, derivative;
    std::vector<Edge *> inEdges, outEdges;
    size_t degree;
public:
    static const int INDEGREE = 0;
    static const int OUTDEGREE = 1;

    Node();
    sn_real_t getW() const;
    void setW(const sn_real_t &value);
    void addW(const sn_real_t &value);
    void addInEdge(Edge *);
    void addOutEdge(Edge *);
    void activate();
    sn_real_t getActivatedW() const;
    const std::vector<Edge *> & getOutEdges() const;
    size_t getDegree() const;
    void decreaseDegree();
    void reset();
    void resetDegree(int);
    void resetDerivative();
    sn_real_t getOffset() const;
    void setOffset(const sn_real_t & value);
    void addOffset(const sn_real_t & value);
    sn_real_t getDerivative() const;
    void setDerivative(const sn_real_t & value);
    void addDerivative(const sn_real_t & value);
    std::vector<Edge *> getInEdges() const;
};

#endif // NODE_H
