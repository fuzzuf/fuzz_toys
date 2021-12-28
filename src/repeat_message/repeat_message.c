// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    uint64_t count;
    size_t read_length;
    size_t _ __attribute__((unused)); // gcc の "error: variable ‘_’ set but not used [-Werror=unused-but-set-variable]" を消すため
    char message[16] = {0};

    read_length = fread(&count, sizeof(count), 1, stdin);
    if (read_length == 0) {
        perror("[!] Failed to read count field");
        exit(1);
    }
    
    _ = fread(message, sizeof(message), 1, stdin);
    for (uint64_t i = 0; i < count; i += 1) {
        printf("%s\n", message);
    }
}