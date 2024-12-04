#include <fstream>
#include <iostream>
#include <vector>

std::string str_shift(std::string &str, std::string delim) {

  size_t delim_pos = str.find(delim);
  std::string subs;
  if (delim_pos != std::string::npos) {
    subs = str.substr(0, delim_pos);
    str.erase(0, delim_pos + 1);
  } else {
    subs = str;
    str.erase(0, delim_pos);
  }

  return subs;
}

bool is_safe1(std::string line) {
  std::string number = str_shift(line, " ");
  std::string next_number = str_shift(line, " ");
  bool incr = false;
  if (std::stoi(number) < std::stoi(next_number))
    incr = true;
  do {

    if (!incr &&
        (std::stoi(number, nullptr) - std::stoi(next_number, nullptr) > 3 ||
         std::stoi(number, nullptr) - std::stoi(next_number, nullptr) < 1)) {
      return false;
    } else if (incr &&
               (std::stoi(next_number, nullptr) - std::stoi(number, nullptr) >
                    3 ||
                std::stoi(next_number, nullptr) - std::stoi(number, nullptr) <
                    1)) {
      return false;
    }

    number = next_number;
    next_number = str_shift(line, " ");
  } while (!next_number.empty());
  return true;
}

bool is_safe2(std::string line) {
  std::vector<int> numbers;

  while (!line.empty()) {
    numbers.push_back(std::stoi(str_shift(line, " ")));
  }

  for (size_t i = 0; i < numbers.size(); i++) {
    bool incr = false;
    bool prev_incr = false;
    std::vector<int> damp_nums = numbers;
    damp_nums.erase(damp_nums.begin() + i);

    for (size_t j = 0; j < damp_nums.size() - 1; j++) {

      incr = damp_nums[j] < damp_nums[j + 1] ? true : false;
      if (incr && (damp_nums[j + 1] - damp_nums[j] > 3 ||
                   (damp_nums[j + 1] - damp_nums[j] < 1))) {
        break;
      } else if (!incr && (damp_nums[j] - damp_nums[j + 1] > 3 ||
                           (damp_nums[j] - damp_nums[j + 1] < 1)))
        break;

      if (j > 0 && prev_incr != incr)
        break;

      if (j == damp_nums.size() - 2) {
        return true;
      }
      prev_incr = incr;
    }
  }
  return false;
}

int main() {
  std::vector<std::string> lines;

  // std::ifstream f("../example.txt");
  std::ifstream f("../input.txt");
  if (!f.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
    return 1;
  }

  std::string line;
  while (getline(f, line)) {
    lines.push_back(line);
  }

  int num_of_safe1 = 0;
  int num_of_safe2 = 0;

  for (auto line : lines) {
    if (is_safe1(line)) {
      num_of_safe1++;
      num_of_safe2++;
    } else if (is_safe2(line)) {
      num_of_safe2++;
    }
  }
  std::cout << "Part 1: " << num_of_safe1 << std::endl;
  std::cout << "Part 2: " << num_of_safe2 << std::endl;
}
