#include <stdio.h> 
#include <stdlib.h>
#include <time.h>



void PrintPole(char A[10][10], char B[10][10]);  // funcrion print pole igry on display
void CreationShipsComputer(char A[10][10]);
void ZoneAroundShip(char A[10][10], int direcU, int coordY, int coordX, int K);


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


    CreationShipsComputer(A);
    
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
            
            /*
            //computer\s ships mark as 0000, 111, 222,33, 44, 55, 6, 7, 8, 9 and pole around as '.'/ It is not printed 
            if (A[i][j] == '0' || A[i][j] == '1' || A[i][j] == '2' || A[i][j] == '3' || A[i][j] == '4' || A[i][j] == '5' || A[i][j] == '6' || A[i][j] == '7' || A[i][j] == '8'
                || A[i][j] == '9' || A[i][j] == '.')

                printf("  ");
            else
                printf(" %c", A[i][j]);
*/
            printf(" %c", A[i][j]); // for otladka uotput ships

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

void CreationShipsComputer(char A[10][10])
 {

    // creation ships computer


    int shep[10] = { 4,3,3,2,2,2,1,1,1,1 };

    int coordY;
    int coordX;
    int direcU;

    srand(time(NULL));

    for (int k = 0; k < 10; k++)
    {
        int shepOK = 0;

        while (shepOK == 0)
        {
            coordY = rand() % (10 - shep[k]);
            coordX = rand() % (10 - shep[k]);
            direcU = rand() & 0x1;
            if (direcU == 1)
            {
                for (int i = 0; i < shep[k]; i++)
                {
                    if (A[coordY + i][coordX] == ' ')
                    {
                        A[coordY + i][coordX] = (char)(k + 48);
                        shepOK = 1;
                    }
                    else
                    {
                        shepOK = 0;
                        for (int j = 0; j < i; j++)
                        {
                            A[coordY + j][coordX] = ' ';
                        }
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < shep[k]; i++)
                {
                    if (A[coordY][coordX + i] == ' ')
                    {
                        A[coordY][coordX + i] = (char)(k + 48);
                        shepOK = 1;
                    }
                    else
                    {
                        shepOK = 0;
                        for (int j = 0; j < i; j++)
                        {
                            A[coordY][coordX + j] = ' ';
                        }
                        break;
                    }
                }
            }
        }


        ZoneAroundShip(A, direcU, coordY, coordX, shep[k]);

    }
 }

 void ZoneAroundShip(char A[10][10], int direcU, int coordY, int coordX, int K)
 {

     // stroim zonu vokrug shep

     if (direcU == 1)
     {
         for (int i = 0; i < (K + 2); i++)
         {
             if (((coordY - 1 + i) >= 0) && ((coordY - 1 + i) <= 9) && ((coordX - 1) >= 0) && ((coordX - 1) <= 9))
                 A[coordY - 1 + i][coordX - 1] = '.';
             if (((coordY - 1 + i) >= 0) && ((coordY - 1 + i) <= 9) && ((coordX + 1) >= 0) && ((coordX + 1) <= 9))
                 A[coordY - 1 + i][coordX + 1] = '.';
         }
         if (((coordY - 1) >= 0) && ((coordY - 1) <= 9))
             A[coordY - 1][coordX] = '.';
         if (((coordY + K) >= 0) && ((coordY + K) <= 9))
             A[coordY + K][coordX] = '.';
     }

     else if (direcU == 0)
     {
         for (int i = 0; i < (K + 2); i++)
         {
             if (((coordY - 1) >= 0) && ((coordY - 1) <= 9) && ((coordX - 1 + i) >= 0) && ((coordX - 1 + i) <= 9))
                 A[coordY - 1][coordX - 1 + i] = '.';
             if (((coordY + 1) >= 0) && ((coordY + 1) <= 9) && ((coordX - 1 + i) >= 0) && ((coordX - 1 + i) <= 9))
                 A[coordY + 1][coordX - 1 + i] = '.';
         }
         if (((coordX - 1) >= 0) && ((coordX - 1) <= 9))
             A[coordY][coordX - 1] = '.';
         if (((coordX + K) >= 0) && ((coordX + K) <= 9))
             A[coordY][coordX + K] = '.';
     }



 }