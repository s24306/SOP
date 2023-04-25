#!/bin/bash

trap start SIGUSR1
trap stop SIGINT

firstCranePID=0
secondCranePID=0

start() {
  ./firstCrane.sh &
  firstCranePID=$!
  echo "First crane operator has started working"
  ./secondCrane.sh $firstCranePID &
  secondCranePID=$!
  echo "Second crane operator has started working"
  wait $firstCranePID
  firstCraneFiles=$?
  echo "First crane has ended work. It moved $firstCraneFiles files."
  wait $secondCranePID
  secondCraneFiles=$?
  echo "Second crane has ended work. It moved $secondCraneFiles files."
  echo "Work's done."
  exit
}

stop() {
  kill -9 $firstCranePID
  kill -9 $secondCranePID
  echo "All crane operators are dead."
  exit
}

while : ; do
  echo "Supervisor PID is: $$ ;"
  sleep 10
done
