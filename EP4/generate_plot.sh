#!/bin/bash

# List of .txt files to process
files=("FLOPS_DP.csv" "ENERGY.csv" "FLOPS_AVX.csv" "time.csv")

# Gnuplot script filename
gnuplot_script="plot_script.gp"

# Iterate through the files and generate plots
for file in "${files[@]}"; do
    # Set the output filename based on the input file
    output_file="${file%.csv}_output.png"

    # switch case to change the YLABEL
    case $file in
        "FLOPS_DP.csv")
            YLABEL="MFLOPS/s"
            ;;
        "FLOPS_AVX.csv")
            YLABEL="MFLOPS/s"
            ;;
        "ENERGY.csv")
            YLABEL="Joules"
            ;;
        "L2CACHE.csv")
            YLABEL="L2 Cache Miss Ratio"
            ;;
        "L3.csv")
            YLABEL="L3 Bandwidth"
            ;;
        "time.csv")
            YLABEL="Time (ms)"
            ;;
    esac
    
    # Generate the Gnuplot script for the current file
    cat > "$gnuplot_script" <<EOL
set terminal pngcairo enhanced font 'Verdana,10' size 1600,1000
set output '$output_file'
set xlabel 'N'
set ylabel '$YLABEL'

set title 'Performance Comparison (Logarithmic Scale)'

set key outside right
set logscale y
set xtics rotate by -45 offset -1,-0.5
set mxtics 2
set size 1.8,1

set lmargin 15
set rmargin 170
set bmargin 8
set tmargin 8
set key at screen 0.95, screen 0.95

plot '$file' using 1:2 with linespoints title 'MultMatVet', \\
     '' using 1:3 with linespoints title 'OptimizedMultMatVet', \\
     '' using 1:4 with linespoints title 'MultMatMat', \\
     '' using 1:5 with linespoints title 'OptimizedMultMatMat'
EOL

    # Generate the plot using Gnuplot
    gnuplot "$gnuplot_script"

    # Optional: Cleanup the temporary Gnuplot script
    rm "$gnuplot_script"
done
