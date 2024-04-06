#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::ifstream t("../input.txt");
  std::stringstream buffer;
  buffer << t.rdbuf();
  std::string test = buffer.str();
  int result = 0;
  // std::cout << test << std::endl;
  // test = "((()(((())";
  for (int i = 0; i < test.length(); i++) {
    result = (test[i] == '(')   ? result + 1
             : (test[i] == ')') ? result - 1
                                : result;
    if (result == -1) {
      std::cout << "Floor: " << result << " at " << i + 1 << std::endl;
    }
  }
  std::cout << result << std::endl;
  return 0;
}
