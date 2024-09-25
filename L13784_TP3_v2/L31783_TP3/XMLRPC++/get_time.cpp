#ifdef _WIN32
#include <windows.h>


int gettimeofday(struct timeval* tp, struct timezone* tzp) {
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (tp) {
        GetSystemTimeAsFileTime(&ft);
        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        tmpres /= 10;  // Convert to microseconds
        tmpres -= 11644473600000000ULL;  // Convert to Unix epoch
        tp->tv_sec = (long)(tmpres / 1000000UL);
        tp->tv_usec = (long)(tmpres % 1000000UL);
    }

    return 0;
}
#endif
