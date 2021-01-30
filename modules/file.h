#ifndef FILE_H
#define FILE_H

#include "../base.h"
#include "../models/graph.h"
#include <string>

void readGraphStructureFromFile(Graph &, const std::string);

void readWeightTableFromFile(Graph &, const std::string);

void saveGraphStructureToFile(const Graph &, const std::string);

void saveWeightTableToFile(const Graph &, const std::string);

#endif // FILE_H
