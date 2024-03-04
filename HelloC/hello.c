#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void PrintPole(char A[10][10], char B[10][10]);  // funcrion print pole igry on display
void CreationShipsComputer(char A[10][10]);
void ZoneAroundShip(char A[10][10], int direcU, int coordY, int coordX, int K);
void ShipCreatorPC(char A[10][10], int K);
int inputDirection();
bool inputCoordinate(int* y, int* x);
void CreationShipsPerson(char A[10][10], char B[10][10]);

bool CheckUdarPerson(char A[10][10], int y, int x);



void main()              
 {                                 
    
    printf("   HELLO                                           \n");
    
    char A[10][10]; // computer
    char* addrA = (char*)A;

    char B[10][10]; // person
    char* addrB = (char*)B;

    // initial pole
    for (int i = 0; i < 100; i++)
        *(addrA + i) = ' ';

    for (int i = 0; i < 100; i++)
        *(addrB + i) = ' ';


    int ShipQtyPC = 20;


    CreationShipsComputer(A);
    
    PrintPole(A, B);
      
    CreationShipsPerson(A, B);

    printf("   All ships are created\n");
    printf("   Startuem fire!!! First udar from Person\n");


    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            if(B[i][j]=='.')
             B[i][j]=' ';
        }



    int y;
    int x;


    // PC part
    int udarY;
    int udarX;
    int UdarCounterPC = 0;
    int ShipQtyPerson = 20;

    // FSM

    int StateFsm = 1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastrelint StateFsm=1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastrel
    int dirFsm = 0; //0-start, 2 vert UP, 1-go RIGHT, 4 vert DOWN, 3  gor LEFT 4- up up, 5 right right6 down down  7 left left
    int udarFsm = 0; //0-mimo, 1- popal
    int ship_4 = 1;
    int ship_3 = 2;
    int max; //q-ty of popal
    int fromDirFsm = 0;


    while (1)

    {
        if (inputCoordinate(&y, &x))
            if (CheckUdarPerson(A, y, x))
                ShipQtyPC--;
        if (ShipQtyPC == 0)
            break;


        //  udar pc

        switch (StateFsm) {
        case 1:  // prost udar 

            if (UdarCounterPC == 0)
            {
                udarY=4;
                udarX=4;

                if (B[udarY][udarX] == 'Y') // popal
                {
                    StateFsm = 2;
                    UdarCounterPC++;
                    ShipQtyPerson--;
                    B[udarY][udarX] = 'X';
                }
                else               // not popal
                    UdarCounterPC++;
            
            }

            break;

        case 2:

            // check UP
            if ((udarY - 1) >= 0 && B[udarY - 2][udarX] != 'X' && B[udarY - 1][udarX] != 'o')  // up mesto est
                if (B[udarY - 1][udarX] == 'Y') // popal up
                {
                    ShipQtyPerson--;
                    fromDirFsm = 2; // verticalno
                    StateFsm = 3;
                }
                else // ne popal
                {
                    B[udarY - 1][udarX] = 'o';

                }



            //check RIGHT
            else if ((udarX + 1) <= 9 && B[udarY][udarX + 2] != 'X' && B[udarY][udarX + 1] != 'o') //rigt mesto est
                if (B[udarY][udarX + 1] == 'Y') //popal
                {
                    ShipQtyPerson--;
                    fromDirFsm = 1; // vpravo
                    StateFsm = 3;
                }
                else
                {
                    B[udarY][udarX + 1] = 'o';

                }



            //check DOWN
            else if ((udarY + 1) <= 9 && B[udarY + 2][udarX] != 'X' && B[udarY + 1][udarX] != 'o')
                if (B[udarY + 1][udarX] == 'Y')
                {
                    ShipQtyPerson--;
                    fromDirFsm = 4; // down
                    StateFsm = 3;
                }

                else
                {
                    B[udarY + 1][udarX] = 'o';

                }

            //check LEFT
            else if ((udarX - 1) >= 0 && B[udarY][udarX - 2] != 'X' && B[udarY][udarX - 1] != 'o')
                if (B[udarY][udarX - 1] == 'Y')
                {
                    ShipQtyPerson--;
                    fromDirFsm = 3; // left
                    StateFsm = 3;

                }

                else
                {
                    B[udarY][udarX - 1] = 'o';
                    StateFsm = 1;
                }


            else // oboshel po krugu, udar, esli mimo FSM 1,esli popal F                                                                                                                                                             SM2
            {
                if (UdarCounterPC == 1)
                {
                    udarY = 1;
                    udarX = 2;

                    if (B[udarY][udarX] == 'Y') // popal
                    {
                        StateFsm = 2;
                        UdarCounterPC++;
                        ShipQtyPerson--;
                        B[udarY][udarX] = 'X';
                    }
                    else               // not popal
                    {
                        UdarCounterPC++;
                        StateFsm = 1;
                    }
                }
            }

            break;

        }



        // end udar pc






        PrintPole(A, B);

    }

    if (ShipQtyPC == 0)
        printf("\n\n   URA URA URA We POBEDILI !!!!\n\n");



    PrintPole(A, B);

}

void PrintPole(char A[10][10], char B[10][10])
{
    
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

    int shep[10] = { 4,3,3,2,2,2,1,1,1,1 };

    srand(time(NULL));

    for (int k = 0; k < 10; k++)
    {        
        ShipCreatorPC(A, shep[k]);     
    }
 }

 void ZoneAroundShip(char A[10][10], int direcU, int coordY, int coordX, int K)
 {
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


 void ShipCreatorPC(char A[10][10], int K) 
 {
     srand(time(NULL));

     int coordY;
     int coordX;
     int direcU;

     int shepOK = 0;

     while (shepOK == 0)
     {
         coordY = rand() % (10 - K);
         coordX = rand() % (10 - K);
         direcU = rand() & 0x1;
 
         if (direcU == 1)
         {
             for (int i = 0; i < K; i++)
             {
                 if (A[coordY + i][coordX] == ' ')
                 {
                     A[coordY + i][coordX] = 'Y';
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
             for (int i = 0; i < K; i++)
             {
                 if (A[coordY][coordX + i] == ' ')
                 {
                     A[coordY][coordX + i] = 'Y';
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

     ZoneAroundShip(A, direcU, coordY, coordX, K);

 }

 int inputDirection()
 {
     char Buffer[10];
     int direction;
     int ok = 0;
     while (ok == 0)
     {
         printf("\n   Input direction of ship, 0 - gorizontal, 1 - vertical ");
     
         fgets(Buffer, 9, stdin);
         direction = Buffer[0];
         direction -= 48;

         //    scanf_s("%d", &direction);
         //    scanf_s("%*c");
         if (direction == 0 || direction == 1)
             ok = 1;
         else
             printf("   Vvod not correct, please input one more");
     }

     return direction;

 }


 bool inputCoordinate(int* y, int* x)
 {

     char Buffer[100];
     int yy;
     int xx;

     printf("\n   Enter coordinats [e.g. 'a6']    ");
     fgets(Buffer, 99, stdin);

     yy = Buffer[0];
     xx = Buffer[1];
     if (yy >= 65 && yy <= 74)
         yy -= 65;
     else
         if (yy >= 97 && yy <= 106)
             yy -= 97;
         else
             yy = 99;
     if (xx >= 48 && xx <= 57)
         xx -= 48;
     else
         xx = 99;

     if (xx == 99 || yy == 99)
         return false;
     else
     {
         *x = xx;
         *y = yy;
         return true;
     }
 }

 
 void CreationShipsPerson(char A[10][10], char B[10][10])
 {
     int ship[10] = { 4,3,3,2,2,2,1,1,1,1 };
     int direction;
     int y;
     int x;
     int inputShipPersonQ = 0;
     bool shipPersonOK;

     for (int k = 0; k < 10; k++)
     {
       
       printf("   Input %d - palubny ship\n", ship[inputShipPersonQ]);

       shipPersonOK = false;

       while (!shipPersonOK)
       {
           bool coordOK;

           if (inputShipPersonQ < 6)
               direction = inputDirection();
           else
               direction = 0;


           if (direction == 0)
           {
               coordOK = inputCoordinate(&y, &x);
               shipPersonOK = true;

               for (int i = 0; i < ship[inputShipPersonQ]; i++)
               {
                   if (B[y][x + i] != ' ')
                       shipPersonOK = false;
               }

               if (shipPersonOK == true && coordOK && x < (11 - ship[inputShipPersonQ]))
               {
                   for (int i = 0; i < ship[inputShipPersonQ]; i++)
                   {

                       B[y][x + i] = 'Y';

                       ZoneAroundShip(B, direction, y, x, ship[inputShipPersonQ]);

                   }

                   inputShipPersonQ++;
                   PrintPole(A, B);
               }

               else
                   printf("   Input NOT CORRECT PLEASE REPEAT!!!\n");

           }

           else
           {
               coordOK = inputCoordinate(&y, &x);
               shipPersonOK = true;
               for (int i = 0; i < ship[inputShipPersonQ]; i++)

               {
                   if (B[y+i][x] != ' ')
                       shipPersonOK = false;
               }

               if (shipPersonOK == true && coordOK && x < (11 - ship[inputShipPersonQ]))
               {
                   for (int i = 0; i < ship[inputShipPersonQ]; i++)
                   {

                       B[y+i][x] = 'Y';
                       ZoneAroundShip(B, direction, y, x, ship[inputShipPersonQ]);

                   }
                   inputShipPersonQ++;
                   PrintPole(A, B);
               }

               else
                   printf("   Input NOT CORRECT PLEASE REPEAT!!!\n");

           }
       }
     }
      

 }

 bool CheckUdarPerson(char A[10][10], int y, int x)
 {
     if (A[y][x] == ' '||A[y][x] == '.')
         {
           A[y][x] = 'o';
           return false;
         }

     else if (A[y][x] == 'Y')
         {
             A[y][x] = 'X';
             return true;
         }

 }