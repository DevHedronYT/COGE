#include <extd_cstd/lib.h>

time_t current_time;
struct tm * m_time; 

void log_msg(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        printf("\n");
    va_end(args);
}


void log_time(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        time(&current_time);
        m_time = localtime(&current_time);
        printf("[%d/%d/%d -> %d:%d]: ", m_time -> tm_mday,
                                        m_time -> tm_mon,
                                        m_time -> tm_year + 1900,
                                        m_time -> tm_hour, 
                                        m_time -> tm_min); 
        log_msg(fmt, args); 
    va_end(args);
}

void log_info(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        time(&current_time);
        m_time = localtime(&current_time);
        printf("%s", GREEN); 
        printf("[%d/%d/%d -> %d:%d]: ", m_time -> tm_mday,
                                        m_time -> tm_mon,
                                        m_time -> tm_year + 1900,
                                        m_time -> tm_hour, 
                                        m_time -> tm_min); 
        printf("[INFO]: ");
        printf(fmt, args);
        printf("%s", DEFAULT); 
        printf("\n"); 
    
    va_end(args);
} 


void log_err(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        time(&current_time);
        m_time = localtime(&current_time);
        printf("%s", RED); 
        printf("[%d/%d/%d -> %d:%d]: ", m_time -> tm_mday,
                                        m_time -> tm_mon,
                                        m_time -> tm_year + 1900,
                                        m_time -> tm_hour, 
                                        m_time -> tm_min); 
        printf("[ERROR]: ");
        printf(fmt, args);
        printf("%s", DEFAULT); 
        printf("\n"); 
    
    va_end(args);
} 

void log_warn(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        time(&current_time);
        m_time = localtime(&current_time);
        printf("%s", YELLOW); 
        printf("[%d/%d/%d -> %d:%d]: ", m_time -> tm_mday,
                                        m_time -> tm_mon,
                                        m_time -> tm_year + 1900,
                                        m_time -> tm_hour, 
                                        m_time -> tm_min); 
        printf("[WARNING]: ");
        printf(fmt, args);
        printf("%s", DEFAULT); 
        printf("\n"); 
    
    va_end(args);
}

void log_fatal_err(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        time(&current_time);
        m_time = localtime(&current_time);
        printf("%s", BOLD); 
        printf("%s", RED); 
        printf("[%d/%d/%d -> %d:%d]: ", m_time -> tm_mday,
                                        m_time -> tm_mon,
                                        m_time -> tm_year + 1900,
                                        m_time -> tm_hour, 
                                        m_time -> tm_min); 
        printf("[FATAL ERROR]: ");
        printf(fmt, args);
        printf("%s", DEFAULT); 
        printf("\n"); 
    
    va_end(args);   
}

void log_blue(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
        time(&current_time);
        m_time = localtime(&current_time);
        printf("%s", UNDERLINE); 
        printf("%s", BLUE); 
        printf("[%d/%d/%d -> %d:%d]: ", m_time -> tm_mday,
                                        m_time -> tm_mon,
                                        m_time -> tm_year + 1900,
                                        m_time -> tm_hour, 
                                        m_time -> tm_min); 
        printf("[IMPORTANT]: ");
        printf(fmt, args);
        printf("%s", DEFAULT); 
        printf("\n"); 
    
    va_end(args);   
}

