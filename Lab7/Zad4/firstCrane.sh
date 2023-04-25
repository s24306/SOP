#!/bin/bash

filesMoved=0

moveFile(){
	fileName=$(ls -AU FirstPlace/ | head -1)
  	file="FirstPlace/${fileName}"
  	mv $file Buffer/
  	filesMoved=$((filesMoved+1))
  	echo "First crane has moved $fileName from FirstPlace to Buffer"
}

while : ; do
	if [ "$(ls -AU FirstPlace/)" ]; then
		if [[ $(ls Buffer/ | wc -l) -ge 3 ]]; then
			echo "Buffer full"
		else
			moveFile
		fi
	else
		exit $filesMoved
	fi
done
