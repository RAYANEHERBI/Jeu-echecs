#ifndef MASK_HPP_
#define MASK_HPP_

#include "types.hpp"
#include "view.hpp"

void empty_mask(Mask mask);                             //cree un masque sans information (tous a 0)
void clear_mask(Mask mask);                             //reinitialise toutes les valeurs a 0
int get_mask(Mask mask, int row, int col);              //lit le contenu d une case
void set_mask(Mask mask, int row, int col, int val);    //modifie le contenu d une case

// ── affichage (surcharge de print_board / print_square_color) ─────────────────

// Convertit une valeur de masque en code couleur ANSI (fond)
// 0  → fond classique de l'échiquier (comportement inchangé)
// >0 → couleur de mise en évidence choisie
void set_background(bool is_white_square, int mask_value);

// Affiche une case avec le fond du masque + la pièce
void print_square_color(Piece piece, bool is_white_square, int mask_value);

// Affiche le plateau entier avec les informations du masque superposées
void print_board(const Game &game, Mask mask);

void highlight_possible_moves(const Game &game, int row, int col, Mask mask);
void highlight_possible_moves_king(const Game &game, int row, int col, Mask mask);
void highlight_possible_moves_rook(const Game &game, int row, int col, Mask mask);
void highlight_possible_moves_bishop(const Game &game, int row, int col, Mask mask);
void highlight_possible_moves_knight(const Game &game, int row, int col, Mask mask);
void highlight_possible_moves_queen(const Game &game, int row, int col, Mask mask);
void highlight_possible_moves_pawn(const Game &game, int row, int col, Mask mask);


void highlight_movable_pieces(const Game &game, Mask mask);
void highlight_attacked_pieces(const Game &game, Mask mask);
void highlight_take_pieces(const Game &game, int row, int col, Mask mask);

void mask_choices_menu();
void mask_choices(const Game &game);

#endif