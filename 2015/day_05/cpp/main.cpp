#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool containsUnwantedStr(std::string s) {

  std::vector<std::string> unwanted = {"ab", "cd", "pq", "xy"};
  for (size_t i = 0; i < unwanted.size(); i++) {
    if (s.find(unwanted[i]) != std::string::npos) {
      return true;
    }
  }
  return false;
}

bool isVowel(char c) {
  switch (c) {
  case 'a':
    return true;
  case 'e':
    return true;
  case 'i':
    return true;
  case 'o':
    return true;
  case 'u':
    return true;
  default:
    return false;
  }
}

bool contains3Vowels(std::string s) {
  size_t num_of_vowels = 0;
  for (size_t i = 0; i < s.length(); i++) {
    if (isVowel(s[i])) {
      num_of_vowels++;
    }
    if (num_of_vowels >= 3) {
      return true;
    }
  }
  return false;
}

bool containsDoubleLetter(std::string s) {
  for (size_t i = 0; i < s.length() - 1; i++) {
    if (s[i] == s[i + 1]) {
      return true;
    }
  }
  return false;
}

bool containsDoublePair(std::string s) {
  for (size_t i = 0; i < s.length() - 1; i++) {
    // std::cout << s.rfind(s.substr(i, 2)) << " " << i << std::endl;
    if (s.rfind(s.substr(i, 2)) - i > 1) {
      return true;
    }
  }
  return false;
}

bool repeatAfterOneLetter(std::string s) {
  for (size_t i = 0; i < s.length() - 2; i++) {
    if (s[i] == s[i + 2]) {
      return true;
    }
  }
  return false;
}

bool isNice(std::string s, size_t part) {
  if (part == 2) {
    if (!containsDoublePair(s)) {
      return false;
    }
    if (!repeatAfterOneLetter(s)) {
      return false;
    }
  } else {
    if (containsUnwantedStr(s)) {
      return false;
    }
    if (!contains3Vowels(s)) {
      return false;
    }
    if (!containsDoubleLetter(s)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::string ex1 = "ugknbfddgicrmopn";
  std::string ex2 = "aaa";
  std::string ex3 = "jchzalrnumimnmhp";
  std::string ex4 = "haegwjzuvuyypxyu";
  std::string ex5 = "dvszwmarrgswjxmb";
  std::string ex6 = "qjhvhtzxzqqjkmpb";
  std::string ex7 = "xxyxx";
  std::string ex8 = "uurcxstgmygtbstg";
  std::string ex9 = "ieodomkazucvgmuy";
  std::cout << isNice(ex1, 1) << std::endl;
  std::cout << isNice(ex2, 1) << std::endl;
  std::cout << isNice(ex3, 1) << std::endl;
  std::cout << isNice(ex4, 1) << std::endl;
  std::cout << isNice(ex5, 1) << std::endl;
  std::cout << std::endl;
  std::cout << isNice(ex6, 2) << std::endl;
  std::cout << isNice(ex7, 2) << std::endl;
  std::cout << isNice(ex8, 2) << std::endl;
  std::cout << isNice(ex9, 2) << std::endl;

  std::ifstream file("../input.txt");
  if (file.is_open()) {
    std::string line;
    size_t num_of_nice1 = 0;
    size_t num_of_nice2 = 0;
    while (std::getline(file, line)) {
      if (isNice(line, 1)) {
        num_of_nice1++;
      }
      if (isNice(line, 2)) {
        num_of_nice2++;
      }
    }
    std::cout << num_of_nice1 << std::endl;
    std::cout << num_of_nice2 << std::endl;
  }
  return 0;
}
