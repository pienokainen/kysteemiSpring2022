#!/bin/bash

echo "Koodia suorittaa $USER"
echo "Ohjelman nimi on $0"
echo "Syötit komentoriviparametreja $# kappaletta"
echo "Nämä parametrit ovat"
printf "%s\n" "$@"
set $(date)
echo "Päivämäärä $*"
