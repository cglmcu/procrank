#ifdef __cplusplus
extern "C" {
    int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,char* filename,int checkWhat,int checkContinuousCount,int checkMaxPeakCount);
}
#else 
int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,char* filename,int checkWhat,int checkContinuousCount,int checkMaxPeakCount);
#endif

enum {
    CHECK_NONE,
    CHECK_USS,
    CHECK_PSS,
    CHECK_FINAL
};
enum {
    SAVE_OFF,
    SAVE_ON,
    SAVE_FINAL
};
#define DEFAULT_CHECK_CONTINUOUS_COUNT 2
#define DEFAULT_CHECK_MAX_PEAK_COUNT 3
#define DEFAULT_CHECK_WAITING_SECONDS 2
