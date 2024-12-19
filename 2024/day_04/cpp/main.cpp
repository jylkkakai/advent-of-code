#include <fstream>
#include <iostream>
#include <vector>

int main() {
  // std::ifstream f("../example.txt");
  std::ifstream f("../input.txt");
  if (!f.is_open()) {
    std::cerr << "Failed to open file!"
              << "\n";
    return 1;
  }

  std::vector<std::string> puzzle;
  std::string s;
  std::string word = "XMAS";
  int count = 0;
  while (getline(f, s)) {
    puzzle.push_back(s);
  }

  for (size_t i = 0; i < puzzle.size(); i++) {
    for (size_t j = 0; j < puzzle[i].length(); j++) {
      if (puzzle[i][j] != word[0] && puzzle[i][j] != word[word.length() - 1])
        continue;
      // right
      if (j < puzzle[i].length() - 1 - (word.length() - 2)) {
        for (size_t k = 1; k < word.length(); k++) {
          if ((puzzle[i][j] == word[0] && puzzle[i][j + k] != word[k]) ||
              (puzzle[i][j] == word[word.length() - 1] &&
               puzzle[i][j + k] != word[word.length() - 1 - k]))
            break;
          if (k == word.length() - 1)
            count++;
        }
      }
      // down
      if (i < puzzle.size() - 1 - (word.length() - 2)) {
        for (size_t k = 1; k < word.length(); k++) {
          if ((puzzle[i][j] == word[0] && puzzle[i + k][j] != word[k]) ||
              (puzzle[i][j] == word[word.length() - 1] &&
               puzzle[i + k][j] != word[word.length() - 1 - k]))
            break;
          if (k == word.length() - 1)
            count++;
        }
      }
      // right down
      if (i < puzzle.size() - 1 - (word.length() - 2) &&
          j < puzzle[i].length() - 1 - (word.length() - 2)) {
        for (size_t k = 1; k < word.length(); k++) {
          if ((puzzle[i][j] == word[0] && puzzle[i + k][j + k] != word[k]) ||
              (puzzle[i][j] == word[word.length() - 1] &&
               puzzle[i + k][j + k] != word[word.length() - 1 - k]))
            break;
          if (k == word.length() - 1)
            count++;
        }
      }
      // left down
      if (i < puzzle.size() - 1 - (word.length() - 2) &&
          j > (word.length() - 2)) {
        for (size_t k = 1; k < word.length(); k++) {
          if ((puzzle[i][j] == word[0] && puzzle[i + k][j - k] != word[k]) ||
              (puzzle[i][j] == word[word.length() - 1] &&
               puzzle[i + k][j - k] != word[word.length() - 1 - k]))
            break;
          if (k == word.length() - 1)
            count++;
        }
      }
    }
  }
  std::cout << "Part 1: " << count << "\n";

  count = 0;
  for (size_t i = 0; i < puzzle.size() - 2; i++) {
    for (size_t j = 0; j < puzzle[i].length() - 2; j++) {
      std::string first;
      first =
          first + puzzle[i][j] + puzzle[i + 1][j + 1] + puzzle[i + 2][j + 2];
      std::string second;
      second =
          second + puzzle[i][j + 2] + puzzle[i + 1][j + 1] + puzzle[i + 2][j];

      if ((first != "MAS" && first != "SAM") ||
          (second != "MAS" && second != "SAM"))
        continue;

      count++;
    }
  }
  std::cout << "Part 2: " << count << "\n";
}
