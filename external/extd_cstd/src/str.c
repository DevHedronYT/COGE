#include <extd_cstd/lib.h>

char * i32_to_str(i32 num) {
    char * string = calloc(64, sizeof(char)); 
    assert(string != NULL);
    snprintf(string, 63, "%d", num); 
    string[64] = '\0';
    return string;
}

char * f64_to_str(f64 num) {
    char * string = malloc(64); 
    assert(string != NULL);
    snprintf(string, 39, "%f", num); 
    string[40] = '\0';
    return string;   
}

// From: https://github.com/TheAlgorithms/C
i32 str_to_i32(char * string) {
    int i;
    int sign;
    long value;
    long prev;

    i = 0;
    sign = 1;
    value = 0;

    while (((string[i] <= 13 && string[i] >= 9) || string[i] == 32) && string[i] != '\0')
        i++;

    if (string[i] == '-') {
        sign = -1;
	    i++;
	}

    else if (string[i] == '+') {
        sign = 1;
	    i++;
	}

    while (string[i] >= 48 && string[i] <= 57 && string[i] != '\0') {
        prev = value;
        value = value * 10 + sign * (string[i] - '0');

        if (sign == 1 && prev > value)
            return (-1);
        else if (sign == -1 && prev < value)
            return (0);
        i++;
    }
    return (value); 
}


