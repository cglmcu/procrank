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
