#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 


echo "Coping files from  $1 to $2 :"
cp -r $1/* $2
echo "Copying finished"
