#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {

  int x[2] = {0};
  int y[2] = {0};
  std::string ex1 = "^v";
  std::string ex2 = "^>v<";
  std::string ex3 = "^v^v^v^v^v";
  std::string str = "";
  std::map<std::string, bool> m;

  std::ifstream file("../input.txt");
  std::stringstream buffer;
  buffer << file.rdbuf();
  str = buffer.str();
  std::cout << str.length() << std::endl;
  std::string mkey = std::to_string(x[0]) + std::to_string(y[0]);
  m[mkey] = true;
  mkey = std::to_string(x[1]) + std::to_string(y[1]);
  m[mkey] = true;
  // str = ex3;
  for (int i = 0; i < str.length(); i++) {

    if (str[i] == '>') {
      x[i % 2]++;
    } else if (str[i] == '<') {
      x[i % 2]--;
    } else if (str[i] == '^') {
      y[i % 2]++;
    } else if (str[i] == 'v') {
      y[i % 2]--;
    }
    // std::cout << i << " " << x << " " << y << std::endl;
    std::string mkey = std::to_string(x[i % 2]) + std::to_string(y[i % 2]);
    m[mkey] = true;
    // mkey = std::to_string(x[0]) + std::to_string(y[0]);
    // m[mkey]++;
    // mkey = std::to_string(x[1]) + std::to_string(y[1]);
    // m[mkey]++;
  }
  // std::cout << m[0].size() << " " << m[1].size() << std::endl;
  std::cout << m.size() << std::endl;
  return 0;
}
