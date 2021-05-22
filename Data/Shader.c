#include "Shader.h"

unsigned int LS(const char * vsFileName, const char * fsFileName) {
    unsigned int vsID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fsID = glCreateShader(GL_FRAGMENT_SHADER);

    FILE * vs = fopen(vsFileName, "r");
    FILE * fs = fopen(fsFileName, "r");

    if (vs == NULL || fs == NULL) {
	printf("One of the shaders is not loaded");
    }

    fseek(vs, 0, SEEK_END);
    long vsize = ftell(vs);
    rewind(vs);

    int vlength = vsize;

    fseek(fs, 0, SEEK_END);
    long fsize = ftell(fs);
    rewind(fs);

    int flength = fsize;


    char * vsCode = malloc(vsize + 1);
    char * fsCode = malloc(fsize + 1);

    int i = 0;
    while (1) {
	if ((vsCode[i] = fgetc(vs)) == EOF) {
	    break;
	}

	i++;

    }

    vsCode[i] = 0;
    fclose(vs);


    i = 0;
    while (1) {

	if ((fsCode[i] = fgetc(fs)) == EOF) {
	    break;
	}

	i++;

    }

    fsCode[i] = 0;
    fclose(fs);

    const char * vsSource = vsCode;
    const char * fsSource = fsCode;

    int result = 0;
    int infoLogLength;

    glShaderSource(vsID, 1, &vsSource, &vlength);
    glCompileShader(vsID);

    glGetShaderiv(vsID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
	char errorMsg[infoLogLength + 1];
	glGetShaderInfoLog(vsID, infoLogLength, NULL, &errorMsg[0]);
	printf("%s\n", &errorMsg[0]);
    }

    glShaderSource(fsID, 1, &fsSource, &flength);
    glCompileShader(fsID);

    glGetShaderiv(fsID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fsID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
	char errorMsg[infoLogLength + 1];
	glGetShaderInfoLog(fsID, infoLogLength, NULL, &errorMsg[0]);
	printf("%s\n", &errorMsg[0]);
    }


	// Link the program
    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vsID);
    glAttachShader(programID, fsID);
    glLinkProgram(programID);

	// Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0){
        char errorMsg[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, &errorMsg[0]);
        printf("%s\n", &errorMsg[0]);
    }


    glDetachShader(programID, vsID);
    glDetachShader(programID, fsID);

    glDeleteShader(vsID);
    glDeleteShader(fsID);

    return programID;
}

