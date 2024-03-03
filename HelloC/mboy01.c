#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// udarPC(B, &udarY, &udarX); //udar computera cherez function

//function udara computera
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





void main()
{

    // initial var
    char A[10][10]; // computer
    char* addrA = (char*)A;


    int inputShepPerson = 0; //flag
    int inputShepPersonQ = 0; //quantity of inputs

    int coordY;
    int coordX;
    int direcU;

    int direction; // direction of ship

    srand(time(NULL));
    int x = -1, y = -1;
    char Buffer[100];


    int udarCount[7] = { 4,3,3,2,2,2,4 };
    int Count = 0;


    int udarCountPC = 0;
    int countShipPerson = 0;

    // FSM

    int StateFsm = 1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastrelint StateFsm=1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastrel
    int dirFsm = 0; //0-start, 2 vert UP, 1-go RIGHT, 4 vert DOWN, 3  gor LEFT 4- up up, 5 right right6 down down  7 left left
    int udarFsm = 0; //0-mimo, 1- popal
    int ship_4 = 1;
    int ship_3 = 2;
    int max; //q-ty of popal
    int fromDirFsm = 0;



    int pointInput = 0; //0-up, 1-right, 2-down, 3-left
    int oldPoint = 0;// old sostoynie 0-start,1-up, 2-right, 3-down, 4-left
    int inputPC = 0; // chel point PC input

    // initial pole
    for (int i = 0; i < 100; i++)
        *(addrA + i) = ' ';


    for (int i = 0; i < 100; i++)
        *(addrB + i) = ' ';




    // creation ships computer


    int shep[10] = { 4,3,3,2,2,2,1,1,1,1 };


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



        // stroim zonu vokrug shep

        if (direcU == 1)
        {
            for (int i = 0; i < (shep[k] + 2); i++)
            {
                if (((coordY - 1 + i) >= 0) && ((coordY - 1 + i) <= 9) && ((coordX - 1) >= 0) && ((coordX - 1) <= 9))
                    A[coordY - 1 + i][coordX - 1] = '.';
                if (((coordY - 1 + i) >= 0) && ((coordY - 1 + i) <= 9) && ((coordX + 1) >= 0) && ((coordX + 1) <= 9))
                    A[coordY - 1 + i][coordX + 1] = '.';
            }
            if (((coordY - 1) >= 0) && ((coordY - 1) <= 9))
                A[coordY - 1][coordX] = '.';
            if (((coordY + shep[k]) >= 0) && ((coordY + shep[k]) <= 9))
                A[coordY + shep[k]][coordX] = '.';
        }

        else if (direcU == 0)
        {
            for (int i = 0; i < (shep[k] + 2); i++)
            {
                if (((coordY - 1) >= 0) && ((coordY - 1) <= 9) && ((coordX - 1 + i) >= 0) && ((coordX - 1 + i) <= 9))
                    A[coordY - 1][coordX - 1 + i] = '.';
                if (((coordY + 1) >= 0) && ((coordY + 1) <= 9) && ((coordX - 1 + i) >= 0) && ((coordX - 1 + i) <= 9))
                    A[coordY + 1][coordX - 1 + i] = '.';
            }
            if (((coordX - 1) >= 0) && ((coordX - 1) <= 9))
                A[coordY][coordX - 1] = '.';
            if (((coordX + shep[k]) >= 0) && ((coordX + shep[k]) <= 9))
                A[coordY][coordX + shep[k]] = '.';
        }




    }
    //-----------------------



    while (1)
    {

        //    int inputPC=0; // point input FSM State 2


        // print pole igry  with ships and udars

        printf("                                                   \n");
        printf("        computer                      person       \n                                                      \n");
        printf("    0 1 2 3 4 5 6 7 8 9         0 1 2 3 4 5 6 7 8 9 \n  +--------------------+      +--------------------+ \n");
        for (int i = 0; i < 10; i++)
        {
            printf("%c |", (char)(i + 65));
            for (int j = 0; j < 10; j++)
            {
                // if(A[i][j]=='.')

                if (A[i][j] == '0' || A[i][j] == '1' || A[i][j] == '2' || A[i][j] == '3' || A[i][j] == '4'||A[i][j] == '5' || A[i][j] == '6' || A[i][j] == '7' || A[i][j] == '8'
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

        //----------------------------------------


        // input sheps chelovek
        int shipPersonOK = 0;
        if (inputShepPersonQ < 10)
        {
            if (inputShepPersonQ < 6)
            {
                printf("\n  input direction ship, 0 - gorizontal, 1 - vertical ");
                scanf_s("%d", &direction);
                scanf_s("%*c");
            }
            else
                direction = 0;



            printf("\n   Enter coords head of ship [e.g. 'a6']: shep %d-palbny :", shep[inputShepPersonQ]);

            fgets(Buffer, 99, stdin);



            if (direction == 0)
            {
                y = Buffer[0];
                x = Buffer[1];
                if (y >= 65 && y <= 74)
                    y -= 65;
                else
                    if (y >= 97 && y <= 106)
                        y -= 97;
                    else
                        y = 99;
                if (x >= 48 && x <= 57)
                    x -= 48;
                else
                    x = 99;



                for (int i = 0; i < shep[inputShepPersonQ]; i++)
                {
                    if (B[y][x + i] != ' ')
                        shipPersonOK = 1;
                }

                if (shipPersonOK == 0 && y != 99 && x != 99 && x < (11 - shep[inputShepPersonQ]))
                {
                    for (int i = 0; i < shep[inputShepPersonQ]; i++)
                    {
                        //          printf("input %d  %d\n", y,x);
                        B[y][x + i] = 'Y';

                        // stroim zonu vokrug

                        for (int i = 0; i < (shep[inputShepPersonQ] + 2); i++)
                        {
                            if (((y - 1) >= 0) && ((y - 1) <= 9) && ((x - 1 + i) >= 0) && ((x - 1 + i) <= 9))
                                B[y - 1][x - 1 + i] = '.';
                            if (((y + 1) >= 0) && ((y + 1) <= 9) && ((x - 1 + i) >= 0) && ((x - 1 + i) <= 9))
                                B[y + 1][x - 1 + i] = '.';
                        }
                        if (((x - 1) >= 0) && ((x - 1) <= 9))
                            B[y][x - 1] = '.';
                        if (((x + shep[inputShepPersonQ]) >= 0) && ((x + shep[inputShepPersonQ]) <= 9))
                            B[y][x + shep[inputShepPersonQ]] = '.';



                        // ------------------

                        //          printf("uspex\n");
                    }
                    inputShepPersonQ++;
                }
                else
                    printf("Input NOT CORRECT!!!");

            }

            else if (direction == 1)
            {

                y = Buffer[0];
                x = Buffer[1];
                if (y >= 65 && y <= 74)
                    y -= 65;
                else
                    if (y >= 97 && y <= 106)
                        y -= 97;
                    else
                        y = 99;
                if (x >= 48 && x <= 57)
                    x -= 48;
                else
                    x = 99;


                for (int i = 0; i < shep[inputShepPersonQ]; i++)
                {
                    if (B[y + i][x] != ' ')
                        shipPersonOK = 1;
                }


                if (shipPersonOK == 0 && y != 99 && x != 99 && y < (11 - shep[inputShepPersonQ]))
                {
                    for (int i = 0; i < shep[inputShepPersonQ]; i++)
                    {
                        B[y + i][x] = 'Y';

                        // stroim zonu vokrug

                        for (int i = 0; i < (shep[inputShepPersonQ] + 2); i++)
                        {
                            if (((y - 1 + i) >= 0) && ((y - 1 + i) <= 9) && ((x - 1) >= 0) && ((x - 1) <= 9))
                                B[y - 1 + i][x - 1] = '.';
                            if (((y - 1 + i) >= 0) && ((y - 1 + i) <= 9) && ((x + 1) >= 0) && ((x + 1) <= 9))
                                B[y - 1 + i][x + 1] = '.';
                        }
                        if (((y - 1) >= 0) && ((y - 1) <= 9))
                            B[y - 1][x] = '.';
                        if (((y + shep[inputShepPersonQ]) >= 0) && ((y + shep[inputShepPersonQ]) <= 9))
                            B[y + shep[inputShepPersonQ]][x] = '.';



                        // ------------------






                    }
                    inputShepPersonQ++;
                }
                else
                    printf("Input NOT CORRECT!!!");


            }



        }






        // input udara person




        if (inputShepPersonQ == 10)

        {


            printf("\n\033[AEnter coords UDARA [e.g. 'a6']:      \b\b\b\b\b");
            fgets(Buffer, 99, stdin);

            Count++;
            y = Buffer[0];
            x = Buffer[1];
            if (y >= 65 && y <= 74)
                y -= 65;
            else
                if (y >= 97 && y <= 106)
                    y -= 97;
                else
                    y = 99;
            if (x >= 48 && x <= 57)
                x -= 48;
            else
                x = 99;


            //-----------------------------------------


            // proverka udara Person





            if (x != 99 && y != 99)
            {
                if ((A[y][x] == ' ') || (A[y][x] == '.'))
                    A[y][x] = 'o';


                else if ((A[y][x] == '6') || (A[y][x] == '7') || (A[y][x] == '8') || (A[y][x] == '9'))
                {
                    udarCount[6] = udarCount[6] - 1;
                    A[y][x] = 'u';
                }


                else if (A[y][x] == '0')
                {
                    udarCount[0] = udarCount[0] - 1;
                    if (udarCount[0] == 0)
                        A[y][x] = 'u';
                    else
                        A[y][x] = 'r';
                }



                else if (A[y][x] == '1')
                {
                    udarCount[1] = udarCount[1] - 1;
                    if (udarCount[1] == 0)
                        A[y][x] = 'u';
                    else
                        A[y][x] = 'r';
                }


                else if (A[y][x] == '2')
                {
                    udarCount[2] = udarCount[2] - 1;
                    if (udarCount[2] == 0)
                        A[y][x] = 'u';
                    else
                        A[y][x] = 'r';
                }


                else if (A[y][x] == '3')
                {
                    udarCount[3] = udarCount[3] - 1;
                    if (udarCount[3] == 0)
                        A[y][x] = 'u';
                    else
                        A[y][x] = 'r';
                }


                else if (A[y][x] == '4')
                {
                    udarCount[4] = udarCount[4] - 1;
                    if (udarCount[4] == 0)
                        A[y][x] = 'u';
                    else
                        A[y][x] = 'r';
                }



                else if (A[y][x] == '5')
                {
                    udarCount[5] = udarCount[5] - 1;
                    if (udarCount[5] == 0)
                        A[y][x] = 'u';
                    else
                        A[y][x] = 'r';
                }









                else if ((A[y][x] == 'r') || (A[y][x] == 'u'))
                {
                }


            }






            //---------------------------------------------
            // udar computera


            //          int StateFsm=1; //1-poisk ship-initial, 2-poisk napravleniya,3-rastr                                                                                                                                                             el
            int flag1 = 0; // proverka udara, 0-prodolgat, 1-ok

            int udarY=0;
            int udarX=0;
            int flag = 0;

            switch (StateFsm) {
            case 1:


                // functia vestrela


                udarPC(B, &udarY, &udarX); //udar computera cherez function

                /*

                                while(flag1==0)
                                 {
                                  udarY=rand()%10;
                                  udarX=rand()%10;
                                  if (B[udarY][udarX]!='X'&&B[udarY][udarX]!='o')
                                   if(((udarX-1)>=0&&B[udarY][udarX-1]!='X')||udarX==0)
                                    if(((udarX+1)<=9&&B[udarY][udarX+1]!='X')||udarX==9)
                                     if(((udarY-1)>=0&&B[udarY-1][udarX]!='X')||udarY==0)
                                      if(((udarY+1)<=9&&B[udarY+1][udarX]!='X')||udarY==9)
                                       flag1=1;
                                 }


                */
                //end of function udar



                if (B[udarY][udarX] == 'Y')
                {
                    B[udarY][udarX] = 'X';
                    udarCountPC++;  // calculation q-ty of ship point, should be                                                                                                                                                              == 20
                    StateFsm = 2;
                }
                else
                    B[udarY][udarX] = 'o';
                break;
            case 2:
                flag = 0; //flag go futher
                // printf("State FSM ==2\n");


                if (oldPoint == 0)
                    pointInput = 0;
                else if (oldPoint == 1)
                    pointInput = 1;
                else if (oldPoint == 2)
                    pointInput = 2;
                else if (oldPoint == 3)
                    pointInput = 3;
                else if (oldPoint == 4)
                    pointInput = 0;


                // check UP
                if ((udarY - 1) >= 0 && B[udarY - 2][udarX] != 'X' && B[udarY - 1][udarX] != 'o')
                    if (B[udarY - 1][udarX] == 'Y')
                    {
                        if (((udarY - 2) == 0 || B[udarY - 2][udarX] == 'o') && ((udarY + 1) == 9 || B[udarY - 1][udarX]) == 'o')
                        {
                            udarCountPC++;
                            B[udarY - 1][udarX] = 'X';
                            StateFsm = 1;
                        }
                        else
                        {
                            B[udarY - 1][udarX] = 'X';
                            dirFsm = 2;
                            udarCountPC++;
                            StateFsm = 3;
                            max = 2; //q-ty popadany
                        }
                    }
                    else
                    {
                        B[udarY - 1][udarX] = 'o';
                        oldPoint = 1;
                        inputPC++;
                    }



                //check RIGHT
                else if ((udarX + 1) <= 9 && B[udarY][udarX + 2] != 'X' && B[udarY][udarX + 1] != 'o')
                    if (B[udarY][udarX + 1] == 'Y')
                    {
                        if (((udarX + 2) == 9 || B[udarY][udarX + 2] == 'o') && ((udarX - 1) == 0 || B[udarY][udarX - 1]) == 'o')//nado fo up too
                        {
                            udarCountPC++;
                            B[udarY][udarX + 1] = 'X';
                            StateFsm = 1;
                        }
                        else
                        {
                            B[udarY][udarX + 1] = 'X';
                            dirFsm = 1;
                            udarCountPC++;
                            StateFsm = 3;
                            max = 2;
                        }
                    }
                    else
                    {
                        B[udarY][udarX + 1] = 'o';
                        oldPoint = 2;
                        inputPC++;
                    }


                //check DOWN
                else if ((udarY + 1) <= 9 && B[udarY + 2][udarX] != 'X' && B[udarY + 1][udarX] != 'o')
                    if (B[udarY + 1][udarX] == 'Y')
                    {
                        if ((udarY + 1) == 9 || ((udarY + 1) < 9) && B[udarY + 2][udarX] == 'o')
                        {
                            B[udarY + 1][udarX] = 'X';
                            udarCountPC++;
                            StateFsm = 1;
                        }
                        else
                        {
                            B[udarY + 1][udarX] = 'X';
                            dirFsm = 4;
                            udarCountPC++;
                            StateFsm = 3;
                            max = 2;
                        }
                    }

                    else
                    {
                        B[udarY + 1][udarX] = 'o';
                        oldPoint = 3;
                        inputPC++;
                    }


                //check LEFT
                else if ((udarX - 1) >= 0 && B[udarY][udarX - 2] != 'X' && B[udarY][udarX - 1] != 'o')
                    if (B[udarY][udarX - 1] == 'Y')
                    {
                        if ((udarX - 1) == 0 || ((udarX - 1) > 0) && B[udarY][udarX - 2] == 'o')//for down too nado
                        {
                            B[udarY][udarX - 1] = 'X';
                            udarCountPC++;
                            StateFsm = 1;
                        }
                        else
                        {
                            B[udarY][udarX - 1] = 'X';
                            dirFsm = 3;
                            udarCountPC++;
                            StateFsm = 3;
                            max = 2;
                        }
                    }

                    else
                    {
                        B[udarY][udarX - 1] = 'o';
                        oldPoint = 4;
                        inputPC++;
                    }

                else // oboshel po krugu, udar, esli mimo FSM 1,esli popal F                                                                                                                                                             SM2
                {
                    // printf("Ne znay chto delat, TOGDA UDAR!!!\n");


                    while (flag1 == 0)
                    {
                        udarY = rand() % 10;
                        udarX = rand() % 10;
                        if (B[udarY][udarX] != 'X' && B[udarY][udarX] != 'o')
                            if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'X' || udarX == 0)
                                if ((udarX + 1) <= 9 && B[udarY][udarX + 1] != 'X' || udarX == 9)
                                    if ((udarY - 1) >= 0 && B[udarY - 1][udarX] != 'X' || udarY == 0)
                                        if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'X' || udarY == 9)
                                            flag1 = 1;
                    }

                    if (B[udarY][udarX] == 'Y')
                    {
                        B[udarY][udarX] = 'X';
                        udarCountPC++;  // calculation q-ty of ship point, shoul                                                                                                                                                             d be ==      20
                        StateFsm = 2;
                    }
                    else
                    {
                        B[udarY][udarX] = 'o';
                        StateFsm = 1;
                    }


                }

                break;
            case 3:
                // printf("FSM-3 !!!!\n");
                // printf("Direction  %d\n", dirFsm);
                // printf("ship-4  %d\n",ship_4);
                // printf("ship-3  %d\n",ship_3);
                inputPC = 0;
                if (ship_4 == 0 && ship_3 == 0)
                {
                    //nuzen udar udar and StateFsm=1 or stateFsm=2


                    while (flag1 == 0)
                    {
                        udarY = rand() % 10;
                        udarX = rand() % 10;
                        if (B[udarY][udarX] != 'X' && B[udarY][udarX] != 'o')
                            if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'X' || udarX == 0)
                                if ((udarX + 1) <= 9 && B[udarY][udarX + 1] != 'X' || udarX == 9)
                                    if ((udarY - 1) >= 0 && B[udarY - 1][udarX] != 'X' || udarY == 0)
                                        if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'X' || udarY == 9)
                                            flag1 = 1;
                    }

                    if (B[udarY][udarX] == 'Y')
                    {
                        B[udarY][udarX] = 'X';
                        udarCountPC++;  // calculation q-ty of ship point, shoul                                                                                                                                                             d be ==      20
                        StateFsm = 2;
                    }
                    else
                    {
                        B[udarY][udarX] = 'o';
                        StateFsm = 1;
                    }




                    break;
                }
                else // est 4 and 3 palubn
                {
                    switch (dirFsm) {
                    case 0:



                        break;





                        //------------------------------------------------------------------------------                                                                                                                                                             --------------------------------------
                    case 1: //right
                        //        printf("O O O O O\n");
                        if ((udarX + 2) <= 9 && B[udarY][udarX + 2] != 'o' && B[udarY][udarX + 3] != 'X')
                            if (B[udarY][udarX + 2] == 'Y')
                            {
                                //          printf("popal\n");
                                B[udarY][udarX + 2] = 'X';
                                udarCountPC++;
                                max++; //popal
                                if ((udarX + 3) <= 9 && B[udarY][udarX + 3] != 'o' && B[udarY][udarX + 4] != 'X')
                                {
                                    dirFsm = 5;
                                    fromDirFsm = 1;
                                }
                                else
                                {
                                    fromDirFsm = 1;
                                    dirFsm = 3;

                                }
                            }
                            else
                            {
                                //       printf("ne popal\n");
                                B[udarY][udarX + 2] = 'o';
                                dirFsm = 3;
                                fromDirFsm = 1;
                            }
                        else
                        {
                            //      printf("net mesta vpravo \n");
                            dirFsm = 3;
                            fromDirFsm = 1;
                        }
                        break;

                        //--------------------------------------------------------------------------

                    case 5: // right -- right
                        //      printf("case-5\n");
                        if (B[udarY][udarX + 3] == 'Y')
                        {
                            B[udarY][udarX + 3] = 'X';
                            udarCountPC++;
                            max = 2;
                            fromDirFsm = 0;
                            StateFsm = 1;
                            ship_4 = 0;
                        }
                        else
                        {
                            B[udarY][udarX + 3] = 'o';
                            dirFsm = 3;
                            //ship_3--; // ????????????????
                        }
                        break;

                        //-----------------------------------------------------------------------

                    case 7:  //  left left
                        //         printf("case-7\n");
                        if (fromDirFsm == 3)// srazu sleva
                            if (B[udarY][udarX - 3] == 'Y')
                            {
                                B[udarY][udarX - 3] = 'X';
                                udarCountPC++;
                                max = 2;
                                fromDirFsm = 0;
                                StateFsm = 1;
                                ship_4 = 0;
                            }
                            else
                            {
                                B[udarY][udarX - 3] = 'o';
                                StateFsm = 1;
                                if (max == 4)
                                    ship_4 = 0;
                                else if (max == 3)
                                    ship_3--;
                                max = 2;
                                fromDirFsm = 0;
                            }

                        else if (fromDirFsm == 11)
                            if (B[udarY][udarX - 2] == 'Y') //???????????????????????????                                                                                                                                                             ?????????
                            {
                                B[udarY][udarX - 2] = 'X';
                                udarCountPC++;
                                max = 2;
                                StateFsm = 1;
                                ship_4 = 0;
                            }
                            else
                            {
                                B[udarY][udarX - 2] = 'o';
                                StateFsm = 1;
                                if (max == 4)
                                    ship_4 = 0;
                                else if (max == 3)
                                    ship_3--;
                                max = 2;
                                fromDirFsm = 0;
                            }

                        break;


                        //-------------------------------------------------------------------

                    case 3:

                        //        printf("A A A A A\n");
                        if (fromDirFsm == 0)// na starte
                        {
                            if ((udarX - 2) >= 0 && B[udarY][udarX - 2] != 'o' && B[udarY][udarX - 3] != 'X')//est mesto
                                if (B[udarY][udarX - 2] == 'Y')//popal
                                {
                                    //           printf("popal-2\n");
                                    B[udarY][udarX - 2] = 'X';
                                    udarCountPC++;
                                    max++; //popal
                                    if ((udarX - 3) >= 0 && B[udarY][udarX - 3] != 'o' && B[udarY][udarX - 4] != 'X')
                                    {
                                        dirFsm = 7;
                                        fromDirFsm = 3;
                                    }
                                    else
                                    {
                                        StateFsm = 1;
                                        dirFsm = 0;
                                        ship_3--;
                                        max = 2;
                                    }
                                }
                                else // ne popal
                                {
                                    //            printf("ne popal-2???????????\n");
                                    B[udarY][udarX - 2] = 'o';
                                    StateFsm = 1;
                                    fromDirFsm = 0;
                                }
                            else //net mesta
                            {
                                //         printf("net mesta \n"); //nuzen udar



                                while (flag1 == 0)
                                {
                                    udarY = rand() % 10;
                                    udarX = rand() % 10;
                                    if (B[udarY][udarX] != 'X' && B[udarY][udarX] != 'o')
                                        if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'X' || udarX == 0)
                                            if ((udarX + 1) <= 9 && B[udarY][udarX + 1] != 'X' || udarX == 9)
                                                if ((udarY - 1) >= 0 && B[udarY - 1][udarX] != 'X' || udarY == 0)
                                                    if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'X' || udarY == 9)
                                                        flag1 = 1;
                                }

                                if (B[udarY][udarX] == 'Y')
                                {
                                    B[udarY][udarX] = 'X';
                                    udarCountPC++;  // calculation q-ty of ship point, s                                                                                                                                                             hould be ==      20
                                    StateFsm = 2;
                                    fromDirFsm = 0;
                                }
                                else
                                {
                                    B[udarY][udarX] = 'o';
                                    StateFsm = 1;
                                    fromDirFsm = 0;
                                }





                            }
                        }
                        else if (fromDirFsm == 1)// cprishlo sprava
                        {
                            if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'o' && B[udarY][udarX - 2] != 'X')//est mesto
                                if (B[udarY][udarX - 1] == 'Y')//popal
                                {
                                    //        printf("popal-2-3-4\n");
                                    B[udarY][udarX - 1] = 'X';
                                    udarCountPC++;
                                    max++; //popal

                                    // proverit if udarCount==4 to vexod

                                    if (max == 4)
                                    {
                                        StateFsm = 1;
                                        dirFsm = 0;
                                        fromDirFsm = 0;
                                        ship_4 = 0;
                                    }

                                    //---------------------------


                                    if ((udarX - 2) >= 0 && B[udarY][udarX - 2] != 'o' && B[udarY][udarX - 3] != 'X')
                                    {
                                        dirFsm = 7;
                                        fromDirFsm = 11;
                                    }
                                    else
                                    {
                                        StateFsm = 1;
                                        dirFsm = 0;
                                        if (max == 4)
                                            ship_4 = 0;
                                        else if (max == 3)
                                            ship_3--;
                                        max = 2;
                                        fromDirFsm = 0;
                                    }
                                }
                                else // ne popal
                                {
                                    //      printf("ne popal-2\n");
                                    B[udarY][udarX - 1] = 'o';
                                    StateFsm = 1;
                                    dirFsm = 0;
                                    if (max == 4)
                                        ship_4 = 0;
                                    else if (max == 3)
                                        ship_3--;
                                    max = 2;
                                    fromDirFsm = 0;
                                }
                            else //net mesta
                            {
                                //       printf("net mesta \n"); //nuzen udar  777

                                if (max == 3)
                                    ship_3--;



                                while (flag1 == 0)
                                {
                                    udarY = rand() % 10;
                                    udarX = rand() % 10;
                                    if (B[udarY][udarX] != 'X' && B[udarY][udarX] != 'o')
                                        if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'X' || udarX == 0)
                                            if ((udarX + 1) <= 9 && B[udarY][udarX + 1] != 'X' || udarX == 9)
                                                if ((udarY - 1) >= 0 && B[udarY - 1][udarX] != 'X' || udarY == 0)
                                                    if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'X' || udarY == 9)
                                                        flag1 = 1;
                                }

                                if (B[udarY][udarX] == 'Y')
                                {
                                    B[udarY][udarX] = 'X';
                                    udarCountPC++;  // calculation q-ty of ship point, s                                                                                                                                                             hould be ==      20
                                    StateFsm = 2;
                                    fromDirFsm = 0;
                                }
                                else
                                {
                                    B[udarY][udarX] = 'o';
                                    StateFsm = 1;
                                    fromDirFsm = 0;
                                }




                            }
                        }


                        break;


                        //---------------------------------------------------------

                        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        // vstavka 22.02.2024


                    case 2: //up


                        printf("O2 O2 O2 O2 O2\n");
                        if ((udarY - 2) >= 0 && B[udarY - 2][udarX] != 'o' && B[udarY - 3][udarX] != 'X')
                            if (B[udarY - 2][udarX] == 'Y')
                            {
                                printf("popal up\n");
                                B[udarY - 2][udarX] = 'X';
                                udarCountPC++;
                                max++; //popal
                                if ((udarY - 3) >= 0 && B[udarY - 3][udarX] != 'o' && B[udarY - 4][udarX] != 'X')
                                {
                                    dirFsm = 15;
                                    fromDirFsm = 2;
                                }
                                else
                                {
                                    fromDirFsm = 2;
                                    dirFsm = 4;

                                }
                            }
                            else
                            {
                                printf("ne popal up\n");
                                B[udarY - 2][udarX] = 'o';
                                dirFsm = 4;
                                fromDirFsm = 2;
                            }
                        else
                        {
                            printf("net mesta up \n");
                            dirFsm = 4;
                            fromDirFsm = 2;
                        }


                        break;

                        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                    case 4: //down


                        printf("A4 A4 A4 A4 A4\n");
                        if (fromDirFsm == 0)// na starte
                        {
                            if ((udarY + 2) <= 9 && B[udarY + 2][udarX] != 'o' && B[udarY + 3][udarX] != 'X')//est mesto
                                if (B[udarY + 2][udarX] == 'Y')//popal
                                {
                                    printf("popal-2-4\n");
                                    B[udarY + 2][udarX] = 'X';
                                    udarCountPC++;
                                    max++; //popal
                                    if ((udarY + 3) <= 9 && B[udarY + 3][udarX] != 'o' && B[udarY + 4][udarX] != 'X')
                                    {
                                        dirFsm = 17;
                                        fromDirFsm = 43;
                                    }
                                    else
                                    {
                                        StateFsm = 1;
                                        dirFsm = 0;
                                        ship_3--;
                                        max = 2;
                                    }
                                }
                                else // ne popal
                                {
                                    printf("ne popal--up--1111???????????\n");
                                    B[udarY + 2][udarX] = 'o';
                                    StateFsm = 1;
                                    fromDirFsm = 0;
                                }
                            else //net mesta
                            {
                                printf("net mesta \n"); //nuzen udar



                                while (flag1 == 0)
                                {
                                    udarY = rand() % 10;
                                    udarX = rand() % 10;
                                    if (B[udarY][udarX] != 'X' && B[udarY][udarX] != 'o')
                                        if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'X' || udarX == 0)
                                            if ((udarX + 1) <= 9 && B[udarY][udarX + 1] != 'X' || udarX == 9)
                                                if ((udarY - 1) >= 0 && B[udarY - 1][udarX] != 'X' || udarY == 0)
                                                    if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'X' || udarY == 9)
                                                        flag1 = 1;
                                }

                                if (B[udarY][udarX] == 'Y')
                                {
                                    B[udarY][udarX] = 'X';
                                    udarCountPC++;  // calculation q-ty of ship point, should be == 20
                                    StateFsm = 2;
                                    fromDirFsm = 0;
                                }
                                else
                                {
                                    B[udarY][udarX] = 'o';
                                    StateFsm = 1;
                                    fromDirFsm = 0;
                                }





                            }
                        }
                        else if (fromDirFsm == 2)// prishlo sverhu
                        {
                            if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'o' && B[udarY + 2][udarX] != 'X')//est mesto
                                if (B[udarY + 1][udarX] == 'Y')//popal
                                {
                                    printf("popal-2-3-4-5-6\n");
                                    B[udarY + 1][udarX] = 'X';
                                    udarCountPC++;
                                    max++; //popal

                                    if (max == 4)
                                    {
                                        StateFsm = 1;
                                        dirFsm = 0;
                                        fromDirFsm = 0;
                                        ship_4 = 0;
                                    }


                                    if ((udarY + 2) <= 9 && B[udarY + 2][udarX] != 'o' && B[udarY + 3][udarX] != 'X')
                                    {
                                        dirFsm = 17;
                                        fromDirFsm = 112;
                                    }
                                    else
                                    {
                                        StateFsm = 1;
                                        dirFsm = 0;
                                        if (max == 4)
                                            ship_4 = 0;
                                        else if (max == 3)
                                            ship_3--;
                                        max = 2;
                                        fromDirFsm = 0;
                                    }
                                }
                                else // ne popal
                                {
                                    printf("ne popal-2-3-4-5\n");
                                    B[udarY + 1][udarX] = 'o';
                                    StateFsm = 1;
                                    dirFsm = 0;
                                    if (max == 4)
                                        ship_4 = 0;
                                    else if (max == 3)
                                        ship_3--;
                                    max = 2;
                                    fromDirFsm = 0;
                                }
                            else //net mesta
                            {
                                printf("net mesta \n"); //nuzen udar

                                if (max == 3)
                                    ship_3--;



                                while (flag1 == 0)
                                {
                                    udarY = rand() % 10;
                                    udarX = rand() % 10;
                                    if (B[udarY][udarX] != 'X' && B[udarY][udarX] != 'o')
                                        if ((udarX - 1) >= 0 && B[udarY][udarX - 1] != 'X' || udarX == 0)
                                            if ((udarX + 1) <= 9 && B[udarY][udarX + 1] != 'X' || udarX == 9)
                                                if ((udarY - 1) >= 0 && B[udarY - 1][udarX] != 'X' || udarY == 0)
                                                    if ((udarY + 1) <= 9 && B[udarY + 1][udarX] != 'X' || udarY == 9)
                                                        flag1 = 1;
                                }

                                if (B[udarY][udarX] == 'Y')
                                {
                                    B[udarY][udarX] = 'X';
                                    udarCountPC++;  // calculation q-ty of ship point, s                                                                                                                                                             hould be ==      20
                                    StateFsm = 2;
                                    fromDirFsm = 0;
                                }
                                else
                                {
                                    B[udarY][udarX] = 'o';
                                    StateFsm = 1;
                                    fromDirFsm = 0;
                                }




                            }
                        }


                        break;



                    case 15: //up and up

                        printf("case-15\n");
                        if (B[udarY - 3][udarX] == 'Y')
                        {
                            B[udarY - 3][udarX] = 'X';
                            udarCountPC++;
                            max = 2;
                            fromDirFsm = 0;
                            StateFsm = 1;
                            ship_4 = 0;
                        }
                        else
                        {
                            B[udarY - 3][udarX] = 'o';
                            dirFsm = 4;
                            //ship_3--;
                        }

                        break;



                    case 17:


                        printf("case-17\n");
                        if (fromDirFsm == 4)// srazu down down
                            if (B[udarY + 3][udarX] == 'Y')
                            {
                                B[udarY + 3][udarX] = 'X';
                                udarCountPC++;
                                max = 2;
                                fromDirFsm = 0;
                                StateFsm = 1;
                                ship_4 = 0;
                            }
                            else
                            {
                                B[udarY + 3][udarX] = 'o';
                                StateFsm = 1;
                                if (max == 4)
                                    ship_4 = 0;
                                else if (max == 3)
                                    ship_3--;
                                max = 2;
                                fromDirFsm = 0;
                            }

                        else if (fromDirFsm == 112)
                            if (B[udarY + 2][udarX] == 'Y') //???????????????????????????                                                                                                                                                             ?????????
                            {
                                B[udarY + 2][udarX] = 'X';
                                udarCountPC++;
                                max = 2;
                                StateFsm = 1;
                                ship_4 = 0;
                            }
                            else
                            {
                                B[udarY + 2][udarX] = 'o';
                                StateFsm = 1;
                                if (max == 4)
                                    ship_4 = 0;
                                else if (max == 3)
                                    ship_3--;
                                max = 2;
                                fromDirFsm = 0;
                            }


                        break;


                        // vstavka 22.02.2024

                    default:
                        printf("chto to ne to\n");
                        break;
                    }


                    break;
                }
            default:
                printf("chto to ne to\n");
                break;
            }




            /*

                      if (*(addrB+udarCountPC) == ' '||*(addrB+udarCountPC) == '.')
                       {
                        *(addrB+udarCountPC)='o';
                        }

                       else if(*(addrB+udarCountPC) == 'Y')
                       {
                        *(addrB+udarCountPC)='X';
                        countShipPerson++;
                       }





                      udarCountPC++;  // calculation q-ty of ship point, should be == 20

            */








            //-----------------------
            // proverka pobedy


            //  for (int i=0; i<100; i++)
            //   {
            //    if (*(addrB+i)=' ';



            int pobeda = udarCount[0] + udarCount[1] + udarCount[2] + udarCount[3] + udarCount[4] + udarCount[5] + udarCount[6];

            if (pobeda == 0)
            {
                printf("URA We Pobedily!!!! End of game\n");
                printf("Quntity of hod = %d\n", Count);
                break;
            }

            if (udarCountPC == 20)
            {
                printf("  SORRY Pobedil Computer\n");
                break;
            }




            //---------------------------------------------

        }



    }

}
