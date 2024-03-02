#include <stdio.h> 
#include <stdlib.h>
#include <time.h>



void PrintPole(char MatrixA[10][10], char MatrixB[10][10]);  // funcrion print pole igry on display


void main()              
 {                                 
    
    
    char A[10][10]; // computer
    char* addrA = (char*)A;

    char B[10][10]; // person
    char* addrB = (char*)B;

    // initial pole
    for (int i = 0; i < 100; i++)
        *(addrA + i) = ' ';


    for (int i = 0; i < 100; i++)
        *(addrB + i) = ' ';

    
    PrintPole(A, B);

    





}

void PrintPole(char A[10][10], char B[10][10])
{
    printf("                                                   \n");
    printf("        computer                      person       \n                                                      \n");
    printf("    0 1 2 3 4 5 6 7 8 9         0 1 2 3 4 5 6 7 8 9 \n  +--------------------+      +--------------------+ \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%c |", (char)(i + 65));
        for (int j = 0; j < 10; j++)
        {

            if (A[i][j] == '0' || A[i][j] == '1' || A[i][j] == '2' || A[i][j] == '3' || A[i][j] == '4' || A[i][j] == '5' || A[i][j] == '6' || A[i][j] == '7' || A[i][j] == '8'
                || A[i][j] == '9' || A[i][j] == '.')

                printf("  ");
            else
                printf(" %c", A[i][j]);
        }
        printf("|");
        printf("    %c |", (char)(i + 65));
        for (int j = 0; j < 10; j++)
        {
            printf(" %c", B[i][j]);
        }
        printf("|\n");

    }
    printf("  +--------------------+      +--------------------+ \n");
    printf("                                                     \n");

}