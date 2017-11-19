#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "Starting to read from file: "
linecounter=0
while read line           
do                
	((linecounter+=1))
	echo "The value of line $linecounter is :  \"$line\""  
	
	if [ "$line" = "END" ]; then
		echo "*********************************"
		break;  
        fi

done <q9_string.txt 
