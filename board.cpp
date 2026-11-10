//ce fichier contient l implementation des F qui manipules le plateau

#include "board.hpp"


//empty cree un TB vide
void empty(Game &game){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            game.board[i][j]= {EMPTY, NONE}; //mettre la case vide
        }
        
    }
    
}

//get recupere la piece situee a une position 
Piece get_square(const Game &game, int row , int col){
    return game.board[row][col]; //row = ligne / col = colonne
}

//set modifie le contenue d une case
void set_square(Game &game , int row, int col, Piece piece){
    game.board[row][col] = piece; //piece = piece a placer
}

//start initialise le plateau avec les pieces dans leurs positions de depart 
void start(Game &game){
    empty(game);//commencer par un plateau vide 

    //on place les pions 
    for(int i = 0 ; i < 8 ; i++)
    {
        game.board[1][i]={PAWN , BLACK}; //LES BLANCS 
        game.board[6][i]={PAWN , WHITE}; //les noirs
    }

    //placement des tours 
    game.board[0][0] = {ROOK, BLACK};
    game.board[0][7] = {ROOK, BLACK};

    game.board[7][0] = {ROOK, WHITE};
    game.board[7][7] = {ROOK, WHITE};

    // placement des cavaliers 

    game.board[0][1] = {KNIGHT, BLACK};
    game.board[0][6] = {KNIGHT, BLACK};

    game.board[7][1] = {KNIGHT, WHITE};
    game.board[7][6] = {KNIGHT, WHITE};

    // fous 
    game.board[0][2] = {BISHOP, BLACK};
    game.board[0][5] = {BISHOP, BLACK};

    game.board[7][2] = {BISHOP, WHITE};
    game.board[7][5] = {BISHOP, WHITE};

    //DAMES 
    game.board[0][3] = {QUEEN, BLACK};
    game.board[7][3] = {QUEEN, WHITE};
    
    //rois
    game.board[0][4] = {KING, BLACK};
    game.board[7][4] = {KING, WHITE};

    game.turn = WHITE ; //les blancs commencent 

    game.nb_captured_white = 0;
    game.nb_captured_black = 0;
    game.historique.nb_coups = 0;
}

//move_piece deplace une piece d une place vers une autre 
//src = depaert / dest= arrivee
void move_piece(Game &game, int sr, int sc, int dr, int dc){

    Piece dest = game.board[dr][dc];

    // si on mange une pièce
    if(dest.type != EMPTY){
        if(dest.color == WHITE){
            game.captured_white[game.nb_captured_white++] = dest;
        } else {
            game.captured_black[game.nb_captured_black++] = dest;
        }
    }

    // déplacement
    game.board[dr][dc] = game.board[sr][sc];
    game.board[sr][sc] = {EMPTY, NONE};

    // changement de tour
    if(game.turn == WHITE)
        game.turn = BLACK;
    else
        game.turn = WHITE;
}