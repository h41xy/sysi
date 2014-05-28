#!/bin/bash

NAME=`echo $1 | cut -d . -f1`
djpeg -outfile $NAME $1 && pnmtopng $NAME > $NAME.png 
