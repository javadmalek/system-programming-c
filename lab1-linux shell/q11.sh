#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 


echo "Getting input values : "
InputDir=$1
InputSize=$2

state=0
echo "looking for result in folder: "
for entry in "$InputDir"/*
do
	if [ -f "$entry" ];then
		FILESIZE=$(stat -c%s "$entry")
		if [ $FILESIZE -ge $InputSize ]; then
			echo "File: $entry 		FILESIZE: "$FILESIZE"B"
			state=1
		fi
	fi

done

if [ $state = 0 ]; then
	echo "No result!....."
fi

