#!/usr/local/bin/bash

if [ $# -eq 0 ]; then
echo "usage: ./which.sh [-as] program ..."
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
find $OK -name $2
;;
"-s")
find $OK -name $2 > /dev/null
;;
*)
find $OK -name $1 | head -n 1 
;;
esac
