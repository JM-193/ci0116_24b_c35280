// Copyright 2024 Jose Manuel Mora Z
#include <limits>
#include <random>
#include <string>

#include "SortingTest.hpp"
#include "Ordenador.hpp"

/**
 * @brief Start program execution.
 *
 * @return Status code to the operating system, 0 means success.
 */
int main(int argc, char* argv[]) {
  // Declare Ordenador.
  Ordenador Test = Ordenador();

  // Obtain array length.
  std::string lenArg = argv[1];
  std::size_t arr_len = std::stoull(lenArg);

  // Declare array.
  std::vector<std::size_t> arr;

  // Generate the array numbers.
  generateRandomArray(arr, arr_len, 0, std::numeric_limits<std::size_t>::max());
}

void generateRandomArray(std::vector<std::size_t> arr, std::size_t arr_len,
    std::size_t min, std::size_t max) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<std::size_t> distribution(min, max);

  for (std::size_t index = 0; index < arr_len; ++index) {
    arr[index] = distribution(generator);
  }
}