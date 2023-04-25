#!/bin/bash

trap end_of_shift SIGUSR2

filesMoved=0

moveFile(){
	fileName=$(ls -AU Buffer/ | head -1)
  	file="Buffer/${fileName}"
  	mv $file SecondPlace/
  	filesMoved=$((filesMoved+1))
  	echo "Second crane has moved $fileName from Buffer to SecondPlace"
}

end_of_shift(){
	exit $filesMoved
}

while : ; do
	if [[ "$(ls -AU Buffer/)" || "$([[ -d proc/$1 ]])" ]]; then
		if [ "$(ls -AU Buffer/)" ]; then
			moveFile
		fi
	else
		end_of_shift
	fi
done
