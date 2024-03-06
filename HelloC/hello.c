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
void udarPC(char Matrix[10][10], int* y, int* x);
bool ChekerPlaceUdar(int direction, char M[10][10], int y, int x);


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

    int ship_4 = 1;
    int ship_3 = 2;
    int ship_2 = 3;

    // FSM

    int StateFsm = 1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastrelint StateFsm=1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastrel
    int dirFsm = 0; //0-start, 1 vert UP, 2-go RIGHT, 3 vert DOWN, 4  gor LEFT 
    int udarFsm = 0; //0-mimo, 1- popal
    int max=0; //q-ty of popal
    int fromDirFsm = 0;


    while (1)

    {
        // udar Person

        if (inputCoordinate(&y, &x))
            if (CheckUdarPerson(A, y, x))
                ShipQtyPC--;
        if (ShipQtyPC == 0)
            break;

        if (ShipQtyPerson == 0)
            break;


        //  udar pc

        switch (StateFsm) 
        {
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
                {
                    UdarCounterPC++;
                    B[udarY][udarX] = 'o';
                }
            }

            else if (UdarCounterPC == 1)
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
                    B[udarY][udarX] = 'o';
                }
            }

            else if (UdarCounterPC == 2)
            {
                udarY = 1;
                udarX = 7;

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
                    B[udarY][udarX] = 'o';
                }
            }

            else if (UdarCounterPC == 3)
            {
                udarY = 7;
                udarX = 7;

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
                    B[udarY][udarX] = 'o';
                }
            }

            else if (UdarCounterPC == 4)
            {
                udarY = 7;
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
                    B[udarY][udarX] = 'o';
                }
            }

            else // posle udara 5 generator skuchainoi y and x
            {

                udarPC(B, &udarY, &udarX); //udar computera cherez function

                if (B[udarY][udarX] == 'Y') // popal
                {
                    if(ship_4!=0||ship_3!=0||ship_2!=0) // if est 2, 3 or 4 palubn
                        StateFsm = 2; // idem na chek napravleniya
                    UdarCounterPC++;
                    ShipQtyPerson--;
                    B[udarY][udarX] = 'X';
                }
                else               // not popal
                {
                    UdarCounterPC++;
                    B[udarY][udarX] = 'o';
                }


            }






            break;

        case 2:

            // check UP
            if ((udarY - 1) >= 0 && B[udarY - 2][udarX] != 'X' && B[udarY - 1][udarX] != 'o')  // up mesto est
                if (B[udarY - 1][udarX] == 'Y') // popal up
                {
                    B[udarY - 1][udarX] = 'X';
                    ShipQtyPerson--;
                    fromDirFsm = 0;
                    dirFsm = 1;
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
                    B[udarY][udarX + 1] = 'X';
                    ShipQtyPerson--;
                    fromDirFsm = 0;
                    dirFsm = 2;
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
                    B[udarY + 1][udarX] = 'X';
                    ShipQtyPerson--;
                    fromDirFsm = 0;
                    dirFsm = 3;
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
                    B[udarY][udarX - 1] = 'X';
                    ShipQtyPerson--;
                    fromDirFsm = 0; 
                    dirFsm = 4;
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
                        B[udarY][udarX] = 'o';
                        }
                    }

                else if (UdarCounterPC == 2)
                    {
                        udarY = 1;
                        udarX = 7;

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
                        B[udarY][udarX] = 'o';
                        }
                    }

                else if (UdarCounterPC == 3)
                    {
                        udarY = 7;
                        udarX = 7;

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
                        B[udarY][udarX] = 'o';
                        }
                    }

                else if (UdarCounterPC == 4)
                    {
                        udarY = 7;
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
                        B[udarY][udarX] = 'o';
                        }
                    }


                else // posle udara 5 generator skuchainoi y and x
                    {

                        udarPC(B, &udarY, &udarX); //udar computera cherez function

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
                        B[udarY][udarX] = 'o';
                        }


                    }




            }

            break;

         case 3:
             switch (dirFsm)
             {
             case 1: // idem na vverx tretiy
                    if (ChekerPlaceUdar(1, B, udarY-2, udarX)) // mesto est
                    {
                        if (B[udarY-2][udarX] == 'Y') // popal
                        {
                            StateFsm = 3;
                            if (ChekerPlaceUdar(1, B, udarY-3, udarX))
                            {
                                dirFsm = 11;
                                fromDirFsm = 1;
                            }
                            else
                            {
                                dirFsm = 3;
                                fromDirFsm = 1;
                            }
                            UdarCounterPC++;
                            ShipQtyPerson--;
                            B[udarY-2][udarX] = 'X';
                        }
                        else               // not popal
                        {
                            UdarCounterPC++;
                            B[udarY-2][udarX] = 'o';
                            if (ChekerPlaceUdar(3, B, udarY+1, udarX))
                            {
                                dirFsm = 3;
                                fromDirFsm = 1;
                            }
                            else
                            {
                                dirFsm = 0;
                                fromDirFsm = 0;
                                StateFsm = 1;
                            }
                        }
                    }

                  break;

             case 2: //iden napravo na tretiy

                   if (ChekerPlaceUdar(1, B, udarY, udarX+2)) // mesto est
                    {
                        if (B[udarY][udarX+2] == 'Y') // popal
                        {
                            StateFsm = 3;
                            if (ChekerPlaceUdar(1, B, udarY, udarX + 3))
                            {
                                dirFsm = 22;
                                fromDirFsm = 2;
                            }
                            else
                            {
                                dirFsm = 4;
                                fromDirFsm = 2;
                            }
                            UdarCounterPC++;
                            ShipQtyPerson--;
                            B[udarY][udarX] = 'X';
                        }
                        else               // not popal
                        {
                            UdarCounterPC++;
                            B[udarY][udarX + 2] = 'o';
                            if (ChekerPlaceUdar(3, B, udarY, udarX - 1))
                            {
                                dirFsm = 4;
                                fromDirFsm = 2;
                            }
                            else
                            {
                                dirFsm = 0;
                                fromDirFsm = 0;
                                StateFsm = 1;
                            }
                        }
                    }


                  break;



             }




            break;

        }



        // end udar pc






        PrintPole(A, B);

    }

    if (ShipQtyPC == 0)
        printf("\n\n   URA URA URA We POBEDILI !!!!\n\n");


    if (ShipQtyPerson == 0)
        printf("\n\n   SORRY SORRY  POBEDIL COMPUTER !!!!\n\n");


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

 void udarPC(char Matrix[10][10], int* y, int* x)

 {
     srand(time(NULL));

     int flag1 = 0;
     int yy;
     int xx;

     while (flag1 == 0)
     {
         yy = rand() % 10;
         xx = rand() % 10;
         // printf("XX == %d\n", xx);
         // printf("YY == %d\n", yy);

         // add proverku dioganali
         if (Matrix[yy][xx] != 'X' && Matrix[yy][xx] != 'o')
             if ((xx - 1) >= 0 && Matrix[yy][xx - 1] != 'X' || xx == 0)
                 if ((xx + 1) <= 9 && Matrix[yy][xx + 1] != 'X' || xx == 9)
                     if ((yy - 1) >= 0 && Matrix[yy - 1][xx] != 'X' || yy == 0)
                         if ((yy + 1) <= 9 && Matrix[yy + 1][xx] != 'X' || yy == 9)
                             flag1 = 1;
     }

     *x = xx;
     *y = yy;


 }

 bool ChekerPlaceUdar(int direction, char M[10][10], int y, int x)
 {
     //directin: 1-up, 2-right, 3-down, 4- left)

     if (direction == 1) // up
     {
         if ((y - 1) >= 0 && M[y - 1][x] == ' ' && M[y - 2][x] != 'X' && M[y - 2][x - 1] != 'X' && M[y - 2][x + 1] != 'X')
             return true;
     }
     else if (direction == 2) // right
     {
         if ((x + 1) <= 9 && M[y][x + 1] == ' ' && M[y][x + 2] != 'X' && M[y - 1][x + 2] != 'X' && M[y + 1][x + 2] != 'X')
             return true;
     }
     else if (direction == 3) // down
     {
         if ((y + 1) <= 9 && M[y + 1][x] == ' ' && M[y + 2][x] != 'X' && M[y + 2][x - 1] != 'X' && M[y + 2][x + 1] != 'X')
             return true;
     }
     else if (direction == 4) // left
     {
         if ((x - 1) >= 0 && M[y][x - 1] == ' ' && M[y][x - 2] != 'X' && M[y - 1][x - 2] != 'X' && M[y + 1][x - 2] != 'X')
             return true;
     }

     else
         return false;
 }