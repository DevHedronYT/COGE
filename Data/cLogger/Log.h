#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

#define SetBGC(x) printf(x)

// 3 Ways:
// 	Dynamically Allocate Memory
// 	Pre-Allocated Memory
// 	Pass in pointer
// 	Pass in array


void cConcatenate(char * msg, char * append, char * st) {
    for (int i = 0; i < strlen(msg) + strlen(append) + 2; i++) {
	st[i] = '\0';
    }

    strcat(st, msg);
    strcat(st, append);

}

char * Concatenate(char * msg, char * append) {
    const char * spc = " ";
    char newS[strlen(msg) + strlen(spc) + strlen(append) + 1];
    for (int i = 0; i < strlen(msg) + strlen(spc) + strlen(append) + 1; i++) {
	newS[i] = '\0';
    }

    strcat(newS, msg);
    strcat(newS, spc);
    strcat(newS, append);
    char * r = &newS;
    return r;
}

char * IntToStr(int x) {
    char s[21];
    sprintf(s, "%d", x);
    char * l = &s;
    return l;
} // DON'T USE UNLESS THE FUNCTION WILL ONLY BE CALLED ONCE AS OTHER FUNCTIONS MAY CHANGE THE STRING RETURNED BY THIS FUNCTION

char * FloatToStr(float x) {
    char s[21];
    sprintf(s, "%f", x);
    char * l = &s;
    return l;
}


int LogMsg(const char * msg, const char * color, int nLine) {
    printf("%s%s%s", color, msg, DEFAULT);
    if (nLine) printf("\n");
    return 1;
}


int LogBoldMsg(const char * msg, const char * color, int nLine) {
    printf("%s%s%s%s", BOLD, color, msg, DEFAULT);
    if (nLine) printf("\n");
    return 1;
}

int LogUnderlinedMsg(const char * msg, const char * color, int nLine) {
    printf("%s%s%s%s", UNDERLINE, color, msg, DEFAULT);
    if (nLine) printf("\n");
    return 1;
}

#define LogInfo(...) LogMsg(__VA_ARGS__, GREEN, 1);
#define LogError(...) LogMsg(__VA_ARGS__, RED, 1);
#define LogWarn(...) LogMsg(__VA_ARGS__, YELLOW, 1);
#define LogFatal(...) LogBoldMsg(__VA_ARGS__, RED, 1);
#define LogImportant(...) LogUnderlinedMsg(__VA_ARGS__, RED, 1);
