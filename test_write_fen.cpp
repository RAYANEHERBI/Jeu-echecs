#include "types.hpp"
#include "board.hpp"
#include "fen.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Usage: ./test_write_fen fichier.txt" << endl;
        return 1;
    }

    Game game;

    // creer plateau initial
    start(game);

    // ecrire FEN
    write_fen(game, argv[1]);

    cout << "FEN ecrite dans " << argv[1] << endl;

    return 0;
}