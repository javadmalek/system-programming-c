#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "Making Folders Based on Tree in nested levels"
mkdir -p a
mkdir -p a/b
mkdir -p a/d
mkdir -p a/b/e
mkdir -p a/b/f
mkdir -p a/b/c
mkdir -p a/b/f/i
mkdir -p a/b/c/g
mkdir -p a/b/c/g/h

echo "changing the permission of folders"
chmod 773 a/b/c/g/h
chmod 737 a/b/c/g
chmod 477 a/b/f/i
chmod 777 a/b/e
chmod 777 a/b/f
chmod 773 a/b/c
chmod 770 a/b
chmod 555 a/d
chmod 777 a

echo "trying to make file and then chenging its permission"
touch a/xyz
chmod 600 a/xyz

echo "Finished"


