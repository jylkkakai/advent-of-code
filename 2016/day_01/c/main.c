#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coord {
  int dir;
  int x;
  int y;
};

int main(void) {

  printf("Hello, World!\n");

  FILE *file = fopen("../input.txt", "r");
  // FILE *file = fopen("../example.txt", "r");

  if (file == NULL) {
    printf("Can't open the file!\n");
    return 1;
  }
  char str[710];
  fgets(str, 710, file);
  fclose(file);
  // printf("%s", str);
  char *ss = NULL;
  ss = strtok(str, " ,");
  struct Coord loc = {0, 0, 0};

  while (ss != NULL) {

    printf("%s\n", ss);
    char ch = ss[0];
    ss++;
    int val = strtol(ss, NULL, 10);
    printf("%c %d\n", ch, val);
    if (ch == 'L')
      loc.dir = (loc.dir == 0) ? 3 : loc.dir - 1;
    else if (ch == 'R')
      loc.dir = (loc.dir + 1) % 4;

    if (loc.dir == 0)
      loc.x += val;
    else if (loc.dir == 1)
      loc.y += val;
    else if (loc.dir == 2)
      loc.x -= val;
    else if (loc.dir == 3)
      loc.y -= val;
    ss = strtok(NULL, " ,");
    printf("%d %d %d\n", loc.dir, loc.x, loc.y);
  }
  printf("%d %d\n", loc.x, loc.y);
  printf("%d\n", loc.x + loc.y);
  return 0;
}
