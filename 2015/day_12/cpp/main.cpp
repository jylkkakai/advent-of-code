#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

using json = nlohmann::json;

int calcNumbers(json j) {
  int result = 0;
  for (auto &el : j.items()) {
    std::cout << el.key() << "\n";
    if (el.value().is_null()) {
      continue;
    } else if (el.value().is_boolean()) {
      continue;
    } else if (el.value().is_number()) {
      std::cout << "number:\t" << el.value() << "\n";
      result += int(el.value());
    } else if (el.value().is_object()) {
      result += calcNumbers(el.value());
    } else if (el.value().is_array()) {
      result += calcNumbers(el.value());
    } else if (el.value().is_string()) {
      if (j.is_object() && el.value() == "red") { // Part 2. Remove for part 1
        return 0;
      }
      continue;
    }
  }
  std::cout << "Result:\t" << result << "\n";
  return result;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  json j;
  is >> j;
  calcNumbers(j);
  return 0;
}
