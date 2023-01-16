#ifdef __cplusplus
extern "C" {
    void check_set_save_filename(char *filename);
    int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,int checkWhat,int checkContinuousCount,int checkMaxPeakCount);
    void print_memory_leak();
}
#else 
void check_set_save_filename(char *filename);
int check_memory_leak(int pid,int vss,int rss,int pss,int uss,char* cmdline,int isSave,int checkWhat,int checkContinuousCount,int checkMaxPeakCount);
void print_memory_leak();
#endif

enum {
    CHECK_NONE,
    CHECK_USS,
    CHECK_PSS,
    CHECK_FINAL
};
enum {
    OFF,
    ON,
    _FINAL
};
#define DEFAULT_CHECK_CONTINUOUS_COUNT 2
#define DEFAULT_CHECK_MAX_PEAK_COUNT 3
#define DEFAULT_CHECK_WAITING_SECONDS 2
