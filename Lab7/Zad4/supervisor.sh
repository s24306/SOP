#!/bin/bash

trap start SIGUSR1
trap stop SIGINT
trap check_child_exit_code SIGCHLD

firstCranePID=0
secondCranePID=0

start() {
  ./firstCrane.sh &
  firstCranePID=$!
  ./secondCrane.sh $firstCranePID &
  secondCranePID=$!
}

stop() {
  kill -9 $firstCranePID
  kill -9 $secondCranePID
  echo "All crane operators are dead."
  exit
}

check_child_exit_code() {
	CODE=$?
	echo $CODE
	if [[ $CODE -eq 0 ]];then
		sleep 2
		echo "Supervisor: First crane ended work"
		kill -SIGUSR2 $secondCranePID
		wait $secondCranePID
		echo "Supervisor: Second crane ended work"
		exit
	fi
}

while : ; do
  echo "Moj PID to: $$ ;"
  sleep 10
done
