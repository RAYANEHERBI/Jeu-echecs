#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "types.hpp"

void empty(Game &game); // Cree un plateau vide

// Renvoie la piece
Piece get_square(const Game &game, int row, int col); 

// Place une piece 
void set_square(Game &game, int row, int col, Piece piece);

// Initialise le plateau avec la position de depart
void start(Game &game);

// Deplace une piece
void move_piece(Game &game, int src_row, int src_col, int dest_row, int dest_col);

#endif 