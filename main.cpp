#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "game.hpp"
#include "historique.hpp"
#include "echec.hpp"
#include <iostream>
#include <ctime>

using namespace std;

int main() {

    srand(time(0)); // pour le random de l ordinateur

    Game game;
    start(game);
    init_historique(game);

    int nb_coups = 0;
    const int MAX_COUPS = 50;

    // boucle du jeu
    while (nb_coups < MAX_COUPS) {

        cout << endl;
        cout << "Tour du joueur : "
             << (game.turn == WHITE ? "BLANC" : "NOIR")
             << endl;

        print_board(game);

        // joue un tour humain ou ordinateur
        one_run(game);

        nb_coups++;
    }

    cout << endl;
    cout << "Partie terminee : limite de 50 coups atteinte." << endl;

    int score_white = score_material(game, WHITE);
    int score_black = score_material(game, BLACK);

    cout << "Score BLANC : " << score_white << endl;
    cout << "Score NOIR  : " << score_black << endl;

    if (score_white > score_black) {
        cout << "Gagnant : BLANC" << endl;
    } else if (score_black > score_white) {
        cout << "Gagnant : NOIR" << endl;
    } else {
        cout << "Egalite." << endl;
    }

    return 0;
}