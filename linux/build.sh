#!/bin/bash

mkdir -p ./build
pushd ./build
g++ -std=c++11 ../linux_woa.cpp `sdl2-config --cflags  --libs` -lX11 -L/usr/X11/lib -o linux_woa
popd
