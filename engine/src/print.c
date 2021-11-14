#include <stdio.h>
#include <print.h>
#include <stdarg.h>
#include <time.h>

time_t current_time;
struct tm * m_time; 

emp_t time_print() {
    time(&current_time);
    m_time = localtime(&current_time);
    printf("[%d/%d/%d at %d:%d]: ", 
            m_time -> tm_mday,
            m_time -> tm_mon,
            m_time -> tm_year + 1900,
            m_time -> tm_hour, 
            m_time -> tm_min);
}

emp_t ge_log(const str_t fmt, ...) {
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
    va_end(args);
}

emp_t ge_log_n(const str_t fmt, ...) {
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        printf("\n");
    va_end(args);
}


emp_t ge_log_t(const str_t fmt, ...) {
    time_print(); 
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        printf("\n");
    va_end(args);
}

emp_t ge_log_i(const str_t fmt, ...) {
    printf("%s", GREEN); 
    time_print();
    printf("[INFO]: ");
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
    va_end(args);
    printf("%s", DEFAULT); 
    printf("\n"); 
} 


emp_t ge_log_e(const str_t fmt, ...) {
    printf("%s", RED); 
    time_print();
    printf("[ERROR]: ");
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
    va_end(args);
    printf("%s", DEFAULT); 
    printf("\n"); 
} 

emp_t ge_log_w(const str_t fmt, ...) {
    printf("%s", YELLOW); 
    time_print();
    printf("[WARNING]: ");
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
    va_end(args);
    printf("%s", DEFAULT); 
    printf("\n"); 
}

emp_t ge_log_fe(const str_t fmt, ...) {
    printf("%s", BOLD); 
    printf("%s", RED); 
    time_print();
    printf("[FATAL ERROR]: ");
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
    va_end(args);
    printf("%s", DEFAULT); 
    printf("\n"); 
}

emp_t ge_log_s(const str_t fmt, ...) {
    printf("%s", UNDERLINE); 
    printf("%s", BLUE); 
    time_print();
    printf("[IMPORTANT]: ");
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
    va_end(args);
    printf("%s", DEFAULT); 
    printf("\n"); 
}

