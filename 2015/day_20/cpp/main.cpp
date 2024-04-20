#include <cmath>
#include <cstddef>
#include <iostream>

int main() {

  std::cout << "Hello, World!" << std::endl;
  size_t input = 36000000;
  size_t sum = 0;
  size_t i = 0;
  while (sum < input) {
    i++;
    sum = 0;
    size_t d = int(std::sqrt(double(i))) + 1;
    for (size_t j = 1; j <= d; j++) {
      if (i % j == 0) {
        sum += j * 10;
        sum += i / j * 10;
      }
    }
    // std::cout << i << " " << d << " " << sum << std::endl;
  }
  std::cout << "Part 1: " << i << " " << sum << std::endl;
  sum = 0;
  i = 0;

  while (sum < input) {
    i++;
    sum = 0;
    size_t d = int(std::sqrt(double(i))) + 1;
    for (size_t j = 1; j <= d; j++) {
      if (i % j == 0) {
        if (j <= 50) {
          sum += i / j * 11;
        }
        if (i / j <= 50) {
          sum += j * 11;
        }
      }
    }
    // std::cout << i << " " << d << " " << sum << std::endl;
  }
  std::cout << "Part 2: " << i << " " << sum << std::endl;
  return 0;
}
