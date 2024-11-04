// Copyright 2024 Jose Manuel Mora Z

#include <array>
#include <chrono>
#include <iostream>
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

template<std::size_t len>
void generateRandomArray(std::array<int, len>& arr) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  for (std::size_t index = 0; index < arr_len; ++index) {
    arr[index] = distribution(generator);
  }
}

void testSLL(SLList<int>& sll, bool random,
    std::array<int, arr_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Insertion
  generateRandomArray(insertArr);
  auto startTimeI = std::chrono::high_resolution_clock::now();
  if (random) {
    for (const auto& value : insertArr) {
      sll.insert(value);
    }
  } else {
    for (std::size_t value = 0; value < arr_len; ++value) {
      sll.insert(value);
    }
  }
  auto endTimeI = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> durationI = endTimeI - startTimeI;
  std::cout << "\t\tInsertion: \t" << durationI.count() << " ms" << std::endl;

  // Search
  generateRandomArray(searchArr);
  auto startTimeS = std::chrono::high_resolution_clock::now();
  for (const auto& value : searchArr) {
    sll.search(value);
  }
  auto endTimeS = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> durationS = endTimeS - startTimeS;
  std::cout << "\t\tSearch: \t" << durationS.count() << " μs" << std::endl;

  // Removal
  generateRandomArray(removeArr);
  auto startTimeR = std::chrono::high_resolution_clock::now();
  for (const auto& value : removeArr) {
    sll.remove(value);
  }
  auto endTimeR = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> durationR = endTimeR - startTimeR;
  std::cout << "\t\tRemoval: \t" << durationR.count() << " s" << std::endl;

  // Clear the list
  sll.clear();
}

int main() {
  SLList<int> sll;
  BSTree<int> bst;
  RBTree<int> rbt;
  ChainedHashTable<int> cht(arr_len);

  std::array<int, arr_len> insertArr;
  std::array<int, search_len> searchArr;
  std::array<int, remove_len> removeArr;

  std::cout << "\nSingly Linked List: Random" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    std::cout << "\tRun " << i + 1 << ":" << std::endl;
    testSLL(sll, /* random */ true, insertArr, searchArr, removeArr);
  }


  std::cout << "\nSingly Linked List: Sorted" << std::endl;
  for (std::size_t i = 0; i < runs; ++i) {
    std::cout << "\tRun " << i + 1 << ":" << std::endl;
    testSLL(sll, /* random */ false, insertArr, searchArr, removeArr);
  }

  std::cout << "\nBinary Search Tree: Random" << std::endl;


  std::cout << "\nBinary Search Tree: Sorted" << std::endl;


  std::cout << "\nRed-Black Tree: Random" << std::endl;


  std::cout << "\nRed-Black Tree: Sorted" << std::endl;


  std::cout << "\nChained Hash Table: Random" << std::endl;


  std::cout << "\nChained Hash Table: Sorted" << std::endl;


  return EXIT_SUCCESS;
}
