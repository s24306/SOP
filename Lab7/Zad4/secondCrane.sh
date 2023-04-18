#!/bin/bash

trap end_of_shift SIGUSR2

filesMoved=0

moveFile(){
	fileName=$(ls -AU Buffer/ | head -1)
  	file="Buffer/${fileName}"
  	mv $file SecondPlace/
  	filesMoved=$((filesMoved+1))
}

end_of_shift(){
	echo "End. The Second Crane moved a total of ${filesMoved} files."
	exit 3
}

while : ; do
	if [ "$(ls -AU Buffer/) || $(ps -p $1 > /dev/null)" ]; then
		if [ "$(ls -AU Buffer/)" ]; then
			echo "Crane 2: Not Empty"
			moveFile
		fi
	fi
done
