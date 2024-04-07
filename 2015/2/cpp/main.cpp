#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

struct Dimensions {
  int l;
  int w;
  int h;
};

Dimensions parseLine(std::string str) {

  Dimensions dim;
  size_t x1 = str.find("x");
  size_t x2 = str.rfind("x");
  dim.l = std::stoi(str.substr(0, x1));
  dim.w = std::stoi(str.substr(x1 + 1, x2 - x1 - 1));
  dim.h = std::stoi(str.substr(x2 + 1, str.length() - x2));
  return dim;
}

int findSmallest(Dimensions dim) {
  if (dim.w * dim.h < dim.l * dim.w && dim.w * dim.h < dim.h * dim.l) {
    return dim.w * dim.h;
  } else if (dim.h * dim.l < dim.l * dim.w && dim.h * dim.l < dim.w * dim.l) {
    return dim.h * dim.l;
  }
  return dim.l * dim.w;
}

int measureRibbon(Dimensions d) {

  int len = 0;
  len = 2 * d.l + 2 * d.w;
  if (d.l >= d.w && d.l >= d.h) {
    len = 2 * d.w + 2 * d.h;
  } else if (d.w >= d.l && d.w >= d.h) {
    len = 2 * d.l + 2 * d.h;
  }
  return len + d.l * d.w * d.h;
}

int main() {

  std::cout << "Hello World!" << std::endl;
  std::string example1 = "2x3x4";
  std::string example2 = "1x1x10";

  std::ifstream file("../input.txt");

  Dimensions dim;
  if (file.is_open()) {
    std::string line;
    int result = 0;
    int ribbon = 0;
    while (std::getline(file, line)) {
      dim = parseLine(line);
      result += 2 * dim.l * dim.w + 2 * dim.w * dim.h + 2 * dim.h * dim.l +
                findSmallest(dim);
      ribbon += measureRibbon(parseLine(line));
    }
    std::cout << "Wrapper: " << result << std::endl;
    std::cout << "Ribbon: " << ribbon << std::endl;
  }
  // std::cout << measureRibbon(parseLine(example1)) << std::endl;
  // std::cout << measureRibbon(parseLine(example2)) << std::endl;
  return 0;
}
