/*
 * wait.c
 *
 *  Created on: Sep 19, 2025
 *      Author: ADMIN
 */

#include <stdio.h>

void wait_for_input(void)
{
    printf("\nPress Enter to exit...");
    while (getchar() != '\n');  // clear input buffer
    getchar();                  // wait for Enter
}

