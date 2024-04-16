#include <fstream>
#include <iostream>
#include <vector>

int main() {

  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  std::string line;
  std::vector<int> containers;
  int num_of_combs = 0;
  int liters = 150;
  while (std::getline(is, line)) {
    containers.push_back(std::stoi(line));
  }
  std::cout << containers.size() << " " << (1 << containers.size())
            << std::endl;
  std::vector<int> num_of_conts(containers.size(), 0);
  for (size_t i = 0; i < (1 << containers.size()); i++) {
    int sum = 0;
    int num_of_ones = 0;
    for (size_t j = 0; j < containers.size(); j++) {
      if (i >> j & 1) {
        sum += containers[j];
        num_of_ones++;
      }
      // sum += containers[]
    }
    if (sum == liters) {
      num_of_combs++;
      num_of_conts[num_of_ones]++;
    }
  }
  int minimum = 100000000;
  for (size_t i = 0; i < num_of_conts.size(); i++) {
    if (num_of_conts[i] != 0) {
      minimum = num_of_conts[i];
      break;
    }
  }
  std::cout << "Part 1: " << num_of_combs << std::endl;
  std::cout << "Part 2: " << minimum << std::endl;
  return 0;
}
