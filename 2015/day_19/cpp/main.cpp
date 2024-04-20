#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <unistd.h>
#include <vector>

// Tried brute force but takes too long time...
void findMolecule(std::string molecule, std::string input, int step,
                  std::vector<std::string> &elements,
                  std::vector<std::vector<std::string>> &replacements) {

  if (molecule == input) {
    std::cout << step << std::endl;
    return;
  }
  if (input.empty()) {
    return;
  }
  for (size_t i = input.length() - 1; i > 0; i--) {
    for (size_t j = 0; j < elements.size(); j++) {
      for (size_t k = 0; k < replacements[j].size(); k++) {
        std::string temps = input.substr(i, replacements[j][k].length());
        // std::cout << temps << std::endl;
        std::string temp;
        if (temps.find(replacements[j][k]) != std::string::npos) {
          temp = input.substr(0, i) + elements[j] +
                 input.substr(i + replacements[j][k].length(),
                              input.length() - i - replacements[j][k].length());
          std::cout << i << " " << input << " " << replacements[j][k] << " "
                    << elements[j] << " " << step << " " << temp << std::endl;
          findMolecule(molecule, temp, step + 1, elements, replacements);
          // }
        }
      }
    }
  }
}

int main() {

  std::cout << "Hello, World!" << std::endl;
  std::ifstream is("../input.txt");
  std::string line;
  std::string input;
  std::vector<std::string> elements;
  std::vector<std::string> distincts;
  std::vector<std::vector<std::string>> replacements;
  while (std::getline(is, line)) {

    if (line.empty()) {
      std::getline(is, line);
      input = line;
    } else {
      std::smatch sm;
      std::regex_match(line, sm, std::regex("(.*) => (.*)"));
      if (elements.empty() || std::find(elements.begin(), elements.end(),
                                        sm[1]) == elements.end()) {
        elements.push_back(sm[1]);
      }
      if (replacements.size() < elements.size()) {
        std::vector<std::string> temp = {sm[2]};
        replacements.push_back(temp);
      } else {
        replacements[elements.size() - 1].push_back(sm[2]);
      }
    }
  }
  for (size_t i = 0; i < elements.size(); i++) {
    std::cout << elements[i] << " -> ";
    for (auto rep : replacements[i]) {
      std::cout << rep << " ";
    }
    std::cout << std::endl;
  }
  std::cout << input << std::endl;
  for (size_t i = 0; i < input.length(); i++) {
    for (size_t j = 0; j < elements.size(); j++) {
      for (auto el : replacements[j]) {
        std::string temps = input.substr(i, elements[j].length());
        std::string temp;
        if (temps.find(elements[j]) != std::string::npos) {
          temp = input.substr(0, i) + el +
                 input.substr(i + elements[j].length(),
                              input.length() - i - elements[j].length());
          if (std::find(distincts.begin(), distincts.end(), temp) ==
                  distincts.end() ||
              distincts.empty()) {
            distincts.push_back(temp);
          }
        }
      }
    }
  }
  std::cout << "Part 1: " << distincts.size() << std::endl;
  std::cout << "Part 2: " << std::endl;
  // findMolecule("e", input, 0, elements, replacements);
  int num_of_elems = 0;
  int num_of_rnar = 0;
  int num_of_ys = 0;
  for (size_t i = 0; i < input.size(); i++) {
    if (std::isupper(input[i])) {
      num_of_elems++;
    }
    if (input[i] == 'Y') {
      num_of_ys++;
    }
    if (input.substr(i, 2) == "Rn" || input.substr(i, 2) == "Ar") {
      num_of_rnar++;
    }
  }
  std::cout << num_of_elems - num_of_rnar - 2 * num_of_ys - 1 << std::endl;

  return 0;
}
