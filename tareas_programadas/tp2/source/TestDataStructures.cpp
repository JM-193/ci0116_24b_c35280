// Copyright 2024 Jose Manuel Mora Z

#include <array>
#include <chrono>
#include <iostream>
#include <random>

#include "BinarySearchTree.hpp"
#include "ChainedHashTable.hpp"
#include "RedBlackTree.hpp"
#include "SinglyLinkedList.hpp"

constexpr std::size_t arr_len = 1000000;
constexpr std::size_t min = 0;
constexpr std::size_t max = 3 * arr_len;
constexpr std::size_t search = 10000;
constexpr std::size_t remove = 10000;

void generateRandomArray(std::array<int, arr_len>& arr) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  for (std::size_t index = 0; index < arr_len; ++index) {
    arr[index] = distribution(generator);
  }
}

int main(int argc, char* argv[]) {
  SLList<int> sll;
  BSTree<int> bst;
  RBTree<int> rbt;
  ChainedHashTable<int> cht(arr_len);

  std::array<int, arr_len> arr;

  std::cout << "Singly Linked List: Random" << std::endl;
  generateRandomArray(arr);
  for (const auto& value : arr) {
    sll.insert(value);
  }

  std::cout << "Singly Linked List: Sorted" << std::endl;


  std::cout << "Binary Search Tree: Random" << std::endl;


  std::cout << "Binary Search Tree: Sorted" << std::endl;


  std::cout << "Red-Black Tree: Random" << std::endl;


  std::cout << "Red-Black Tree: Sorted" << std::endl;


  std::cout << "Chained Hash Table: Random" << std::endl;


  std::cout << "Chained Hash Table: Sorted" << std::endl;


  return EXIT_SUCCESS;
}
