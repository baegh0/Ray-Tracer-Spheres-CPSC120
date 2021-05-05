#!/bin/sh -l

echo "Hello, Hello! Let's see if your programs compile. If they don't you won't get any credit!"
echo "Compiling..."
c=1
for p in part-1 part-2 part-3; do
  if [ -r $p/*.cc ]; then
    set -x
    clang++ -Wall -std=c++14 $p/*.cc -o p$c
    set +x
    if [ $? -ne 0 ]; then
      echo "Whoa! There was an error compiling $p. Stopping the check. Fix it ASAP!"
      break
    fi
  fi
  (( c++ ))
done
echo "If you don't see any errors or warnings then you're on the right track!"
echo "Did you test your programs thoroughly? Make sure they don't break otherwise you won't get the score you want."
