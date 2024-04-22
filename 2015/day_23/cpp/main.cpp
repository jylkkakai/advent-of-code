#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  std::string line;
  std::vector<std::vector<std::string>> lines;

  size_t a = 1; // 0 for part 1
  size_t b = 0;
  while (std::getline(is, line)) {

    std::vector<std::string> temp;
    temp.push_back(line.substr(0, line.find(" ")));
    temp.push_back(line.substr(line.find(" ") + 1, 1));
    temp.push_back(
        line.substr(line.rfind(" ") + 1, line.length() - line.rfind(" ")));
    lines.push_back(temp);
  }
  for (size_t i = 0; i < lines.size(); i++) {
    if (lines[i][0] == "hlf") {
      if (lines[i][1] == "a") {
        a /= 2;
      } else {
        b /= 2;
      }
    } else if (lines[i][0] == "tpl") {
      if (lines[i][1] == "a") {
        a *= 3;
      } else {
        b *= 3;
      }
    } else if (lines[i][0] == "inc") {
      if (lines[i][1] == "a") {
        a++;
      } else {
        b++;
      }
    } else if (lines[i][0] == "jmp") {
      i += std::stoi(lines[i][2]) - 1;
    } else if (lines[i][0] == "jie") {
      if ((lines[i][1] == "a" && a % 2 == 0) ||
          (lines[i][1] == "b" && b % 2 == 0)) {
        i += std::stoi(lines[i][2]) - 1;
      }
    } else if (lines[i][0] == "jio") {
      if ((lines[i][1] == "a" && a == 1) || (lines[i][1] == "b" && b == 1)) {
        i += std::stoi(lines[i][2]) - 1;
      }
    }
  }
  std::cout << a << " " << b << std::endl;
  return 0;
}
