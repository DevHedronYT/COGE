#ifndef _COGE_SHADER
#define _COGE_SHADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include <gl.h>

/* Credits to: https://github.com/templalizer1284/cshader */

unsigned int coge_load_shader(const char *vsFileName, const char *fsFileName);

#endif
