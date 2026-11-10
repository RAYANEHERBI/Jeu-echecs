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

    game.turn = WHITE;

    game.board[4][4] = {QUEEN, WHITE};
    game.board[7][0] = {ROOK, WHITE};

    game.board[4][6] = {PAWN, BLACK};
    game.board[2][4] = {KNIGHT, BLACK};
    game.board[7][4] = {BISHOP, BLACK};

    cout << "Plateau :" << endl;
    print_board(game);

    cout << endl;
    cout << "Pieces adverses qui peuvent etre prises :" << endl;
    highlight_attacked_pieces(game, mask);
    print_board(game, mask);

    return 0;
}