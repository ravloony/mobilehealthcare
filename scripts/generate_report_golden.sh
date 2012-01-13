#!/bin/bash

DIR=$1
echo "\begin{tabular}{ | l | l | l | l | l | l | l | l | l | l |}"
echo "\hline"
echo "file & no of clients & regret & const avg & total const & time & greedy & const avg & total const & time &\\\ \hline" 
for file in $DIR/*.vrp
do
    echo "\verb=$(basename $file .vrp)= & 10 & \$$(build/bin/Debug/mobilehealthcare 2 $file 1 | grep "Cost of solution" | awk '{print $4 "$ & $" $8 "$ &$" $12 "$ & $" $16}')\$ & \$$(build/bin/Debug/mobilehealthcare 2 $file 3 | grep "Cost of solution" | awk '{print $4 "$ & $" $8 "$ & $" $12 "$ & $" $16}')\$\\\ \hline" 
done
echo "\end{tabular}"
