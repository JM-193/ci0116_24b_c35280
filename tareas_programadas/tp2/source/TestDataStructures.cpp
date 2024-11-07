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

/// @brief Main functions
/// @return EXIT_SUCCESS if the program ends successfully
int main() {
  // Random arrays to test the data structures
  std::array<int, insert_len> insertArr;
  generateRandomArray(insertArr);
  std::array<int, search_len> searchArr;
  generateRandomArray(searchArr);
  std::array<int, remove_len> removeArr;
  generateRandomArray(removeArr);

  // SLL Sorted
  std::cout << "\nSingly Linked List: Sorted" << std::endl;
  testSLL(/* random */ false, insertArr, searchArr, removeArr);

  // SLL Random
  std::cout << "\nSingly Linked List: Random" << std::endl;
  testSLL(/* random */ true, insertArr, searchArr, removeArr);

  // BST Sorted
  std::cout << "\nBinary Search Tree: Sorted" << std::endl;
  testBST(/* random */ false, insertArr, searchArr, removeArr);

  // BST Random
  std::cout << "\nBinary Search Tree: Random" << std::endl;
  testBST(/* random */ true, insertArr, searchArr, removeArr);

  // RBT Sorted
  std::cout << "\nRed-Black Tree: Sorted" << std::endl;
  testRBT(/* random */ false, insertArr, searchArr, removeArr);

  // RBT Random
  std::cout << "\nRed-Black Tree: Random" << std::endl;
  testRBT(/* random */ true, insertArr, searchArr, removeArr);

  // CHT Sorted
  std::cout << "\nChained Hash Table: Sorted" << std::endl;
  testCHT(/* random */ false, insertArr, searchArr, removeArr);

  // CHT Random
  std::cout << "\nChained Hash Table: Random" << std::endl;
  testCHT(/* random */ true, insertArr, searchArr, removeArr);

  return EXIT_SUCCESS;
}
