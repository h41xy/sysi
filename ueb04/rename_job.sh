#!/bin/bash

# Rename fileendings

# if there are no files, error gets auto thrown

if [ $# -ne 2 ]
then
  echo ">2< Argumente!"
  exit 1
fi

# toDo: test argument style (dot infront)
#not yet working
#if [ ${1%.*} = "" ]
#then
#  echo "Dateisuffixe beginnen immer mit ."
#  exit 1
#fi

for x in `ls *$1`; do
  mv $x "${x%$1}$2"
done

exit 0
