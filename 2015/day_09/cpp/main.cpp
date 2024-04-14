#include <fstream>
#include <iostream>
#include <vector>

struct Distance {
  std::string start;
  std::string dest;
  size_t dist;
};

bool isVisited(std::string s, std::vector<std::string> &v) {
  for (auto place : v) {
    if (place.compare(s) == 0) {
      return true;
    }
  }
  return false;
}

size_t findLongestRec(std::vector<Distance> &distances,
                      std::vector<std::string> &visited,
                      std::vector<std::string> &shortest) {

  const size_t MIN_DIST = 0;
  size_t dist = MIN_DIST;
  std::string nearest = "";
  std::string next = "";
  std::string city = visited.back();
  for (auto d : distances) {
    size_t tdist = MIN_DIST;
    if (d.start == visited.back() && !isVisited(d.dest, visited)) {
      visited.push_back(d.dest);
      tdist = d.dist;
      tdist += findLongestRec(distances, visited, shortest);
      next = visited.back();
      visited.pop_back();
    } else if (d.dest == visited.back() && !isVisited(d.start, visited)) {
      visited.push_back(d.start);
      tdist = d.dist;
      tdist += findLongestRec(distances, visited, shortest);
      next = visited.back();
      visited.pop_back();
    }
    if (tdist > dist) {
      dist = tdist;
      nearest = next;
    }
  }
  if (dist > MIN_DIST) {
    shortest[visited.size()] = nearest;
  }
  return (dist > MIN_DIST) ? dist : 0;
}
void findLongest(std::vector<std::string> places,
                 std::vector<Distance> &distances) {

  for (auto place : places) {
    size_t dist = 0;
    std::vector<std::string> shortest(places.size());
    std::vector<std::string> visited;
    visited.push_back(place);
    shortest[0] = place;
    dist += findLongestRec(distances, visited, shortest);
    for (auto place : shortest) {
      std::cout << place << " -> ";
    }
    std::cout << dist << std::endl;
    visited.clear();
  }
}
size_t findShortestRec(std::vector<Distance> &distances,
                       std::vector<std::string> &visited,
                       std::vector<std::string> &shortest) {

  const size_t MAX_DIST = 100000000;
  size_t dist = MAX_DIST;
  std::string nearest = "";
  std::string next = "";
  std::string city = visited.back();
  for (auto d : distances) {
    size_t tdist = MAX_DIST;
    if (d.start == visited.back() && !isVisited(d.dest, visited)) {
      visited.push_back(d.dest);
      tdist = d.dist;
      tdist += findShortestRec(distances, visited, shortest);
      next = visited.back();
      visited.pop_back();
    } else if (d.dest == visited.back() && !isVisited(d.start, visited)) {
      visited.push_back(d.start);
      tdist = d.dist;
      tdist += findShortestRec(distances, visited, shortest);
      next = visited.back();
      visited.pop_back();
    }
    if (tdist < dist) {
      dist = tdist;
      nearest = next;
    }
  }
  if (dist < MAX_DIST) {
    shortest[visited.size()] = nearest;
  }
  return (dist < MAX_DIST) ? dist : 0;
}
void findShortest(std::vector<std::string> places,
                  std::vector<Distance> &distances) {

  for (auto place : places) {
    size_t dist = 0;
    std::vector<std::string> shortest(places.size());
    std::vector<std::string> visited;
    visited.push_back(place);
    shortest[0] = place;
    dist += findShortestRec(distances, visited, shortest);
    for (auto place : shortest) {
      std::cout << place << " -> ";
    }
    std::cout << dist << std::endl;
    visited.clear();
  }
}
int main() {
  std::cout << "Hello, World!" << std::endl;
  std::string ex[] = {"London to Dublin = 464", "London to Belfast = 518",
                      "Dublin to Belfast = 141"};
  std::ifstream file("../input.txt");
  std::string line;
  std::vector<std::string> places;
  std::vector<Distance> distances;
  while (std::getline(file, line)) {
    // for (auto line : ex) {
    Distance temp;
    temp.start = line.substr(0, line.find(" "));
    temp.dest = line.substr(line.find(" to ") + 4,
                            line.find(" =") - line.find(" to ") - 4);
    temp.dist = std::stoi(
        line.substr(line.rfind(" "), line.length() - line.rfind(" ")));
    std::cout << line << std::endl;
    std::cout << temp.start << " " << temp.dest << " " << temp.dist
              << std::endl;

    if (!isVisited(temp.start, places)) {
      places.push_back(temp.start);
    }
    if (!isVisited(temp.dest, places)) {
      places.push_back(temp.dest);
    }
    distances.push_back(temp);
  }
  for (auto place : places) {
    std::cout << place << std::endl;
  }
  findShortest(places, distances);
  findLongest(places, distances);

  return 0;
}
