#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <vector>

struct Stats {
  int hp;
  int dam;
  int mana;
  int arm;
  int shi_timer;
  int poi_timer;
  int rec_timer;
};

void updateTimers(Stats &p, Stats &b) {

  if (p.poi_timer > 0) {
    b.hp -= 3;
    if (p.poi_timer == 1) {
      p.dam = 0;
    }
    p.poi_timer--;
  }
  if (p.shi_timer > 0) {
    if (p.shi_timer == 1) {
      p.arm = 0;
    }
    p.shi_timer--;
  }
  if (p.rec_timer > 0) {
    p.mana += 101;
    p.rec_timer--;
  }
}
void fight(Stats p, Stats b, std::array<std::array<int, 9>, 5> &spells,
           int total_cost, int &min_cost, std::vector<int> us, int hard_mode) {

  for (size_t i = 0; i < spells.size(); i++) {
    int cost = 0;
    Stats player = p;
    Stats boss = b;
    std::vector<int> used_spells = us;
    if (player.shi_timer > 1 && i == 2) {
      continue;
    }
    if (player.poi_timer > 1 && i == 3) {
      continue;
    }
    if (player.rec_timer > 1 && i == 4) {
      continue;
    }
    // -- Player turn --
    player.hp -= hard_mode;
    if (player.hp <= 0) {
      continue;
    }
    updateTimers(player, boss);

    if (boss.hp <= 0) {
      min_cost = std::min(min_cost, total_cost + cost);
      continue;
    }

    if (min_cost < total_cost + spells[i][0]) {
      continue;
    }
    if (player.mana < spells[i][0]) {
      continue;
    }
    player.arm += spells[i][3];
    player.hp += spells[i][4];
    player.shi_timer += spells[i][5];
    player.poi_timer += spells[i][6];
    player.rec_timer += spells[i][7];
    if (boss.hp <= 0) {
      min_cost = std::min(min_cost, total_cost + cost);
      continue;
    }
    player.mana -= spells[i][0];
    boss.hp -= spells[i][1];
    cost = spells[i][0];
    used_spells.push_back(i);
    if (boss.hp <= 0) {
      min_cost = std::min(min_cost, total_cost + cost);
      continue;
    }
    // -- Boss turn --
    player.hp -= hard_mode;
    updateTimers(player, boss);
    if (boss.hp <= 0) {
      min_cost = std::min(min_cost, total_cost + cost);
      continue;
    }
    player.hp -= (boss.dam - player.arm);
    if (player.hp <= 0) {
      continue;
    }
    fight(player, boss, spells, total_cost + cost, min_cost, used_spells,
          hard_mode);
  }
}

int main() {

  std::cout << "Hello, World!" << std::endl;

  Stats boss = {55, 8, 0, 0, 0, 0};
  Stats player = {50, 0, 500, 0, 0, 0};
  std::vector<int> used_spells;
  std::array<std::array<int, 9>, 5> spells{{{53, 4, 0, 0, 0, 0, 0, 0, 0},
                                            {73, 2, 0, 0, 2, 0, 0, 0, 0},
                                            {113, 0, 0, 7, 0, 6, 0, 0, 0},
                                            {173, 0, 3, 0, 0, 0, 6, 0, 0},
                                            {229, 0, 0, 0, 0, 0, 0, 5, 101}}};

  int min_cost = 1000000;
  fight(player, boss, spells, 0, min_cost, used_spells, 0);
  std::cout << "Part 1: " << min_cost << std::endl;
  min_cost = 1000000;
  fight(player, boss, spells, 0, min_cost, used_spells, 1);
  std::cout << "Part 2: " << min_cost << std::endl;
  return 0;
}
