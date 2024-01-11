import argparse
import glob
import os
import signal
import subprocess
try:
    from colorama import Fore, Style, Back
except ImportError:
    print("INFO - If you want colors to easily check test status, run pip install colorama")
    class Fore():  # Create a fake Colorama
        BLUE=""
        GREEN=""
        RED=""
    class Back():
        WHITE=""
    class Style():
        RESET_ALL=""
    
def outPass():
    return Fore.GREEN + Back.WHITE + "Passed!" + Style.RESET_ALL

def outFail():
    return Fore.RED + Back.WHITE + "Failed." + Style.RESET_ALL

def runTests(c):
    for t in sorted(glob.glob(f"bin/{c}/*")):
        try:
            if "user" in t:
                continue
            result = subprocess.run([t, "1", "2", "3"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        except Exception as e:
            print(f"ERROR: Could not run {t} with {c}")
            exit(-1)

        fileName = os.path.basename(t)
        with open("testkeys/" + os.path.splitext(fileName)[0] + ".txt", 'r') as file:
            # Write content to the file
            if file.read() == str(result.stdout):
                if "fail" in fileName:
                    if result.returncode == -signal.SIGSEGV and result.returncode != -signal.SIGIOT:
                        print(t + "."*(40-len(t)) + outFail())
                    else:
                        print(t + "."*(40-len(t)) + outPass())
                else:
                    print(t + "."*(40-len(t)) + outPass())
            else:
                print(t + "."*(40-len(t)) + outFail())

# Note: argparse code below written (mostly) by ChatGPT
def main():
    parser = argparse.ArgumentParser(description='Argument Parser for chibi, aclang, and rclang')

    # Add arguments
    parser.add_argument('args', nargs='*', choices=['aclang', 'rclang'], help='Specify arguments: chibi, aclang, rclang')

    # Parse the arguments
    args = parser.parse_args()

    # Remove duplicates while preserving order
    unique_args = list(dict.fromkeys(args.args))

    for c in unique_args:
        print(f"------{c}------")
        runTests(c)
        print(f"------{c}------")

if __name__ == "__main__":
    main()