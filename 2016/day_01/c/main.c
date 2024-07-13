#include <stdio.h>
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

  while (ss != NULL) {

    ss = strtok(NULL, " ,");
    printf("%s\n", ss);
  }
  return 0;
}
