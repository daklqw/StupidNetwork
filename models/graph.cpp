#include "graph.h"
#include "../utility/mathematics.h"
#include <queue>

std::vector<Edge *> Graph::getEdges() const
{
    return edges;
}

std::vector<Node *> Graph::getVertices() const
{
    return vertices;
}

std::vector<Node *> Graph::getSources() const
{
    return sources;
}

std::vector<Node *> Graph::getDestinations() const
{
    return destinations;
}

void Graph::addEdge(Edge * e)
{
    edges.push_back(e);
    e->getTail()->addInEdge(e);
    e->getHead()->addOutEdge(e);
}

void Graph::addVertex(Node * v)
{
    vertices.push_back(v);
}

void Graph::addSource(Node * v)
{
    sources.push_back(v);
}

void Graph::addDestination(Node * v)
{
    destinations.push_back(v);
}

void Graph::setSources(const std::vector<Node *> & value)
{
    sources = value;
}

void Graph::setDestinations(const std::vector<Node *> & value)
{
    destinations = value;
}

void Graph::setVertices(const std::vector<Node *> & value)
{
    vertices = value;
}

void Graph::initializeTopoSort()
{
    const size_t len = vertices.size();
    for (size_t i = 0; i < len; ++i)
    {
        vertices[i]->reset();
        vertices[i]->resetDegree(Node::INDEGREE);
    }
}

void Graph::topologySort()
{
    std::queue<Node *> que;
    const size_t s_len = sources.size();
    for (size_t i = 0; i < s_len; ++i)
    {
        que.push(sources[i]);
    }

    while (!que.empty())
    {
        Node * u = que.front();
        que.pop();

        u->activate();

        for (auto e : u->getOutEdges())
        {
            Node * v = e->getTail();
            v->addW(u->getActivatedW() * e->getScale());
            v->decreaseDegree();
            if (v->getDegree() == 0)
            {
                que.push(v);
            }
        }
    }
}

void Graph::initializeSpreadBack()
{
    for (Node * v : vertices) {
        // v->resetDerivative();
        v->resetDegree(Node::OUTDEGREE);
    }

    for (Edge * e : edges)
    {
        e->reset();
    }
}

void Graph::spreadBack()
{
    std::queue<Node *> que;
    const size_t d_len = destinations.size();
    for (size_t i = 0; i < d_len; ++i)
    {
        que.push(destinations[i]);
    }

    while (!que.empty())
    {
        Node * u = que.front();
        que.pop();

        sn_real_t der = u->getDerivative();
        der *= d_ActivationFunc(u->getW());
        u->setDerivative(der);
        for (Edge * e : u->getInEdges())
        {
            e->addDerivative(der);
            Node * v = e->getHead();
            v->addDerivative(e->getScale() * der);
            v->decreaseDegree();
            if (v->getDegree() == 0)
            {
                que.push(v);
            }
        }
    }
}

Graph::Graph()
{

}

std::vector<sn_real_t> Graph::operator ()(std::vector<sn_real_t> params)
{
    const size_t s_len = sources.size();
    assert(s_len == params.size());

    initializeTopoSort();

    for (size_t i = 0; i != s_len; ++i)
    {
        // Initalize input
        sources[i]->setW(params[i]);
    }

    topologySort();

    std::vector<sn_real_t> result;
    const size_t d_len = destinations.size();
    result.reserve(d_len);
    for (size_t i = 0; i != d_len; ++i)
    {
        // Get outputs
        result.push_back(destinations[i]->getActivatedW());
    }
    return result;
}

/*!
 * \brief Graph::train
 * \param params
 * \param expected
 * \return error value
 */
sn_real_t Graph::train(std::vector<sn_real_t> params,
                       std::vector<sn_real_t> expected,
                       sn_real_t alpha)
{
    std::vector<Node *> sources = getSources();
    const size_t s_len = sources.size();
    std::vector<Node *> destinations = getDestinations();
    const size_t d_len = destinations.size();
    assert(s_len == params.size());

    std::vector<sn_real_t> result = this->operator()(params);
    sn_real_t error = errorFunction(result, expected);

    initializeSpreadBack();

    // sn_real_t d_error = d_errorFunction(result, expected);
    for (size_t i = 0; i < d_len; ++i) {
        sn_real_t d = 2 * (result[i] - expected[i]);
        destinations[i]->addDerivative(d);
    }

    spreadBack();

    const size_t n_nodes = vertices.size();
    const size_t n_edges = edges.size();

    for (size_t i = 0; i < n_nodes; ++i) {
        sn_real_t d = vertices[i]->getDerivative();
        d *= alpha;
        vertices[i]->addOffset(-d);
    }

    for (size_t i = 0; i < n_edges; ++i) {
        sn_real_t d = edges[i]->getDerivative();
        Node * u = edges[i]->getHead();
        d *= u->getActivatedW();
        d *= alpha;
        edges[i]->addScale(-d);
    }

    return error;
}
