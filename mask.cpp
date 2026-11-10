#include "mask.hpp"

using namespace std;

#define RESET "\x1b[0m"

// Crée un masque sans information (toutes les cases à 0)
void empty_mask(Mask mask) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            mask[i][j] = 0;
}

// Réinitialise un masque aux valeurs 0
void clear_mask(Mask mask) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            mask[i][j] = 0;
}

// Lit le contenu d'une case du masque
int get_mask(Mask mask, int row, int col) {
    return mask[row][col];
}

// Modifie le contenu d'une case du masque
void set_mask(Mask mask, int row, int col, int value) {
    mask[row][col] = value;
}

// Affichage (surcharges)
void set_background(bool is_white_square, int mask_value) {
    switch (mask_value) {
        // comportement original : fond de l'échiquier
        case 0: 
            if (is_white_square)
                cout << "\x1b[48;5;245m";
            else
                cout << "\x1b[48;5;230m";
        break;
        // bleu  (déplacements possibles)
        case 1:  cout << "\x1b[48;5;27m";  break;
        // rouge (pièces attaquables)
        case 2:  cout << "\x1b[48;5;160m"; break;    
        // vert  (pièces non attaquables / pièces pouvant se déplacer)
        case 3:  cout << "\x1b[48;5;34m";  break;
        // bleu clair (pièces pouvant attaquer une cible)
        case 4:  cout << "\x1b[48;5;39m";  break;
        // magenta (valeur inconnue, pour le débogage)
        default: cout << "\x1b[48;5;129m";
            break;
            
    }
}

// Surcharge pour afficher une case avec le fond issu du masque
void print_square_color(Piece piece, bool is_white_square, int mask_value) {
    set_background(is_white_square, mask_value);
    set_foreground(piece);
    cout << " ";    // espace après le symbole
    cout << RESET;
}

// Surcharge : affiche le plateau entier avec les couleurs du masque superposées
void print_board(const Game &game, Mask mask) {
    cout << "  a b c d e f g h" << endl;

    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            bool is_white_square = (i + j) % 2 == 0;
            int  mask_value      = mask[i][j];
            print_square_color(game.board[i][j], is_white_square, mask_value);
        }
        cout << " " << 8 - i << endl;
    }

    cout << "  a b c d e f g h" << endl;
}

void highlight_possible_moves(const Game &game, int row, int col, Mask mask) {
    Piece piece = game.board[row][col]; // recupere la piece situe a la pos row,col

    //si la case est vide aucun coup possible
    if (piece.type == EMPTY) {
        clear_mask(mask);// on vide le mask
        return;
    }

        //selon le type de la piece on appelle la foction
    if (piece.type == KING) {
        highlight_possible_moves_king(game, row, col, mask);
    }
    else if (piece.type == ROOK) {
        highlight_possible_moves_rook(game, row, col, mask);
    }
    else if (piece.type == BISHOP) {
        highlight_possible_moves_bishop(game, row, col, mask);
    }
    else if (piece.type == KNIGHT) {
        highlight_possible_moves_knight(game, row, col, mask);
    }
    else if (piece.type == QUEEN) {
        highlight_possible_moves_queen(game, row, col, mask);
    }
    else if (piece.type == PAWN) {
        highlight_possible_moves_pawn(game, row, col, mask);
    }
}

void highlight_possible_moves_king(const Game &game, int row, int col, Mask mask) {
    Piece king = game.board[row][col]; //on recupere le roi a la position donnee

    //parcours tout les directions autour du roi
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {

            // on saute la case du roi 
            if (dr == 0 && dc == 0) {
                continue;
            }
            //nouvelle position possible
            int new_row = row + dr;
            int new_col = col + dc;

            // vérifier que la case reste dans le plateau
            if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {

                //recupere la piece sur la case cible
                Piece target = game.board[new_row][new_col];

                // case vide ou pièce enemie donc mouvement possi ble
                if (target.type == EMPTY || target.color != king.color) {
                    mask[new_row][new_col] = 1; // on marque la case
                }
            }
        }
    }
}

void highlight_possible_moves_rook(const Game &game, int row, int col, Mask mask) {
    Piece rook = game.board[row][col]; // recupere la tour

    // vers le haut
    //pour aller vers le haut on diminue le numero de lignes 
    for (int i = row - 1; i >= 0; i--) {
        //on regarde le case situee a la ligne i et a la meme col
        Piece target = game.board[i][col];

        //si la case est vide la tour peut aller dessus on met 1 dans le mask
        if (target.type == EMPTY) {
            mask[i][col] = 1;
        }
        else {
            //si c pas la meme couleur la tour peut la capturer
            if (target.color != rook.color) {
                mask[i][col] = 1;
            }
            break;// on s arrete ici prcq la tour peut pas sauter 
        }
    }

    // bas
    //on augmente le numero de la ligne
    for (int i = row + 1; i < 8; i++) {
        Piece target = game.board[i][col];

        if (target.type == EMPTY) {
            mask[i][col] = 1;
        }
        else {
            if (target.color != rook.color) {
                mask[i][col] = 1;
            }
            break;
        }
    }

    // gauche 
    //on diminue le numero de colonnes
    for (int j = col - 1; j >= 0; j--) {
        //on regarde la case situee sur la meme ligne mais col j
        Piece target = game.board[row][j];

        if (target.type == EMPTY) {
            mask[row][j] = 1;
        }
        else {
            if (target.color != rook.color) {
                mask[row][j] = 1;
            }
            break;
        }
    }

    // droite
    //on augmente le nombre de colonnes
    for (int j = col + 1; j < 8; j++) {
        Piece target = game.board[row][j];

        if (target.type == EMPTY) {
            mask[row][j] = 1;
        }
        else {
            if (target.color != rook.color) {
                mask[row][j] = 1;
            }
            break;
        }
    }
}
void highlight_possible_moves_bishop(const Game &game, int row, int col, Mask mask) {
    //on cide le mask pour effacer les ncien deoplacements
    clear_mask(mask);

    // On récupère la pièce de départ (fou)
    Piece piece = game.board[row][col];

    // Sécurité : si la case est vide il n y a rien à calculer
    if (piece.type == EMPTY) {
        return;
    }

    // haut gauche
    //pour aller en cette direction on diminue row-1 et col-1
    int i = row - 1;
    int j = col - 1;

    while (i >= 0 && j >= 0) {//tant qu on est dans le plateau 
        // Si la case est vide le fou peut avancer
        if (game.board[i][j].type == EMPTY) {
            mask[i][j] = 1;
        }
        else {
            // Si la pièce rencontrée est ennemie le fou peut la prendre
            if (game.board[i][j].color != piece.color) {
                mask[i][j] = 1;
            }
            // Ensuite on s arrête dans tous les cas
            break;
        }
        //on avance d une case
        i--;
        j--;
    }

    // haut droite
    i = row - 1;
    j = col + 1;

    while (i >= 0 && j < 8) {
        if (game.board[i][j].type == EMPTY) {
            mask[i][j] = 1;
        }
        else {
            if (game.board[i][j].color != piece.color) {
                mask[i][j] = 1;
            }
            break;
        }

        i--;
        j++;
    }

    //bas gauche
    i = row + 1;
    j = col - 1;

    while (i < 8 && j >= 0) {
        if (game.board[i][j].type == EMPTY) {
            mask[i][j] = 1;
        }
        else {
            if (game.board[i][j].color != piece.color) {
                mask[i][j] = 1;
            }
            break;
        }

        i++;
        j--;
    }

    // bas droite
    i = row + 1;
    j = col + 1;

    while (i < 8 && j < 8) {
        if (game.board[i][j].type == EMPTY) {
            mask[i][j] = 1;
        }
        else {
            if (game.board[i][j].color != piece.color) {
                mask[i][j] = 1;
            }
            break;
        }

        i++;
        j++;
    }
}

void highlight_possible_moves_knight(const Game &game, int row, int col, Mask mask) {
    clear_mask(mask);

    // On récupère la pièce située sur la case de départ
    Piece piece = game.board[row][col];

    // Si la case est vide y a rien à faire
    if (piece.type == EMPTY) {
        return;
    }

    // Tableau contenant les 8 déplacements possibles du cavalier
    int moves[8][2] = {
        {-2, -1}, {-2,  1},
        {-1, -2}, {-1,  2},
        { 1, -2}, { 1,  2},
        { 2, -1}, { 2,  1}
    };

    // On teste chaque déplacement possible
    for (int k = 0; k < 8; k++) {
        //nouvelles ligne/col apres l aplication du deplacement de k
        int new_row = row + moves[k][0];
        int new_col = col + moves[k][1];

        // On vérifie que la case obtenue reste dans le plateau
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {

            // Si la case est vide, le cavalier peut y aller
            if (game.board[new_row][new_col].type == EMPTY) {
                mask[new_row][new_col] = 1;
            }
            // Si la case contient une pièce ennemie le cavalier peut aussi y aller
            else if (game.board[new_row][new_col].color != piece.color) {
                mask[new_row][new_col] = 1;
            }
        }
    }
}

void highlight_possible_moves_queen(const Game &game, int row, int col, Mask mask) {
    clear_mask(mask);//on vide le mask pour supprimer les anciens deplacements

    //on recupere la piece situee sur la case de depart
    Piece piece = game.board[row][col];

    // Si la case de départ est vide on arrête
    if (piece.type == EMPTY) {
        return;
    }

    // Partie TOUR

    // Haut
    // on diminue les lignes 
    for (int i = row - 1; i >= 0; i--) {
        if (game.board[i][col].type == EMPTY) {
            mask[i][col] = 1;
        } else {
            if (game.board[i][col].color != piece.color) {
                mask[i][col] = 1;
            }
            break;
        }
    }

    // Bas
    for (int i = row + 1; i < 8; i++) {
        if (game.board[i][col].type == EMPTY) {
            mask[i][col] = 1;
        } else {
            if (game.board[i][col].color != piece.color) {
                mask[i][col] = 1;
            }
            break;
        }
    }

    // Gauche
    // diminue les colonnes 
    for (int j = col - 1; j >= 0; j--) {
        if (game.board[row][j].type == EMPTY) {
            mask[row][j] = 1;
        } else {
            if (game.board[row][j].color != piece.color) {
                mask[row][j] = 1;
            }
            break;
        }
    }

    // Droite
    for (int j = col + 1; j < 8; j++) {
        if (game.board[row][j].type == EMPTY) {
            mask[row][j] = 1;
        } else {
            if (game.board[row][j].color != piece.color) {
                mask[row][j] = 1;
            }
            break;
        }
    }

    // Partie FOU

    // Haut gauche
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        if (game.board[row - i][col - i].type == EMPTY) {
            mask[row - i][col - i] = 1;
        } else {
            if (game.board[row - i][col - i].color != piece.color) {
                mask[row - i][col - i] = 1;
            }
            break;
        }
    }

    // Haut droite
    for (int i = 1; row - i >= 0 && col + i < 8; i++) {
        if (game.board[row - i][col + i].type == EMPTY) {
            mask[row - i][col + i] = 1;
        } else {
            if (game.board[row - i][col + i].color != piece.color) {
                mask[row - i][col + i] = 1;
            }
            break;
        }
    }

    // Bas gauche
    for (int i = 1; row + i < 8 && col - i >= 0; i++) {
        if (game.board[row + i][col - i].type == EMPTY) {
            mask[row + i][col - i] = 1;
        } else {
            if (game.board[row + i][col - i].color != piece.color) {
                mask[row + i][col - i] = 1;
            }
            break;
        }
    }

    // Bas droite
    for (int i = 1; row + i < 8 && col + i < 8; i++) {
        if (game.board[row + i][col + i].type == EMPTY) {
            mask[row + i][col + i] = 1;
        } else {
            if (game.board[row + i][col + i].color != piece.color) {
                mask[row + i][col + i] = 1;
            }
            break;
        }
    }
}

void highlight_possible_moves_pawn(const Game &game, int row, int col, Mask mask) {
    
    clear_mask(mask);// on vide le mask

    Piece piece = game.board[row][col];

    // Si la case est vide, on arrête
    if (piece.type == EMPTY) {
        return;
    }

    // Si ce n est pas un pion on arrête 
    if (piece.type != PAWN) {
        return;
    }

    // Cas du pion blanc
    //les pions blancs montent dans le plateau
    if (piece.color == WHITE) {
        // Avancer d une case vers le haut
        //on verifie la case juste au dessus row-1
        if (row - 1 >= 0 && game.board[row - 1][col].type == EMPTY) { //si la case est dans le plateau et la case devant est vide
            mask[row - 1][col] = 1; // deplacement possible

            // Avancer de deux cases depuis la ligne de départ
            if (row == 6 && game.board[row - 2][col].type == EMPTY) {
                mask[row - 2][col] = 1;
            }
        }

        // Prise diagonale à gauche
        if (row - 1 >= 0 && col - 1 >= 0) {
            // on verifie qu il y a une piece sur cette case et que cette piece est noire
            if (game.board[row - 1][col - 1].type != EMPTY &&
                game.board[row - 1][col - 1].color == BLACK) {
                mask[row - 1][col - 1] = 1; // capture possible
            }
        }

        // Prise diagonale à droite
        if (row - 1 >= 0 && col + 1 < 8) {
            //case droite contient une pc noire
            if (game.board[row - 1][col + 1].type != EMPTY &&
                game.board[row - 1][col + 1].color == BLACK) {
                mask[row - 1][col + 1] = 1;
            }
        }
    }

    // Cas du pion noir
    // les pions noirs decendent dans le plateau (row+1)
    else if (piece.color == BLACK) {
        // Avancer d une case
        if (row + 1 < 8 && game.board[row + 1][col].type == EMPTY) {
            mask[row + 1][col] = 1;

            // Avancer de deux cases depuis la ligne de départ
            if (row == 1 && game.board[row + 2][col].type == EMPTY) {
                mask[row + 2][col] = 1;
            }
        }

        // Prise diagonale à gauche
        if (row + 1 < 8 && col - 1 >= 0) {
            if (game.board[row + 1][col - 1].type != EMPTY &&
                game.board[row + 1][col - 1].color == WHITE) {
                mask[row + 1][col - 1] = 1;
            }
        }

        // Prise diagonale à droite
        if (row + 1 < 8 && col + 1 < 8) {
            if (game.board[row + 1][col + 1].type != EMPTY &&
                game.board[row + 1][col + 1].color == WHITE) {
                mask[row + 1][col + 1] = 1;
            }
        }
    }
}



// Met en évidence les pièces du joueur courant qui peuvent bouger
void highlight_movable_pieces(const Game &game, Mask mask) {
    clear_mask(mask);//on vide le mask 

    Mask temp;//mask temporaire
    //sert a stocker les deplacements possible d une seule piece

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            // On ne traite que les pièces du joueur dont c est le tour
            if (game.board[i][j].color == game.turn) {

                clear_mask(temp);// on vide le mask temporaire avant de tester cette piece 

                // On calcule les déplacements possibles de cette pièce
                highlight_possible_moves(game, i, j, temp);
                
                //on suppose que la piece ne peut pas bouger
                bool can_move = false;

                // On regarde si au moins une case est accessible
                //on parcourt tt le mask temp
                //si on trouve au moin  une case diff de 0 cela veut dire que la piece a au moin un deplacement
                for (int r = 0; r < 8; r++) {
                    for (int c = 0; c < 8; c++) {
                        if (temp[r][c] != 0) {
                            can_move = true;
                        }
                    }
                }

                // Si oui2 on colore la case de la pièce
                if (can_move) {
                    mask[i][j] = 3;
                }
            }
        }
    }
}

// Met en évidence les pièces adverses qui peuvent être prises
void highlight_attacked_pieces(const Game &game, Mask mask) {
    clear_mask(mask);

    Mask temp;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            // On regarde les pièces du joueur courant
            if (game.board[i][j].color == game.turn) {

                clear_mask(temp);

                // On calcule les déplacements possibles
                highlight_possible_moves(game, i, j, temp);

                // On cherche les cases atteignables occupées par un ennemi
                for (int r = 0; r < 8; r++) { //parcourt tt les cases atteignables
                    for (int c = 0; c < 8; c++) {
                        // case est atteignable
                        // case contient une piece
                        // cette piece est ennemie
                        if (temp[r][c] != 0 &&
                            game.board[r][c].type != EMPTY &&
                            game.board[r][c].color != game.turn) {
                            mask[r][c] = 2; // on marque cette case dans le mask principal 
                        }
                    }
                }
            }
        }
    }
}

// Met en évidence les pièces ennemies qui peuvent prendre
// la pièce située en (row, col)
void highlight_take_pieces(const Game &game, int row, int col, Mask mask) {
    clear_mask(mask);

    Piece target = game.board[row][col];

    // Si la case choisie est vide, on ne fait rien
    if (target.type == EMPTY) {
        return;
    }

    Mask temp;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            // On cherche les pièces de couleur adverse
            if (game.board[i][j].type != EMPTY &&
                game.board[i][j].color != target.color) {

                clear_mask(temp);

                // On calcule les déplacements possibles de cette pièce ennemie
                highlight_possible_moves(game, i, j, temp);

                // Si elle peut atteindre la case cible, elle est dangereuse
                if (temp[row][col] != 0) {
                    mask[i][j] = 4;
                }
            }
        }
    }
}

// F pour afficher le menu des masques disponibles
void mask_choices_menu() {
    cout << endl;
    cout << " MENU DES MASQUES :" << endl;
    cout << "1 - Voir les pieces qui peuvent bouger" << endl;
    cout << "2 - Voir les pieces adverses qui peuvent etre prises" << endl;
    cout << "3 - Voir les pieces dangereuses pour une piece" << endl;
    cout << "0 - Quitter le menu" << endl;
    cout << "Votre choix : ";
}


// Permet au joueur de choisir et d'afficher autant de masques qu'il veut
void mask_choices(const Game &game) {
    int choix;
    Mask mask;

    do {
        clear_mask(mask);
        mask_choices_menu();
        cin >> choix;

        if (choix == 1) {
            highlight_movable_pieces(game, mask);

            cout << endl;
            cout << "Pieces qui peuvent bouger :" << endl;
            print_board(game, mask);
        }
        else if (choix == 2) {
            highlight_attacked_pieces(game, mask);

            cout << endl;
            cout << "Pieces adverses attaquables :" << endl;
            print_board(game, mask);
        }
        else if (choix == 3) {
            int row, col;

            cout << "Donner la ligne de la piece (0 a 7) : ";
            cin >> row;
            cout << "Donner la colonne de la piece (0 a 7) : ";
            cin >> col;

            if (row >= 0 && row < 8 && col >= 0 && col < 8) {
                highlight_take_pieces(game, row, col, mask);

                cout << endl;
                cout << "Pieces dangereuses pour la case choisie :" << endl;
                print_board(game, mask);
            }
            else {
                cout << "Position invalide." << endl;
            }
        }
        else if (choix == 0) {
            cout << "Fin du menu." << endl;
        }
        else {
            cout << "Choix invalide." << endl;
        }

    } while (choix != 0);
}

