#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/ias-computer 
else
    ./bin/debug/ias-computer 
fi