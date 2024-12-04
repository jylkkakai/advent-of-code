#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int dir;
  int x;
  int y;
} Coord;

typedef struct {
  Coord *array;
  size_t size;
  size_t capacity;
} Array;

void init_array(Array *arr, const size_t capacity) {

  arr->array = (Coord *)malloc(capacity * sizeof(Coord));
  arr->size = 0;
  arr->capacity = capacity;
  printf("Capacity: %zu\n", arr->capacity);
}
void push_back(Array *arr, const Coord element) {
  if (arr->size == arr->capacity) {
    arr->capacity *= 2;
    arr->array = realloc(arr->array, arr->capacity * sizeof(Coord));
    printf("Capacity: %zu\n", arr->capacity);
  }
  arr->array[arr->size++] = element;
}
void print_array(const Array *arr) {

  for (size_t i = 0; i < arr->size; i++) {

    printf("%zu %d %d %d\n", i, arr->array[i].dir, arr->array[i].x,
           arr->array[i].y);
  }
}
void free_array(Array *arr) {
  free(arr->array);
  arr->array = NULL;
  arr->size = 0;
  arr->capacity = 0;
}

void add_loc(Array *arr, int dir, int val) {

  Coord loc = arr->array[arr->size - 1];
  for (size_t i = 0; i < val; i++) {
    if (dir == 0) {
      loc.x++;
      push_back(arr, loc);
    } else if (dir == 1) {
      loc.y++;
      push_back(arr, loc);
    } else if (dir == 2) {
      loc.x--;
      push_back(arr, loc);
    } else if (dir == 3) {
      loc.y--;
      push_back(arr, loc);
    }
  }
}
int main(void) {

  Array arr;
  init_array(&arr, 1);

  FILE *file = fopen("../input.txt", "r");
  // FILE *file = fopen("../example.txt", "r");
  // FILE *file = fopen("../example2.txt", "r");

  if (file == NULL) {
    printf("Can't open the file!\n");
    return 1;
  }
  char str[710];
  fgets(str, 710, file);
  fclose(file);
  char *ss = NULL;
  ss = strtok(str, " ,");
  Coord loc = {0, 0, 0};
  push_back(&arr, loc);

  while (ss != NULL) {
    char ch = ss[0];
    ss++;
    int val = strtol(ss, NULL, 10);
    if (ch == 'L')
      loc.dir = (loc.dir == 0) ? 3 : loc.dir - 1;
    else if (ch == 'R')
      loc.dir = (loc.dir + 1) % 4;

    if (loc.dir == 0) {
      loc.x += val;
    } else if (loc.dir == 1) {
      loc.y += val;
    } else if (loc.dir == 2) {
      loc.x -= val;
    } else if (loc.dir == 3) {
      loc.y -= val;
    }
    add_loc(&arr, loc.dir, val);
    ss = strtok(NULL, " ,");
  }
  int found = 0;
  for (size_t i = 1; i < arr.size - 1 && !found; i++) {
    for (size_t j = 0; j < i - 1 && !found; j++) {
      if (arr.array[i].x == arr.array[j].x &&
          arr.array[i].y == arr.array[j].y) {

        printf("i   = %zu: \t%d %d\n", i, arr.array[i].x, arr.array[i].y);
        printf("j   = %zu: \t%d %d\n", j, arr.array[j].x, arr.array[j].y);
        printf("Part 2: %d\n", arr.array[j].x + arr.array[i].y);
        found = 1;
      }
    }
  }
  // print_array(&arr);
  printf("%d %d\n", loc.x, loc.y);
  printf("Part 1: %d\n", loc.x + loc.y);
  free_array(&arr);
  return 0;
}
