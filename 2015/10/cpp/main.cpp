#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::string input = "3113322113";
  std::string result = "";
  for (size_t i = 0; i < 50; i++) {
    std::string result = "";
    for (size_t j = 0; j < input.length(); j++) {
      size_t count = 1;
      char temp = input[j];
      while (temp == input[j + 1]) {
        count++;
        j++;
      }
      result.append(std::to_string(count) + temp);
    }
    input = result;
    std::cout << i << ": " << result.length() << std::endl;
    // std::string result = "";
  }
  return 0;
}
