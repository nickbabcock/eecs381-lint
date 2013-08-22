# EECS 381 Style Check

Scripts for vera++ to verify correctness of style for C/C++ code

EECS 381 has a well defined style guidelines for [C][] and [C++][].  Some of the
rules aren't the most intuitive and I won't be able to remember them while
coding. This is the main reason behind this project; to have a series of style
scripts to make sure my code is stylistically correct. By piggy backing off of
vera++, I can use their engine and just write specific rules.

## Installation

Resolving vera++ isn't the easiest of tasks but the following command solved it.
Your mileage may vary.

```bash
sudo apt-get install cmake tcl8.5 tcl8.5-dev tk8.5-dev libboost-all-dev
```

After installing the prerequisites, clone this repo and run `make`.  vera++ will
be in the folder vera/build/src.

## Running

for instance to run vera++ on `main.cpp` in the top level directory with the c
profile execute the following command

```bash
./vera/build/src/vera++ --profile c main.cpp
```

This is not a good idea as there will be many errors as vera++ doesn't
understand raw string literals.

[C]: http://www.umich.edu/~eecs381/handouts/C_Coding_Standards.pdf
[C++]: http://www.umich.edu/~eecs381/handouts/C++_Coding_Standards.pdf