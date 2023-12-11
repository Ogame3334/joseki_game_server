#!/bin/bash

cd /root/joseki_server
# cp -r ./static_contents/ ./build/static_contents/
 
DIR="build"
 
if [ -d $DIR ];then
  rm -rf $DIR
fi

mkdir $DIR

cd $DIR
cmake ..
make
./joseki_server