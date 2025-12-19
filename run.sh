#!/usr/bin/env bash
gcc -Wall -Wextra -Werror -O3 -o main main.c

mkdir -p target

mv main target/main

./target/main