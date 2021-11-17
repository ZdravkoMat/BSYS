#!/bin/bash

for (( i = 2; i <= 1024; i *= 2 ))
do
    ./tlb.out $i 1000
done