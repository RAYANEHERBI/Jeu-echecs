#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include <iostream>

using namespace std;

int main() {
    Game game;
    Mask mask;

    start(game);
    clear_mask(mask);

    cout << "Plateau initial :" << endl;
    print_board(game);

    cout << endl;
    cout << "Pieces qui peuvent se deplacer :" << endl;
    highlight_movable_pieces(game, mask);
    print_board(game, mask);

    return 0;
}