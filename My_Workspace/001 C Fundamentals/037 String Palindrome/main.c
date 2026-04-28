/*
 * main.c
 *
 *  Created on: Apr 28, 2026
 *      Author: CITI
 */


#include <stdio.h>

void wait_for_input(void);

int main() {
    char str[100];
    int i = 0, length = 0, flag = 1;

    printf("Enter a string: ");
    scanf("%s", str);

    // Find length
    while (str[length] != '\0') {
        length++;
    }

    // Check palindrome
    for (i = 0; i < length / 2; i++) {
        if (str[i] != str[length - i - 1]) {
            flag = 0;
            break;
        }
    }

    if (flag == 1)
        printf("Palindrome");
    else
        printf("Not a Palindrome");

    wait_for_input();

}

void wait_for_input()
{
	printf("\nPress ENTER for Exit");
	while (getchar () != '\n');
	getchar();
}


//Output:
//Enter a string: level
//Palindrome
//Press ENTER for Exit
