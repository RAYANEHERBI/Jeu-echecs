#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "echec.hpp"
#include <iostream>

using namespace std;

int main() {
    Game game;
    empty(game);

    game.turn = BLACK;

    // Roi noir en a8
    game.board[0][0] = {KING, BLACK};

    // Roi blanc en c6
    game.board[2][2] = {KING, WHITE};

    // Dame blanche en b7 : elle attaque a8 et controle les cases de fuite
    game.board[1][1] = {QUEEN, WHITE};

    cout << "Position de test echec et mat :" << endl;
    print_board(game);

    if (!king_in_check(game, BLACK)) {
        cout << "Erreur : le roi noir devrait etre en echec." << endl;
        return 1;
    }

    if (!king_in_checkmate(game, BLACK)) {
        cout << "Erreur : le roi noir devrait etre echec et mat." << endl;
        return 1;
    }

    cout << "Test king_in_checkmate reussi." << endl;
    return 0;
}