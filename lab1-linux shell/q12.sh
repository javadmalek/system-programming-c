#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "Giving the permission to users: "
umask u+rwx g+rwx o+rwx

echo "Making nested folders: "
mkdir -v $1

cd $1
mkdir -v $2

cd $2
mkdir -v branches tags trunk
