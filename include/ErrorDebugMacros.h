#ifndef ERRORDEBUGMACROS_H_
    #define ERRORDEBUGMACROS_H_

#include <stdio.h>

#define ERROR(fmt)\
    fprintf(stderr, fmt);\
    printf("\nFILE: %s, LINE %d\n", __FILE__, __LINE__);

#endif //ERRORDEBUGMACROS_H_