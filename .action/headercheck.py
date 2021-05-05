#!/usr/bin/env python3

import re
import sys

def main():
  header_re = re.compile(r"(#|/{2}) ([a-zA-Z0-9_-]+) ([a-zA-Z0-9_-]+)\n(#|/{2}) ([a-zA-Z]{4} \d\d\d-\d\d)\n(#|/{2}) \d\d\d\d-\d\d?-\d\d?\n(#|/{2}) (\w+[.-_0-9\w]*@csu\.fullerton\.edu)\n(#|/{2}) @([a-zA-Z\d](?:[a-zA-Z\d]|-(?=[a-zA-Z\d])){0,38})\n(#|/{2})\s*\n(#|/{2}) (Lab \d\d-\d\d)\n(#|/{2})\s*\n(#|/{2}) (\w+.*)\n(#|/{2})")
  if len(sys.argv) < 2:
    print("Not enough args. Exiting.")
    exit(1)
  with open(sys.argv[1]) as fh:
    contents = fh.read()
  matches = re.findall(header_re, contents)
  if len(matches) < 1:
    print("No matches found in {}.".format(sys.argv[1]))
    for i in contents.split('\n')[:10]:
      print("\t{}".format(i))
    exit(1)
  else:
    matches = matches[0]
  #print(matches)
  if len(matches) < 15:
    print("Too few matches in {}.".format(sys.argv[1]))
  else:
    print("{}".format(sys.argv[1]))
    print("Name: {} {}".format(matches[1], matches[2]))
    print("Class: {}".format(matches[4]))
    print("Email: {}".format(matches[7]))
    print("GitHub Handle: {}".format(matches[9]))
    print("Lab: {}".format(matches[12]))
    print("Comment: {}".format(matches[15]))


if __name__ == '__main__':
  main()