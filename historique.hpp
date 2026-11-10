#ifndef HISTORIQUE_HPP_
#define HISTORIQUE_HPP_

#include "types.hpp"

// Initialise l historique avec l etat actuel du jeu.
void init_historique(Game &game);

// Ajoute un coup joue dans l historique.
void maj_historique(Game &game, int src_row, int src_col, int dest_row, int dest_col, Piece piece_deplacee, Piece piece_capturee);

// Joue un coup puis met a jour l historique.
void jouer_coup_historique(Game &game, int src_row, int src_col, int dest_row, int dest_col);

// Affiche les plateaux successifs de l historique.
void play_historique(const Game &game);

// Revient en arriere de nb_coups_retour coups.
void backtrack_historique(Game &game, int nb_coups_retour);

#endif