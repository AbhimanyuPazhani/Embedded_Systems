/*
 * main.c
 *
 *  Created on: Jun 25, 2026
 *      Author: CITI
 */


#include <stdio.h>
#include <stddef.h>

// Function prototype
size_t my_strlen(const char *str);

int main() {
    // Define a few test strings
    const char *string1 = "Hello, World!";
    const char *string2 = "";  // Empty string
    const char *string3 = "Pointers are powerful.";
    const char *string4 = NULL; // Null pointer test

    // Test the function and print the results using %lu (format specifier for size_t)
    // Cast the return value to (unsigned long) and use %lu
        printf("Length of '%s': %lu\n", string1, (unsigned long)my_strlen(string1));
        printf("Length of empty string: %lu\n", (unsigned long)my_strlen(string2));
        printf("Length of '%s': %lu\n", string3, (unsigned long)my_strlen(string3));

    // Testing the NULL pointer safely
        printf("Length of NULL pointer: %lu\n", (unsigned long)my_strlen(string4));

    return 0;
}

// Function definition using only pointers
size_t my_strlen(const char *str) {
    // 1. Safety check: Handle NULL pointers to prevent segmentation faults
    if (str == NULL) {
        return 0;
    }

    // 2. Initialize a traversal pointer to the start of the string
    const char *p = str;

    // 3. Move the pointer forward until it hits the null terminator
    while (*p != '\0') {
        p++;
    }

    // 4. Return the difference between the final memory address and the starting memory address
    return (size_t)(p - str);
}



