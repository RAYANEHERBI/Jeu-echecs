#include "game.hpp"
#include "board.hpp"
#include "mask.hpp"
#include "echec.hpp"
#include "historique.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// cette fonction decide qui joue
//blanc :humain / noir:ordinateur
void one_run(Game &game){
    if(game.turn == WHITE){
        one_run_human(game); // humain
    } else {
        one_run_computer(game); // ordi
    }
}

//humain
//demande un coup a l user le verifie puis le joue si valide
void one_run_human(Game &game) {
    int sr, sc, dr, dc;

    if (king_in_check(game, game.turn)) {
        cout << "Votre roi est en echec." << endl;
    }

    choose_movement_human(sr, sc, dr, dc);

    if (test_run(game, sr, sc, dr, dc)) {
        move_piece(game, sr, sc, dr, dc);
        cout << "Coup joue !" << endl;
    } else {
        cout << "Coup invalide !" << endl;
    }
}
//l user entre pos de depart et d arrivee
void choose_movement_human(int &sr, int &sc, int &dr, int &dc){
    cout << "Depart (ligne colonne) : ";
    cin >> sr >> sc;

    cout << "Arrivee (ligne colonne) : ";
    cin >> dr >> dc;
}


//verifie si le coup est valide 
bool test_run(const Game &game, int sr, int sc, int dr, int dc) {
    if (sr < 0 || sr >= 8 || sc < 0 || sc >= 8 ||
        dr < 0 || dr >= 8 || dc < 0 || dc >= 8) {
        return false;
    }

    Piece p = game.board[sr][sc];

    if (p.type == EMPTY) {
        return false;
    }

    if (p.color != game.turn) {
        return false;
    }

    Piece dest = game.board[dr][dc];

    if (dest.type != EMPTY && dest.color == p.color) {
        return false;
    }

    Mask mask;
    empty_mask(mask);
    highlight_possible_moves(game, sr, sc, mask);

    if (mask[dr][dc] != 1) {
        return false;
    }

    if (!move_keeps_king_safe(game, sr, sc, dr, dc)) {
        return false;
    }

    return true;
}

//ordi

//l ordi joue un coup alea valide
void one_run_computer(Game &game) {
    int sr, sc, dr, dc;

    if (king_in_check(game, game.turn)) {
        cout << "Le roi de l ordinateur est en echec." << endl;
        choose_movement_king_in_check_computer(game, sr, sc, dr, dc);
    } else {
        choose_movement_computer(game, sr, sc, dr, dc);
    }

    move_piece(game, sr, sc, dr, dc);

    cout << "Ordinateur joue : "
         << sr << "," << sc << " -> "
         << dr << "," << dc << endl;
}

//choisir une piece alea calculer ses mouvements et choisir une des valide
void choose_movement_computer(const Game &game, int &sr, int &sc, int &dr, int &dc) {
    int moves[4096][4];
    int count = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece p = game.board[i][j];

            if (p.type == EMPTY || p.color != game.turn) {
                continue;
            }

            Mask mask;
            empty_mask(mask);
            highlight_possible_moves(game, i, j, mask);

            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    if (mask[r][c] == 1 && test_run(game, i, j, r, c)) {
                        moves[count][0] = i;
                        moves[count][1] = j;
                        moves[count][2] = r;
                        moves[count][3] = c;
                        count++;
                    }
                }
            }
        }
    }

    if (count == 0) {
        sr = 0;
        sc = 0;
        dr = 0;
        dc = 0;
        return;
    }

    int choice = rand() % count;

    sr = moves[choice][0];
    sc = moves[choice][1];
    dr = moves[choice][2];
    dc = moves[choice][3];
}

// Choisit un coup legal pour l ordinateur lorsque son roi est en echec
void choose_movement_king_in_check_computer(const Game &game,int &sr,int &sc,int &dr,int &dc) {
    choose_movement_computer(game, sr, sc, dr, dc);
}