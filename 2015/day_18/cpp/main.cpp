#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {

  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  std::string line;
  std::vector<std::vector<bool>> lights;
  while (std::getline(is, line)) {

    std::vector<bool> row(line.length());
    for (size_t i = 0; i < line.length(); i++) {
      row[i] = line[i] == '#' ? true : false;
    }
    lights.push_back(row);
  }
  std::cout << lights.size() << " " << lights[0].size() << std::endl;

  lights[0][0] = true;                                    // Part 2
  lights[0][lights[0].size() - 1] = true;                 // Part 2
  lights[lights[0].size() - 1][0] = true;                 // Part 2
  lights[lights.size() - 1][lights[0].size() - 1] = true; // Part 2
  int steps = 100;
  for (int s = 0; s < steps; s++) {
    std::vector<std::vector<bool>> next(lights.size(),
                                        std::vector<bool>(lights[0].size()));
    for (int i = 0; i < lights.size(); i++) {
      for (int j = 0; j < lights[i].size(); j++) {
        int neighbors = 0;
        for (int y = std::max(0, i - 1);
             y <= std::min(i + 1, int(lights.size()) - 1); y++) {
          for (int x = std::max(0, j - 1);
               x <= std::min(j + 1, int(lights.size()) - 1); x++) {

            if (lights[y][x] && !(x == j && y == i)) {
              neighbors++;
            }
          }
        }
        if (neighbors == 3) {
          next[i][j] = true;
        } else if (neighbors == 2 && lights[i][j]) {
          next[i][j] = true;
        } else {
          next[i][j] = false;
        }
      }
    }
    next[0][0] = true;                                    // Part 2
    next[0][lights[0].size() - 1] = true;                 // Part 2
    next[lights[0].size() - 1][0] = true;                 // Part 2
    next[lights.size() - 1][lights[0].size() - 1] = true; // Part 2
    lights = next;
  }
  int lights_on = 0;
  for (int i = 0; i < lights.size(); i++) {
    for (int j = 0; j < lights[i].size(); j++) {
      if (lights[i][j]) {
        lights_on++;
      } else {
      }
    }
  }
  std::cout << "Part 1: " << lights_on << std::endl;
  return 0;
}
