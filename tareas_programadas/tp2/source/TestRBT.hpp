// Copyright 2024 Jose Manuel Mora Z
#pragma once
#include <array>
#include <iostream>
#include <fstream>

#include "RedBlackTree.hpp"
#include "TestConstants.hpp"

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
  *resultStream << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Red-Black Tree
/// @param rbt Red-Black Tree to test
/// @param searchArr Array of values to search
/// @param resultStream Stream to write the results
void testSearch(RBTree<int>& rbt, std::array<int, search_len>& searchArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : searchArr) {
    rbt.search(value);
  }
  endTimer()
  *resultStream << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Red-Black Tree
/// @param rbt Red-Black Tree to test
/// @param removeArr Array of values to remove
/// @param resultStream Stream to write the results
void testRemove(RBTree<int>& rbt, std::array<int, remove_len>& removeArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : removeArr) {
    rbt.remove(value);
  }
  endTimer()
  *resultStream << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Red-Black Tree with the given parameters
/// @param random True if the data should be inserted randomly
/// @param resultStream Stream to write the results
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testRBT(bool random, std::ostream*& resultStream,
    std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Red-Black Tree
  RBTree<int>* rbt = new RBTree<int>();

  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*rbt, random, insertArr, resultStream);

    // Search
    testSearch(*rbt, searchArr, resultStream);

    // Removal
    testRemove(*rbt, removeArr, resultStream);

    // Clear the tree
    rbt->clear();
  }

  // Free the memory
  delete rbt;
}
