// Copyright 2024 Jose Manuel Mora Z
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "Ordenador.hpp"

// TODO(jm): doc
void generateRandomArray(std::vector<int>& arr, std::size_t arr_len,
    int min, int max);

// TODO(jm): doc
#define TEST_SORT(sort_func, sort_name) \
  std::cout << std::endl; \
  for (std::size_t i = 0; i < 3; ++i) { \
    std::copy(arr.begin(), arr.end(), arr_cpy.begin()); \
    auto startTime = std::chrono::high_resolution_clock::now(); \
    Test.sort_func(arr_cpy.data(), arr_len); \
    auto endTime = std::chrono::high_resolution_clock::now(); \
    std::chrono::duration<double, std::milli> duration = endTime - startTime; \
    std::cout << i + 1 << ". " << sort_name << ":\t" << duration.count() \
              << "ms" << std::endl; \
  }

/**
 * @brief Start program execution.
 *
 * @return Status code to the operating system, 0 means success.
 */
int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cerr << "Error: No Array Length Provided as Command Line Argument"
              << std::endl;
    return EXIT_FAILURE;
  }

  // Declare Ordenador.
  Ordenador Test = Ordenador();

  // Obtain array length.
  const std::size_t arr_len = std::strtoull(argv[1], nullptr, 10);
  std::cout << std::endl << "Array Length:\t" << arr_len << std::endl;

  // Declare array.
  std::vector<int> arr(arr_len);

  // Generate the array numbers.
  generateRandomArray(arr, arr_len, 0, std::numeric_limits<int>::max());

  // Copy to preserve original.
  std::vector<int> arr_cpy(arr_len);

  // Insertion Sort.
  TEST_SORT(ordenamientoPorInsercion, "Insertion")

  // Selection Sort.
  TEST_SORT(ordenamientoPorSeleccion, "Selection")

  // Merge Sort.
  TEST_SORT(ordenamientoPorMezcla, "Merge")

  // Extra empty line just because.
  std::cout << std::endl;
}

void generateRandomArray(std::vector<int>& arr, std::size_t arr_len,
    int min, int max) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);

  for (std::size_t index = 0; index < arr_len; ++index) {
    arr[index] = distribution(generator);
  }
}
