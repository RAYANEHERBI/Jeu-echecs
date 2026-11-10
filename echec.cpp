#include "echec.hpp"
#include "board.hpp"
#include "mask.hpp"

// Verifie si une case est dans le plateau.
static bool inside_board(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

// Cherche la position du roi de la couleur donnee.
static bool find_king(const Game &game, Color color, int &king_row, int &king_col) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece p = game.board[i][j];

            if (p.type == KING && p.color == color) {
                king_row = i;
                king_col = j;
                return true;
            }
        }
    }

    return false;
}

// Verifie qu aucune piece ne bloque une ligne de deplacement.
static bool clear_line(const Game &game, int sr, int sc, int dr, int dc) {
    int row_step = 0;
    int col_step = 0;

    if (dr > sr) row_step = 1;
    if (dr < sr) row_step = -1;

    if (dc > sc) col_step = 1;
    if (dc < sc) col_step = -1;

    int r = sr + row_step;
    int c = sc + col_step;

    while (r != dr || c != dc) {
        if (game.board[r][c].type != EMPTY) {
            return false;
        }

        r += row_step;
        c += col_step;
    }

    return true;
}

// Verifie si une piece attaque une case donnee.
static bool piece_attacks_square(const Game &game,
                                 int piece_row,
                                 int piece_col,
                                 int target_row,
                                 int target_col) {
    Piece p = game.board[piece_row][piece_col];

    if (p.type == EMPTY) {
        return false;
    }

    int dr = target_row - piece_row;
    int dc = target_col - piece_col;

    if (p.type == PAWN) {
        if (p.color == WHITE) {
            return dr == -1 && (dc == -1 || dc == 1);
        } else {
            return dr == 1 && (dc == -1 || dc == 1);
        }
    }

    if (p.type == KNIGHT) {
        return ((dr == 2 || dr == -2) && (dc == 1 || dc == -1))
            || ((dr == 1 || dr == -1) && (dc == 2 || dc == -2));
    }

    if (p.type == KING) {
        return dr >= -1 && dr <= 1
            && dc >= -1 && dc <= 1
            && !(dr == 0 && dc == 0);
    }

    if (p.type == ROOK) {
        if (piece_row == target_row || piece_col == target_col) {
            return clear_line(game, piece_row, piece_col, target_row, target_col);
        }

        return false;
    }

    if (p.type == BISHOP) {
        if (dr == dc || dr == -dc) {
            return clear_line(game, piece_row, piece_col, target_row, target_col);
        }

        return false;
    }

    if (p.type == QUEEN) {
        if (piece_row == target_row || piece_col == target_col ||
            dr == dc || dr == -dc) {
            return clear_line(game, piece_row, piece_col, target_row, target_col);
        }

        return false;
    }

    return false;
}

// Teste si le roi de color est attaque.
bool king_in_check(const Game &game, Color color) {
    int king_row;
    int king_col;

    if (!find_king(game, color, king_row, king_col)) {
        return false;
    }

    Color enemy;

    if (color == WHITE) {
        enemy = BLACK;
    } else {
        enemy = WHITE;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece p = game.board[i][j];

            if (p.type != EMPTY && p.color == enemy) {
                if (piece_attacks_square(game, i, j, king_row, king_col)) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Simule un coup et verifie que le roi reste protege.
bool move_keeps_king_safe(const Game &game, int sr, int sc, int dr, int dc) {
    if (!inside_board(sr, sc) || !inside_board(dr, dc)) {
        return false;
    }

    Piece p = game.board[sr][sc];

    if (p.type == EMPTY) {
        return false;
    }

    Game copy = game;

    move_piece(copy, sr, sc, dr, dc);

    return !king_in_check(copy, p.color);
}

// Verifie si color possede au moins un coup permi
bool has_legal_move(const Game &game, Color color) {
    for (int sr = 0; sr < 8; sr++) {
        for (int sc = 0; sc < 8; sc++) {
            Piece p = game.board[sr][sc];

            if (p.type == EMPTY || p.color != color) {
                continue;
            }

            Mask mask;
            empty_mask(mask);
            highlight_possible_moves(game, sr, sc, mask);

            for (int dr = 0; dr < 8; dr++) {
                for (int dc = 0; dc < 8; dc++) {
                    if (mask[dr][dc] == 1 &&
                        move_keeps_king_safe(game, sr, sc, dr, dc)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// Renvoie la valeur d une piece.
static int piece_value(Piece p) {
    if (p.type == PAWN) return 1;
    if (p.type == KNIGHT) return 3;
    if (p.type == BISHOP) return 3;
    if (p.type == ROOK) return 5;
    if (p.type == QUEEN) return 9;

    return 0;
}

// Calcule le score
int score_material(const Game &game, Color color) {
    int score = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece p = game.board[i][j];

            if (p.type != EMPTY && p.color == color) {
                score += piece_value(p);
            }
        }
    }

    return score;
}

// Teste si le roi est en echec et mat.
bool king_in_checkmate(const Game &game, Color color) {
    return king_in_check(game, color) && !has_legal_move(game, color);
}