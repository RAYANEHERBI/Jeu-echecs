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

    game.board[4][4] = {KNIGHT, WHITE};
    game.board[2][3] = {PAWN, BLACK};
    game.board[3][2] = {PAWN, WHITE};

    cout << "Plateau :" << endl;
    print_board(game);

    highlight_possible_moves_knight(game, 4, 4, mask);

    cout << endl;
    cout << "Deplacements possibles du cavalier :" << endl;
    print_board(game, mask);

    return 0;
}