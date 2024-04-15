#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int travelledDistance(std::vector<std::string> reindeer, int ttime) {
  return ttime / (std::stoi(reindeer[2]) + std::stoi(reindeer[3])) *
             std::stoi(reindeer[1]) * std::stoi(reindeer[2]) +
         std::min(
             std::stoi(reindeer[2]),
             int(ttime % (std::stoi(reindeer[2]) + std::stoi(reindeer[3])))) *
             std::stoi(reindeer[1]);
}

int main() {

  // std::ifstream is("../example.txt");
  std::ifstream is("../input.txt");
  std::string line;
  const size_t travel_time = 2503;
  std::vector<std::vector<std::string>> reindeers;

  while (std::getline(is, line)) {

    std::vector<std::string> reindeer;
    std::smatch sm;
    std::regex_match(
        line, sm,
        std::regex("(.*) can fly (.*) km/s for (.*) seconds, but then "
                   "must rest for (.*) seconds."));

    reindeer.push_back(sm[1]);
    reindeer.push_back(sm[2]);
    reindeer.push_back(sm[3]);
    reindeer.push_back(sm[4]);
    reindeers.push_back(reindeer);
  }

  // Part 1
  std::cout << "Part 1:" << std::endl;
  for (auto r : reindeers) {
    std::cout << r[0] << " " << travelledDistance(r, travel_time) << std::endl;
  }
  // Part 2
  std::cout << "Part 2:" << std::endl;
  std::vector<int> points(reindeers.size());
  for (size_t i = 1; i <= travel_time; i++) {
    size_t fastest = 0;
    size_t max_dist = 0;
    std::vector<int> distances(reindeers.size(), 0);
    for (size_t j = 0; j < reindeers.size(); j++) {
      distances[j] = travelledDistance(reindeers[j], i);
      if (distances[j] > max_dist) {
        max_dist = distances[j];
      }
    }
    for (size_t j = 0; j < reindeers.size(); j++) {
      if (distances[j] == max_dist) {
        points[j]++;
      }
    }
  }
  for (size_t j = 0; j < reindeers.size(); j++) {
    std::cout << reindeers[j][0] << " " << points[j] << std::endl;
  }
  return 0;
}
