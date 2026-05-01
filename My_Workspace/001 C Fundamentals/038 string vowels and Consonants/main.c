/*
 * main.c
 *
 *  Created on: May 1, 2026
 *      Author: CITI
 */


#include <stdio.h>

void wait_for_input(void);
int main()
{
    char str[100];
    int i=0,vowels=0,consonents=0;

    printf("Enter the string:");
    scanf("%s", str);


    while (str[i] !='\0')
    {
      char  ch = str[i];

        if ((ch >='a' && ch<='z') || (ch>='A' && ch<='Z'))
        {
            if( ch=='a'|| ch=='e'||ch=='i'||ch=='o'||ch=='u'||ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U')
            {
                vowels++;
            }
            else
            {
                consonents++;
            }
        }
        i++;
    }
    printf("Vowels: %d \nConsonents: %d", vowels, consonents);
    wait_for_input();

}

void wait_for_input()
{
	printf("\nPress ENTER for EXIT");

	while (getchar()!='\n');
	getchar();
}

//Output:
//Enter the string:Abhimanyu
//Vowels: 4
//Consonents: 5
//Press ENTER for EXIT
