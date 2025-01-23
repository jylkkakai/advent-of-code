#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t len;
  char *data;
} strslice_t;

strslice_t str_to_slice(char *s) {
  return (strslice_t){.len = strlen(s), .data = s};
}

strslice_t slc_shift(strslice_t *s, char delim) {
  size_t len = 0;
  strslice_t ret;
  for (size_t i = 0; i < s->len; i++) {
    if (s->data[i] == delim) {
      len = i;
      break;
    }
  }
  ret.data = s->data;
  ret.len = len;
  s->data = s->data + len + 1;
  return ret;
}

void print_slc(const strslice_t *s) {
  for (size_t i = 0; i < s->len; i++) {
    printf("%c", s->data[i]);
  }
}
void part1(FILE *f) {

  int count = 0;
  size_t buf_len = 32;
  char *buf = NULL;

  while (getline(&buf, &buf_len, f) != -1) {
    strslice_t ss = str_to_slice(buf);
    strslice_t as = slc_shift(&ss, ' ');
    int a = (int)strtol(as.data, NULL, 10);
    strslice_t bs = slc_shift(&ss, ' ');
    int b = (int)strtol(bs.data, NULL, 10);
    strslice_t cs = slc_shift(&ss, '\n');
    int c = (int)strtol(cs.data, NULL, 10);
    // if (b == 201 || b == 202 || b == 203)
    //   printf("%d %d %s", count, b, buf);
    // printf("%ld | %ld | %ld\n", strtol(a.data, NULL, 10),
    //        strtol(b.data, NULL, 10), strtol(c.data, NULL, 10));
    if (a + b <= c || a + c <= b || b + c <= a)
      continue;
    count++;
  }

  printf("Part 1: %d\n", count);
  free(buf);
}

void part2(FILE *f) {

  int count = 0;
  size_t buf_len = 32;
  char *buf1 = NULL;
  char *buf2 = NULL;
  char *buf3 = NULL;

  while (getline(&buf1, &buf_len, f) != -1) {
    strslice_t ss1 = str_to_slice(buf1);
    getline(&buf2, &buf_len, f);
    strslice_t ss2 = str_to_slice(buf2);
    getline(&buf3, &buf_len, f);
    strslice_t ss3 = str_to_slice(buf3);
    for (size_t i = 0; i < 3; i++) {
      strslice_t as = slc_shift(&ss1, ' ');
      strslice_t bs = slc_shift(&ss2, ' ');
      strslice_t cs = slc_shift(&ss3, ' ');
      int a = (int)strtol(as.data, NULL, 10);
      int b = (int)strtol(bs.data, NULL, 10);
      int c = (int)strtol(cs.data, NULL, 10);
      if (a + b <= c || a + c <= b || b + c <= a)
        continue;
      count++;
    }
  }

  printf("Part 2: %d\n", count);
  free(buf1);
  free(buf2);
  free(buf3);
}

int main() {
  // FILE *f = fopen("../example.txt", "r");
  FILE *f = fopen("../input.txt", "r");
  if (f == NULL) {
    printf("Falied to read file!");
    return 1;
  }

  part1(f);
  rewind(f);
  part2(f);

  fclose(f);
  return 0;
}
