#include "Log.h"

int main(void) {
    // LogMsg("Works!", GREEN, 1);
    LogInfo("Hello, World!");
    LogError("Lets gooo..Lets gooo....");
    LogWarn("bruh...");
    LogFatal("nonono");
    char * msg = "heello, world";
    char * spc = " ";
    char * append = "cConcatenateion works//";
    char st[strlen(msg) + strlen(spc) + strlen(append) + 1];
    cConcatenate(msg, append, st);
    LogImportant(Concatenate("lol", st));
}
// Logging library that works on all ANSI supporting terminals, good for logging errors..
