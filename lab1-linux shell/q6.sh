#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "searching for files with 2mg and starting with a and finishing by o:  "
find /size  +2M | find / -type f -name 'a*o'
