// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <iostream>

int main() {
  unsigned int a, b;
  std::cin >> a;
  std::cin >> b;
  do {
    unsigned int c = a % b;
    a = b;
    b = c;
  } while( b );
  std::cout << a << std::endl;
}


