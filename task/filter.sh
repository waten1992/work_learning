#!/bin/sh
echo $1
grep  "$1" rss.txt  | sed 's/|/ /g' | awk '{print $6 ,$9}' >out.txt
exit 0
