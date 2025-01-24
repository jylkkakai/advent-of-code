#include "../../../include/strslice.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char c;
  int num;
} letter_t;

typedef struct {
  letter_t letters[30];
  size_t len;
} letters_t;

void sort_letters(letters_t *l) {

  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (size_t i = 0; i < l->len - 1; i++) {
      if (l->letters[i].num < l->letters[i + 1].num ||
          (l->letters[i].num == l->letters[i + 1].num &&
           l->letters[i].c > l->letters[i + 1].c)) {
        letter_t temp = l->letters[i];
        l->letters[i] = l->letters[i + 1];
        l->letters[i + 1] = temp;
        sorted = false;
      }
    }
  }
}

void part1(FILE *f) {

  size_t line_max = 128;
  char *line = NULL;
  int sum_of_ids = 0;
  while (getline(&line, &line_max, f) != -1) {
    letters_t letters = {.len = 0};
    strslice_t ss = str_to_slice(line);
    // printf("");
    while (ss.data[0] > 0x60) {
      strslice_t word = slc_shiftc(&ss, '-');

      // printf("....2");
      for (size_t i = 0; i < word.len; i++) {
        bool found = false;
        for (size_t j = 0; j < letters.len; j++) {
          if (word.data[i] == letters.letters[j].c) {
            letters.letters[j].num++;
            found = true;
          }
        }
        if (!found) {
          letters.letters[letters.len].c = word.data[i];
          letters.letters[letters.len].num++;
          letters.len++;
        }
      }
    }
    sort_letters(&letters);
    strslice_t ids = slc_shiftc(&ss, '[');
    int id = strtol(ids.data, NULL, 10);
    // printf("%d\n", id);
    strslice_t checksum = slc_shiftc(&ss, ']');
    // print_slc(&checksum);
    // printf("\n");
    for (size_t i = 0; i < 5; i++) {
      if (letters.letters[i].c != checksum.data[i])
        break;
      if (i == 4)
        sum_of_ids += id;
      // printf("%c %d\n", letters.letters[i].c, letters.letters[i].num);
    }
    // printf("----\n");
  }
  printf("Part 1: %d\n", sum_of_ids);
  free(line);
}

void part2(FILE *f) {

  size_t line_max = 128;
  char *line = NULL;
  int sum_of_ids = 0;

  printf("Part 2:\n");
  char *ds = "0123456789";
  strslice_t digits = {.data = ds, .len = 10};
  while (getline(&line, &line_max, f) != -1) {
    // /*   */ letters_t letters = {.len = 0};
    strslice_t ss = str_to_slice(line);

    strslice_t name = slc_shifts(&ss, digits);
    strslice_t id = slc_shiftc(&ss, '[');
    for (size_t i = 0; i < name.len; i++) {
      if (name.data[i] != '-')
        printf("%c",
               ((name.data[i] - 0x61) + (int)strtol(id.data, NULL, 10)) % 26 +
                   0x61);
      else
        printf("%c", name.data[i]);
    }
    print_slc(&id);
    printf("\n");
  }
  free(line);
}

int main() {
  // FILE *f = fopen("../example.txt", "r");
  FILE *f = fopen("../input.txt", "r");
  if (f == NULL) {
    printf("Failed to read file!");
    return 1;
  }
  part1(f);
  rewind(f);
  part2(f);

  fclose(f);
  return 0;
}
