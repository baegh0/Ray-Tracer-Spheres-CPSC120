#!/bin/sh -l

TIDYFLAGS="-checks=-*,google-*,modernize-*,readability-*,cppcoreguidelines-*,-google-build-using-namespace,-modernize-use-trailing-return-type,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers"

echo "Hello, Hello! Let's see if you're sticking to the Google C++ Style Guide!"
for p in part-1 part-2 part-3; do
  if [ -r $p/*.cc ]; then
    clang-tidy $p/*.cc $TIDYFLAGS 2>/dev/null
  fi
done
echo "If you don't see any errors or warnings then you're on the right track!"
echo "Did you test your programs thoroughly? Make sure they don't break otherwise you won't get the score you want."
