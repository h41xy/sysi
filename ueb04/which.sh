#!/usr/local/bin/bash

if [ $# -eq 0 ]; then
echo "usage: $0 [-as] program ..."
exit 1
fi


PFAD=`echo $PATH | tr : " "`

for i in $PFAD
do
if [ -d $i ]; then
OK=$OK" "$i
fi
done

case $1 in
	"-a")
	for i in $OK
	do
		if [ -a $i/$2 ]; then
			echo $i/$2
		fi
	done
	;;
 
	"-s")
	for i in $OK
	do
		if [ -a $i/$2 ]; then
			exit 0 
		fi
	done
	exit 1
	;;

	*)
	for i in $OK
	do
		if [ -a $i/$2 ]; then
			echo $i/$1
		exit 0
		fi
	done
	;;
esac
