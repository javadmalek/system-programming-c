#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "Getting the inputs"
N=$1
M=$2

echo "Drwing the Schame"
for (( i=1; i<=N; i++ ))
do
	printf "-"
done

echo "" #New Line

for (( j=1; j<=M; j++ ))
do
	printf "|" 
	for (( i=2; i<N; i++ ))
	do
		printf " "
	done
	printf "|"
	echo ""
done

for (( i=1; i<=N; i++ ))
do
	printf "-"
done

echo ""
