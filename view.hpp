#ifndef VIEW_HPP_
#define VIEW_HPP_

#include "types.hpp"
#include <iostream>

using namespace std;

// La fonction precedente qui transforme une piece en caractere pour l affichage 
// char print_square(Piece piece);

// Affiche le plateau avec les pieces.
void print_board(const Game &game);

// Choisit la couleur de fond d une case.
void set_background(int is_white_square);

// Choisit le symbole et la couleur d une piece.
void set_foreground(Piece piece);

// Affiche une case avec sa couleur et sa piece.
void print_square_color(Piece piece, int is_white_square);
#endif
