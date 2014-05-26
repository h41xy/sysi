#!/bin/bash

# Druckt alle ganzen Zahlen zwischen zwei gegbenen bereichen

if [ $# -ne 2 ]
then
  echo "Zwei Zahlen werden als Argumente benoetigt."
  exit 1
fi

x=$1

while [[ $x -le $2 ]]
do
  echo -n "$x "
  x=`expr $x + 1`
done
echo ""
exit 0
