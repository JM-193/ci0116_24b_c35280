// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>

#include "DoublyLinkedList.hpp"

template <typename DataType>

class ChainedHashTable {
 public:
  explicit ChainedHashTable(size_t size) = default;

  ~ChainedHashTable() = default;

  void insert(const DataType& value);

  DLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  size_t getSize() const;

  void setSize(size_t size);

  std::vector<DLList<DataType>> getTable() const;

  void setTable(std::vector<DLList<DataType>>);

 private:
  size_t size;

  std::vector<DLList<DataType>> table;
};
