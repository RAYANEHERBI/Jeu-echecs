#ifndef GAME_HPP
#define GAME_HPP

#include "types.hpp"

// boucle principale
void one_run(Game &game);

// humain
void one_run_human(Game &game);
void choose_movement_human(int &sr, int &sc, int &dr, int &dc);
bool test_run(const Game &game, int sr, int sc, int dr, int dc);

// ordi
void one_run_computer(Game &game);
void choose_movement_computer(const Game &game, int &sr, int &sc, int &dr, int &dc);
void choose_movement_king_in_check_computer(const Game &game, int &sr, int &sc, int &dr, int &dc);

#endif