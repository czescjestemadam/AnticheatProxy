#!/bin/fish

cat (fd -tf . src/) | wc
