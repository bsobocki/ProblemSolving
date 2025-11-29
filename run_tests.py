from os import listdir
import os.path as path
import re
import subprocess
import sys

setGreen = "\033[32m"
setRed = "\033[31m"
endColor = "\033[m"

success_emoji= setGreen + "✓" + endColor
fail_emoji= setRed + "✗" + endColor

solutionDirRegex = "[0-9]+_.+"
solutionsRootDir = "./solutions"

def isSolutionDir(entry):
    solutionDir = solutionsRootDir + "/" + entry
    return path.isdir(solutionDir) and re.match(solutionDirRegex, entry)

def isTestNumberOprton(opt):
    return re.match("--test=[0-9]+", opt)

allSolutionDirs = list(filter(isSolutionDir, listdir(solutionsRootDir)))
solutionDirNames = []

if len(sys.argv) > 1:
    arg = sys.argv[1]

    if isTestNumberOprton(arg):
        solutionNumSearchResult = re.search('\\d+', arg)
        if solutionNumSearchResult:
            num = int(solutionNumSearchResult.group())
            solutionDirNames = list(filter(lambda solDir: re.match(f'{num}_.*', solDir), allSolutionDirs))

    elif isSolutionDir(arg):
        solutionDirNames = [arg]

if not solutionDirNames:
    solutionDirNames = allSolutionDirs

print("Cleaning old files..")
subprocess.run(['make', 'clean'])
print("")

print("Solutions:")
print("----------")
print('\n'.join(solutionDirNames))
print("----------\n")

for solutionDirName in solutionDirNames:
    solutionDir = solutionsRootDir + "/" + solutionDirName
    try:
        print(f"Trying to call 'make compile {solutionDir}'..")
        subprocess.run(['make', 'compile', solutionDir], 
                    check=True,  # Raises exception on non-zero exit
                    capture_output=True, 
                    text=True)
        print(f"{success_emoji} {solutionDir} compiled successfully\n")
    except subprocess.CalledProcessError as e:
        print(f"{fail_emoji} {solutionDir} failed: {e.stderr}\n")

for solutionDirName in solutionDirNames:
    solutionDir = solutionsRootDir + "/" + solutionDirName
    try:
        print(f"Trying to call 'make run {solutionDir}'..\n")
        result = subprocess.run(['make', 'run', solutionDir], 
                    check=True,  # Raises exception on non-zero exit
                    capture_output=True, 
                    text=True)
        print(result.stdout)
        print(f"{success_emoji} {solutionDir} run successfully\n")
    except subprocess.CalledProcessError as e:
        print(f"{fail_emoji} {solutionDir} failed: {e.stderr}\n")
        
    print("----------------------------------------------\n")