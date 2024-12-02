// Copyright 2024 Jose Manuel Mora Z
#include <algorithm>
#include <limits>
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
    dest->edges.push_back(Edge{dest, src, weight});
  }

  const std::unordered_map<int, Vertex>& getVertices() const {
    return vertices;
  }

  std::vector<std::vector<int>> floydWarshall() const {
    const int INF = std::numeric_limits<int>::max();
    int n = vertices.size();
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));

    // Initialize distances with edge weights
    for (const auto& pair : vertices) {
      int u = pair.first;
      dist[u][u] = 0;
      for (const Edge& edge : pair.second.edges) {
        int v = edge.dest->id;
        dist[u][v] = edge.weight;
      }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (dist[i][k] != INF && dist[k][j] != INF) {
            dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }

    return dist;
  }
};
