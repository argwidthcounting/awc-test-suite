import os
import subprocess
import re
import sys

awcProg = "./bin/benchmark/man2html-aclang"
regProg = "./bin/benchmark/man2html-rclang"

iterations = 100

manDir = "manfiles/"
tests = ["rbash.1", "modify_ldt.2", "dpkg-buildpackage.1", "x86_64-linux-gnu-gcc.1"]

def runBenchmark(prog, file):
    # print(f"Running {prog}, file {file}")
    p = subprocess.run(f"./timer.sh {prog} ./{manDir}{file}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
    time = p.stdout.split("\n")[-1]
    return float(re.search(r"([0-9]*\.[0-9]*)", time).group(0))
    

def runTests(prog):
    results = {}
    for i in tests:
        vals = []
        # print(f"Running {iterations} iterations of {prog}, size {i}")
        for _ in range(0, iterations):
            vals.append(runBenchmark(prog, i))

        valSum = sum(vals)

        print(f"{prog} ({i:<22}) -- total: {valSum}, iterations:{len(vals)}, average:{valSum/len(vals)}")
        results[i] = (i, valSum, valSum/len(vals)) # num total average
    return results

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            iterations = int(sys.argv[1])
        except ValueError:
            print(f"Could not run program with '{sys.argv[1]}' iterations, defaulting to {iterations}")


    if not os.path.exists(awcProg):
        print(f"{awcProg} does not exist. Did you run build.sh?")
        exit(-1)

    if not os.path.exists(regProg):
        print(f"{regProg} does not exist but {awcProg} does. Only running benchmark for aclang.")
        awcResults = runTests(awcProg)

        for i in tests:
            awcInMS = awcResults[i][2] * 1000
            print(f"Result Table ({i:<22}) -- \tTotal-AWC(ms): {awcInMS: 10.5f}")
    else:
        awcResults = runTests(awcProg)
        regResults = runTests(regProg)

        for i in tests:
            if awcResults[i][0] != regResults[i][0]:
                print("Something wrong; tuple size mismatch.")
                exit(-1)
            awcInMS = awcResults[i][2] * 1000
            regInMS = regResults[i][2] * 1000
            diff = awcInMS - regInMS
            print(f"Result Table ({i:<22}) -- \tTotal(ms): {regInMS: 10.5f} \tTotal-AWC(ms): {awcInMS: 10.5f} \tOverhead(ms): {diff: 10.5f} \tOverhead(%): {(diff/regInMS)*100: 10.5f}%")

# ./man2html-awc (rbash.1               ) -- total: 11.660805000000032, length:10000, average:0.001166080500000003
# ./man2html-awc (modify_ldt.2          ) -- total: 13.292638000000073, length:10000, average:0.0013292638000000072
# ./man2html-awc (dpkg-buildpackage.1   ) -- total: 18.04655900000001, length:10000, average:0.001804655900000001
# ./man2html-awc (x86_64-linux-gnu-gcc.1) -- total: 318.170555999999, length:10000, average:0.0318170555999999
# ./man2html-reg (rbash.1               ) -- total: 12.059723999999978, length:10000, average:0.0012059723999999978
# ./man2html-reg (modify_ldt.2          ) -- total: 13.265176999999985, length:10000, average:0.0013265176999999984
# ./man2html-reg (dpkg-buildpackage.1   ) -- total: 18.092928000000086, length:10000, average:0.0018092928000000086
# ./man2html-reg (x86_64-linux-gnu-gcc.1) -- total: 317.6015920000007, length:10000, average:0.031760159200000075
# Result Table (rbash.1               ) --   Total(ms):    1.20597   Total-AWC(ms):    1.16608       Overhead(ms):   -0.03989        Overhead(%):   -3.30786%
# Result Table (modify_ldt.2          ) --   Total(ms):    1.32652   Total-AWC(ms):    1.32926       Overhead(ms):    0.00275        Overhead(%):    0.20702%
# Result Table (dpkg-buildpackage.1   ) --   Total(ms):    1.80929   Total-AWC(ms):    1.80466       Overhead(ms):   -0.00464        Overhead(%):   -0.25628%
# Result Table (x86_64-linux-gnu-gcc.1) --   Total(ms):   31.76016   Total-AWC(ms):   31.81706       Overhead(ms):    0.05690        Overhead(%):    0.17914%