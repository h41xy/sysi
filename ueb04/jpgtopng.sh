#!/bin/bash

NAME= echo $1 | cut -d . -f 1
djpeg -outfile "$(NAME)" "$1" && pnmtopng "$NAME" > "$(NAME).png" 
