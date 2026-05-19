/*
 * main.c
 *
 *  Created on: May 19, 2026
 *      Author: CITI
 */

#include<stdio.h>

void wait_for_input(void);
struct student{
	int roll;
	char name[20];
	float marks;
};

int main()
{
	struct student s1 = {2214201, "Abhimanyu", 7.79};
	struct student *ptr;
	ptr = &s1;


	printf("Student details\n");
	printf("Roll Number: %d\n", ptr-> roll);
	printf("Student name: %s\n", ptr->name);
	printf("Student marks: %lf\n", ptr-> marks);

	wait_for_input();
}
void wait_for_input(void)
{
	printf("Press ENTER for Exit\n");
	while(getchar()!='\n');
	getchar();

}
