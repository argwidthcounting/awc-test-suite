# Argument Width Counting Test Suite

This repository contains the scripts and programs used to test AWC-enabled Clang.

If you have not already, please see the aclang repository [here](https://github.com/argwidthcounting/awc-clang).

# Building the test files
The [build.sh](./build.sh) bash script will build all of the testing scripts and benchmarking
programs for aclang, rclang, rchibicc, and achibicc. To run the build script, you will
need the load_awc_run_commands.sh file that you received while building aclang.

```bash
# No args will build just awc and assume your load_awc_run_commands.sh file is in your $HOME directory
./build.sh      
# The first arg is the path to your load_awc_run_commands.sh file, builds aclang only
./build.sh ./load_awc_run_commands.sh
# The next two args can be rclang (r) or chibi (c) to build rclang and chibicc in addition to aclang. Order doesn't matter   
./build.sh ./load_awc_run_commands.sh c r  # Build aclang, rclang, and chibicc tests
./build.sh ./load_awc_run_commands.sh r c
./build.sh ./load_awc_run_commands.sh rclang chibi
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

# AWC's Potential Impact on glibc Positional Arguments

For the sake of brevity, the discussion of AWC and glibc positional arguments is included here, rather than the original article. In a past review, it was suggested that positional arguments are 
implemented via pointer arithmetic, and thus AWC would not provide protection to the positional arguments. However, pointer arithmetic is not a possible solution due to how variadic arguments are
stored in non-sequential memory sections, including two different sections for arguments passed by registers (one for floating points and one for general purpose). For a more detailed description of how variadic arguments are retrieved,
please refer to Section 4 of the original article.

The glibc positional arguments are instead implemented by repeatedly calling `va_arg`. This is shown in the following code snippets, taken from the file `glibc-2.39/stdio-common/vfprintf-internal.c` on the latest version at the time of writing, (https://ftp.gnu.org/gnu/glibc/glibc-2.39.tar.gz)[2.39].

```C
// Line 1046
static void
printf_positional (struct Xprintf_buffer * buf, const CHAR_T *format,
		   int readonly_format,
		   va_list ap, va_list *ap_savep, int nspecs_done,
		   const UCHAR_T *lead_str_end,
		   CHAR_T *work_buffer, int save_errno,
		   const char *grouping, THOUSANDS_SEP_T thousands_sep,
		   unsigned int mode_flags)
{

...
// Line 1155
  /* XXX Could do sanity check here: If any element in ARGS_TYPE is
     still zero after this loop, format is invalid.  For now we
     simply use 0 as the value.  */

  /* Fill in the types of all the arguments.  */
  for (cnt = 0; cnt < nspecs; ++cnt)
    {
      /* If the width is determined by an argument this is an int.  */
      if (specs[cnt].width_arg != -1)
	args_type[specs[cnt].width_arg] = PA_INT;

      /* If the precision is determined by an argument this is an int.  */
      if (specs[cnt].prec_arg != -1)
	args_type[specs[cnt].prec_arg] = PA_INT;

      switch (specs[cnt].ndata_args)
	{
	case 0:		/* No arguments.  */
	  break;
	case 1:		/* One argument; we already have the
			   type and size.  */
	  args_type[specs[cnt].data_arg] = specs[cnt].data_arg_type;
	  args_size[specs[cnt].data_arg] = specs[cnt].size;
	  break;
	default:
	  /* We have more than one argument for this format spec.
	     We must call the arginfo function again to determine
	     all the types.  */
	  (void) (*__printf_arginfo_table[specs[cnt].info.spec])
	    (&specs[cnt].info,
	     specs[cnt].ndata_args, &args_type[specs[cnt].data_arg],
	     &args_size[specs[cnt].data_arg]);
	  break;
	}
    }

  /* Now we know all the types and the order.  Fill in the argument
     values.  */
  for (cnt = 0; cnt < nargs; ++cnt)
    switch (args_type[cnt])
      {
#define T(tag, mem, type)				\
	case tag:					\
	  args_value[cnt].mem = va_arg (*ap_savep, type); \
	  break

	T (PA_WCHAR, pa_wchar, wint_t);
      case PA_CHAR:				/* Promoted.  */
      case PA_INT|PA_FLAG_SHORT:		/* Promoted.  */
#if LONG_MAX == INT_MAX
      case PA_INT|PA_FLAG_LONG:
#endif
	T (PA_INT, pa_int, int);
#if LONG_MAX == LONG_LONG_MAX
      case PA_INT|PA_FLAG_LONG:
#endif
	T (PA_INT|PA_FLAG_LONG_LONG, pa_long_long_int, long long int);
#if LONG_MAX != INT_MAX && LONG_MAX != LONG_LONG_MAX
# error "he?"
#endif
      case PA_FLOAT:				/* Promoted.  */
	T (PA_DOUBLE, pa_double, double);
      case PA_DOUBLE|PA_FLAG_LONG_DOUBLE:
	if (__glibc_unlikely ((mode_flags & PRINTF_LDBL_IS_DBL) != 0))
	  {
	    args_value[cnt].pa_double = va_arg (*ap_savep, double);
	    args_type[cnt] &= ~PA_FLAG_LONG_DOUBLE;
	  }
...
```

While this code is quite complex, it primarily consists of two key ideas.  In the function `printf_positional`, the first loop shown
is responsible for determining the type of each argument. As the comment suggests, any unknown arguments are simply assumed to be the
integer value `0`. These types are stored in an array called `args_type`.

The next loop then is responsible for retrieving the arguments. This is done by calling `va_arg` with the "correct" type as listed in 
the `args_type` array. The value is then stored in `args_value` for access later. Thus, the variadic arguments are accessed by 
repeatedly calling `va_arg`.


Finally, as further proof, consider the following code snippet and sample output. 

```C
#include <stdio.h>
int main(){
    printf("%10$d %1$d %11$f %12$f %13$f %14$f %15$f %16$f %17$f %18$f %19$f\n", 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10);
}
//Output on a gcc compiler with glibc: 0 10 1.000000 2.000000 3.000000 4.000000 5.000000 6.000000 7.000000 8.000000 0.000000
```

If a positional argument is requested and the prior argument types are unknown, `printf` will assume those types are `int`. In the following snippet, when `%10$d` is
requested, variadic arguments 1-9 are assumed to be integers. Variadic arguments 1-9 are, however, floating points. The 10th variadic argument, `10`, is the first non-floating point argument and thus is actually stored as the first entry in the 
region of memory allocated for general-purpose variadic arguments. The printf will incorrectly consume this memory region as arguments 1-9 using `va_arg`, and thus prints out-of-bounds stack memory for `%10$d` (which happens to be `0` in this case).

Next, the `%1$d` specifier is processed. The `10`, which should actually be the tenth argument, is printed! As discussed above, this is the result of `va_arg` incorrectly retrieving the first variadic argument from the general-purpose region. 

For the specifiers with args 11-18, the floating-point arguments are stored in the region of memory allocated for variadic arguments passed by a floating-point register. When `%11$f` is processed, this will be the first call to `va_arg` for a floating-point value, and the `1.0` will be retrieved despite this actually being the first variadic argument. Note that we did not need to use 11-19 specifically; requesting any 9 sequential arguments such as 36-44 (e.g., `%36$f`) would have gotten similar results, as these would still be the first time a floating point is requested! 

Finally, for `%19$f`, `va_arg` has now run out of space for arguments passed in floating point registers and performs an out-of-bounds memory access once again (which also happens to be a `0` in this case). 

This out-of-order access is only possible due to the complexities of retrieving arguments using `va_arg`; if simple pointer arithmetic was being used, one would simply expect all of these accesses to result in leaked stack values. 




