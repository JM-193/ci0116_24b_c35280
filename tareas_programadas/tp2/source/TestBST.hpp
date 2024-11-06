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
  *resultStream << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Binary Search Tree
/// @param bst Binary Search Tree to test
/// @param searchArr Array of values to search
/// @param resultStream Stream to write the results
void testSearch(BSTree<int>& bst, std::array<int, search_len>& searchArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : searchArr) {
    bst.search(value);
  }
  endTimer()
  *resultStream << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Binary Search Tree
/// @param bst Binary Search Tree to test
/// @param removeArr Array of values to remove
/// @param resultStream Stream to write the results
void testRemove(BSTree<int>& bst, std::array<int, remove_len>& removeArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : removeArr) {
    bst.remove(value);
  }
  endTimer()
  *resultStream << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Binary Search Tree with the given parameters
/// @param random True if the data should be inserted randomly
/// @param resultStream Stream to write the results
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testBST(bool random, std::ostream*& resultStream,
    std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Binary Search Tree
  BSTree<int>* bst = new BSTree<int>();

  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*bst, random, insertArr, resultStream);

    // Search
    testSearch(*bst, searchArr, resultStream);

    // Removal
    testRemove(*bst, removeArr, resultStream);

    // Clear the tree
    bst->clear();
  }

  // Free the memory
  delete bst;
}
