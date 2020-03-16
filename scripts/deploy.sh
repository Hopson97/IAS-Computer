#!/bin/bash

sh scripts/build.sh release 

rm -rf -d ias-computer

mkdir ias-computer

cp bin/release/ias-computer ias-computer
cp -r res ias-computer

echo "Deploy build created."
echo "cd ias-computer to find it"