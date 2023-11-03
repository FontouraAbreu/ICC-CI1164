#!/bin/bash                                                                                                                                                                                                                                   

EXECUTABLE="$1"
INPUT="$2"
METRICAS="ENERGY FLOPS_DP"
CPU=0

for m in $METRICAS; do
    likwid-perfctr -C ${CPU} -g ${m} -m ${EXECUTABLE} < ${INPUT} >> result.out
done
    
cat result.out | sed -n '6,9p'

echo "group: Energy"
echo "region: LEAST_SQUARE_METHOD"
cat result.out | sed -n '40p'
echo "region: SYSTEM_SOLVER"
cat result.out | sed -n '77p'

echo " "

echo "group: FLOPS_DP"
echo "region: LEAST_SQUARE_METHOD"
cat result.out | sed -n '123,124p'
echo "region: SYSTEM_SOLVER"
cat result.out | sed -n '159,160p'

rm result.out