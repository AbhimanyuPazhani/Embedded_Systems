///*
// * main.c
// *
// *  Created on: 21-Jan-2026
// *      Author: CITI
// */
//
//




#include<stdio.h>

int main (void)
{
    int i,j,rows;

    printf("Enter the number of rows:");
    scanf("%d", &rows);

    for(i=1; i<=rows; i++)
    {


        for(j=1; j<=(i); j++)
        {
            printf("*");
        }
        printf("\n");
    }

    for (i=rows-1; i>=1; i--)
    {


        for (j=1; j<=(i); j++)
        {
            printf("*");
        }
        printf("\n");
    }

    getchar();
    getchar();

}



//Output
//Enter the number of rows:9
//*
//**
//***
//****
//*****
//******
//*******
//********
//*********
//********
//*******
//******
//*****
//****
//***
//**
//*

