#include "types.hpp"
#include "board.hpp"
#include "view.hpp"
#include "historique.hpp"
#include <iostream>

using namespace std;

// Teste l ajout, l affichage et le retour en arriere de l historique.
int main() {
    Game game;

    start(game);
    init_historique(game);

    // Trois coups sont joues et ajoutes dans l historique.
    jouer_coup_historique(game, 6, 4, 4, 4); // e2 -> e4
    jouer_coup_historique(game, 1, 4, 3, 4); // e7 -> e5
    jouer_coup_historique(game, 7, 6, 5, 5); // g1 -> f3

    cout << "Historique complet :" << endl;
    play_historique(game);

    // Retour en arriere de deux coups.
    backtrack_historique(game, 2);

    if (game.historique.nb_coups != 1) {
        cout << "Erreur : il devrait rester 1 coup apres retour en arriere." << endl;
        return 1;
    }

    if (game.board[4][4].type != PAWN || game.board[4][4].color != WHITE) {
        cout << "Erreur : le pion blanc devrait etre en e4 apres le backtrack." << endl;
        return 1;
    }

    if (game.board[1][4].type != PAWN || game.board[1][4].color != BLACK) {
        cout << "Erreur : le pion noir devrait etre revenu en e7 apres le backtrack." << endl;
        return 1;
    }

    if (game.board[7][6].type != KNIGHT || game.board[7][6].color != WHITE) {
        cout << "Erreur : le cavalier blanc devrait etre revenu en g1." << endl;
        return 1;
    }

    cout << "Test historique reussi." << endl;
    return 0;
}