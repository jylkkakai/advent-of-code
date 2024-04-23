#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;
  int row = 2981;
  int col = 3075;
  int col_sum = 0;
  int row_sum = 0;
  for (int i = 0; i < col; i++) {
    col_sum += i + 1;
  }
  for (int i = 0; i < row - 1; i++) {
    row_sum += i + col;
  }
  long code = 20151125;
  for (int i = 0; i < col_sum + row_sum - 1; i++) {
    code = code * 252533 % 33554393;
  };
  std::cout << code << std::endl;
  return 0;
}
