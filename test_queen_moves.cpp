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

    game.board[4][4] = {QUEEN, WHITE};
    game.board[4][6] = {PAWN, BLACK};
    game.board[2][2] = {ROOK, BLACK};
    game.board[4][2] = {PAWN, WHITE};
    game.board[6][6] = {BISHOP, WHITE};

    cout << "Plateau :" << endl;
    print_board(game);

    highlight_possible_moves_queen(game, 4, 4, mask);

    cout << endl;
    cout << "Deplacements possibles de la dame :" << endl;
    print_board(game, mask);

    return 0;
}