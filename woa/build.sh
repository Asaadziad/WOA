#!/usr/bin/bash 


clang -Wall src/*.c src/DS/*.c src/Player/*.c src/lib/*.c -o main -lSDL2_image -lSDL2 -lSDL2_ttf -lm
