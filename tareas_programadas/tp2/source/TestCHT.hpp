// Copyright 2024 Jose Manuel Mora Z
#pragma once
#include <array>
#include <iostream>
#include <fstream>

#include "ChainedHashTable.hpp"
#include "TestConstants.hpp"

/// @brief Test the insertion of values in the Chained Hash Table
/// @param cht Chained Hash Table to test
/// @param random True if the values should be inserted randomly
/// @param insertArr Array of values to insert
void testInsert(ChainedHashTable<int>& cht, bool random,
    std::array<int, insert_len>& insertArr) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      cht.insert(value);
  } else {
    for (std::size_t value = 0; value < insert_len; ++value)
      cht.insert(value);
  }
  endTimer()
  std::cout << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Chained Hash Table
/// @param cht Chained Hash Table to test
/// @param searchArr Array of values to search
void testSearch(ChainedHashTable<int>& cht,
    std::array<int, search_len>& searchArr) {
  startTimer()
  for (const auto& value : searchArr) {
    cht.search(value);
  }
  endTimer()
  std::cout << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Chained Hash Table
/// @param cht Chained Hash Table to test
/// @param removeArr Array of values to remove
void testRemove(ChainedHashTable<int>& cht,
    std::array<int, remove_len>& removeArr) {
  startTimer()
  for (const auto& value : removeArr) {
    cht.remove(value);
  }
  endTimer()
  std::cout << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Chained Hash Table with the given parameters
/// @param random True if the data should be inserted randomly
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testCHT(bool random, std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Chained Hash Table
  ChainedHashTable<int>* cht = new ChainedHashTable<int>(insert_len);

  for (std::size_t i = 0; i < runs; ++i) {
    std::cout << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*cht, random, insertArr);

    // Search
    testSearch(*cht, searchArr);

    // Removal
    testRemove(*cht, removeArr);

    // Clear the hash table
    cht->clear();
  }

  // Free the memory
  delete cht;
}
