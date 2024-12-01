// Copyright 2024 Jose Manuel Mora Z
#include <string>
#include <unordered_map>
#include <vector>

struct Vertex;

struct Edge {
  Vertex* src = nullptr;
  Vertex* dest = nullptr;
  int weight = 0;
};

struct Vertex {
  int id = 0;
  std::string name = "";
  std::vector<Edge> edges;
};

class Graph {
 private:
  std::unordered_map<int, Vertex> vertices;
 public:
  Graph() = default;
  ~Graph() = default;

  void addVertex(int id, const std::string& name) {
    vertices[id] = Vertex{id, name, {}};
  }

  void addEdge(int srcId, int destId, int weight) {
    Vertex* src = &vertices[srcId];
    Vertex* dest = &vertices[destId];
    src->edges.push_back(Edge{src, dest, weight});
  }

  const std::unordered_map<int, Vertex>& getVertices() const {
    return vertices;
  }
};