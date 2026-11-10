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

    game.board[4][4] = {BISHOP, WHITE};
    game.board[2][2] = {PAWN, BLACK};

    game.board[6][6] = {PAWN, WHITE};

    cout << "Plateau :" << endl;
    print_board(game);

    highlight_possible_moves_bishop(game, 4, 4, mask);

    cout << endl;
    cout << "Deplacements possibles du fou :" << endl;
    print_board(game, mask);

    return 0;
}