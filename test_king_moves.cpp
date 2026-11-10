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

    game.board[4][4] = {KING, WHITE};
    game.board[3][4] = {PAWN, WHITE};
    game.board[3][3] = {PAWN, BLACK};

    highlight_possible_moves_king(game, 4, 4, mask);

    print_board(game, mask);

    return 0;
}