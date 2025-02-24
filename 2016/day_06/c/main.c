#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // FILE *f = fopen("../example.txt", "r");
  FILE *f = fopen("../input.txt", "r");
  if (f == NULL) {
    printf("Can`t open file!\n");
    return 1;
  }
  char *buf;
  size_t sz = 10;
  int chars[8 * 26] = {0};

  while (getline(&buf, &sz, f) != -1) {
    printf("%s", buf);
    for (size_t i = 0; i < 8; i++) {
      // printf("%c", buf[i]);
      int idx = buf[i] - 97;
      chars[i * 26 + idx]++;
    }
  }
  fclose(f);
  // printf("Part 1: ");
  // for (size_t i = 0; i < 8; i++) {
  //   int max_idx = 0;
  //   int max_val = 0;
  //   for (size_t j = 0; j < 26; j++) {
  //     if (chars[i * 26 + j] > max_val) {
  //       max_val = chars[i * 26 + j];
  //       max_idx = j;
  //     }
  //   }
  //   printf("%c", max_idx + 97);
  // }
  // printf("\n");

  printf("Part 2: ");
  for (size_t i = 0; i < 8; i++) {
    int min_idx = 0;
    int min_val = 100;
    for (size_t j = 0; j < 25; j++) {
      if (chars[i * 26 + j] < min_val && chars[i * 26 + j] > 0) {
        min_val = chars[i * 26 + j];
        min_idx = j;
      }
    }
    printf("%c", min_idx + 97);
  }
  printf("\n");
  return 0;
}
