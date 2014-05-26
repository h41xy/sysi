#!/bin/bash

# Begruessung zur pasenden tageszeit

echo "`date`"

hour="`date | cut -c 12-13`"

case $hour in
  0[0-3]) echo "Gute Nacht" ;;
  0[4-8]) echo "Guten Morgen" ;;
  09) echo "Guten Tag" ;;
  1[0-8]) echo "Guten Tag" ;;
  19) echo "Guten Abend" ;;
  2[0-3]) echo "Gute Nacht" ;;
  *) echo "Shit, da lief was falsch"
    exit 1
    ;;
esac

exit 0
