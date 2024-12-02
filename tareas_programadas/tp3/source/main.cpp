// Copyright 2024 Jose Manuel Mora Z
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

#include "main.h"

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

  // Floyd-Warshall algorithm
  std::vector<std::vector<int>> dist = graph.floydWarshall();

  // Menu
  menu(graph, dist);

  return EXIT_SUCCESS;
}

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

void menu(const Graph& graph, const std::vector<std::vector<int>>& dist) {
  while (true) {
    std::cout << showMenu();
    int choice;
    std::cin >> choice;

    switch (choice) {
      case 1: {
        std::vector<int> cities = findCentralCities(dist);
        std::cout << "City with the shortest paths to all other cities: ";
        for (int city : cities) {
          std::cout << graph.getVertices().at(city).name << " ";
        }
        std::cout << std::endl;
        break;
      }
      case 2: {
        printCities(graph);
        int x;
        std::cout << "Enter city x: ";
        std::cin >> x;
        std::vector<int> cities = pathToX(dist, x);
        std::cout << "City with the shortest path to city "
                  << graph.getVertices().at(x).name << ": ";
        for (int city : cities) {
          std::cout << graph.getVertices().at(city).name << " ";
        }
        std::cout << std::endl;
        break;
      }
      case 3: {
        std::vector<std::pair<int, int>> cities = findFurthestCities(dist);
        std::cout << "The furthest cities from one another are: ";
        for (const auto& pair : cities) {
          std::cout << "(" << graph.getVertices().at(pair.first).name << ", "
                    << graph.getVertices().at(pair.second).name << ") ";
        }
        std::cout << std::endl;
        break;
      }
      case 4: {
        std::vector<std::pair<int, int>> cities = findClosestCities(dist);
        std::cout << "The closest cities from one another are: ";
        for (const auto& pair : cities) {
          std::cout << "(" << graph.getVertices().at(pair.first).name << ", "
                    << graph.getVertices().at(pair.second).name << ") ";
        }
        std::cout << std::endl;
        break;
      }
      case 5: {
        std::vector<std::pair<int, double>> cities = citiesByAvgDist(dist);
        std::cout << "List cities by their average distance to all cities: "
                  << std::endl;
        for (const auto& pair : cities) {
          std::cout << graph.getVertices().at(pair.first).name << " ("
                    << pair.second << ") " << std::endl;
        }
        std::cout << std::endl;
        break;
      }
      case 6:
        return;
      default:
        std::cerr << "Invalid choice. Please try again." << std::endl;
    }
  }
}

std::string showMenu() {
  std::stringstream ss;
  ss << "Menu:" << std::endl
  << "1. Find the city with the shortest paths to all other cities"
  << std::endl
  << "2. Given a city x, find the city y which has the shortest path to x"
  << std::endl
  << "3. Find the two furthest cities from one another" << std::endl
  << "4. Find the two closest cities from one another" << std::endl
  << "5. List all cities in order of their average distance to all cities"
  << std::endl
  << "6. Exit" << std::endl
  << "Enter your choice: ";

  return ss.str();
}

// Function to find the city with the shortest paths to all other cities
std::vector<int> findCentralCities(const std::vector<std::vector<int>>& dist) {
  int n = dist.size();
  std::vector<int> result;
  int minSum = std::numeric_limits<int>::max();

  // Go through the matrix
  for (int i = 0; i < n; ++i) {
    int sum = 0;
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] != std::numeric_limits<int>::max()) {
        sum += dist[i][j];
      }
    }
    if (sum < minSum) {
      // If the sum is less
      minSum = sum;
      result.clear();
      result.push_back(i);
    } else if (sum == minSum) {
      // If the sum is the same
      result.push_back(i);
    }
  }

  return result;
}

// Function to find the city y which has the shortest path to city x
std::vector<int> pathToX(const std::vector<std::vector<int>>& dist, int x) {
  int n = dist.size();
  std::vector<int> result;
  int minDist = std::numeric_limits<int>::max();

  for (int i = 0; i < n; ++i) {
    if (i != x && dist[i][x] < minDist) {
      minDist = dist[i][x];
      result.clear();
      result.push_back(i);
    } else if (i != x && dist[i][x] == minDist) {
      result.push_back(i);
    }
  }

  // If no valid path is found, return an empty result
  if (minDist == std::numeric_limits<int>::max()) {
    result.clear();
  }

  return result;
}

// Function to find the two furthest cities from one another
std::vector<std::pair<int, int>> findFurthestCities(
      const std::vector<std::vector<int>>& dist) {
  int n = dist.size();
  int maxDist = 0;
  std::vector<std::pair<int, int>> result;

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (dist[i][j] > maxDist &&
          dist[i][j] != std::numeric_limits<int>::max()) {
        maxDist = dist[i][j];
        result.clear();
        result.push_back({i, j});
      } else if (dist[i][j] == maxDist) {
        result.push_back({i, j});
      }
    }
  }

  return result;
}

// Function to find the two closest cities from one another
std::vector<std::pair<int, int>> findClosestCities(
      const std::vector<std::vector<int>>& dist) {
  int n = dist.size();
  int minDist = std::numeric_limits<int>::max();
  std::vector<std::pair<int, int>> result;

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (dist[i][j] < minDist && i != j) {
        minDist = dist[i][j];
        result.clear();
        result.push_back({i, j});
      } else if (dist[i][j] == minDist && i != j) {
        result.push_back({i, j});
      }
    }
  }

  return result;
}

// Function to list all cities in order of their average distance to all cities
std::vector<std::pair<int, double>> citiesByAvgDist(
      const std::vector<std::vector<int>>& dist) {
  int n = dist.size();
  std::vector<std::pair<int, double>> avgDistances;

  for (int i = 0; i < n; ++i) {
    double sum = 0;
    int count = 0;
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] != std::numeric_limits<int>::max()) {
        sum += dist[i][j];
        count++;
      }
    }
    double avg = sum / count;
    avgDistances.push_back({i, avg});
  }

  std::sort(avgDistances.begin(), avgDistances.end(),
      [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
    return a.second < b.second;
  });

  return avgDistances;
}

void printCities(const Graph& graph) {
  const auto& vertices = graph.getVertices();
  std::cout << "Cities:" << std::endl;
  for (const auto& pair : vertices) {
    std::cout << pair.first << ": " << pair.second.name << std::endl;
  }
}
