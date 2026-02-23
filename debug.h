#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif