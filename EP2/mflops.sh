#!/bin/bash

# This script will run likwid-perfctr on the perfEG executable and extract the "DP [MFLOP/s] STAT" metric with the average value.

likwid-perfctr -g FLOPS_DP -f ./perfEG | grep "DP\ \[MFLOP/s\]\ STAT" | head -n1 | awk {'print $12'}