#!/bin/bash

# Expression

if [ $# -ne 2 ]
then
	echo "Brauche 2 Argumente."
	exit 1
fi

result=$((($1*$1*$1*$1*$1-$1)/30+$2))

if [ $? -ne 0 ]
then
	echo "expr resultet in an Error"
	exit $?
fi

echo "$result"
exit 0
