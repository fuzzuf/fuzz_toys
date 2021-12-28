// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <cstdint>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
int main() {
  std::vector< char > data(
    std::istreambuf_iterator< char >{ std::cin },
    std::istreambuf_iterator< char >{}
  );
  data.erase(
    std::remove_if(
      data.begin(), data.end(),
      []( auto v ) { return v < ' ' || v > '~'; }
    ),
    data.end()
  );
  std::sort( data.begin(), data.end() );
  std::cout.write( data.data(), data.size() );
}

