#include "types.hpp"
#include "board.hpp"
#include "mask.hpp"
#include "view.hpp"
#include <iostream>

using namespace std;

int main() {
    Game game;
    Mask mask;
    empty(game);
    empty_mask(mask);

    game.board[4][4] = {ROOK, WHITE};
    game.board[2][4] = {PAWN, BLACK};
    game.board[4][6] = {PAWN, WHITE};

    highlight_possible_moves_rook(game, 4, 4, mask);

    print_board(game, mask);

    return 0;
}