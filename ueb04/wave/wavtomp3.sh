#!/bin/bash

# Konvertiere eine, EINE .wav Datei in eine .mp3 Datei

# Argumente abfragen
if [ $# -ne 1 ]
then
  echo "Nur eine Datei als Argument angeben."
  exit 1
fi

# Filetyp abfragen
type=`file -b --mime-type "$1"`
if [[ $type != "audio/x-wav" ]]
then
  echo "Die Datei ist keine .wav"
  exit 1
fi

inputFile=$1

ffmpeg -i $inputFile -f mp3 "${inputFile%.*}.mp3"

echo "success"
exit 0
