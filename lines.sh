#!/bin/fish

echo -n "files: "
fd -tf . src/ | wc -l

echo -n "source files: "
fd -tf . src/ -e cc | wc -l

echo -n "header files: "
fd -tf . src/ -e hh | wc -l
echo

echo "lines words chars"
cat (fd -tf . src/) | wc
