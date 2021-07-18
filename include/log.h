#ifndef _COGE_LOGGER

    #define _COGE_LOGGER
    #include <stdio.h>

    #define DEFAULT       "\x1b[0m"

    #define RED           "\x1b[31m"
    #define GREEN         "\x1b[32m"
    #define ORANGE        "\x1b[33m"
    #define BLUE          "\x1b[34m"
    #define PURPLE        "\x1b[35m"
    #define CYAN          "\x1b[36m"
    #define LIGHTGRAY     "\x1b[37m"
    #define BLACK         "\x1b[30m"

    // --- \x1b[0;36m

    #define LIGHTRED      "\x1b[1;31m"
    #define LIGHTGREEN    "\x1b[1;32m"
    #define YELLOW        "\x1b[1;33m"
    #define LIGHTBLUE     "\x1b[1;34m"
    #define LIGHTPURPLE   "\x1b[1;35m"
    #define LIGHTCYAN     "\x1b[1;36m"
    #define LIGHTWHITE    "\x1b[1;37m"

    #define BOLD          "\x1b[1m"
    #define DARKEN        "\x1b[2m"
    #define ITALIC        "\x1b[3m"
    #define UNDERLINE     "\x1b[4m"
    #define BRIGHTEN      "\x1b[1m"

    #define BGCWHITE      "\x1b[47m"
    #define BGCBLACK      "\x1b[40m"
    #define BGCBLUE       "\x1b[44m"
    #define BGCRED        "\x1b[41m"
    #define BGCGREEN      "\x1b[42m"
    #define BGCYELLOW     "\x1b[43m"
    #define BGCPURPLE     "\x1b[45m"
    #define BACKCYAN      "\x1b[46m"

    #define coge_set_output_bg_color(x) printf(x)

    #define coge_log_info(msg, ...) \
	printf("%s", GREEN); \
	printf("INFO: "); \
	printf(msg, __VA_ARGS__); \
	printf("%s", DEFAULT); \
	printf("\n"); 

    #define coge_log_error(msg, ...) \
	printf("%s", RED); \
	printf("ERROR: "); \
	printf(msg, __VA_ARGS__); \
	printf("%s", DEFAULT); \
	printf("\n"); 

    #define coge_log_warning(msg, ...) \
	printf("%s", YELLOW); \
	printf("WARNING: "); \
	printf(msg, __VA_ARGS__); \
	printf("%s", DEFAULT); \
	printf("\n"); 

    #define coge_log_fatal_error(msg, ...) \
	printf("%s", BOLD); \
	printf("%s", RED); \
	printf("FATAL ERROR: "); \
	printf(msg, __VA_ARGS__); \
	printf("%s", DEFAULT); \
	printf("\n"); 

    #define coge_log_important(msg, ...) \
	printf("%s", UNDERLINE); \
	printf("%s", BLUE); \
	printf("IMPORTANT: "); \
	printf(msg, __VA_ARGS__); \
	printf("%s", DEFAULT); \
	printf("\n"); 

#endif
