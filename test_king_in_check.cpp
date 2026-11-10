#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "echec.hpp"
#include <iostream>

using namespace std;

// Teste la detection d un roi en echec.
int main() {
    Game game;
    empty(game);

    game.turn = WHITE;

    // La tour noire attaque le roi blanc sur la meme colonne.
    game.board[7][4] = {KING, WHITE};
    game.board[0][4] = {ROOK, BLACK};
    game.board[0][0] = {KING, BLACK};

    print_board(game);

    if (!king_in_check(game, WHITE)) {
        cout << "Erreur : le roi blanc devrait etre en echec." << endl;
        return 1;
    }

    if (king_in_check(game, BLACK)) {
        cout << "Erreur : le roi noir ne devrait pas etre en echec." << endl;
        return 1;
    }

    cout << "Test king_in_check reussi." << endl;
    return 0;
}