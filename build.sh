#!/bin/bash

aclangSH="$HOME/load_awc_run_commands.sh"
BUILD_CHIBI=false
BUILD_REG=false

ACLANG="aclang"
REG=""
CHIBI=""
CHIBI_AWC=""

if [ $# -eq 0 ]; then
    echo "Building test files for aclang, assuming load_awc_run_commands.sh in $HOME"
else
    aclangSH="$1"
fi

if [ $# -eq 1 ]; then
    echo "Building test files for aclang using $aclangSH"
else 
    out="aclang"
    for a in $2 $3; do
        if [ "$a" = "chibi" ] || [ "$a" = "c" ]; then
            BUILD_CHIBI=true
            out="$out, achibicc, rchibicc"
            CHIBI="rchibicc"
            CHIBI_AWC="achibicc"
        fi
        if [ "$a" = "reg" ] || [ "$a" = "r" ]; then
            BUILD_REG=true
            out="$out, rclang"
            REG="rclang"
        fi
    done
    echo "Building test files for $out using $aclangSH"
fi

. "$aclangSH"

if ! [ -d "bin" ]; then
    mkdir bin
fi

if ! type 'aclang' 2>/dev/null | grep -q 'function'; then
  echo "Error: To build with aclang, please ensure that $aclangSH contains a rclang function" >&2
  exit 1
fi

if $BUILD_REG && ! $(type 'rclang' 2>/dev/null | grep -q 'function') ; then
  echo "Error: To build with rclang, please ensure that $aclangSH contains a rclang function" >&2
  exit 1
fi

if $BUILD_CHIBI && ! $(type 'achibicc' 2>/dev/null | grep -q 'function') && ! $(type 'rchibicc' 2>/dev/null | grep -q 'function') ; then
  echo "Error: To build with chibicc, please ensure that $aclangSH contains a achibicc and rchibicc function" >&2
  exit 1
fi

cd tests
for compiler in $ACLANG $CHIBI $CHIBI_AWC $REG; do

    if ! [ -d "../bin/$compiler" ]; then
        mkdir "../bin/$compiler"
    fi

    for file in *.c; do 
        if [ "$file" = "dumpVAList-awc.c" ] || [ "$file" = "dumpVAList.c" ] || [ "$file" = "tests.c" ]; then 
            continue # Skip this helper c file
        fi
        name=$(basename $file .c)
        list="dumpVAList.c"
        if [ "$compiler" = "$ACLANG" ] || [ "$compiler" = "$CHIBI_AWC" ]; then
            list="dumpVAList-awc.c"
        fi

        echo "Building $name with $compiler (with debugging enabled)"
        if ! [ "$compiler" = "achibicc" ]; then
            if ! $compiler tests.c "$list" "$file" -g -o "../bin/$compiler/$name" 2>/dev/null; then 
                echo 
                echo "ERROR: Could not compile $name with $compiler"
                exit -1
            fi
        else
            # Chibicc with AWC only supports one .c file
            cat tests.c <(echo) "$list" <(echo) "$file" > "achibicc-temp.c"
            if ! $compiler "achibicc-temp.c" -g -o "../bin/$compiler/$name" 2>/dev/null; then 
                echo 
                echo "ERROR: Could not compile $name with $compiler"
                exit -1
            fi
        fi
    done

    if [ -f "achibicc-temp.c" ]; then
        rm "achibicc-temp.c"
    fi
done

cd ../
echo 
for compiler in $ACLANG $CHIBI $CHIBI_AWC $REG; do
    echo "Building microbenchmark.c with $compiler"

    if ! [ -d "bin/benchmark" ]; then
        mkdir "bin/benchmark"
    fi

    if ! $compiler "benchmark/microbenchmark.c" -o "bin/benchmark/microbenchmark-$compiler" 2>/dev/null; then 
        echo 
        echo "ERROR: Could not compile microbenchmark.c with $compiler"
        exit -1
    fi
done

cd man2html/man-1.6g/man2html
echo 
for compiler in $ACLANG $REG; do
    echo "Building man2html with $compiler"

    if ! $compiler abbrev.c cgibase.c man2html.c strdefs.c -o "../../../bin/benchmark/man2html-$compiler" 2>/dev/null; then 
        echo 
        echo "ERROR: Could not compile man2html with $compiler"
        exit -1
    fi
done