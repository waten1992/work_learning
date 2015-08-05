#!/bin/sh

sed 's/|/ /g' rss.txt  | awk '$4==20140912 && $7==4 {print $6,$9}' > sed_out.txt

exit 0

