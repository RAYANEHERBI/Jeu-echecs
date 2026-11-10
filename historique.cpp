#include "historique.hpp"
#include "board.hpp"
#include "view.hpp"
#include <iostream>

using namespace std;

// Copie tout le plateau source vers destination.
static void copier_plateau(Piece destination[8][8], const Piece source[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

// Copie la liste des pieces capturees.
static void copier_pieces_capturees(Piece destination[32], const Piece source[32]) {
    for (int i = 0; i < 32; i++) {
        destination[i] = source[i];
    }
}

// Initialise l historique avec l etat actuel du jeu.
void init_historique(Game &game) {
    game.historique.nb_coups = 0;

    copier_plateau(game.historique.initial_board, game.board);
    game.historique.initial_turn = game.turn;

    copier_pieces_capturees(game.historique.initial_captured_white, game.captured_white);
    copier_pieces_capturees(game.historique.initial_captured_black, game.captured_black);

    game.historique.initial_nb_captured_white = game.nb_captured_white;
    game.historique.initial_nb_captured_black = game.nb_captured_black;
}

// Ajoute le coup joue et l etat du jeu dans l historique.
void maj_historique(Game &game,
                    int src_row, int src_col,
                    int dest_row, int dest_col,
                    Piece piece_deplacee,
                    Piece piece_capturee) {
    if (game.historique.nb_coups >= MAX_HISTORIQUE) {
        cout << "Erreur : historique plein." << endl;
        return;
    }

    int index = game.historique.nb_coups;

    game.historique.coups[index].src_row = src_row;
    game.historique.coups[index].src_col = src_col;
    game.historique.coups[index].dest_row = dest_row;
    game.historique.coups[index].dest_col = dest_col;

    game.historique.coups[index].piece_deplacee = piece_deplacee;
    game.historique.coups[index].piece_capturee = piece_capturee;

    copier_plateau(game.historique.coups[index].board_after, game.board);
    game.historique.coups[index].turn_after = game.turn;

    copier_pieces_capturees(game.historique.coups[index].captured_white_after,
                            game.captured_white);
    copier_pieces_capturees(game.historique.coups[index].captured_black_after,
                            game.captured_black);

    game.historique.coups[index].nb_captured_white_after = game.nb_captured_white;
    game.historique.coups[index].nb_captured_black_after = game.nb_captured_black;

    game.historique.nb_coups++;
}

// Joue un coup puis appelle la mise a jour de l historique.
void jouer_coup_historique(Game &game,
                           int src_row, int src_col,
                           int dest_row, int dest_col) {
    Piece piece_deplacee = game.board[src_row][src_col];
    Piece piece_capturee = game.board[dest_row][dest_col];

    move_piece(game, src_row, src_col, dest_row, dest_col);

    maj_historique(game,
                   src_row, src_col,
                   dest_row, dest_col,
                   piece_deplacee,
                   piece_capturee);
}

// Convertit une piece en lettre pour l affichage de l historique.
static char piece_to_letter(Piece piece) {
    if (piece.type == EMPTY) {
        return '.';
    }

    char c = '?';

    switch (piece.type) {
        case PAWN:   c = 'P'; break;
        case ROOK:   c = 'R'; break;
        case KNIGHT: c = 'N'; break;
        case BISHOP: c = 'B'; break;
        case QUEEN:  c = 'Q'; break;
        case KING:   c = 'K'; break;
        default:     c = '?'; break;
    }

    if (piece.color == BLACK && c >= 'A' && c <= 'Z') {
        c = c + ('a' - 'A');
    }

    return c;
}

// Affiche chaque coup de l historique avec le plateau obtenu.
void play_historique(const Game &game) {
    if (game.historique.nb_coups == 0) {
        cout << "Historique vide." << endl;
        return;
    }

    Game affichage = game;

    for (int k = 0; k < game.historique.nb_coups; k++) {
        const Coup &coup = game.historique.coups[k];

        cout << endl;
        cout << "Coup " << k + 1 << " : ";
        cout << piece_to_letter(coup.piece_deplacee) << " ";
        cout << "(" << coup.src_row << "," << coup.src_col << ") -> ";
        cout << "(" << coup.dest_row << "," << coup.dest_col << ")";

        if (coup.piece_capturee.type != EMPTY) {
            cout << " capture " << piece_to_letter(coup.piece_capturee);
        }

        cout << endl;

        copier_plateau(affichage.board, coup.board_after);
        affichage.turn = coup.turn_after;

        affichage.nb_captured_white = coup.nb_captured_white_after;
        affichage.nb_captured_black = coup.nb_captured_black_after;

        copier_pieces_capturees(affichage.captured_white, coup.captured_white_after);
        copier_pieces_capturees(affichage.captured_black, coup.captured_black_after);

        print_board(affichage);
    }
}

// Revient en arriere et restaure l etat du jeu correspondant.
void backtrack_historique(Game &game, int nb_coups_retour) {
    if (nb_coups_retour <= 0) {
        return;
    }

    if (nb_coups_retour > game.historique.nb_coups) {
        nb_coups_retour = game.historique.nb_coups;
    }

    game.historique.nb_coups -= nb_coups_retour;

    if (game.historique.nb_coups == 0) {
        copier_plateau(game.board, game.historique.initial_board);
        game.turn = game.historique.initial_turn;

        copier_pieces_capturees(game.captured_white,
                                game.historique.initial_captured_white);
        copier_pieces_capturees(game.captured_black,
                                game.historique.initial_captured_black);

        game.nb_captured_white = game.historique.initial_nb_captured_white;
        game.nb_captured_black = game.historique.initial_nb_captured_black;

        return;
    }

    const Coup &dernier_coup = game.historique.coups[game.historique.nb_coups - 1];

    copier_plateau(game.board, dernier_coup.board_after);
    game.turn = dernier_coup.turn_after;

    copier_pieces_capturees(game.captured_white, dernier_coup.captured_white_after);
    copier_pieces_capturees(game.captured_black, dernier_coup.captured_black_after);

    game.nb_captured_white = dernier_coup.nb_captured_white_after;
    game.nb_captured_black = dernier_coup.nb_captured_black_after;
}