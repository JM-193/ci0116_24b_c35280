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
  *resultStream << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Chained Hash Table
/// @param cht Chained Hash Table to test
/// @param searchArr Array of values to search
/// @param resultStream Stream to write the results
void testSearch(ChainedHashTable<int>& cht,
    std::array<int, search_len>& searchArr, std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : searchArr) {
    cht.search(value);
  }
  endTimer()
  *resultStream << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Chained Hash Table
/// @param cht Chained Hash Table to test
/// @param removeArr Array of values to remove
/// @param resultStream Stream to write the results
void testRemove(ChainedHashTable<int>& cht,
    std::array<int, remove_len>& removeArr, std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : removeArr) {
    cht.remove(value);
  }
  endTimer()
  *resultStream << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Chained Hash Table with the given parameters
/// @param random True if the data should be inserted randomly
/// @param resultStream Stream to write the results
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testCHT(bool random, std::ostream*& resultStream,
    std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Chained Hash Table
  ChainedHashTable<int>* cht = new ChainedHashTable<int>(insert_len);

  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*cht, random, insertArr, resultStream);

    // Search
    testSearch(*cht, searchArr, resultStream);

    // Removal
    testRemove(*cht, removeArr, resultStream);

    // Clear the hash table
    cht->clear();
  }

  // Free the memory
  delete cht;
}
