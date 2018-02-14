# EECS 381 Lint

Hello intrepid University of Michigan student!

You're taking EECS 381 - Object-Oriented and Advanced Programming and heard
there are style guidelines for [C][] and [C++][]. Most of the guidelines make
sense and are easy to keep in the back of your mind, but even I slip up and
forget occasionally. This repo is here to help.

By taking advantage of the [clang](https://en.wikipedia.org/wiki/Clang)
compiler's deep knowledge of C/C++ files we can create robust patterns to match
on code that isn't as error prone as regular expressions and tokenizing C code
yourself. This repo adds checks to
[`clang-tidy`](http://clang.llvm.org/extra/clang-tidy/) to run against your
code.

If you take away one thing from this repo -- even if you don't use this repo --
use clang-tidy! 

## Getting Started

Writing plugins for clang-tidy, unfortunately means you need to compile the
whole clang toolchain, which requires a relatively beefy machine (8GB RAM and
5GB disk free). To make compilation reasonable, we're using the gold linker
(which is in your development tools already if you are on a recent version of
Ubuntu) and doing a release build so that all the debug symbols aren't included
(which will take up 50GB+ of space)

```bash
git clone --recursive https://github.com/nickbabcock/eecs381-lint
cd eecs381-lint

# LLVM is large, so to keep all of the subprojects manageable, we recreate the mono-repo by linking clang and clang-tidy appropriately.
ln -s clang-tools-extra clang/tools/extra
ln -s clang llvm/tools/.
mkdir -p eecs381-lint/build
cd eecs381-lint/build
cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
               -DLLVM_PARALLEL_LINK_JOBS=1 \
               -DLLVM_USE_LINKER=gold \
               -DCMAKE_BUILD_TYPE=Release \
               ../llvm

ninja check-clang-tools
# And now we wait awhile.
# Our clang-tidy executable is in bin/clang-tidy
```

## History

The first implementation, written in 2013, was a plugin written for
[vera++](https://bitbucket.org/verateam/vera/overview), which parses C/C++ code
and hands tokens to Tcl scripts written by you.  As a first implementation this
is fine, but I believe one is limited in the confidence of the solution as they
aren't handed a deep and rich AST that can be interrogated. It's a step above
regular expressions, but still far from ideal. Tcl is also an odd choice -- not
that it is the wrong choice, but in all my time this has been the only codebase
that I've written Tcl and it didn't leave a great impression.

Maybe the best reason for migrating away from vera is that it's simply not as
well supported as `clang-tidy`. The last commit for vera was in the first half
of 2016. Clang tidy receives updates weekly if not daily. There is a difference
between mature software that is stable and doesn't receive updates and projects
where the maintainers have moved on. For instance, vera doesn't understand much
of C++11 syntax, and thus will be confused when parsing modern C++ files.

[C]: http://www.umich.edu/~eecs381/handouts/C_Coding_Standards.pdf
[C++]: http://www.umich.edu/~eecs381/handouts/C++_Coding_Standards.pdf

## Checks

### Typedef end in `_t`

```cpp
struct Point {
    int x;
    int y;
};

typedef struct Point Point_t;

typedef struct Point Pointed;

typedef struct Thing {
   int cheese;
} Thing;

typedef struct Book {
   int author;
} Book_t;
```

Results in the following errors:

```
misc-eecs-typedef-t.cpp:10:22: warning: typedefs must end in `_t` ('Pointed') [misc-eecs-typedef-t]
typedef struct Point Pointed;
                     ^
misc-eecs-typedef-t.cpp:15:3: warning: typedefs must end in `_t` ('Thing') [misc-eecs-typedef-t]
} Thing;
  ^
```
