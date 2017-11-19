#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "First Find and saving the errors into log file: 
"
find / -name 'core' 2>log.txt

echo "Second Find with their weights:
"
find / -name 'conf' printf "%p%k KB"

echo "Third Find with specific permission:
"
find / -user bin -perm 555

echo "Fourth Find for less than a week:
"
find / -user s224309 -mtime -7
