#!/usr/bin/env bash

frame_count=60
frames_per_second=60
width=1280
height=720
cargo run --release -- --frame_count "$frame_count" --frames_per_second "$frames_per_second" --width "$width" --height "$height"