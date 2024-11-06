// Copyright 2024 Jose Manuel Mora Z
#pragma once
#include <chrono>
#include <string>

/// @brief Number of runs to test the data structures
constexpr std::size_t runs = 3;
/// @brief Number of elements to insert in the data structures
constexpr std::size_t insert_len = 1000000;
/// @brief Number of elements to search in the data structures
constexpr std::size_t search_len = 10000;
/// @brief Number of elements to remove in the data structures
constexpr std::size_t remove_len = 10000;
/// @brief Minimum value for the random numbers
constexpr std::size_t min = 0;
/// @brief Maximum value for the random numbers
constexpr std::size_t max = 3 * insert_len;

/// @brief Start the timer to calculate the duration
#define startTimer() auto startTime = std::chrono::high_resolution_clock::now();
/// @brief End the timer to calculate the duration
#define endTimer() auto endTime = std::chrono::high_resolution_clock::now();

std::string getDuration(std::chrono::high_resolution_clock::time_point startTime,
    std::chrono::high_resolution_clock::time_point endTime) {
  std::chrono::duration<double, std::nano> duration = endTime - startTime;
  double finalDuration = 0.0;
  std::string unit;
  if (duration.count() > 1000000000) {
    finalDuration = duration.count() / 1000000000;
    unit = " s";
  } else if (duration.count() > 1000000) {
    finalDuration = duration.count() / 1000000;
    unit = " ms";
  } else if (duration.count() > 1000) {
    finalDuration = duration.count() / 1000;
    unit = " μs";
  } else {
    finalDuration = duration.count();
    unit = " ns";
  }
  return std::to_string(finalDuration) + unit;
}