#!/usr/bin/bash 

set echo on

mkdir -p ../bin

cFilenames=$(find . -type f -name "*.c")

assembly="engine"
compilerFlags="-g -shared -fdeclspec -fPIC"

includeFlags="-Isrc"
linkedFlags="-lSDL2_image -lSDL2 -lSDL2_ttf -lm"
defines=""

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/lib$assembly.so $defines $includeFlags $linkedFlags
