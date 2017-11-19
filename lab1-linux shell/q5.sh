#!/bin/bash
# My first script
#S224309 Javad Malek Shahkoohi 

echo "Searching for any things finished by backup: "
find /home/s224309 -name '*backup' -type d -exec mv \{} ./backup \;
