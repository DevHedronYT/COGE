#ifndef PROF_H 
    #define PROF_H

    #include "./types.h"
    #include <time.h>

    typedef struct {
        char * name;
        f64 elapsed;
        clock_t start;
        clock_t end;
    } prof_t;
    
    void prof_start(prof_t * profiler, char * name);
    void prof_end  (prof_t * profiler);

#endif
