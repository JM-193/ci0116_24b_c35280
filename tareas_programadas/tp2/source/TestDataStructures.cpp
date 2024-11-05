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

/// @brief Number of runs to test the data structures
constexpr std::size_t runs = 3;
/// @brief Number of elements to insert in the data structures
constexpr std::size_t insert_len = 1000000;
/// @brief Number of elements to search in the data structures
constexpr std::size_t search_len = 10000;
/// @brief Number of elements to remove in the data structures
constexpr std::size_t remove_len = 10000;
/// @brief Minimum value for the random numbers
constexpr std::size_t min = 0;
/// @brief Maximum value for the random numbers
constexpr std::size_t max = 3 * insert_len;

/// @brief Start the timer to calculate the duration
#define startTimer() auto startTime = std::chrono::high_resolution_clock::now();
/// @brief End the timer to calculate the duration
#define endTimer() auto endTime = std::chrono::high_resolution_clock::now();

/// @brief Generate a random array of integers
/// @tparam len Length of the array
/// @param arr Array to fill with random integers
template<std::size_t len>
void generateRandomArray(std::array<int, len>& arr) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  for (std::size_t index = 0; index < insert_len; ++index) {
    arr[index] = distribution(generator);
  }
}

/// @brief Test the insertion of values in the Singly Linked List
/// @param sll Singly Linked List to test
/// @param random True if the values should be inserted randomly
/// @param insertArr Array of values to insert
/// @param resultStream Stream to write the results
void testInsert(SLList<int>& sll, bool random,
    std::array<int, insert_len>& insertArr, std::ostream*& resultStream) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      sll.insert(value);
  } else {
    for (std::size_t value = 0; value < insert_len; ++value)
      sll.insert(value);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  *resultStream << "\t\tInsertion: \t" << duration.count()
                << " ms" << std::endl;
}

/// @brief Test the insertion of values in the Binary Search Tree
/// @param bst Binary Search Tree to test
/// @param random True if the values should be inserted randomly
/// @param insertArr Array of values to insert
/// @param resultStream Stream to write the results
void testInsert(BSTree<int>& bst, bool random,
    std::array<int, insert_len>& insertArr, std::ostream*& resultStream) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      bst.insert(value);
  } else {
    bst.fastInsert(insert_len);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  *resultStream << "\t\tInsertion: \t" << duration.count()
                << " ms" << std::endl;
}

/// @brief Test the insertion of values in the Red-Black Tree
/// @param rbt Red-Black Tree to test
/// @param random True if the values should be inserted randomly
/// @param insertArr Array of values to insert
/// @param resultStream Stream to write the results
void testInsert(RBTree<int>& rbt, bool random,
    std::array<int, insert_len>& insertArr, std::ostream*& resultStream) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      rbt.insert(value);
  } else {
    for (std::size_t value = 0; value < insert_len; ++value)
      rbt.insert(value);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  *resultStream << "\t\tInsertion: \t" << duration.count()
                << " ms" << std::endl;
}

/// @brief Test the insertion of values in the Chained Hash Table
/// @param cht Chained Hash Table to test
/// @param random True if the values should be inserted randomly
/// @param insertArr Array of values to insert
/// @param resultStream Stream to write the results
void testInsert(ChainedHashTable<int>& cht, bool random,
    std::array<int, insert_len>& insertArr, std::ostream*& resultStream) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      cht.insert(value);
  } else {
    for (std::size_t value = 0; value < insert_len; ++value)
      cht.insert(value);
  }
  endTimer()
  std::chrono::duration<double, std::milli> duration = endTime - startTime;
  *resultStream << "\t\tInsertion: \t" << duration.count()
                << " ms" << std::endl;
}

/// @brief Test the insertion of values in the data structure
/// @tparam DataStructure Type of the data structure
/// @param ds Data structure to test
/// @param searchArr Array of values to search
/// @param resultStream Stream to write the results
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

/// @brief Test the removal of values in the data structure
/// @tparam DataStructure Type of the data structure
/// @param ds Data structure to test
/// @param removeArr Array of values to remove
/// @param resultStream Stream to write the results
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

/// @brief Test the data structure with the given parameters
/// @tparam DataStructure Type of the data structure
/// @param ds Data structure to test
/// @param random True if the data should be inserted randomly
/// @param resultStream Stream to write the results
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
template<typename DataStructure>
void testStructure(DataStructure& ds, bool random, std::ostream*& resultStream,
    std::array<int, insert_len>& insertArr,
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

/// @brief Get the result stream to write the results
/// @param writeToFile True if the results should be written to a file
/// @param resultStream Stream to write the results
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

/// @brief Main functions
/// @return EXIT_SUCCESS if the program ends successfully
int main() {
  // Want to write to results file or the standard output?
  const bool writeToFile = false;
  std::ostream* resultStream;
  getResultStream(writeToFile, resultStream);

  // Data structures to test
  SLList<int> sll;
  BSTree<int> bst;
  RBTree<int> rbt;
  ChainedHashTable<int> cht(insert_len);

  // Random arrays to test the data structures
  std::array<int, insert_len> insertArr;
  generateRandomArray(insertArr);
  std::array<int, search_len> searchArr;
  generateRandomArray(searchArr);
  std::array<int, remove_len> removeArr;
  generateRandomArray(removeArr);

  // SLL Random
  *resultStream << "\nSingly Linked List: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(sll, /* random */ true, resultStream,
        insertArr, searchArr, removeArr);
  }

  // SLL Sorted
  *resultStream << "\nSingly Linked List: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(sll, /* random */ false, resultStream,
        insertArr, searchArr, removeArr);
  }

  // BST Random
  *resultStream << "\nBinary Search Tree: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(bst, /* random */ true, resultStream,
        insertArr, searchArr, removeArr);
  }

  // BST Sorted
  *resultStream << "\nBinary Search Tree: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(bst, /* random */ false, resultStream,
        insertArr, searchArr, removeArr);
  }

  // RBT Random
  *resultStream << "\nRed-Black Tree: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(rbt, /* random */ true, resultStream,
        insertArr, searchArr, removeArr);
  }

  // RBT Sorted
  *resultStream << "\nRed-Black Tree: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(rbt, /* random */ false, resultStream,
        insertArr, searchArr, removeArr);
  }

  // CHT Random
  *resultStream << "\nChained Hash Table: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(cht, /* random */ true, resultStream,
        insertArr, searchArr, removeArr);
  }

  // CHT Sorted
  *resultStream << "\nChained Hash Table: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    testStructure(cht, /* random */ false, resultStream,
        insertArr, searchArr, removeArr);
  }

  return EXIT_SUCCESS;
}
