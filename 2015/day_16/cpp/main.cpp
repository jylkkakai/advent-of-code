#include <fstream>
#include <iostream>
#include <regex>

int main() {

  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  std::string line;
  std::map<std::string, int> things;
  things = {
      {"children", 3}, {"cats", 7},     {"samoyeds", 2}, {"pomeranians", 3},
      {"akitas", 0},   {"vizslas", 0},  {"goldfish", 5}, {"trees", 3},
      {"cars", 2},     {"perfumes", 1},
  };

  // //
  int max_sum = -5;
  std::string sue;
  while (std::getline(is, line)) {
    int sum = 0;
    std::smatch sm;
    std::regex_match(line, sm,
                     std::regex("(.*): (.*): (.*), (.*): (.*), (.*): (.*)"));
    for (size_t i = 2; i < sm.size(); i += 2) {
      std::cout << sm[1] << " " << things[sm[i]] << " " << sm[i + 1]
                << std::endl;
      if (sm[i] == "cats" || sm[i] == "trees") { // Part 2
        sum += (things[sm[i]] < std::stoi(sm[i + 1])) ? 1 : -1;
      } else if (sm[i] == "pomeranians" || sm[i] == "goldfish") { // Part 2
        sum += (things[sm[i]] > std::stoi(sm[i + 1])) ? 1 : -1;
      } else {
        sum += (things[sm[i]] == std::stoi(sm[i + 1])) ? 1 : -1;
      }
    }
    std::cout << sm[1] << " " << sum << std::endl;
    if (sum > max_sum) {
      max_sum = sum;
      sue = sm[1];
    }
    sum = 0;
  }
  std::cout << sue << " " << max_sum << std::endl;
  return 0;
}
