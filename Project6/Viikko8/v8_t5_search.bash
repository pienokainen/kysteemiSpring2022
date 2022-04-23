#!/bin/bash

file_path="/usr/share/man"
if  [ $# -eq 0 ]
then
    echo "usage: search_page command"
    exit 1
elif [ $# -eq 1 ]
then
    find $file_path -type f -name "$1*"
fi
