#ifndef TYPES_HPP_
#define TYPES_HPP_

// Couleurs possibles
enum Color {
    NONE,   // pour les cases vides
    WHITE, //blanc
    BLACK //noir
};

// Types de pieces
enum PieceType {
    EMPTY, //case vides 
    PAWN, //pions
    ROOK, //tour
    KNIGHT, //cavalier
    BISHOP, //fou
    QUEEN, //reine
    KING  //roi
};

// Structure d une piece
struct Piece {
    PieceType type;
    Color color;
};// donc une piece a un type et une couleur

const int MAX_HISTORIQUE = 512;

// Structure d un coup joue dans la partie
struct Coup {
    int src_row;
    int src_col;
    int dest_row;
    int dest_col;

    Piece piece_deplacee;
    Piece piece_capturee;

    // Etat du jeu apres ce coup
    Piece board_after[8][8];
    Color turn_after;

    Piece captured_white_after[32];
    Piece captured_black_after[32];
    int nb_captured_white_after;
    int nb_captured_black_after;
};

// Structure de l historique de la partie
struct Historique {
    Coup coups[MAX_HISTORIQUE];
    int nb_coups;

    // Etat initial, utile pour revenir au debut
    Piece initial_board[8][8];
    Color initial_turn;

    Piece initial_captured_white[32];
    Piece initial_captured_black[32];
    int initial_nb_captured_white;
    int initial_nb_captured_black;
};

// Structure du jeu
struct Game {
    Piece board[8][8]; // plateau 8x8
    Color turn;        // joueur dont c est le tour

    // pieces capturees
    Piece captured_white[32];
    Piece captured_black[32];
    int nb_captured_white;
    int nb_captured_black;
    
    //Stockage de l historique de jeu
    Historique historique;
};

// Masque utilise pour afficher les deplacements ou les attaques
typedef int Mask[8][8];

#endif 