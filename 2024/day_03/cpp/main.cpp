#include <fstream>
#include <iostream>
#include <string>

std::string str_shift(std::string &str, std::string delim) {

  size_t delim_pos = str.find(delim);
  std::string substring;
  if (delim_pos != std::string::npos) {
    substring = str.substr(0, delim_pos);
    str.erase(0, delim_pos + delim.length());
  } else {
    substring = str;
    str.erase(0, delim_pos);
  }

  return substring;
}

bool get_number(std::string &prog, int &num) {

  if (!isdigit(prog[0]))
    return false;
  size_t idx = 0;
  num = std::stoi(prog, &idx);
  if (idx > 3)
    return false;
  prog.erase(0, idx);
  return true;
}

int get_sum(std::string prog) {
  int sum = 0;
  while (prog.length() > 0) {
    str_shift(prog, "mul");
    if ('(' != prog[0])
      continue;
    str_shift(prog, "(");
    int first_num = 0;
    if (!get_number(prog, first_num))
      continue;
    if (',' != prog[0])
      continue;
    str_shift(prog, ",");
    int second_num = 0;
    if (!get_number(prog, second_num))
      continue;
    if (')' != prog[0])
      continue;
    sum += first_num * second_num;
  }
  return sum;
}

std::string get_dos(std::string str) {

  std::string dos = "";
  while (str.length() > 0) {
    dos += str_shift(str, "don't()");
    str_shift(str, "do()");
  }
  return dos;
}

int main() {

  // std::ifstream f("../example.txt");
  // std::ifstream f("../example2.txt");
  std::ifstream f("../input.txt");
  if (!f.is_open()) {
    std::cerr << "Failed to open file!"
              << "/n";
    return 1;
  }
  std::string prog;
  std::string full_prog = "";
  std::string do_prog = "";
  int sum1 = 0;
  int sum2 = 0;
  while (getline(f, prog)) {
    full_prog += prog;
  }
  sum1 += get_sum(full_prog);
  sum2 += get_sum(get_dos(full_prog));
  std::cout << "Part 1: " << sum1 << std::endl;
  std::cout << "Part 2: " << sum2 << std::endl;
}
