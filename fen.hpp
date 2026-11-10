#ifndef FEN_HPP_
#define FEN_HPP_

#include "types.hpp"
#include <string>

using namespace std;

// Convertit une piece en caractere FEN.
char piece_to_char(Piece p);

// Convertit un caractere FEN en piece.
Piece char_to_piece(char c);

// Ecrit le plateau du jeu dans un fichier au format FEN.
void write_fen(const Game &game, const string &filename);

// Lit un plateau depuis un fichier au format FEN.
void read_fen(Game &game, const string &filename);

#endif