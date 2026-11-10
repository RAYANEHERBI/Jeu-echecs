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

    // Pion blanc
    game.board[6][3] = {PAWN, WHITE};

    // Pièces noires que le pion blanc peut prendre
    game.board[5][2] = {ROOK, BLACK};
    game.board[5][4] = {KNIGHT, BLACK};

    cout << "Plateau :" << endl;
    print_board(game);

    highlight_possible_moves_pawn(game, 6, 3, mask);

    cout << endl;
    cout << "Deplacements possibles du pion blanc :" << endl;
    print_board(game, mask);

    return 0;
}