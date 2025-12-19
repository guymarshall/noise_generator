#!/usr/bin/env bash
gcc -Wall -Wextra -Werror -O3 -o main main.c

mkdir -p target

mv main target/main

frame_count=60
frames_per_second=60
width=$((16 * 60)) #960
height=$((9 * 60)) #540
./target/main "$frame_count" "$frames_per_second" "$width" "$height"