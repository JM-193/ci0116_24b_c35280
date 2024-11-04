// Copyright 2024 Jose Manuel Mora Z

#include <array>
#include <chrono>
#include <iostream>
#include <fstream>
#include <random>

#include "BinarySearchTree.hpp"
#include "ChainedHashTable.hpp"
#include "RedBlackTree.hpp"
#include "SinglyLinkedList.hpp"

constexpr std::size_t runs = 3;
constexpr std::size_t arr_len = 1000000;
constexpr std::size_t min = 0;
constexpr std::size_t max = 3 * arr_len;
constexpr std::size_t search_len = 10000;
constexpr std::size_t remove_len = 10000;

#define startTimer() auto startTime = std::chrono::high_resolution_clock::now();
#define endTimer() auto endTime = std::chrono::high_resolution_clock::now();

template<std::size_t len>
void generateRandomArray(std::array<int, len>& arr) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  for (std::size_t index = 0; index < arr_len; ++index) {
    arr[index] = distribution(generator);
  }
}

void testInsert(SLList<int>& sll, bool random,
    std::array<int, arr_len>& insertArr, std::ostream*& resultStream) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      sll.insert(value);
  } else {
    for (std::size_t value = 0; value < arr_len; ++value)
      sll.insert(value);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  *resultStream << "\t\tInsertion: \t" << duration.count() << " ms" << std::endl;
}

void testInsert(BSTree<int>& bst, bool random,
    std::array<int, arr_len>& insertArr, std::ostream*& resultStream) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      bst.insert(value);
  } else {
    bst.fastInsert(arr_len);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  *resultStream << "\t\tInsertion: \t" << duration.count() << " ms" << std::endl;
}

template<typename DataStructure>
void testSearch(DataStructure& ds, std::array<int, search_len>& searchArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : searchArr) {
    ds.search(value);
  }
  endTimer()
  std::chrono::duration<double, std::nano> duration = endTime - startTime;
  *resultStream << "\t\tSearch: \t" << duration.count() << " ns" << std::endl;
}

template<typename DataStructure>
void testRemove(DataStructure& ds, std::array<int, remove_len>& removeArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : removeArr) {
    ds.remove(value);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  double finalDuration = duration.count() > 1000 ?
      duration.count() / 1000 : duration.count();
  std::string unit = duration.count() > 1000 ? " s" : " ms";
  *resultStream << "\t\tRemoval: \t" << finalDuration << unit << std::endl;
}

template<typename DataStructure>
void testStructure(DataStructure& ds, bool random, std::ostream*& resultStream,
    std::array<int, arr_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Insertion
  testInsert(ds, random, insertArr, resultStream);

  // Search
  testSearch(ds, searchArr, resultStream);

  // Removal
  testRemove(ds, removeArr, resultStream);

  // Clear the list
  ds.clear();
}

void getResultStream(bool writeToFile, std::ostream*& resultStream) {
  if (writeToFile) {
    // Open the file to write the results
    std::ofstream resultsFile;
    resultsFile.open("results.txt", std::ios::out);
    if (!resultsFile.is_open()) {
      std::cerr << "Error: Could not open the file to write the results, "
                << "using standard output" << std::endl;
      resultStream = &std::cout;
      return;
    }
    // Assign the file stream to the result stream
    resultStream = &resultsFile;
  } else {
    // Assign the standard output to the result stream
    resultStream = &std::cout;
  }
}

int main() {
  // Want to write to results file or the standard output?
  const bool writeToFile = false;
  std::ostream* resultStream;
  getResultStream(writeToFile, resultStream);

  SLList<int> sll;
  BSTree<int> bst;
  RBTree<int> rbt;
  ChainedHashTable<int> cht(arr_len);

  std::array<int, arr_len> insertArr;
  generateRandomArray(insertArr);
  std::array<int, search_len> searchArr;
  generateRandomArray(searchArr);
  std::array<int, remove_len> removeArr;
  generateRandomArray(removeArr);

  *resultStream << "\nSingly Linked List: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(sll, /* random */ true, resultStream,
        insertArr, searchArr, removeArr);
  }

  *resultStream << "\nSingly Linked List: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(sll, /* random */ false, resultStream,
        insertArr, searchArr, removeArr);
  }

  *resultStream << "\nBinary Search Tree: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(bst, /* random */ true, resultStream,
        insertArr, searchArr, removeArr);
  }

  *resultStream << "\nBinary Search Tree: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(bst, /* random */ false, resultStream,
        insertArr, searchArr, removeArr);
  }

  *resultStream << "\nRed-Black Tree: Random" << std::endl;


  *resultStream << "\nRed-Black Tree: Sorted" << std::endl;


  *resultStream << "\nChained Hash Table: Random" << std::endl;


  *resultStream << "\nChained Hash Table: Sorted" << std::endl;


  return EXIT_SUCCESS;
}
