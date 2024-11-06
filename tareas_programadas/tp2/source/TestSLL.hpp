// Copyright 2024 Jose Manuel Mora Z
#pragma once
#include <array>
#include <iostream>
#include <fstream>

#include "SinglyLinkedList.hpp"
#include "TestConstants.hpp"

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
  *resultStream << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Singly Linked List
/// @param sll Singly Linked List to test
/// @param searchArr Array of values to search
/// @param resultStream Stream to write the results
void testSearch(SLList<int>& sll, std::array<int, search_len>& searchArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : searchArr) {
    sll.search(value);
  }
  endTimer()
  *resultStream << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Singly Linked List
/// @param sll Singly Linked List to test
/// @param removeArr Array of values to remove
/// @param resultStream Stream to write the results
void testRemove(SLList<int>& sll, std::array<int, remove_len>& removeArr,
    std::ostream*& resultStream) {
  startTimer()
  for (const auto& value : removeArr) {
    sll.remove(value);
  }
  endTimer()
  *resultStream << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Singly Linked List with the given parameters
/// @param random True if the data should be inserted randomly
/// @param resultStream Stream to write the results
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testSLL(bool random, std::ostream*& resultStream,
    std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Singly Linked List
  SLList<int>* sll = new SLList<int>();

  for (std::size_t i = 0; i < runs; ++i) {
    *resultStream << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*sll, random, insertArr, resultStream);

    // Search
    testSearch(*sll, searchArr, resultStream);

    // Removal
    testRemove(*sll, removeArr, resultStream);

    // Clear the list
    sll->clear();
  }

  // Free the memory
  delete sll;
}
