#include <stdlib.h>
#include <str.h>
#include <stdio.h>

i32_t ge_str_length(const str_t str_one) {
    i32_t len;
    for (len = 0; str_one[len] != '\0'; len++);
    return len;
}

i32_t ge_str_compare(const str_t str_one, const str_t str_two) {
    if (ge_str_length(str_one) != ge_str_length(str_two)) {
        return 0;
    }
    
    i32_t i = 0;
    i32_t flag = 0;

    while (str_one[i] != '\0' && str_two[i] != '\0') {
        if (str_one[i] != str_two[i]) {
            flag = 1;
            break;
        }

        i++;
    }

    if (flag == 0 && str_one[i] == '\0' && str_two[i] == '\0') {
        return 1;
    }

    else {
        return 0;
    }
} 
str_t ge_str_concat(const str_t str_one, const str_t str_two) {    
    i32_t size_str_one = ge_str_length(str_one);
    i32_t size_str_two = ge_str_length(str_two);
    str_t new_char = (str_t) malloc(size_str_one + size_str_two + 1);
    
    for (i32_t i = 0; i < size_str_one; i++) {
        new_char[i] = str_one[i];
    }

    for (i32_t i = 0; i < size_str_two; i++) {
        new_char[i + size_str_one] = str_two[i];
    }

    return new_char;
}
i32_t ge_str_starts_with(const str_t str_one, const str_t str_two) {
    i32_t len = ge_str_length(str_two);
    i32_t flag = 0;

    for (i32_t i = 0; i < len; i++) {
        if (str_one[i] != str_two[i]) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) return 1;
    return 0;
}
str_t ge_str_reverse(str_t str_one) {
    i32_t len = ge_str_length(str_one) - 1;
    str_t new_char = (str_t) malloc(len + 1); 
    
    for (i32_t i = 0; i < ge_str_length(str_one); i++) {
        new_char[i] = str_one[len - i];
    }

    return new_char;
}
i32_t ge_str_ends_with(str_t str_one, str_t str_two) {
    str_t new_str = ge_str_reverse(str_one);
    str_t new_str_o = ge_str_reverse(str_two);

    return ge_str_starts_with(new_str, new_str_o);
}
i32_t ge_str_substring(const str_t str_one, const str_t str_two) {
    i32_t i = 0;
    i32_t j = 0;

    while (str_one[j] != '\0' && str_two[i] != '\0') {
        if (str_two[i] != str_one[j]) {
            j++;
            i = 0;
        }

        else {
            i++;
            j++;
        }
    }

    if (str_two[i] == '\0') {
        return 1;
    }

    else {
        return 0;
    }
}
str_t ge_str_split(const str_t str_one, chr_t c) {
    str_t new_char = (str_t) malloc(ge_str_length(str_one));

    for (i32_t i = 0; i < ge_str_length(str_one); i++) {
        if (str_one[i] == c) {
            break;
        }

        new_char[i] = str_one[i];
    }

    return new_char;
}
str_t ge_i32_to_str(i32_t num) {
    str_t string = (str_t) malloc(41); 
    snprintf(string, 39, "%d", num); 
    string[40] = '\0';
    return string;
}
// From: https://github.com/TheAlgorithms/C
i32_t ge_str_to_i32(str_t string) {
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
str_t ge_f64_to_str(f64_t num) {
    str_t string = (str_t) malloc(40); 
    snprintf(string, 39, "%f", num); 
    string[40] = '\0';
    return string;   
}

