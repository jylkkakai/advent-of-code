#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main() {

  std::cout << "Hello, World!" << std::endl;
  // std::ifstream is("../example.txt");
  std::ifstream is("../input.txt");
  std::string line;
  // const size_t travel_time = 2503;
  std::vector<std::vector<int>> ings;
  //
  while (std::getline(is, line)) {
    //
    std::vector<int> ing;
    std::smatch sm;
    std::regex_match(line, sm,
                     std::regex("(.*): capacity (.*), durability (.*), "
                                "flavor (.*), texture (.*), calories (.*)"));
    ing.push_back(std::stoi(sm[2]));
    ing.push_back(std::stoi(sm[3]));
    ing.push_back(std::stoi(sm[4]));
    ing.push_back(std::stoi(sm[5]));
    ing.push_back(std::stoi(sm[6]));
    ings.push_back(ing);
    // for (auto el : sm) {
    //   std::cout << el << std::endl;
    // }
  }
  // for (auto el : ingredients) {
  //   std::cout << el[0] << " " << el[1] << " " << el[2] << " " << el[3] << " "
  //             << el[4] << std::endl;
  // }
  int max_score = 0;
  for (size_t i = 0; i < 100; i++) {
    for (size_t j = 0; j < 100 - i; j++) {
      for (size_t k = 0; k < 100 - i - j; k++) {
        size_t l = 100 - k - j - i;
        int cap_sum =
            ings[0][0] * i + ings[1][0] * j + ings[2][0] * k + ings[3][0] * l;
        int dur_sum =
            ings[0][1] * i + ings[1][1] * j + ings[2][1] * k + ings[3][1] * l;
        int fla_sum =
            ings[0][2] * i + ings[1][2] * j + ings[2][2] * k + ings[3][2] * l;
        int tex_sum =
            ings[0][3] * i + ings[1][3] * j + ings[2][3] * k + ings[3][3] * l;
        int cal_sum =
            ings[0][4] * i + ings[1][4] * j + ings[2][4] * k + ings[3][4] * l;
        int total;
        if (cap_sum <= 0 || dur_sum <= 0 || fla_sum <= 0 || tex_sum <= 0) {
          continue;
        }
        total = cap_sum * dur_sum * fla_sum * tex_sum;
        if (total > max_score && cal_sum == 500) {
          max_score = total;
        }
      }
    }
  }
  std::cout << max_score << std::endl;
  return 0;
}
