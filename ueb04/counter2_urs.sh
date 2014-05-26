#!/bin/bash

# Alle zweier potenzen in einem gegebenen bereich drucken

if [ $# -ne 2 ]
then
  echo "Zwei Zahlen als  Argumente werden boetigt."
  exit 1
fi

x=2

while [[ $x -le $2 ]]
do
  if [[ $x -ge $1 ]]
  then
    echo -n "$x "
  fi
  x=`expr $x \* 2`
done

echo ""
exit 1
