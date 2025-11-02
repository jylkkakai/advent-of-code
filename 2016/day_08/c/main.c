#include "../../../include/strslice.c"
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
// #define gw 7
// #define gh 3
#define gw 50
#define gh 6

void print_grid(int *grid) {
  for (int i = 0; i < gh; i++) {
    for (int j = 0; j < gw; j++) {
      char c = '.';
      if (grid[i * gw + j])
        c = '#';
      // printf("%i ", grid[i * gw + j]);
      printf("%c", c);
    }
    printf("\n");
  }
}

int main() {
  FILE *file;
  file = fopen("../input.txt", "r");
  // file = fopen("../example.txt", "r");
  if (file == NULL) {
    return 1;
  }
  size_t sz = 64;
  char buf[sz];
  char *b = buf;
  int grid[gw * gh] = {0};
  int resgrid[gw * gh] = {0};

  while (getline(&b, &sz, file) != -1 && counter < 3) {
    strslice_t slc = str_to_slice(b);
    strslice_t s = slc_shiftc(&slc, ' ');

    if (slc_comp_str(&s, "rect")) {

      s = slc_shiftc(&slc, 'x');
      for (int i = 0; i < atoi(slc.data); i++) {
        for (int j = 0; j < atoi(s.data); j++) {
          grid[i * gw + j] = true;
        }
      }

    } else if (slc_comp_str(&s, "rotate")) {

      s = slc_shiftc(&slc, '=');
      strslice_t st = slc_shiftc(&slc, ' ');
      int start = atoi(st.data);
      slc_shiftc(&slc, ' ');
      int num = atoi(slc.data);

      if (s.data[0] == 'c') {
        int res[gh];
        for (int i = 0; i < gh; i++) {
          resgrid[(i + num) % gh] = grid[i * gw + start];
        }
        for (int i = 0; i < gh; i++) {
          grid[i * gw + start] = resgrid[i];
        }

      } else if (s.data[0] == 'r') {
        int res[gw];
        for (int i = 0; i < gw; i++) {
          resgrid[(i + num) % gw] = grid[start * gw + i];
        }
        for (int i = 0; i < gw; i++) {
          grid[start * gw + i] = resgrid[i];
        }
      }
    }
    // print_grid(grid);
    // printf("----------\n");
  }
  int res = 0;
  for (int i = 0; i < gw * gh; i++) {
    if (grid[i] == 1)
      res++;
  }
  printf("%i\n", res);

  print_grid(grid);
  fclose(file);
  return 0;
}
