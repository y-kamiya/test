#!/bin/bash

extList=$1

# extList file example
# jpg
# png
# mp3
# ...

exts=$(cat extList)

for ext in $exts; do
    git ls-files | grep -e "\.$ext$" >> file_to_rm
done
