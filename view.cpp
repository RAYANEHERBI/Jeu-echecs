#include "view.hpp"

using namespace std;

#define RESET "\x1b[0m"

// Affichage des fonds des cases de l echiquier
void set_background(bool is_white_square){
    if (is_white_square){ 
        cout << "\x1b[48;5;245m";
    }else{
        cout << "\x1b[48;5;230m";
    }
}

// Affichage des pieces
void set_foreground(Piece piece) {
    // case vide
    if (piece.color == NONE) {
        cout << " ";
        return;
    }
    
    // symbole Unicode selon le type et la couleur
    switch (piece.type) {
        case PAWN:   (piece.color == WHITE) ? cout << "\u2659" : cout << "\u265f"; break;
        case ROOK:   (piece.color == WHITE) ? cout << "\u2656" : cout << "\u265c"; break;
        case KNIGHT: (piece.color == WHITE) ? cout << "\u2658" : cout << "\u265e"; break;
        case BISHOP: (piece.color == WHITE) ? cout << "\u2657" : cout << "\u265d"; break;
        case QUEEN:  (piece.color == WHITE) ? cout << "\u2655" : cout << "\u265b"; break;
        case KING:   (piece.color == WHITE) ? cout << "♔" : cout << "\u265a"; break;
        default:     cout << " "; break;
    }
}

//  Affiche une case avec fond + pièce
void print_square_color(Piece piece, bool is_white_square) {
    set_background(is_white_square);
    set_foreground(piece);
    cout << " "; // espace après la pièce
    cout << RESET;
}

//  Affichage de l echiquier dans la console
void print_board(const Game &game) {
    cout << "  a b c d e f g h" << endl;

    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            bool is_white_square = (i + j) % 2 == 0;
            print_square_color(game.board[i][j], is_white_square);
        }
        cout << " " << 8 - i << endl;
    }

    cout << "  a b c d e f g h" << endl;
}

/*

// La fonctions precedente qui transforme une piece en caractere pour l affichage 

char print_square(Piece piece){
    if(piece.color==NONE){ // si la case est vide
        return '.';
    }
    switch(piece.type) { // selon le type de la piece 

        case PAWN:      return (piece.color == WHITE) ? 'P' : 'p';// BLANCHES noires
        case ROOK:      return (piece.color == WHITE) ? 'R' : 'r';
        case KNIGHT:    return (piece.color == WHITE) ? 'N' : 'n';
        case BISHOP:    return (piece.color == WHITE) ? 'B' : 'b';
        case QUEEN:     return (piece.color == WHITE) ? 'Q' : 'q';
        case KING:      return (piece.color == WHITE) ? 'K' : 'k';

        default:
            return '.';
    }
}

// fonction precedante pour afficher l echiquier dans la console

void print_board(const Game &game){
    cout << "  a b c d e f g h" << endl;

    // parcourir les lignes
    for(int i = 0; i < 8; i++) {
        cout << 8-i << " ";
        // parcourir les colonnes
        for(int j = 0; j < 8; j++) {
            cout << print_square(game.board[i][j]) << " ";// afficher la piece en char
        }

        cout << 8-i << endl;
    }

    cout << "  a b c d e f g h" << endl;
}

*/
