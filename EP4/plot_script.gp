set terminal pngcairo enhanced font 'Verdana,10' size 1200,800
set output 'output.png'
set xlabel 'N'
set ylabel 'MFLOPS/s'
set title 'Performance Comparison (Logarithmic Scale)'
set key outside right
set logscale y

# Set x-axis tick marks based on the 'N' values
set xtics (64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000)
set xtics rotate by -45 offset -1,-0.5


# Set canvas size and margins
set size 1.8,1
set lmargin 15
set rmargin 125
set bmargin 8
set tmargin 8

set key at screen 0.95, screen 0.95

plot 'FLOPS_DP.csv' using 1:2 with linespoints title 'MultMatVet', \
     '' using 1:4 with linespoints title 'OptimizedMultMatVet', \
     '' using 1:6 with linespoints title 'MultMatMat', \
     '' using 1:8 with linespoints title 'OptimizedMultMatMat'