#!/bin/bash

gcc  ./src/*.c ./src/DS/*.c ./src/lib/*.c ./src/Player/*.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o main

