#!/bin/sh -l

echo "Hello, Hello! Let's see if your files have headers. If they doesn't you won't get any credit."
F="NO"
for p in part-1 part-2 part-3; do
  for f in $p/*.cc; do
    python3 .action/headercheck.py $f
    if [ $? -ne 0 ]; then
      echo "Whoa! $f seems to be missing a header! Stopping the check. Please fix."
      F="YES"
      break
    fi
  done
  if [ $F"x" = "YESx" ]; then
    break
  fi
done
