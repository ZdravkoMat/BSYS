#!/bin/bash
POLICIES=("FIFO" "LRU" "OPT" "RAND" "CLOCK")

for policy in "${POLICIES[@]}"
do
    for i in 1 2 3 4
    do
        python3 paging-policy.py -c -f ./vpn.txt -p "$policy" -C "$i"
    done
    echo ""
done