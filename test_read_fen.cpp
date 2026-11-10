#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "fen.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    // vérifier qu on donne un fichier
    if (argc < 2) {
        cout << "Usage: ./test_read_fen fichier.txt" << endl;
        return 1;
    }

    Game game;

    // lire la FEN
    read_fen(game, argv[1]);

    // afficher le plateau
    print_board(game);

    return 0;
}