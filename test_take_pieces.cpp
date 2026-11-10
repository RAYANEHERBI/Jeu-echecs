#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include <iostream>

using namespace std;

int main() {
    Game game;
    Mask mask;

    empty(game);
    clear_mask(mask);

    // Pièce blanche cible
    game.board[4][3] = {PAWN, WHITE};

    // Pièces noires
    game.board[4][7] = {ROOK, BLACK};
    game.board[2][3] = {QUEEN, BLACK};
    game.board[3][2] = {BISHOP, BLACK};

    cout << "Plateau :" << endl;
    print_board(game);

    cout << endl;
    cout << "Pieces dangereuses pour la piece blanche en d4 :" << endl;
    highlight_take_pieces(game, 4, 3, mask);
    print_board(game, mask);

    return 0;
}