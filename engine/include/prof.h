#ifndef __GE_PROF__ 
    
    #define __GE_PROF__

    #include <types.h>

    typedef struct {
        str_t name;
        f64_t elapsed;
        str_t elapsed_string;
    } prof_t;
    
    emp_t ge_start_prof(prof_t * profiler, str_t name);
    emp_t ge_end_prof(prof_t * profiler);


#endif
