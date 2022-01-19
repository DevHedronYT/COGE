#include <extd_cstd/lib.h>

void prof_start(prof_t * profiler, char * name) {
    assert(profiler != NULL && name != NULL);
    profiler -> name = name;
    profiler -> elapsed = 0.0f;
    profiler -> start = clock();
}

void prof_end(prof_t * profiler) {
    assert(profiler != NULL);
    profiler -> end = clock();
    profiler -> elapsed = (f64)(profiler -> end - profiler -> start) / CLOCKS_PER_SEC;
}
