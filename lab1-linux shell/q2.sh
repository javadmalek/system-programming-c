#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "Making Files and Folsers and entering in Directory a: "
mkdir q2
touch q2/a
touch q2/b
mkdir q2/d

cd q2

echo "Using  umask command for first Time: "
umask u+rw

ls -l

echo "Using  umask command for second Time: "
umask a+rw

ls -l

touch q2/a2
touch q2/b2
mkdir q2/d2

echo "
The result is look like toghather when we applied to directory in second time
"
