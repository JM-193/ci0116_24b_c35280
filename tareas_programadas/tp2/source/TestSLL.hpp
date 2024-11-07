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
void testInsert(SLList<int>& sll, bool random,
    std::array<int, insert_len>& insertArr) {
  startTimer()
  if (random) {
    for (const auto& value : insertArr)
      sll.insert(value);
  } else {
    for (std::size_t value = 0; value < insert_len; ++value)
      sll.insert(value);
  }
  endTimer()
  std::cout << "\t\tInsertion: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the insertion of values in the Singly Linked List
/// @param sll Singly Linked List to test
/// @param searchArr Array of values to search
void testSearch(SLList<int>& sll, std::array<int, search_len>& searchArr) {
  startTimer()
  for (const auto& value : searchArr) {
    sll.search(value);
  }
  endTimer()
  std::cout << "\t\tSearch: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the removal of values in the Singly Linked List
/// @param sll Singly Linked List to test
/// @param removeArr Array of values to remove
void testRemove(SLList<int>& sll, std::array<int, remove_len>& removeArr) {
  startTimer()
  for (const auto& value : removeArr) {
    sll.remove(value);
  }
  endTimer()
  std::cout << "\t\tRemoval: \t" << getDuration(startTime, endTime)
                << std::endl;
}

/// @brief Test the Singly Linked List with the given parameters
/// @param random True if the data should be inserted randomly
/// @param insertArr Array of values to insert
/// @param searchArr Array of values to search
/// @param removeArr Array of values to remove
void testSLL(bool random, std::array<int, insert_len>& insertArr,
    std::array<int, search_len>& searchArr,
    std::array<int, remove_len>& removeArr) {
  // Singly Linked List
  SLList<int>* sll = new SLList<int>();

  for (std::size_t i = 0; i < runs; ++i) {
    std::cout << "\tRun " << i + 1 << ":" << std::endl;
    // Insertion
    testInsert(*sll, random, insertArr);

    // Search
    testSearch(*sll, searchArr);

    // Removal
    testRemove(*sll, removeArr);

    // Clear the list
    sll->clear();
  }

  // Free the memory
  delete sll;
}
