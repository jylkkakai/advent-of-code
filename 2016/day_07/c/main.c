#include "../../../include/strslice.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // FILE *f = fopen("../example.txt", "r");
  // FILE *f = fopen("../example2.txt", "r");
  FILE *f = fopen("../input.txt", "r");
  if (f == NULL) {
    printf("Can`t open file!\n");
    return 1;
  }
  char *buf = malloc(256);
  size_t sz = 256;

  int count1 = 0;
  int count2 = 0;
  while (getline(&buf, &sz, f) != -1) {
    // printf("%s", buf);
    strslice_t str = str_to_slice(buf);
    bool hypernet = false;
    bool is_tls = false;
    bool is_ssl = false;

    // Part 1
    for (size_t i = 0; i < str.len - 4; i++) {
      if (str.data[i] == '[')
        hypernet = true;
      else if (str.data[i] == ']')
        hypernet = false;
      ;

      if (str.data[i] == str.data[i + 3] &&
          str.data[i + 1] == str.data[i + 2] &&
          str.data[i] != str.data[i + 1]) {
        if (hypernet) {
          is_tls = false;
          break;
        }
        is_tls = true;
      }
    }
    if (is_tls)
      count1++;

    // Part 2
    hypernet = false;
    for (size_t i = 0; i < str.len - 3 && !is_ssl; i++) {
      if (str.data[i] == '[')
        hypernet = true;
      else if (str.data[i] == ']')
        hypernet = false;

      if (str.data[i] == str.data[i + 2] && str.data[i] != str.data[i + 1] &&
          !hypernet) {
        strslice_t aba = (strslice_t){.len = 3, .data = str.data + i};
        strslice_t scp = (strslice_t){str.len, str.data};
        while (!is_ssl) {
          slc_shiftc(&scp, '[');
          strslice_t hyper = slc_shiftc(&scp, ']');
          if (hyper.len == 0)
            break;
          for (size_t j = 0; j < hyper.len - 2; j++) {
            if (hyper.data[j + 2] == aba.data[1] &&
                hyper.data[j] == aba.data[1] &&
                hyper.data[j + 1] == aba.data[0]) {
              is_ssl = true;
              break;
            }
          }
        }
      }
    }
    if (is_ssl)
      count2++;
  }
  printf("Part 1: %d\n", count1);
  rewind(f);
  printf("Part 2: %d\n", count2);
  fclose(f);
  return 0;
}
