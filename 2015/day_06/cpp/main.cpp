#include <array>
#include <fstream>
#include <iostream>
#include <string>

const size_t GRID_W = 1000;
const size_t GRID_H = 1000;
struct Instruction {
  std::string com;
  size_t x1;
  size_t y1;
  size_t x2;
  size_t y2;
};

Instruction parseLine(std::string s) {
  Instruction ins;
  std::string coord1;
  std::string coord2;
  if (s.find("turn on") != std::string::npos) {
    ins.com = "turn on";
    s = s.substr(8);
  } else if (s.find("turn off") != std::string::npos) {
    ins.com = "turn off";
    s = s.substr(9);
  } else if (s.find("toggle") != std::string::npos) {
    ins.com = "toggle";
    s = s.substr(6);
  }
  // std::cout << s << std::endl;
  ins.x1 = std::stoi(s.substr(0, s.find(",")));
  // std::cout << ins.x1 << std::endl;
  // std::cout << s.find(",") << std::endl;
  ins.y1 = std::stoi(s.substr(s.find(",") + 1, s.find(" ") - s.find(",")));
  // std::cout << ins.y1 << std::endl;
  ins.x2 = std::stoi(s.substr(s.rfind(" "), s.rfind(",") - s.rfind(" ")));
  // std::cout << ins.x2 << std::endl;
  // std::cout << s.rfind(",") << std::endl;
  ins.y2 = std::stoi(s.substr(s.rfind(",") + 1, s.length() - s.rfind(",")));
  // std::cout << ins.y2 << std::endl;

  return ins;
}

void executeInstruction(Instruction ins,
                        std::array<std::array<bool, GRID_W>, GRID_H> &grid) {
  for (size_t i = ins.x1; i <= ins.x2; i++) {
    for (size_t j = ins.y1; j <= ins.y2; j++) {
      if (ins.com == "turn on") {
        grid[i][j] = true;
      } else if (ins.com == "turn off") {
        grid[i][j] = false;
      } else if (ins.com == "toggle") {
        grid[i][j] = !grid[i][j];
      }
    }
  }
}
void executeInstruction(Instruction ins,
                        std::array<std::array<int, GRID_W>, GRID_H> &grid) {
  for (size_t i = ins.x1; i <= ins.x2; i++) {
    for (size_t j = ins.y1; j <= ins.y2; j++) {
      if (ins.com == "turn on") {
        grid[i][j]++;
      } else if (ins.com == "turn off") {
        grid[i][j] = std::max(0, grid[i][j] - 1);
      } else if (ins.com == "toggle") {
        grid[i][j] += 2;
      }
    }
  }
}
size_t getNumOfLit(std::array<std::array<bool, GRID_W>, GRID_H> &grid) {
  size_t res = 0;
  for (size_t i = 0; i < GRID_W; i++) {
    for (size_t j = 0; j < GRID_H; j++) {
      if (grid[i][j]) {
        res++;
      }
    }
  }
  return res;
}
size_t getNumOfLit(std::array<std::array<int, GRID_W>, GRID_H> &grid) {
  size_t res = 0;
  for (size_t i = 0; i < GRID_W; i++) {
    for (size_t j = 0; j < GRID_H; j++) {
      res += grid[i][j];
    }
  }
  return res;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::string ex1 = "turn on 0,0 through 999,999";
  std::string ex2 = "toggle 0,0 through 999,0";
  std::string ex3 = "turn off 499,499 through 500,500";
  std::string ex4 = "toggle 0,0 through 999,999";
  std::string ex5 = "turn on 0,0 through 0,0";

  std::array<std::array<bool, GRID_W>, GRID_H> grid1 = {false};
  std::array<std::array<int, GRID_W>, GRID_H> grid2 = {0};

  Instruction ins;
  std::ifstream file("../input.txt");
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      ins = parseLine(line);
      executeInstruction(ins, grid1);
      executeInstruction(ins, grid2);
    }
    std::cout << getNumOfLit(grid1) << std::endl;
    std::cout << getNumOfLit(grid2) << std::endl;
  }
  // std::cout << getNumOfLit(grid) << std::endl;
  // ins = parseLine(ex5);
  //
  // executeInstruction(ins, grid2);
  // std::cout << getNumOfLit(grid2) << std::endl;
  // ins = parseLine(ex2);
  // executeInstruction(ins, grid);
  // std::cout << getNumOfLit(grid) << std::endl;
  // ins = parseLine(ex3);
  // executeInstruction(ins, grid);
  // std::cout << getNumOfLit(grid) << std::endl;
  return 0;
}
