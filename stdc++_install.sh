#!/bin/sh

BITSPATH="/usr/local/include/bits/"

if [ ! -d BITSPATH ]; then 
    mkdir $BITSPATH
    cp stdc++.h $BITSPATH/stdc++.h
fi