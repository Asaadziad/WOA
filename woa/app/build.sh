#/usr/bin/bash

mkdir -p ../bin/

cFilenames=$(find . -type f -name "*.c")

assembly="app"
compilerFlags="-g -fdeclspec -fPIC -Wall -Werror"
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../bin/ -lengine -Wl,-rpath,. -lSDL2_image -lSDL2 -lSDL2_ttf -lm"
defines=""

echo "Building $assembly"
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
