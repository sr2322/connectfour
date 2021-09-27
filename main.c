#include <stdio.h>

/////////////////////////////////
//STRUCT DEFINITION
/////////////////////////////////
typedef struct
{
  int grid[8][8];
  int counters[8];
  int pieceCount;
  int winner;
  int lastPlayedIdx[2];
} game_t;

/////////////////////////////////
//FUNCTION DECLARATIONS
/////////////////////////////////
void gridInit(game_t* game);
void printGrid(game_t* game);
int insertPiece(game_t* game, int player, int column);
int checkWin_diag(game_t* game, int row, int col, int player);
int checkWin_hori(game_t* game, int row, int col, int player);
int checkWin_vert(game_t* game, int row, int col, int player);
int checkWin(game_t* game);

/////////////////////////////////
//MAIN LOOP
/////////////////////////////////
int main( void )
{
  printf("Welcome to Connect Four!\n");
  printf("Let's start a new game\n");

  game_t newGame; 
  gridInit(&newGame);
  printGrid(&newGame);

  int insertStatus= 0;
  int playerNum = 1;
  while(newGame.winner==0){
    printf("Player %d's turn\n",playerNum);
    printf("Pick a column: ");
    int column;
    scanf("%d",&column);
    insertStatus = insertPiece(&newGame, playerNum, column);
    printGrid(&newGame);
    printf("Player %d placed a piece at row %d column %d\n\n", playerNum, newGame.lastPlayedIdx[0], newGame.lastPlayedIdx[1]);
    int winStatus = checkWin(&newGame);
    playerNum = 3 - playerNum;

  }
  //printf("game over man\n");
  return 0;
}

/////////////////////////////////
// FUNCTION DEFINITIONS
/////////////////////////////////

// Initializes game
void gridInit(game_t* game)
{ 
  for (int i=0; i<8;i++){
    for (int j=0; j<8;j++){
      game->grid[i][j]=0;
    }
  }
  for (int c=0; c<8; c++){
    game->counters[c] = 0;
  }
  game->pieceCount=0;
  game->winner = 0;
  game->lastPlayedIdx[0]=-1;
  game->lastPlayedIdx[1]=-1;
  return;
}

// Prints game
void printGrid(game_t* game)
{
  printf("\n");
  for (int i=7; i>=0;i--){
    for (int j=0; j<8;j++){
      printf("%d ",game->grid[i][j]);
    }
    printf("\n"); 
  }
  printf("\n"); 
  return;
}

// Inserts piece
int insertPiece(game_t* game, int player, int column)
{
  if(game->pieceCount >= 64){
    printf("Grid full! Game over\n");
    return -2;
  }
  if (game->counters[column] >= 8){
    printf("column %d full, try another one\n",column);
    return -1;
  }
  // Place player's token in the topmost available slot
  game->grid[game->counters[column]][column] = player;
  game->lastPlayedIdx[0] = game->counters[column];
  game->lastPlayedIdx[1] = column;
  //increment the column-based- and overall- piece counters
  game->counters[column]++;
  game->pieceCount++;

  return 0;
}

// Checks whether game is won
// Using last played position and player
int checkWin(game_t* game)
{
  int row = game->lastPlayedIdx[0];
  int col = game->lastPlayedIdx[1];
  int player = game->grid[row][col]; //get player number
  if (checkWin_vert(game, row, col, player)==1){
    game->winner = player;
    printf("Player %d wins along the vertical\n",player);
    return 10;
  }

  else if (checkWin_hori(game, row, col, player)==1){
    game->winner = player;
    printf("Player %d wins along the horizontal\n",player);
    return 20;
  }
  else if (checkWin_diag(game, row, col, player)==1){
    game->winner = player;
    printf("Player %d wins along the diagonal\n",player);
    return 30;
  }

  else return 0;
}

//returns 1 if diagonal win condition is true, 0 if not
int checkWin_diag(game_t* game, int row, int col, int player){
  if(row<0 || row>7 || col<0 || col>7){
    printf("Out of bounds access!\n");
    return -1;
  }
  int countFour = 0;
  
  // get row and col that represent the botton-right most point 
  // of the diagonal that intersects a given piece
  while(row>0 && col>0){
    row--;
    col--;
  }

  while(row<8 && col<8){
    //increment countFour
    if(game->grid[row][col]==player){
      countFour++;      
    }
    else if(countFour<4) countFour=0;     
    row++;
    col++;
  }
  if(countFour>=4){
    return 1;
  }
  else{
    return 0;
  }
}

//returns 1 if horizontal win condition is true, 0 if not
int checkWin_hori(game_t* game, int row, int col, int player){
  if(row<0 || row>7 || col<0 || col>7){
    printf("Out of bounds access!\n");
    return -1;
  }
  int countFour = 0;
  col=0;
  while(col<8){
    if(game->grid[row][col]==player){
      countFour++;      
    }
    else if(countFour<4) countFour=0;
    col++;
  }
  if(countFour>=4){
    return 1;
  }
  else{
    return 0;
  }
}

  //returns 1 if vertical win condition is true, 0 if not
int checkWin_vert(game_t* game, int row, int col, int player){
  if(row<0 || row>7 || col<0 || col>7){
    printf("Out of bounds access!\n");
    return -1;
  }

  int countFour = 0;
  row=0;
  while(row<8){
    if(game->grid[row][col]==player){
      countFour++;      
    }
    else if(countFour<4) countFour=0;
    row++;
  }
  if(countFour>=4){
    return 1;
  }
  else{
    return 0;
  }
}
