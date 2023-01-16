#include <map>
#include <iostream>
#include <cstdio>
#include "map.h"

struct processMem {
    int pid;
    int vss;
    int rss;
    int pss;
    int uss;
    std::string cmdline;
    int isSave;
    int checkWhat;
    int checkContinuousCount;
    int checkMaxPeakCount;
    int currentContinuousCount;
};
static std::map<int,struct processMem> map;
static std::string savefilename;

void check_set_save_filename(char *filename)
{
    savefilename = filename;
}
int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,int checkWhat,int checkContinuousCount,int checkMaxPeakCount)
{
    std::cout << "CHECK_PSS:" << CHECK_PSS << "    " << "CHECK_USS:" << CHECK_USS << std::endl;
    std::cout << "checkWhat:" << checkWhat << std::endl;
    std::cout << "OFF:" << OFF << "    " << "ON:" << ON << std::endl;
    if(ON == isSave){
        std::cout << "saving filename:" << savefilename << std::endl;
    }
    if(auto search = map.find(pid); search == map.end()){       // not found
        std::cout << "not found (now created)" << pid  << " : " << cmdline << std::endl;
        struct processMem p;
        p.pid = pid;
        p.vss = vss;
        p.rss = rss;
        p.pss = pss;
        p.uss = uss;
        p.cmdline = cmdline;
        p.isSave = isSave;
        p.checkWhat = checkWhat;
        p.checkContinuousCount = checkContinuousCount;
        p.checkMaxPeakCount = checkMaxPeakCount;
        p.currentContinuousCount = 0;
        map.insert(std::make_pair(pid,p));
    } 
    else {
        map[pid].pid = pid;
        map[pid].vss += vss;
        map[pid].rss += rss;
        map[pid].pss += pss;
        map[pid].uss += uss;
        map[pid].currentContinuousCount += 1;
    }
    return 1;
}
void print_memory_leak()
{
    std::cout << "print_memory_leak():" << std::endl;
    for (auto it=map.begin(); it!=map.end(); ++it){
        std::cout << "    " << it->first << " => " << it->second.uss << "  " << it->second.currentContinuousCount << "    " << it->second.cmdline << std::endl;
    }
}
