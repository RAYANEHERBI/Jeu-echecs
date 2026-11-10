#ifndef ECHEC_HPP_
#define ECHEC_HPP_

#include "types.hpp"

// Teste si le roi est en echec
bool king_in_check(const Game &game, Color color);

// Teste si le coup garde le roi du joueur en securite
bool move_keeps_king_safe(const Game &game, int sr, int sc, int dr, int dc);

// Teste le joueur possede au moins un coup legal
bool has_legal_move(const Game &game, Color color);

// Calcule le score d'un joueur
int score_material(const Game &game, Color color);

// Teste si le roi de color est echec et mat
bool king_in_checkmate(const Game &game, Color color);

#endif