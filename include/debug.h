#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
#include <stdlib.h>

#define _alert(message, ...) { \
    fprintf(stdout, "Alert in file: %s, line: %d!\n" message "\n", \
            __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define _error(message, ...) { \
    fprintf(stderr, "Error in file: %s, line: %d!\n" message "\n", \
            __FILE__, __LINE__, ##__VA_ARGS__); \
    exit(1); \
}

#endif 
