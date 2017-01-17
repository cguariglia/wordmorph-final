# wordmorph-final

## Overview

Finds the shortest path between two words using Dijkstra's algorithm.

## Usage
```
./wordmorph dictionary.txt problems.txt
```
The dictionary file is a list of words without special characters, separated by newlines or spaces.
The problems file has the following format:
```
[source word] [destination word] [max permutation between words]
```
There can be as many or as few problems in each problem file as you like.

The solutions are written into a separate file, with the same name as the problems file but with .path extension.

