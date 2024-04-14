#include <iostream>

bool isValid(std::string s) {
  bool valid = false;
  for (size_t i = 0; i < s.length(); i++) {
    if (s.length() - i > 2) {
      if (int(s[i + 1]) - int(s[i]) == 1 && int(s[i + 2]) - int(s[i]) == 2) {
        // std::cout << i << " " << int(s[i]) << " " << int(s[i + 1]) << " "
        //           << int(s[i + 2]) << std::endl;
        valid = true;
        // break;
      }
    }
  }
  if (!valid) {
    return false;
  }
  valid = false;
  char first = ' ';
  for (size_t i = 0; i < s.length(); i++) {
    if (s.length() - i > 1 && s[i + 1] == s[i]) {
      if (s[i] != first && first != ' ') {
        valid = true;
      }
      first = s[i];
    }
  }
  if (!valid) {
    return false;
  }
  if (s.find_first_of("iol") != std::string::npos) {
    return false;
  }
  return true;
}

void addRec(std::string &s, int idx) {
  int i = s.length() - 1 - idx;
  int tempi = int(s[i]) + 1;
  if (tempi == 123) {

    tempi = 97;
    addRec(s, idx + 1);
  }
  s[i] = tempi;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::string ex1 = "hijklmmn";
  std::string ex2 = "abbceffg";
  std::string ex3 = "abbcegjk";
  std::string ex4 = "abcdefgh";
  std::string ex5 = "ghijklmn";
  std::string in = "hxbxwxba";
  std::string in2 = "hxbxxzaa";
  // std::cout << isValid(ex1) << std::endl;
  // std::cout << isValid(ex2) << std::endl;
  // std::cout << isValid(ex3) << std::endl;
  // for (size_t i = 0; i < 20; i++) {
  while (!isValid(in2)) {
    // int tempi = int(ex1[i]);
    addRec(in2, 0);
    // char tempc = char(tempi + 1);
    // std::cout << tempi + 1 << " " << tempc << std::endl;
  }
  std::cout << in2 << std::endl;
  return 0;
}
