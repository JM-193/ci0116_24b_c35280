// Copyright 2024 Jose Manuel Mora Z
#include <unistd.h>
#include <array>
#include <iostream>
#include <fstream>
#include <random>

#include "TestBST.hpp"
#include "TestCHT.hpp"
#include "TestConstants.hpp"
#include "TestRBT.hpp"
#include "TestSLL.hpp"

/// @brief Generate a random array of integers
/// @tparam len Length of the array
/// @param arr Array to fill with random integers
template<std::size_t len>
void generateRandomArray(std::array<int, len>& arr) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  for (std::size_t index = 0; index < len; ++index) {
    arr[index] = distribution(generator);
  }
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

  // Random arrays to test the data structures
  std::array<int, insert_len> insertArr;
  generateRandomArray(insertArr);
  std::array<int, search_len> searchArr;
  generateRandomArray(searchArr);
  std::array<int, remove_len> removeArr;
  generateRandomArray(removeArr);

  // SLL Random
  *resultStream << "\nSingly Linked List: Random" << std::endl;
  testSLL(/* random */ true, resultStream, insertArr, searchArr, removeArr);

  // SLL Sorted
  *resultStream << "\nSingly Linked List: Sorted" << std::endl;
  testSLL(/* random */ false, resultStream, insertArr, searchArr, removeArr);

  // BST Random
  *resultStream << "\nBinary Search Tree: Random" << std::endl;
  testBST(/* random */ true, resultStream, insertArr, searchArr, removeArr);

  // BST Sorted
  *resultStream << "\nBinary Search Tree: Sorted" << std::endl;
  testBST(/* random */ false, resultStream, insertArr, searchArr, removeArr);

  // RBT Random
  *resultStream << "\nRed-Black Tree: Random" << std::endl;
  testRBT(/* random */ true, resultStream, insertArr, searchArr, removeArr);

  // RBT Sorted
  *resultStream << "\nRed-Black Tree: Sorted" << std::endl;
  testRBT(/* random */ false, resultStream, insertArr, searchArr, removeArr);

  // CHT Random
  *resultStream << "\nChained Hash Table: Random" << std::endl;
  testCHT(/* random */ true, resultStream, insertArr, searchArr, removeArr);

  // CHT Sorted
  *resultStream << "\nChained Hash Table: Sorted" << std::endl;
  testCHT(/* random */ false, resultStream, insertArr, searchArr, removeArr);

  return EXIT_SUCCESS;
}
