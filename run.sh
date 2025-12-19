#!/usr/bin/env bash
gcc -Wall -Wextra -Werror -O3 -o main main.c

mkdir -p target

mv main target/main

frame_count=600
frames_per_second=60
width=1280
height=720
./target/main "$frame_count" "$frames_per_second" "$width" "$height"