#ifndef GRAPH_H
#define GRAPH_H

#include "../base.h"
#include "node.h"
#include "edge.h"

class Graph
{
private:
    std::vector<Node *> vertices;
    std::vector<Edge *> edges;

    std::vector<Node *> sources, destinations;

    void initializeTopoSort();
    void topologySort();
    void initializeSpreadBack();
    void spreadBack();
public:
    Graph();
    std::vector<sn_real_t> operator () (std::vector<sn_real_t>);
    sn_real_t train(std::vector<sn_real_t>,
                    std::vector<sn_real_t>,
                    sn_real_t alpha = 0.3);

    std::vector<Edge *> getEdges() const;
    std::vector<Node *> getVertices() const;
    std::vector<Node *> getSources() const;
    std::vector<Node *> getDestinations() const;
    void addEdge(Edge *);
    void addVertex(Node *);
    void addSource(Node *);
    void addDestination(Node *);
    void setSources(const std::vector<Node *> & value);
    void setDestinations(const std::vector<Node *> & value);
    void setVertices(const std::vector<Node *> & value);
};

#endif // GRAPH_H
