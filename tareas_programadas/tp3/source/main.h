// Copyright 2024 Jose Manuel Mora Z
#include <string>
#include <vector>

#include "Graph.hpp"

void readCSV(const std::string& csvFilePath, Graph& graph);
void menu(const Graph& graph, const std::vector<std::vector<int>>& dist);
std::string showMenu();
std::vector<int> findCentralCities(const std::vector<std::vector<int>>& dist);
std::vector<int> pathToX(const std::vector<std::vector<int>>& dist, int x);
std::vector<std::pair<int, int>> findFurthestCities(
      const std::vector<std::vector<int>>& dist);
std::vector<std::pair<int, int>> findClosestCities(
      const std::vector<std::vector<int>>& dist);
std::vector<std::pair<int, double>> citiesByAvgDist(
      const std::vector<std::vector<int>>& dist);
void printCities(const Graph& graph);
