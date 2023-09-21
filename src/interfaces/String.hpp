#pragma once
#include <stddef.h>
#include <stdint.h>

// const char* to_string(const char* str, char* buf = nullptr) {
//   return str;
// }
const char* to_string(uint64_t& num) {
  char* buf = new char[21];
  parseNumber(num, buf);

  return buf;
}

void parseNumber(uint64_t x, char* buf, size_t it = 0) {
  if (x >= 10)
    parseNumber(x / 10, buf, it + 1);

  int digit = x % 10;

  buf[it] = digit;
}

// const char* to_string(int64_t str) {
//   return str;
// }
// const char* to_string(float str) {
//   return str;
// }
// const char* to_string(double str) {
//   return str;
// }

// void print_each_digit(int x) {
//   if (x >= 10)
//     print_each_digit(x / 10);

//   int digit = x % 10;

//   std::cout << digit << '\n';
// }