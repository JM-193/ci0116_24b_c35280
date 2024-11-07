// Copyright 2024 Jose Manuel Mora Z
#pragma once
#include <array>
#include <iostream>
#include <fstream>

#include "BinarySearchTree.hpp"
#include "TestConstants.hpp"

/// @brief Test the insertion of values in the Binary Search Tree
/// @param bst Binary Search Tree to test
/// @param random True if the values should be inserted randomly
/// @param insertArr Array of values to insert
void testInsert(BSTree<int>& bst, bool random,
    std::array<int, insert_len>& insertArr) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      bst.insert(value);
  } else {
    bst.fastInsert(insert_len);
  }
  endTimer()
  std::cout << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Binary Search Tree
/// @param bst Binary Search Tree to test
/// @param searchArr Array of values to search
void testSearch(BSTree<int>& bst, std::array<int, search_len>& searchArr) {
  startTimer()
  for (const auto& value : searchArr) {
    bst.search(value);
  }
  endTimer()
  std::cout << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Binary Search Tree
/// @param bst Binary Search Tree to test
/// @param removeArr Array of values to remove
void testRemove(BSTree<int>& bst, std::array<int, remove_len>& removeArr) {
  startTimer()
  for (const auto& value : removeArr) {
    bst.remove(value);
  }
  endTimer()
  std::cout << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Binary Search Tree with the given parameters
/// @param random True if the data should be inserted randomly
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testBST(bool random, std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Binary Search Tree
  BSTree<int>* bst = new BSTree<int>();

  for (std::size_t i = 0; i < runs; ++i) {
    std::cout << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*bst, random, insertArr);

    // Search
    testSearch(*bst, searchArr);

    // Removal
    testRemove(*bst, removeArr);

    // Clear the tree
    bst->clear();
  }

  // Free the memory
  delete bst;
}
