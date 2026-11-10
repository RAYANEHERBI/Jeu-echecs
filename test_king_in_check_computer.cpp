#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "game.hpp"
#include "echec.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Teste le choix d un coup legal par l ordinateur quand son roi est en echec.
int main() {
    srand(time(0));

    Game game;
    empty(game);

    game.turn = BLACK;

    // La tour blanche met le roi noir en echec sur la colonne e.
    game.board[0][4] = {KING, BLACK};
    game.board[7][4] = {ROOK, WHITE};
    game.board[7][0] = {KING, WHITE};

    cout << "Position initiale :" << endl;
    print_board(game);

    if (!king_in_check(game, BLACK)) {
        cout << "Erreur : le roi noir devrait etre en echec." << endl;
        return 1;
    }

    int sr, sc, dr, dc;

    choose_movement_king_in_check_computer(game, sr, sc, dr, dc);

    if (!test_run(game, sr, sc, dr, dc)) {
        cout << "Erreur : l ordinateur n a pas choisi un coup legal." << endl;
        return 1;
    }

    move_piece(game, sr, sc, dr, dc);

    cout << "Apres le coup de l ordinateur :" << endl;
    print_board(game);

    if (king_in_check(game, BLACK)) {
        cout << "Erreur : le roi noir est encore en echec." << endl;
        return 1;
    }

    cout << "Test ordinateur en echec reussi." << endl;
    return 0;
}