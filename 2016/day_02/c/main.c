#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} coord_t;

char part1(char *line, int len) {
  char *arr[] = {"123", "456", "789"};
  static coord_t coord = {.x = 1, .y = 1};
  for (size_t i = 0; i < len - 1; i++) {
    if (line[i] == 'U' && coord.y > 0)
      coord.y -= 1;
    else if (line[i] == 'D' && coord.y < 2)
      coord.y += 1;
    else if (line[i] == 'L' && coord.x > 0)
      coord.x -= 1;
    else if (line[i] == 'R' && coord.x < 2)
      coord.x += 1;
    // printf("%c", arr[coord.y][coord.x]);
  }
  return arr[coord.y][coord.x];
}

char part2(char *line, int len) {
  char *arr[] = {"  1  ", " 234 ", "56789", " ABC ", "  D  "};
  static coord_t coord = {.x = 0, .y = 2};
  for (size_t i = 0; i < len - 1; i++) {
    if (line[i] == 'U' && coord.y > 0 && arr[coord.y - 1][coord.x] != ' ')
      coord.y -= 1;
    else if (line[i] == 'D' && coord.y < 4 && arr[coord.y + 1][coord.x] != ' ')
      coord.y += 1;
    else if (line[i] == 'L' && coord.x > 0 && arr[coord.y][coord.x - 1] != ' ')
      coord.x -= 1;
    else if (line[i] == 'R' && coord.x < 4 && arr[coord.y][coord.x + 1] != ' ')
      coord.x += 1;
    // printf("%c %d %d\n", arr[coord.y][coord.x], coord.y, coord.x);
  }
  return arr[coord.y][coord.x];
}

int main() {
  // FILE *f = fopen("../example.txt", "r");
  FILE *f = fopen("../input.txt", "r");
  size_t buf_size = 1024;
  char *line = NULL;
  char p1[8] = " ";
  char p2[8] = " ";
  size_t len = 0;
  size_t i = 0;

  while ((len = getline(&line, &buf_size, f)) != -1) {
    p1[i] = part1(line, len);
    p2[i] = part2(line, len);
    i++;
  }
  printf("Part 1: %s\n", p1);
  printf("Part 2: %s\n", p2);

  free(line);
  fclose(f);

  return 0;
}
