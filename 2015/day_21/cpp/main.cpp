#include <cmath>
#include <cstddef>
#include <iostream>

int main() {

  std::cout << "Hello, World!" << std::endl;
  int boss_hp = 109;
  int boss_dam = 8;
  int boss_arm = 2;
  int hp = 100;
  int weapons[5][2] = {{8, 4}, {10, 5}, {25, 6}, {40, 7}, {74, 8}};
  int armor[6][2] = {{0, 0}, {13, 1}, {31, 2}, {53, 3}, {75, 4}, {102, 5}};
  int ringdam[4][2] = {{0, 0}, {25, 1}, {50, 2}, {100, 3}};
  int ringdef[4][2] = {{0, 0}, {20, 1}, {40, 2}, {80, 3}};
  int min_cost = 1000000;
  int max_cost = 0;
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 6; j++) {
      for (size_t k = 0; k < 4; k++) {
        for (size_t l = 0; l < 4; l++) {
          int hits = int(boss_hp /
                         std::max(weapons[i][1] + ringdam[k][1] - boss_arm, 1));
          int boss_hits =
              int(hp / std::max(boss_dam - armor[j][1] - ringdef[l][1], 1));
          int cost =
              weapons[i][0] + armor[j][0] + ringdam[k][0] + ringdef[l][0];
          // std::cout << hits << " " << boss_hits << " " << cost << std::endl;
          if (hits <= boss_hits) {
            // std::cout << hits << " " << boss_hits << " " << cost <<
            // std::endl;
            if (cost < min_cost) {
              min_cost = cost;
            }
          }
          if (hits > boss_hits) {
            std::cout << hits << " " << boss_hits << " " << cost << std::endl;
            if (cost > max_cost) {
              max_cost = cost;
            }
          }
        }
      }
    }
  }
  std::cout << "Part 1: " << min_cost << std::endl;
  std::cout << "Part 2: " << max_cost << std::endl;
  return 0;
}
