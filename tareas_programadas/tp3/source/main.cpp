// Copyright 2024 Jose Manuel Mora Z
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Graph.hpp"

void readCSV(const std::string& csvFilePath, Graph& graph) {
  std::ifstream file(csvFilePath);

  if (!file.is_open()) {
    throw std::runtime_error("couldn't open file: " + csvFilePath);
  }

  std::string line("");
  // Skip the header line
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string sourceIdStr, sourceName, targetIdStr, targetName, weightStr;

    std::getline(ss, sourceIdStr, ',');
    std::getline(ss, sourceName, ',');
    std::getline(ss, targetIdStr, ',');
    std::getline(ss, targetName, ',');
    std::getline(ss, weightStr, ',');

    int sourceId = std::stoi(sourceIdStr);
    int targetId = std::stoi(targetIdStr);
    int weight = std::stoi(weightStr);

    // Add vertices if they don't exist
    if (graph.getVertices().find(sourceId) == graph.getVertices().end()) {
      graph.addVertex(sourceId, sourceName);
    }
    if (graph.getVertices().find(targetId) == graph.getVertices().end()) {
      graph.addVertex(targetId, targetName);
    }

    // Add edge
    graph.addEdge(sourceId, targetId, weight);
  }

  file.close();
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_csv>" << std::endl;
    return EXIT_FAILURE;
  }

  Graph graph;
  std::string csvFilePath = argv[1];

  try {
    readCSV(csvFilePath, graph);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  // Output the graph (for debugging purposes)
  for (const auto& pair : graph.getVertices()) {
    const Vertex& vertex = pair.second;
    std::cout << "Vertex " << vertex.id << " (" << vertex.name << "):" << std::endl;
    for (const Edge& edge : vertex.edges) {
      std::cout << "  -> " << edge.dest->id << " (" << edge.dest->name << "), weight: " << edge.weight << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
