#!/usr/bin/bash 

set echo on

echo "Building everything..."

pushd engine
source build.sh
popd

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "ERROR:"$ERRORLEVEL && exit
fi

pushd app
source build.sh
popd
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "ERROR:"$ERRORLEVEL && exit
fi

echo "All assembles built successfully"
