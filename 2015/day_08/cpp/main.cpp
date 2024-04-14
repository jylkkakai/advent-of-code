#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main() {

  std::cout << "Hello, World!" << std::endl;
  std::string ex[] = {"", "abc", "aaa\"aaa", "\x27"};
  std::ifstream is("../input.txt");

  std::string line = "";
  size_t scount = 0;
  size_t mcount = 0;
  size_t ecount = 0;
  std::string temp = "";

  while (getline(is, line)) {
    size_t tcount = 0;
    // std::cout << line << std::endl;
    // std::cout << line.length() << std::endl;
    for (size_t i = 1; i < line.length() - 1; i++) {
      // temp = line.substr(1, line.length() - 2);
      // std::cout << line[i];
      if (line[i] == '\\') {
        if (line[i + 1] == 'x') {
          i += 3;
        } else {
          i++;
        }
      }
      tcount++;
    }
    ecount += 2;
    for (size_t i = 0; i < line.length(); i++) {
      if (line[i] == '\\' || line[i] == '"') {
        ecount++;
      }
      ecount++;
    }
    // std::cout << std::endl;
    mcount += tcount;
    // std::cout << tcount << std::endl;
    tcount = 0;
    // std::cout << std::endl;
    scount += line.length();
  }

  std::cout << "Part 1:" << std::endl;
  std::cout << scount << std::endl;
  std::cout << mcount << std::endl;
  std::cout << scount - mcount << std::endl;
  std::cout << "Part 2:" << std::endl;
  std::cout << ecount << std::endl;
  std::cout << ecount - scount << std::endl;

  return 0;
}
