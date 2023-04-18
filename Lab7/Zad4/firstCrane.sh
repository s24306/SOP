#!/bin/bash

filesMoved=0

moveFile(){
	fileName=$(ls -AU FirstPlace/ | head -1)
  	file="FirstPlace/${fileName}"
  	mv $file Buffer/
  	filesMoved=$((filesMoved+1))
}

while : ; do
	if [ "$(ls -AU FirstPlace/)" ]; then
		echo "Not Empty"
		if [[ $(ls Buffer/ | wc -l) -ge 3 ]]; then
			echo "Buffer full"
		else
			moveFile
		fi
	else
		echo "Empty. The First Crane moved a total of ${filesMoved} files."
		exit 2
	fi
done
