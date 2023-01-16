# procrank
C files and header files are copied from android 7.1, the procrank can both use on linux and android devices,or others.

procrank is a great memory tool, you can get the VSS, RSS, PSS, USS of proc.

# HOWTO
first in your device kernel, you should slect CONFIG_PROC_PAGE_MONITOR=y 
then
```
# download code  
# export CC=your crosscompile
# cd procrank  
# make  
# sudo make install  
# ./procrank
```

# change options
- original
```
Usage: ./procrank [ -W ] [ -v | -r | -p | -u | -s | -h ]
    -v  Sort by VSS.
    -r  Sort by RSS.
    -p  Sort by PSS.
    -u  Sort by USS.
    -s  Sort by swap.
        (Default sort order is PSS.)
    -R  Reverse sort order (default is descending).
    -c  Only show cached (storage backed) pages
    -C  Only show non-cached (ram/swap backed) pages
    -k  Only show pages collapsed by KSM
    -w  Display statistics for working set only.
    -W  Reset working set of all processes.
    -h  Display this help screen.
```

- new design 
    - option u : check USS (default)
    - option p : check PSS
    - option c count : contiguous count when it increase continually  (+1 peak count)
    - option p peakcount : peaked count (if reached , it is memory leak for pid)
    - option r count : repeated period seconds (sleep seconds)
```
Usage: ./procrank [ -p | -u | -c # | -m # | -w # | -h ]
    -u  : Check by USS.(default)
    -p  : Check by PSS.
    -c  Count : contiguous count when it increase continually  (+1 peak count). default 2:
    -m  MaxPeakCount : peaked count (if reached , it is memory leak for pid). default :3
    -w  PeriodicalWaitingSeconds : wating seconds periodically. default :2
    -h  : Display this help screen.
```

# how to run
- make

# database
- map - key : pid
    - current contiguous increasing count : +1 peak count when it reaches -c
    - current peak count : it is memory leak when peak count reaches -m
    - cmdline : to know what has problem
- this function returns result.
    extern C {    }
- can we link between c and c++?
    - https://www.oracle.com/technical-resources/articles/it-infrastructure/mixing-c-and-cplusplus.html

# makefile
- makefile : https://makefiletutorial.com/
- Automatic Variables
    - Automatic variables are set by make after a rule is matched. There include:
    - ```
        $@: the target filename.
        $*: the target filename without the file extension.
        $<: the first prerequisite filename.
        $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
        $+: similar to $^, but includes duplicates.
        $?: the names of all prerequisites that are newer than the target, separated by spaces.
      ```
# example of mixing c and c++ code
- example : prorank.c , map.h , map.cpp
    - ```int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,char* filename,int checkWhat,int checkContinuousCount,int checkMaxPeakCount);```
    - additional option : run command when memory leak happens

# reference
- makefile : https://makefiletutorial.com/
- Mixing C and C++ Code in the Same Program : https://www.oracle.com/technical-resources/articles/it-infrastructure/mixing-c-and-cplusplus.html
- GCC and Make Compiling, Linking and Building C/C++ Applications : https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
- How to mix C and C++ : https://isocpp.org/wiki/faq/mixing-c-and-cpp
    - How do I call a C++ function from C?
- How do I migrate a local git repository to github? : https://stackoverflow.com/questions/56302112/how-do-i-migrate-a-local-git-repository-to-github

