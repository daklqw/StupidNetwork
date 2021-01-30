#include "base.h"
#include "models/graph.h"
#include <random>
#include <iostream>
#include <iomanip>

void testBinaryNumbers()
{
    std::cerr << std::fixed << std::setprecision(3);
    const sn_real_t eps = 1e-7;
    Graph gr;
    sn_real_t error;
    Node * src[4], * dest[16], * center[16];
    for (int i = 0; i < 4; ++i) src[i] = new Node();
    for (int i = 0; i < 16; ++i) dest[i] = new Node();
    for (int i = 0; i < 16; ++i) center[i] = new Node();

    for (int i = 0; i < 4; ++i) gr.addVertex(src[i]);
    for (int i = 0; i < 16; ++i) gr.addVertex(center[i]);
    for (int i = 0; i < 16; ++i) gr.addVertex(dest[i]);

    for (int i = 0; i < 4; ++i) gr.addSource(src[i]);
    for (int i = 0; i < 16; ++i) gr.addDestination(dest[i]);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 16; ++j)
            gr.addEdge(new Edge(src[i], center[j], 0.5));

    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j)
            gr.addEdge(new Edge(center[i], dest[j], 0.5));

    std::mt19937 rd(12243);
    int steps = 0;
    do
    {
        std::vector<sn_real_t> in(4, 0), out(16, 0);
        int nu = rd() % 16;
        for (int j = 0; j < 4; ++j)
            if (nu >> j & 1)
                in[j] = 1;
        out[nu] = 1;
        error = gr.train(in, out, 1.1);
        ++steps;
        std::cerr << steps << " error : " << error << std::endl;
    } while (error > eps && steps < 1000);

    const int ALL_TESTS = 8;
    for (int TEST = 0; TEST < ALL_TESTS; ++TEST) {
        std::vector<sn_real_t> in(4, 0);
        int nu = rd() % 16;
        for (int j = 0; j < 4; ++j)
            if (nu >> j & 1)
                in[j] = 1;
        std::vector<sn_real_t> res = gr(in);
        std::cerr << "TEST " << TEST << " answer " << nu << " result :";
        for (int i = 0; i < 16; ++i)
            std::cerr << " " << res[i];
        std::cerr << std::endl;
    }

    for (auto e : gr.getEdges()) delete e;
    for (auto v : gr.getVertices()) delete v;
}

int main()
{
    testBinaryNumbers();
    return 0;
}
