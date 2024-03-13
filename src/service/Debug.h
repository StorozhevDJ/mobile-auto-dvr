#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
    #define LOG      debugLog
#else
    #define LOG(...)
#endif


void debugLog(const char __flash *str);
void debugLog(const char __flash *str, unsigned int n);

#endif

