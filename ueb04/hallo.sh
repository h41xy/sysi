#!/bin/bash

# Setze Hallo vor jedes Argument

for x in $*; do
  echo "Hallo $x"
done
