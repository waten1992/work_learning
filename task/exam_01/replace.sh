#!/bin/sh

if [ $# -ne 2 ] 
then
	echo "argc not equal 2"
	exit 126;
fi
 
find ./ -name '*.c' -print |xargs  grep -w -n $1 | sed -n "s/"$1"/"$2"/gp"

find ./ -name '*.h' -print |xargs  grep -w -n $1 | sed -n "s/"$1"/"$2"/gp"

exit 0
