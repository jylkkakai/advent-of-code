#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  size_t len;
  char *data;
} strslice_t;

strslice_t str_to_slice(char *s) {
  return (strslice_t){.len = strlen(s), .data = s};
}

strslice_t slc_shiftc(strslice_t *s, char delim) {
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
  if (len != 0) {
    s->data = s->data + len + 1;
    s->len = s->len - len - 1;
  }
  return ret;
}

bool char_is_in(char c, strslice_t s) {

  for (size_t i = 0; i < s.len; i++) {
    if (c == s.data[i])
      return true;
  }
  return false;
}

// Not sure about the input slice data pointer position or do I need this one
strslice_t slc_shifts(strslice_t *s, strslice_t delims) {
  size_t len = 0;
  strslice_t ret;
  for (size_t i = 0; i < s->len; i++) {
    if (char_is_in(s->data[i], delims)) {
      len = i;
      break;
    }
  }

  ret.data = s->data;
  ret.len = len;
  if (len != 0) {
    s->data = s->data + len;
    s->len = s->len - len;
  }
  return ret;
}

void print_slc(const strslice_t *s) {
  for (size_t i = 0; i < s->len; i++) {
    printf("%c", s->data[i]);
  }
}
