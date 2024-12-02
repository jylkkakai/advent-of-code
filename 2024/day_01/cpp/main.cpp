#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::cout << "Hello, World!" << std::endl;

  std::vector<std::string> arr1;
  std::vector<std::string> arr2;
  // std::vector<std::string> arr1 = {"3", "4", "2", "1", "3", "3"};
  // std::vector<std::string> arr2 = {"4", "3", "5", "3", "9", "3"};
  std::ifstream f("../input.txt");
  if (!f.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
  }
  std::string line;
  while (getline(f, line)) {
    arr1.push_back(line.substr(0, line.find(" ")));
    arr2.push_back(
        line.substr(line.find(" ") + 3, line.length() - line.find(" ")));
  }
  std::sort(arr1.begin(), arr1.end());
  std::sort(arr2.begin(), arr2.end());
  int distance = 0;
  for (size_t i = 0; i < arr1.size(); i++) {
    distance +=
        std::abs(std::stoi(arr1[i], nullptr) - std::stoi(arr2[i], nullptr));
  }
  std::cout << "Distance: " << distance << std::endl;
  int similarity = 0;
  for (size_t i = 0, j = 0; i < arr1.size() && j < arr2.size();) {
    if (arr1[i] == arr2[j]) {
      similarity += std::stoi(arr1[i], nullptr);
      j++;
    } else if (arr1[i] < arr2[j]) {
      i++;
      j = 0;
    } else
      j++;
    // std::cout << i << " " << j << " " << arr1[i] << " " << arr2[j] <<
    // std::endl;
  }
  std::cout << "Similarity: " << similarity << std::endl;
}
