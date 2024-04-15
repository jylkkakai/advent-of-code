#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

int main() {
  std::ifstream is("../input.txt");
  std::map<std::string, std::map<std::string, int>> attendees;
  std::vector<std::string> order;
  std::string line;
  std::smatch sm;
  while (std::getline(is, line)) {

    std::regex_match(line, sm,
                     std::regex("(.*) would (lose|gain) (.*) happiness units "
                                "by sitting next to (.*)."));

    if (std::find(order.begin(), order.end(), sm[1]) == order.end()) {
      order.push_back(sm[1]);
    }
    if (sm[2] == "lose") {
      attendees[sm[1]][sm[4]] = -std::stoi(sm[3]);
    } else {
      attendees[sm[1]][sm[4]] = std::stoi(sm[3]);
    }
  }
  order.push_back("me"); // Part 2; comment out for part 1
  for (auto el : attendees) {
    for (auto el2 : el.second) {
      std::cout << el.first << " " << el2.first << " " << el2.second
                << std::endl;
    }
  }
  int max = 0;
  std::vector<std::string>::iterator left;
  std::vector<std::string>::iterator right;
  do {

    int happi = 0;

    for (auto it = order.begin(); it != order.end(); it++) {
      if (*it != "me") {

        left = (it == order.begin()) ? (order.end() - 1) : std::prev(it);
        right = (it == order.end() - 1) ? order.begin() : std::next(it);
        happi += (*it == "me") ? 0 : attendees[*left][*it];
        happi += (*it == "me") ? 0 : attendees[*right][*it];
      }
    }
    if (happi > max) {
      max = happi;
    }
  } while (std::next_permutation(order.begin(), order.end()));
  std::cout << max << std::endl;
  return 0;
}
