#include "../../../include/strslice.c"

int main() {
  char *str = "Hello World!\n";
  strslice_t slc = str_to_slice(str);
  print_slc(&slc);
  print_slc_len(&slc);
  strslice_t word = slc_shiftc(&slc, ' ');
  print_slc(&word);
  print_slc_len(&word);
  print_slc(&slc);
  print_slc_len(&slc);
  word = slc_shiftc(&slc, ' ');
  print_slc(&word);
  print_slc_len(&word);
  print_slc(&slc);
  print_slc_len(&slc);
  return 0;
}
