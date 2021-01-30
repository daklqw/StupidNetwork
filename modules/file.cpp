#include "file.h"
#include <fstream>
#include <map>

void readGraphStructureFromFile(Graph & graph, const std::string file)
{
    std::ifstream inf(file.c_str(), std::ios::binary);
    if (!inf.is_open())
    {
        throw "Cannot open file";
    }

    size_t n_vertices, n_sources, n_destinations, n_edges;
    inf.read((char*) &n_vertices, sizeof(n_vertices));
    std::vector<Node*> vertices;
    vertices.resize(n_vertices);
    for (size_t i = 0; i < n_vertices; ++i)
    {
        vertices[i] = new Node();
    }
    graph.setVertices(vertices);

    std::vector<size_t> src_indices;
    inf.read((char*) &n_sources, sizeof(n_sources));
    src_indices.resize(n_sources);
    inf.read((char*) src_indices.data(), sizeof(size_t) * n_sources);
    std::vector<Node*> sources;
    sources.reserve(n_sources);
    for (size_t i = 0; i != n_sources; ++i)
    {
        sources.push_back(vertices[src_indices[i]]);
    }
    graph.setSources(sources);

    std::vector<size_t> dst_indices;
    inf.read((char*) &n_destinations, sizeof(n_destinations));
    dst_indices.resize(n_destinations);
    inf.read((char*) dst_indices.data(), sizeof(size_t) * n_destinations);
    std::vector<Node*> destinations;
    destinations.reserve(n_destinations);
    for (size_t i = 0; i != n_destinations; ++i)
    {
        destinations.push_back(vertices[dst_indices[i]]);
    }
    graph.setSources(destinations);

    inf.read((char*) &n_edges, sizeof(n_edges));
    for (size_t i = 0; i != n_edges; ++i)
    {
        size_t u, v;
        inf.read((char*) &u, sizeof(u));
        inf.read((char*) &v, sizeof(v));
        Edge * edge = new Edge(vertices[u], vertices[v]);
        graph.addEdge(edge);
    }

    if (!inf.good())
    {
        throw "Unavailable file format";
    }
    inf.close();
}

void readWeightTableFromFile(Graph & graph, const std::string file)
{
    std::ifstream inf(file.c_str(), std::ios::binary);
    if (!inf.is_open())
    {
        throw "Cannot open file";
    }

    std::vector<Edge *> edges = graph.getEdges();
    const size_t n_edges = edges.size();
    for (size_t i = 0; i < n_edges; ++i) {
        sn_real_t v;
        inf.read((char*) &v, sizeof(v));
        edges[i]->setScale(v);
    }

    std::vector<Node *> nodes = graph.getVertices();
    const size_t n_nodes = nodes.size();
    for (size_t i = 0; i < n_nodes; ++i) {
        sn_real_t v;
        inf.read((char*) &v, sizeof(v));
        nodes[i]->setOffset(v);
    }

    if (!inf.good())
    {
        throw "Unavailable file format";
    }
    inf.close();
}


void saveGraphStructureToFile(const Graph & graph, const std::string file)
{
    std::ofstream ouf(file.c_str(), std::ios::binary);
    if (!ouf.is_open())
    {
        throw "Cannot open file";
    }

    size_t n_vertices, n_sources, n_destinations, n_edges;
    std::vector<Node*> vertices = graph.getVertices();
    std::map<Node*, size_t> idMapper;
    n_vertices = vertices.size();
    ouf.write((char*) &n_vertices, sizeof(n_vertices));
    for (size_t i = 0; i < n_vertices; ++i)
    {
        idMapper[vertices[i]] = i;
    }

    std::vector<Node*> sources = graph.getSources();
    n_sources = sources.size();
    ouf.write((char*) &n_sources, sizeof(n_sources));
    std::vector<size_t> src_indices;
    src_indices.resize(n_sources);
    for (size_t i = 0; i < n_sources; ++i) {
        src_indices[i] = idMapper[sources[i]];
    }
    ouf.write((char*) src_indices.data(), sizeof(size_t) * n_sources);

    std::vector<Node*> destinations = graph.getDestinations();
    n_destinations = destinations.size();
    ouf.write((char*) &n_destinations, sizeof(n_destinations));
    std::vector<int> dst_indices;
    dst_indices.reserve(n_destinations);
    for (size_t i = 0; i != n_destinations; ++i)
    {
        dst_indices[i] = idMapper[destinations[i]];
    }
    ouf.write((char*) dst_indices.data(), sizeof(size_t) * n_destinations);

    std::vector<Edge *> edges = graph.getEdges();
    n_edges = edges.size();
    ouf.write((char*) &n_edges, sizeof(n_edges));
    for (size_t i = 0; i != n_edges; ++i)
    {
        Edge * e = edges[i];
        size_t u = idMapper[e->getHead()];
        size_t v = idMapper[e->getTail()];
        ouf.write((char*) &u, sizeof(u));
        ouf.write((char*) &v, sizeof(v));
    }

    ouf.close();
}

void saveWeightTableToFile(const Graph & graph, const std::string file)
{
    std::ofstream ouf(file.c_str(), std::ios::binary);
    if (!ouf.is_open())
    {
        throw "Cannot open file";
    }

    std::vector<Edge *> edges = graph.getEdges();
    const size_t n_edges = edges.size();
    for (size_t i = 0; i < n_edges; ++i) {
        sn_real_t v = edges[i]->getScale();
        ouf.write((char*) &v, sizeof(v));
    }

    std::vector<Node *> nodes = graph.getVertices();
    const size_t n_nodes = nodes.size();
    for (size_t i = 0; i < n_nodes; ++i) {
        sn_real_t v = nodes[i]->getOffset();
        ouf.write((char*) &v, sizeof(v));
    }

    ouf.close();
}
