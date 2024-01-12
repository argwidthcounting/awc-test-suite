import subprocess
import re
import sys

awcClangProg = "./bin/benchmark/microbenchmark-aclang"
regClangProg = "./bin/benchmark/microbenchmark-rclang"

awcChibiProg = "./bin/benchmark/microbenchmark-achibicc"
regChibiProg = "./bin/benchmark/microbenchmark-rchibicc"

iterations = 100
tests = [0, 3, 16, 100]

def runBenchmark(prog, num):
    # print(f"{prog} {num}")
    p = subprocess.run(f"{prog} {num}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
    # print(p.stdout, end="")
    return float(re.match(r"([0-9]*\.[0-9]*)", p.stdout).group(0))

def runTests(prog):
    results = {}
    for i in tests:
        vals = []
        # print(f"Running {iterations} iterations of {prog}, size {i}")
        for _ in range(0, iterations):
            vals.append(runBenchmark(prog, i))

        valSum = sum(vals)

        print(f"{prog} ({i}) -- total: {valSum}, iterations:{len(vals)}, average:{valSum/len(vals)}")
        results[i] = (i, valSum, valSum/len(vals)) # num total average
    return results

def confirmAWC(prog):
    try:
        p = subprocess.run(f"{prog} 0 test", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
        if "Test failed, no AWC present" not in p.stdout:
            print("Did not terminate, but also did not get the failure message")
    except subprocess.CalledProcessError:
        return True
    return False

if __name__ == "__main__":
    awcProg = awcClangProg
    regProg = regClangProg
    if len(sys.argv) > 1: # Enable chibi
        if str.lower(sys.argv[1]) == 'c' or str.lower(sys.argv[1]) == 'chibi':
            awcProg = awcChibiProg
            regProg = regChibiProg

    if len(sys.argv) > 2: # Num iterations
        try:
            iterations = int(sys.argv[2])
        except ValueError:
            print(f"Could not run program with '{sys.argv[2]}' iterations, defaulting to {iterations}")
    
    if len(sys.argv) > 3:  # Single test case
        if int(sys.argv[3]) in tests:
            tests = [int(sys.argv[3])]

    if not confirmAWC(awcProg):
        print(f"The awc program {awcProg} did not terminate when running the test arg")
        exit()
    else:
        print(f"{awcProg} confirmed to have AWC")
    if confirmAWC(regProg):
        print(f"The regular program {regProg} did terminate when running the test arg")
        exit()
    else:
        print(f"{regProg} confirmed to not have AWC")

    awcResults = runTests(awcProg)
    regResults = runTests(regProg)

    for i in tests:
        if awcResults[i][0] != regResults[i][0]:
            print("Something wrong; tuple size mismatch.")
            exit(-1)
        awcInMS = awcResults[i][2] * 1000
        regInMS = regResults[i][2] * 1000
        diff = awcInMS - regInMS
        print(f"Comparison Table ({i}) -- \tTotal(ms): {regInMS: 10.5f} \tTotal-AWC(ms): {awcInMS: 10.5f} \tOverhead(ms): {diff: 10.5f} \tOverhead(%): {(diff/regInMS)*100: 10.5f}%")


# ./microbenchmarkAWC confirmed to have AWC
# ./microbenchmarkREG confirmed to not have AWC
# ./microbenchmarkAWC (0) -- total: 2.1579809999999986, length:1000, average:0.0021579809999999985
# ./microbenchmarkAWC (3) -- total: 5.855527999999995, length:1000, average:0.005855527999999995
# ./microbenchmarkAWC (16) -- total: 37.59705799999999, length:1000, average:0.03759705799999999
# ./microbenchmarkAWC (100) -- total: 156.84092599999997, length:1000, average:0.15684092599999996
# ./microbenchmarkREG (0) -- total: 2.153110999999997, length:1000, average:0.002153110999999997
# ./microbenchmarkREG (3) -- total: 4.879603999999995, length:1000, average:0.004879603999999995
# ./microbenchmarkREG (16) -- total: 29.988840999999994, length:1000, average:0.029988840999999995
# ./microbenchmarkREG (100) -- total: 111.05518600000016, length:1000, average:0.11105518600000017
# Comparison Table (0) --         Total(ms):    2.15311   Total-AWC(ms):    2.15798       Overhead(ms):    0.00487        Overhead(%):    0.22618%
# Comparison Table (3) --         Total(ms):    4.87960   Total-AWC(ms):    5.85553       Overhead(ms):    0.97592        Overhead(%):   20.00007%
# Comparison Table (16) --        Total(ms):   29.98884   Total-AWC(ms):   37.59706       Overhead(ms):    7.60822        Overhead(%):   25.37016%
# Comparison Table (100) --       Total(ms):  111.05519   Total-AWC(ms):  156.84093       Overhead(ms):   45.78574        Overhead(%):   41.22792%

# ./microbenchmarkAWC-chibi confirmed to have AWC
# ./microbenchmarkREG-chibi confirmed to not have AWC
# ./microbenchmarkAWC-chibi (0) -- total: 16.54642299999998, length:1000, average:0.01654642299999998
# ./microbenchmarkAWC-chibi (3) -- total: 50.999677999999975, length:1000, average:0.05099967799999997
# ./microbenchmarkAWC-chibi (16) -- total: 239.6025380000002, length:1000, average:0.2396025380000002
# ./microbenchmarkAWC-chibi (100) -- total: 1494.0272409999977, length:1000, average:1.4940272409999977
# ./microbenchmarkREG-chibi (0) -- total: 15.650171000000002, length:1000, average:0.015650171
# ./microbenchmarkREG-chibi (3) -- total: 48.750712000000014, length:1000, average:0.048750712000000015
# ./microbenchmarkREG-chibi (16) -- total: 233.343179, length:1000, average:0.23334317899999998
# ./microbenchmarkREG-chibi (100) -- total: 1490.4128300000007, length:1000, average:1.4904128300000006
# Comparison Table (0) --         Total(ms):   15.65017   Total-AWC(ms):   16.54642       Overhead(ms):    0.89625        Overhead(%):    5.72679%
# Comparison Table (3) --         Total(ms):   48.75071   Total-AWC(ms):   50.99968       Overhead(ms):    2.24897        Overhead(%):    4.61320%
# Comparison Table (16) --        Total(ms):  233.34318   Total-AWC(ms):  239.60254       Overhead(ms):    6.25936        Overhead(%):    2.68247%
# Comparison Table (100) --       Total(ms):  1490.41283  Total-AWC(ms):  1494.02724      Overhead(ms):    3.61441        Overhead(%):    0.24251%