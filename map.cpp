#include <map>
#include <iostream>
#include <cstdio>
#include "map.h"
#include <fstream>

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
    int currentPeakCount;
    int currentContinuousCount;
    int checkPeakestValue;
};
static std::map<int,struct processMem> map;
static std::string savefilename;

void check_set_save_filename(char *filename)
{
    savefilename = filename;
}
int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,int checkWhat,int checkContinuousCount,int checkMaxPeakCount,int debug)
{
    if(debug){
        std::cout << "CHECK_PSS:" << CHECK_PSS << "    " << "CHECK_USS:" << CHECK_USS << std::endl;
        std::cout << "checkWhat:" << checkWhat << std::endl;
        std::cout << "OFF:" << OFF << "    " << "ON:" << ON << std::endl;
        if(ON == isSave){
            std::cout << "saving filename:" << savefilename << std::endl;
        }
    }
    if(auto search = map.find(pid); search == map.end()){       // not found
        if(debug) std::cout << "not found (now created)" << pid  << " : " << cmdline << std::endl;
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
        p.currentPeakCount = 0;
        p.currentContinuousCount = 1;
        int n;
        if(checkWhat == CHECK_PSS){
            n = pss;
        } else {
            n = uss;
        }
        p.checkPeakestValue = n;
        map.insert(std::make_pair(pid,p));
    } 
    else {
        int o,n;
        if(checkWhat == CHECK_PSS){
            o = map[pid].pss;
            n = pss;
        } else {
            o = map[pid].uss;
            n = uss;
        }
        if(o < n){
            map[pid].currentContinuousCount += 1;
        } else if(o > n){
            map[pid].currentContinuousCount = 0;
        }
        map[pid].pid = pid;
        map[pid].vss = vss;
        map[pid].rss = rss;
        map[pid].pss = pss;
        map[pid].uss = uss;
        if((map[pid].currentContinuousCount >= map[pid].checkContinuousCount) && (map[pid].checkPeakestValue < n)){
            map[pid].currentPeakCount += 1;
            map[pid].currentContinuousCount = 0;
        }
        if(map[pid].checkPeakestValue < n){
            map[pid].checkPeakestValue = n;
        }
    }
    if(map[pid].cmdline.find("procrank") != std::string::npos){
        return 0;
    }
    if(map[pid].currentPeakCount >= map[pid].checkMaxPeakCount){
        return 1;
    }
    return 0;
}
void print_memory_leak(int checkWhat,int isSave,char* filename,int wait_count)
{
    std::cout << "print_memory_leak():" << std::endl;
    for (auto it=map.begin(); it!=map.end(); ++it){
        std::cout << "    " << it->first << " => ";
        if(it->second.checkWhat == CHECK_PSS){
            std::cout << it->second.pss;
        } else {
            std::cout << it->second.uss;
        }
        std::cout << "  Con:" << it->second.currentContinuousCount;
        std::cout << "  Peak:" << it->second.currentPeakCount;
        std::cout << "  cmd:" << it->second.cmdline << std::endl;
    }
    if(isSave == ON){
        std::ofstream file;
        file.open(filename, std::ios_base::app);
        if(checkWhat == CHECK_PSS){
            file << "PSS wait_count:" << wait_count << std::endl;
        } else {
            file << "USS wait_count:" << wait_count << std::endl;
        }
        for (auto it=map.begin(); it!=map.end(); ++it){
            file << it->first << ":" ;
            if(it->second.checkWhat == CHECK_PSS){
                file << it->second.pss << std::endl;
            } else {
                file << it->second.uss << std::endl;
            }
        }
    }
}
