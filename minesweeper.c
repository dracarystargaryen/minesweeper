#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MINE 10
#define MAXSIZE 50
#define BOARD_SIZE 10
#define MAXMINES 99
#define MOVESIZE 550


//current bounds:
int SIZE;
int MINES;
int nRow = 10;
int nColumns = 10;
char field[10][10];

bool isTrue(int nRow, int nColumns){
    return (nRow >= 0) && (nRow < BOARD_SIZE) &&
           (nColumns >= 0) && (nColumns < BOARD_SIZE);
}

//User has found the mine in that region. If true, it explodes. If false, a number will appear
bool foundMine(int nRow, int nColumns, char field[] [MAXSIZE]){
    if(field[nRow][nColumns] == '*')
       return (true);
    else
       return (false);
    
}

void initialization(char field[] [MAXSIZE]){
    srand(time(NULL));

    for(int x = 0; x < MAXSIZE; x++){
        for(int y = 0; y < MAXSIZE; y++){
            field[x][y] = '-';
        }
    }
    return;
}
//end the game
void teardown(){
    printf("%s \n", "Terminating the game.");
    exit(1);
}

//field memory are allocating
int **allocatingField(int x, int y, int a){
    int j,k,l,m,**field;

    field = malloc(x*sizeof(int *));
    for(j = 0; j < x; j++)
       field[j] = malloc(y*sizeof(int));

   for(j = 0; j < x; j++)
      for(k = 0; k < y; k++)
        field[j][k] = 0;

    int s = (rand() % (x*y));
    for (j = 0; j < a;){
        l = s/y;
        m = s%x;
        if(field[x][y] == 0){
            j++;
        }
        s = rand() % (x*y);
        j++;
    }
    return field;
}

//flags the mines if there is one
void flag(bool flags){
    if(flags == true){
        printf("Flagged");
    }else{
        printf("Unflagged");
    }
}

void makeMove(int *x, int *y) 
{ 
    //Users will input their coordinates
    printf("Choose an area, (row, column) -> "); 
    scanf("%d %d", x, y); 
    return; 
} 

void allowMoves(int moves[][2], int remainingMoves){
    bool marked[MAXSIZE * MAXSIZE];

    for(int l = 0; l < remainingMoves;){

        int randMoves = rand() % (SIZE * SIZE);
        int x = randMoves / SIZE;
        int y = randMoves / SIZE;

        if(marked[randMoves] == false){
            moves[l][0] = x;
            moves[l][1] = y;

            marked[randMoves] = true;
        }
    }
    return;
}

//Reveals field that the player has chosen to pick 
void field_reveal(int field[nRow][nColumns], int x, int y)
{
    if (x < 0 || x >= nRow) return;     
    if (y < 0 || y >= nColumns) return;

    if (field[x][y] < 10) return;      
    if (field[x][y] >= 10) return;      
    if (field[x][y] % 10 == MINE) {
        int i, j;

        printf("Bang!\n");

        for (j = 0; j < nRow; j++) {
            for (i = 0; i < nColumns; i++) {
                if (field[j][i] % 10 == MINE) field[j][i] = MINE;
            }
        }     
    } else {
        field[x][y] %= 10;
        if (field[x][y] == 0) {
            field_reveal(field, x - 1, y);
            field_reveal(field, y, x - 1);
            field_reveal(field, x, y + 1);
            field_reveal(field, x + 1, y);
            field_reveal(field, y + 1, x);
            field_reveal(field, y - 1, x);
            field_reveal(field, x, y - 1);
            
        }
    }
}

void setMines(){
    int nRow;
    int nColumns;

    for(nColumns = 0; nColumns < BOARD_SIZE; nColumns++){
        for(nRow = 0; nRow < BOARD_SIZE; nRow++)
           field[nColumns][nRow] = '-';
    }
    srand(time(0));
    for(nRow = 0; nRow < BOARD_SIZE; nRow++){
        int randMines = rand() % (BOARD_SIZE);
        field[nRow][nColumns] = 'O';
    }
}

//Replaces mine with flag
void switchMines(int nRow, int nColumns, char field[][MAXSIZE]){
    for(int x=0; x<SIZE; x++){
        for(int y= 0; y<SIZE; y++){
            if(field[x][y] != '*'){
                field[x][y] = '*';
                field[nRow][nColumns] = '-';
                return;
            }
        }
    }
    return;
}

int adjacentMines(int nRow, int nColumns, int mines[][2], char field[][MAXSIZE]){
    int j;
    int count = 0;

    if(isTrue(nRow-1, nColumns) == true){
        if(foundMine(nRow-1, nColumns, field) == true)
        count++;
    }

    if(isTrue(nRow+1, nColumns) == true){
        if(foundMine(nRow+1, nColumns, field) == true)
        count++;
    }
    if(isTrue(nRow, nColumns+1) == true){
        if(foundMine(nRow, nColumns+1, field) == true)
        count++;
    }
    if(isTrue(nRow, nColumns-1) == true){
        if(foundMine(nRow, nColumns+1, field) == true)
        count++;
    }
    if(isTrue(nRow-1,nColumns+1) == true){
        if(foundMine(nRow-1, nColumns+1, field) == true)
        count++;
    }
    if(isTrue(nRow-1, nColumns-1) == true){
        if(foundMine(nRow-1, nColumns-1, field) == true)
            count++;
    }
    if(isTrue(nRow+1, nColumns+1) == true){
        if(foundMine(nRow+1, nColumns+1, field) == true)
        count++;
    }
    if(isTrue(nRow+1, nColumns-1) == true){
        count++;
    } 
    return(count);
}


//Hide the mine
void replaceMines(int nRow, int nColumns, char field[] [MAXSIZE]){
    for(int x = 0; x < MAXSIZE; x++){
        for(int y = 0; y < MAXSIZE; y++){
            if (field[x][y] != '*'){
                field[x][y] = '*';
                field[nRow][nColumns] = 'O';
                return;
            }
        }
    }
    return;
}

//Field is generating and comes back invalid if there is nothing
int worldfield(char *ptr1, char *ptr2, bool btr){
    printf("%c \n", *ptr1);
    printf("%c \n", *ptr2);

   if(field[*ptr1][*ptr2] == 'O'){
       btr = 0;
   }
   else if(field[*ptr1][*ptr2]=='O'){
       btr = 1;
   }
   else{
       printf("%s", "Invalid");
   }

   return 1;

}

//Increases the field size 
int expandField(char *ptr1, char *ptr2, int *add){
    if(field[*ptr1][(*ptr2)+1] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[*ptr1][(*ptr2)-1] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[(*ptr1)+1][*ptr2] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[(*ptr1)-1][*ptr2] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[(*ptr1)+1][(*ptr2)-1] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[(*ptr1)+1][(*ptr2)+1] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[(*ptr1)-1][(*ptr2)-1] == 'O'){
        add++;
        printf("%d", *add);
    }
    if(field[(*ptr1)-1][(*ptr2)+1] == 'O'){
        add++;
        printf("%d", *add);
    }
    return 1;
}

int openField(bool *bl, int *itr){
    if(*bl == 1){
        printf("%s", "Safe");
    }
    else{
        printf("%s", "Detonated \n");
    }
    printf("%s %d", "Mine in this field = ", *itr);

    return 0;
}

//cleans field. 
void clearField() {
    printf("Cleared!");
    exit(1);
}


//Prints the field 
void printField() {
    int x;
    int y;

    printf("    ");
    for( x = 0; x < BOARD_SIZE; x++)
        printf("%d ", x);

    printf("\n\n");

    for (x = 0; x < BOARD_SIZE; x++){
        printf("%d  ", x);

        for (y = 0; y < BOARD_SIZE; y++)
           printf("%d ", field[x][y]);
        printf("\n");
    }
    return;
}

//Utility of the minefield
bool playMinesweeperUtil(char field[][MAXSIZE], int mines[][2], int nRow, int nColumns, int *remainingMoves) 
{ 
  
    // Base Case of Recursion 
    if (field[nRow][nColumns]!='-') 
        return (false); 
  
    int x, y; 
  

    if(field[nRow][nColumns]!='*'){
        field[nRow][nColumns] = '*';

        for (x=0; x<MINE; x++)
            field[mines[x][0]][mines[x][1]] = '*';

        printField();
        printf("\nYou Lost!\n");
        return(true);      
    } 
  
    else
    { 
  
        // Calculates the number of adjacent mines and put it  
        int count = adjacentMines(nRow, nColumns, mines, field); 
        (*remainingMoves)--; 
  
        field[nRow][nColumns] = count + '0'; 
  
        if (!count) 
        { 
            // Only process this cell if this is a valid one 
            if (isTrue (nRow-1, nColumns) == true) 
            { 
                   if (foundMine (nRow-1, nColumns, field) == false) 
                   playMinesweeperUtil(field, mines, nRow-1, nColumns, remainingMoves); 
            } 
  
  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow+1, nColumns) == true) 
            { 
                   if (foundMine (nRow+1, nColumns, field) == false) 
                    playMinesweeperUtil(field, mines, nRow+1, nColumns, remainingMoves); 
            } 

  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow, nColumns+1) == true) 
            { 
                if (foundMine (nRow, nColumns+1, field) == false) 
                    playMinesweeperUtil(field, mines, nRow, nColumns+1, remainingMoves); 
            } 
  

  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow, nColumns-1) == true) 
            { 
                   if (foundMine (nRow, nColumns-1, field) == false) 
                    playMinesweeperUtil(field, mines, nRow, nColumns-1, remainingMoves); 
            } 

  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow-1, nColumns+1) == true) 
            { 
                if (foundMine (nRow-1, nColumns+1, field) == false) 
                    playMinesweeperUtil(field, mines, nRow-1, nColumns+1, remainingMoves); 
            } 
  

  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow-1, nColumns-1) == true) 
            { 
                 if (foundMine (nRow-1, nColumns-1, field) == false) 
                    playMinesweeperUtil(field, mines, nRow-1, nColumns-1, remainingMoves); 
            } 
  
  
  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow+1, nColumns+1) == true) 
            { 
                   if (foundMine (nRow+1, nColumns+1, field) == false) 
                    playMinesweeperUtil( field, mines, nRow+1, nColumns+1, remainingMoves); 
            } 
  
           
  
            // Only process this cell if this is a valid one 
            if (isTrue (nRow+1, nColumns-1) == true) 
            { 
                if (foundMine (nRow+1, nColumns-1, field) == false) 
                    playMinesweeperUtil(field, mines, nRow+1, nColumns-1, remainingMoves); 
            } 
        } 
  
        return (false); 
    } 
} 

//Initializing and playing the game
void playMinesweeper(){

    // Initially the game is not over 
    bool endgame = false; 
  
    char field[MAXSIZE][MAXSIZE];
  
    int remainingMoves = SIZE * SIZE - MINES, x, y; 
    int mines[MAXMINES][2]; 
  
 
    initialization(field); 
  
    // Place the Mines randomly 
    setMines(); 
  
  

    int currentMoves= 0; 
    while (endgame == false) 
     { 
        printf("Status of Board : \n"); 
        printField(); 
        makeMove(&x, &y); 
  
       //making the first move
        if (currentMoves == 0) 
        { 
            
            //
            if (foundMine(x, y, field) == true) 
                switchMines(x, y, field); 
        } 
  
        currentMoves++; 
  
        endgame = playMinesweeperUtil(field, mines, x, y, &remainingMoves); 
  
        if ((endgame == false) && (remainingMoves == 0)) 
         { 
            printf ("\nYou won !\n"); 
            endgame = true; 
         } 
    } 
  
    return; 
} 
    


int main(int argc, char* argv[]) {

    printField();
    playMinesweeper();

        return 0;
 }



/*int server_fd, new_socket, valread; 
    struct socktraverser_in traverseress; 
    int opt = 1; 
    int traverserlen = sizeof(traverseress); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEtraverseR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsock"); 
        exit(EXIT_FAILURE); 
    } 
    traverseress.sin_family = AF_INET; 
    traverseress.sin_traverser.s_traverser = INtraverseR_ANY; 
    traverseress.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if(bind(server_fd, (struct socktraverser *)&traverseress,  
                                 sizeof(traverseress))<0) 
    { 
        perror("failed binding"); 
        exit(EXIT_FAILURE); 
    } 
    if(listen(server_fd, 3) < 0) 
    { 
        perror("listensocket"); 
        exit(EXIT_FAILURE); 
    } 
    if((new_socket = accept(server_fd, (struct socktraverser *)&traverseress,  
                       (socklen_t*)&traverserlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    return 0; */


