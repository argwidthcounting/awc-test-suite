# Argument Width Counting Test Suite

This repository contains the scripts and programs used to test AWC-enabled Clang.

If you have not already, please see the aclang repository [here](https://github.com/argwidthcounting/awc-clang).

# Building the test files
The [build.sh](./build.sh) bash script will build all of the testing scripts and benchmarking
programs for aclang, rclang, chibicc-reg, and chibicc-awc. To run the build script, you will
need the load_aclang.sh file that you received while building aclang.

```bash
# No args will build just awc and assume your load_aclang.sh file is in your $HOME directory
./build.sh      
# The first arg is the path to your load_aclang.sh file, builds aclang only
./build.sh ./load_aclang.sh
# The next two args can be rclang (r) or chibi (c) to build rclang and chibicc in addition to aclang. Order doesn't matter   
./build.sh ./load_aclang.sh c r  # Build aclang, rclang, and chibicc tests
./build.sh ./load_aclang.sh r c
./build.sh ./load_aclang.sh rclang chibi
```

When run, build.sh will compile all of the files under [tests](./tests/) with each specified compiler.
The resulting executable will be output to "bin/{compiler}/{testname}"; for example, 
"bin/aclang/alternateDoubleInt".

The tests with "fail" in the name call va_arg too many times, while those with "user" in the name
take user input (these two files are not included in the python testing script).

Each test file contains a brief description of its purpose as a comment at the beginning of the file.

The tests also include "dumpVAList-awc.c" and "dumpVAList.c" with a helper function to print all
of the values in a va_list. These are output to stderr so you can track how the va_list
are modified as the program executes. The awc version includes the added remaining variable.

If you do not want to see the va_list information when running, you can use redirection. For example,

```bash
./bin/aclang/passStrings_ROTS 2>/dev/null
```

The expected results of each test can be found under [./testkeys/](./testkeys/).  For each test program,
there is a {test}.txt and a {test}-arglist.txt file. The {test}.txt file contains the expected normal 
output that is printed to stdout. You can compare this to the output of the test to ensure it working
correctly.

The {test}-arglist.txt files contain the va_list output that was printed to stderr during a run.
While this cannot be used for comparison easily, as the values of the pointers will change,  
it can be useful if you make changes to aclang and want to compare the output va_lists to a working 
implementation.

All of the benchmarking programs will also be built, and stored under "bin/benchmark".

# runTests.py

The [runTests.py](./runTests.py) python script will run all of the test files and compare them
to the expected results under [./testkeys/](./testkeys/).

```bash
# The script takes 1 or 2 arguments with the compiler version you'd like to use
python3 ./runTests.py aclang  # Run the tests for aclang
python3 ./runTests.py rclang  # Run the tests for rclang
python3 ./runTests.py aclang rclang  # Run the tests for both
```

If you have colorama installed (pip install colorama), the results will be printed with color
to help quickly determine which files failed or passed.

# Benchmark

The benchmarking executables can be run using [runMan.py](./runMan.py) and [runMicro.py](./runMicro.py)
python scripts.

The runMicro.py scripts runs the [microbenchmark program](./benchmark/microbenchmark.c).

```bash
# The script takes 2 optional argument: aclang or chibicc, and # of iterations
python3 ./runMicro.py  # Run the microbenchmark on aclang and rclang with 100 iterations
python3 ./runMicro.py c # Run the microbenchmark on the chibicc awc and regular versions
python3 ./runMicro.py a 1000 # Run the microbenchmark on aclang and rclang with 1000 iterations
```

The runMan.py script runs man2html on the man pages found under [./manfiles](./manfiles).
```bash
# The script takes only 1 optional argument # of iterations
python3 ./runMan.py  # Run man2html on aclang and rclang with 100 iterations
python3 ./runMan.py 1000 # Run man2html on aclang and rclang with 1000 iteration
```

The source code for the version of man2html used is included under [./man2html](./man2html/). 
The man2html code was originally downloaded from this [debian snapshot](http://snapshot.debian.org/archive/debian/20110109T212222Z/pool/main/m/man2html) [(direct link to source tar)](http://snapshot.debian.org/archive/debian/20110109T212222Z/pool/main/m/man2html/man2html_1.6g.orig.tar.gz). This was included directly rather than just linking for posterity; such links are prone to being unreliable over time.

Since Chibicc does not implement a full stdlib,
it does not make sense to compile man2html with chibicc for macrobenchmarking. 

### Odd Edge Case with rclang
I noticed a weird edge case with rclang on the test [struct_100args.c](./tests/struct_100args.c). The 
double addition sometimes results in a NAN result. This seems to have a faily common chance of 
happening (I'd wager about 10% of the time). Notably, I did not witness this even once with aclang. 
