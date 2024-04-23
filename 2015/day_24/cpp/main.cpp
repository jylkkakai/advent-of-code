#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

long combinations(int N, int K, std::vector<int> w, int target) {
  std::string bitmask(K, 1);
  bitmask.resize(N, 0);

  int count = 0;
  long min_qe = 1000000000000;
  do {
    int sum = 0;
    long qe = 1;
    for (int i = 0; i < N; ++i) {
      if (bitmask[i]) {
        sum += w[i];
        qe *= w[i];
      }
    }
    if (sum == target) {
      if (qe < min_qe) {
        min_qe = qe;
      }
      count++;
    }
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
  return min_qe;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  std::string line;
  std::vector<int> wgts;

  while (std::getline(is, line)) {
    wgts.push_back(std::stoi(line));
  }
  int sum = 0;
  for (auto i : wgts) {
    sum += i;
  }
  std::cout << sum << std::endl;
  std::cout << sum / 3 << std::endl; // Part 1 group size
  std::cout << sum / 4 << std::endl; // Part 1 group size
  std::vector<int> g;
  int min_len = 100;
  int group = 0;
  long min_qe = 10000000000;
  std::cout << "Part 1: " << combinations(wgts.size(), 6, wgts, sum / 3)
            << std::endl;
  std::cout << "Part 2: " << combinations(wgts.size(), 4, wgts, sum / 4)
            << std::endl;
  return 0;
}
