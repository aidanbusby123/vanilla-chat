#ifndef ERRORDEBUGMACROS_H_
    #define ERRORDEBUGMACROS_H_

    #include <stdio.h>

    #define ERROR(fmt) do{\
        fprintf(stderr, fmt); printf("\nFILE: %s, LINE %d\n", __FILE__, __LINE__);\
    } while(0)

    #ifdef DEBON
        #define DEBUG(fmt, ...) printf(fmt, __VA_ARGS__)
    #else
        #define DEBUG(fmt, ...) do { } while(0)
    #endif  //DEBON

#endif //ERRORDEBUGMACROS_H_