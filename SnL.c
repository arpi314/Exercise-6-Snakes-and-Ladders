#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct coordinates{
    int x;
    int y;
};
typedef struct coordinates coordinates;

struct snakes{
    char xStart;
    char yStart;
    char xEnd;
    char yEnd;
};
typedef struct snake snake;

struct ladders{
    char xStart;
    char yStart;
    char xEnd;
    char yEnd;
};
typedef struct ladders ladders;

void board(char arrA[10][10], char arrB[10][10], char arrC[10][10], char arrD[10][10], char arrSNL[10][10]); 
int dice();
void makeSnake(char arr[10][10], struct snakes *Ss);
void makeLadder(char arr[10][10], struct ladders *Ll);
void movePlayers(char arr[10][10], char **ptr, int dice, struct coordinates *XY, char X);
void moveSL(char arr[10][10], char **ptr, struct coordinates *XY, struct snakes *sOne, struct snakes *sTwo, struct snakes *sThree, struct ladders *lOne, struct ladders *lTwo, struct ladders *lThree, char X);
int checkWin(struct coordinates *XY);

int main(){

    srand(time(NULL));

    //10x10 arrays for each player and for the snakes and ladders
    char arrA[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
    char arrB[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
    char arrC[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
    char arrD[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
    char SnL[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

    //Setting up the original position in XY coordinate
    struct coordinates coorA = {0, 0};
    struct coordinates coorB = {0, 0};
    struct coordinates coorC = {0, 0};
    struct coordinates coorD = {0, 0};

    //Tokens for the players
    char A = 'a';
    char B = 'b';
    char C = 'c';
    char D = 'd';

    //Attaching pointers to the first position in the board
    char *ptrA = &arrA[coorA.x][coorA.y];
    *ptrA = 'a';
    char *ptrB = &arrB[coorB.x][coorB.y];
    *ptrB = 'b';
    char *ptrC = &arrC[coorC.x][coorC.y];
    *ptrC = 'c';
    char *ptrD = &arrD[coorD.x][coorD.y];
    *ptrD = 'd';

    //Making Snakes using a start position (X.Start, Y.Start) and end position (X.end, Y.end)
    struct snakes snakeOne = {0,0,0,0};
    struct snakes snakeTwo = {0,0,0,0};
    struct snakes snakeThree = {0,0,0,0};

    //Making Ladders using a start position (X.Start, Y.Start) and end position (X.end, Y.end)
    struct ladders ladderOne = {0,0,0,0};
    struct ladders ladderTwo = {0,0,0,0};
    struct ladders ladderThree = {0,0,0,0};

    //Randomizes the values for the three Snakes and the three Ladders
    makeSnake(SnL, &snakeOne);
    makeSnake(SnL, &snakeTwo);
    makeSnake(SnL, &snakeThree);
    makeLadder(SnL, &ladderOne);
    makeLadder(SnL, &ladderTwo);
    makeLadder(SnL, &ladderThree);

    int win = 0, player = 1, die;

    board(arrA, arrB, arrC, arrD, SnL);

    while(win != 1){

        if(player == 1){

            printf("a's turn.\na, press <Enter> to roll.\n");
            getchar();
            die = dice();
            printf("a rolls a %i!\n", die);
            movePlayers(arrA, &ptrA, die, &coorA, A);
            moveSL(arrA, &ptrA, &coorA, &snakeOne, &snakeTwo, &snakeThree, &ladderOne, &ladderTwo, &ladderThree, A);
            board(arrA, arrB, arrC, arrD, SnL);
            win = checkWin(&coorA);
            player = 2;
            die = 0;

        }else if(player == 2){

            printf("b's turn.\nb, press <Enter> to roll.\n");
            getchar();
            die = dice();
            printf("b rolls a %i!\n", die);
            movePlayers(arrB, &ptrB, die, &coorB, B);
            moveSL(arrB, &ptrB, &coorB, &snakeOne, &snakeTwo, &snakeThree, &ladderOne, &ladderTwo, &ladderThree, B);
            board(arrA, arrB, arrC, arrD, SnL);
            win = checkWin(&coorB);
            player = 3;
            die = 0;

        }else if(player == 3){

            printf("c's turn.\nc, press <Enter> to roll.\n");
            getchar();
            die = dice();
            printf("c rolls a %i!\n", die);
            movePlayers(arrC, &ptrC, die, &coorC, C);
            moveSL(arrC, &ptrC, &coorC, &snakeOne, &snakeTwo, &snakeThree, &ladderOne, &ladderTwo, &ladderThree, C);
            board(arrA, arrB, arrC, arrD, SnL);
            win = checkWin(&coorC);
            player = 4;
            die = 0;

        }else if(player == 4){

            printf("d's turn.\nd, press <Enter> to roll.\n");
            getchar();
            die = dice();
            printf("d rolls a %i!\n", die);
            movePlayers(arrD, &ptrD, die, &coorD, D);
            moveSL(arrD, &ptrD, &coorD, &snakeOne, &snakeTwo, &snakeThree, &ladderOne, &ladderTwo, &ladderThree, D);
            board(arrA, arrB, arrC, arrD, SnL);
            win = checkWin(&coorD);
            player = 1;
            die = 0;

        }

    }

    //Printing of winner
    if(player-1 == 1){
        printf("\nCONGRATULATIONS Player a!!!\nYou won the game :DDD\nHere's ASCII cake for you UwU~\n\n");
    }else if(player-1 == 2){
        printf("\nCONGRATULATIONS Player b!!!\nYou won the game :DDD\nHere's ASCII cake for you UwU~\n\n");
    }else if(player-1 == 3){
        printf("\nCONGRATULATIONS Player c!!!\nYou won the game :DDD\nHere's ASCII cake for you UwU~\n\n");
    }else if(player-1 == 0){
        printf("\nCONGRATULATIONS Player d!!!\nYou won the game :DDD\nHere's ASCII cake for you UwU~\n\n");
    }
    printf("            `'.\n       .`' ` * .\n      :  *  *|  :\n       ' |  || '\n        `|~'||'\n        v~v~v~v\n        !@!@!@!\n       _!_!_!_!_\n      |  ||    ||\n      |  ||   |||\n      }{{{{}}}{{{\n        __||__");

    return 0;
}




void board(char arrA[10][10], char arrB[10][10], char arrC[10][10], char arrD[10][10], char arrSNL[10][10]){

    int firstLine = 1, secondLine, thirdLine, lineOne = 1, lineTwo = 0, ok = 1, endMarker = 1;
    int i = 0, j = 0, k = 1;
    int row = 9, col = 9;
    int snlcol = 9;

    while(ok <= 11){

        if(firstLine == 1){ //Outputs the divider line while activating line second line and its corresponding first line

            printf("+----+----+----+----+----+----+----+----+----+----+\n"); 
            firstLine = 0;
            ok++;
            lineOne = 1;
            secondLine = 1;

        }else if(secondLine == 1){ //The second line is what prints out the corresponding Snake and Ladder (S -> s & L -> l)

            k = 1;

            while(k<=11){

                if(lineOne == 1){

                    printf("|");
                    lineOne = 0;
                    lineTwo = 1;
                    k++;

                }else if(lineTwo == 1){

                    if(endMarker == 1){

                        printf("#   |");
                        endMarker = 0;

                    }else{
                        
                        printf("%c   ", (*(*(arrSNL + row) + snlcol)));
                        if(row%2 != 0 && k != 11){
                            snlcol--;
                        }else if(row%2 == 0 && k != 11){
                            snlcol++;
                        }

                        lineOne = 1;
                        lineTwo = 0;

                    }
                }
            }

            secondLine = 0;
            thirdLine = 1;
            lineOne = 1;

            printf("\n");

        }else if(thirdLine == 1){ //This line prints out the positions of the players a, b, c, d on the board

            k = 1;

            while(k<=11){

                if(lineOne == 1){

                    printf("|");

                    lineOne = 0;
                    lineTwo =1;
                    k++;

                }else if (lineTwo == 1){

                    printf("%c%c%c%c", *(*(arrA + row)+ col), *(*(arrB + row)+ col), *(*(arrC + row)+ col), *(*(arrD + row)+ col));

                    if(row%2 != 0 && k != 11){
                        col--;
                    }else if(row%2 == 0 && k != 11){
                        col++;
                    }

                    lineOne = 1;
                    lineTwo = 0;

                }
            }

            row--;
            firstLine = 1;
            thirdLine = 0;
            printf("\n");

        }
    }
}

int dice(){ //makes the dice number

    int p = (rand()%6) + 1;
    return p;

}

//Transfers the players to their specific places on the board
void movePlayers(char arr[10][10], char **ptr, int dice, struct coordinates *XY, char X){
    
    XY->y += dice;

    //Transfers the extra values on the next row
    if(XY->y > 9){

        XY->y = XY->y - 10;
        XY->x++;

    }

    //If the position goes beyond the maximum coordinate which is 9,9
    if(XY->x > 9){

        XY->x = 9;
        XY-> y = 9;

    }
    
    **ptr = ' '; // remove token from old position

    *ptr = &(*(*(arr + XY->x)+ XY->y)); // pointing to the new position

    **ptr = X; // print player token in the new position

}

//Creates the random snake positions for the board
void makeSnake(char arr[10][10], struct snakes *Ss){

    int ok = 0;

    while(ok != 2){

        ok = 0;

        //Sets the value of the array at the position which will be read later on the code to blank again as to not create unecessary snakes
        (*(*(arr + Ss->xStart)+Ss->yStart)) = ' ';
        (*(*(arr + Ss->xEnd)+Ss->yEnd)) = ' ';

        //This part is crucial to create snakes that go from top to bottom using the X coordinate as the marker 
        do{

            Ss->xStart = (rand()%9);
            Ss->yStart = (rand()%9);
            Ss->xEnd = (rand()%9);
            Ss->yEnd = (rand()%9);

        }while(Ss->xStart <= Ss->xEnd);

        //Marker if its okay to continue
        if(Ss->xStart > Ss->xEnd){
                ok++;
        }

        //Assigns the value to the specific XY coordinate for the snakes
        //The condition checks if that area truly is blank as to not cover up previously placed snakes or ladders
        if((*(*(arr + Ss->xStart)+Ss->yStart)) == ' ' && (*(*(arr + Ss->xEnd)+Ss->yEnd)) == ' '){

            (*(*(arr + Ss->xStart)+Ss->yStart)) = 'S';
            (*(*(arr + Ss->xEnd)+Ss->yEnd)) = 's';
            ok++;

        }

    }
}

//Does the same mechanism as the makeSnake function 
void makeLadder(char arr[10][10], struct ladders *Ll){

    int ok = 0; 
    
    while(ok != 2){

        ok = 0;

        (*(*(arr + Ll->xStart)+Ll->yStart)) = ' ';
        (*(*(arr + Ll->xEnd)+Ll->yEnd)) = ' ';

        //Makes coordinates that truly go from bottom to up
        do{

            Ll->xStart = (rand()%9);
            Ll->yStart = (rand()%9);
            Ll->xEnd = (rand()%9);
            Ll->yEnd = (rand()%9);
            
        }while(Ll->xStart >= Ll->xEnd);

        if(Ll->xStart < Ll->xEnd){
                ok++;
        }

        if((*(*(arr + Ll->xStart)+Ll->yStart)) == ' ' && (*(*(arr + Ll->xEnd)+Ll->yEnd)) == ' '){

            (*(*(arr + Ll->xStart)+Ll->yStart)) = 'L';
            (*(*(arr + Ll->xEnd)+Ll->yEnd)) = 'l';
            ok++;

        }
    }
}

//This is the function that makes the player move to the coordinates specified for the snake and ladder
void moveSL(char arr[10][10], char **ptr, struct coordinates *XY, struct snakes *sOne, struct snakes *sTwo, struct snakes *sThree, struct ladders *lOne, struct ladders *lTwo, struct ladders *lThree, char X){

    //The conditionals check if the XY coordinates of the player token is the same as the XY coordinate of the snake or ladder
    if(XY->x == sOne->xStart && XY->y == sOne->yStart){

        //Moves the position of the player token to the position of the end of the snake or ladder
        XY->x = sOne->xEnd;
        XY->y = sOne->yEnd;
        printf("\nPlayer %c lands on a snake and goes down :(\n", X);

    }else if(XY->x == sTwo->xStart && XY->y == sTwo->yStart){

        XY->x = sTwo->xEnd;
        XY->y = sTwo->yEnd;
        printf("\nPlayer %c lands on a snake and goes down :(\n", X);

    }else if(XY->x == sThree->xStart && XY->y == sThree->yStart){

        XY->x = sThree->xEnd;
        XY->y = sThree->yEnd;
        printf("\nPlayer %c lands on a snake and goes down :(\n", X);

    }else if(XY->x == lOne->xStart && XY->y == lOne->yStart){

        XY->x = lOne->xEnd;
        XY->y = lOne->yEnd;
        printf("\nPlayer %c lands on a ladder and goes up :D\n", X);

    }else if(XY->x == lTwo->xStart && XY->y == lTwo->yStart){

        XY->x = lTwo->xEnd;
        XY->y = lTwo->yEnd;
        printf("\nPlayer %c lands on a ladder and goes up :D\n", X);

    }else if(XY->x == lThree->xStart && XY->y == lThree->yStart){

        XY->x = lThree->xEnd;
        XY->y = lThree->yEnd;
        printf("\nPlayer%c lands on a ladder and goes up :D\n", X);

    }

    //Similar as to movePlayers function
    **ptr = ' '; 

    *ptr = &(*(*(arr + XY->x)+ XY->y)); 

    **ptr = X; 

}

//When player reaches max coordinate
int checkWin(struct coordinates *XY){

    if(XY->x == 9 && XY->y == 9){
        return 1;
    }else{
        return 0;
    } 
}


