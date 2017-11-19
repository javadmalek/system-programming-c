#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 


echo "Make 15 new files XXXi ANd folder q4 :"
mkdir "q4"

for (( i=1; i<=15; i++ ))
do
	touch "q4/XXX"$i
done

echo "Openning the folder q4"
cd q4

echo "Disply the list of files in descending order
***************************************************"
ls -ltu>list_descending.txt

echo "Disply the list of files in ascending order
**************************************************"
ls -ltr>list_ascending.txt
