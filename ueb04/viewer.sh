#!/bin/sh

# Dateien anhand von Dateinendung oeffnen

#if [ $# -ne 1 ]
#then
#  echo "Fehler: Brauche >EIN< Argument."
#  exit 1;
#fi

png="PNG*"
jpeg="JPEG*"
bmp="BMP*"


x=`file ~/wallpaper.png`
echo "$x"
echo "${x#PNG*}"
