#include "md5.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *md5hash = malloc(17);
  char id[4] = "abc";
  char ans1[9] = "";
  char ans2[9] = "";
  // char hash[32] = "abc";
  char hash[32] = "abbhdwsy";
  char num[16];
  bool found = false;
  uint8_t filled = 0;
  int counter1 = 0;
  int counter2 = 0;
  int idx = 0;
  while (counter1 < 8 || counter2 < 8) {
    int len = sprintf(num, "%d", idx);

    strcat(hash, num);
    md5(hash, md5hash);

    found = true;
    for (size_t i = 0; i < 5; i++) {
      if (md5hash[i] != '0') {
        found = false;
        break;
      }
    }

    if (found) {
      if (counter1 < 8) {
        printf("%d1: %s\n", idx, md5hash);
        ans1[counter1] = md5hash[5];
        counter1++;
      }
      int pos = md5hash[5] - 48;
      if (counter2 < 8 && !((filled >> pos) & 1) && pos >= 0 && pos < 8) {
        printf("%d2: %s %d\n", idx, md5hash, pos);
        ans2[pos] = md5hash[6];
        filled |= 1 << pos;
        counter2++;
      }
    }
    idx++;
    // hash[3] = '\0';
    hash[8] = '\0';
    md5hash[0] = '\0';
  }

  printf("Part 1: %s\n", ans1);
  printf("Part 2: %s\n", ans2);
  free(md5hash);
  return 0;
}
