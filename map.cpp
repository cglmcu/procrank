#include <map>
#include <iostream>
#include <cstdio>
#include "map.h"

int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,char* filename,int checkWhat,int checkContinuousCount,int checkMaxPeakCount)
{
    std::cout << "CHECK_PSS:" << CHECK_PSS << "    " << "CHECK_USS:" << CHECK_USS << std::endl;
    std::cout << "checkWhat:" << checkWhat << std::endl;
    std::cout << "SAVE_OFF:" << SAVE_OFF << "    " << "SAVE_ON:" << SAVE_ON << std::endl;
    if(SAVE_ON == isSave){
        std::cout << "saving filename:" << filename << std::endl;
    }
    return 3;
}
