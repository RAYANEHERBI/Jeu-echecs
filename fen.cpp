#include "fen.hpp"
#include <fstream>
#include <cctype>
#include <iostream>

using namespace std;

//une f qui covertit une case en charactere fen 
char piece_to_char(Piece p){
    char c;
    switch(p.type){
        case PAWN:   c = 'P'; break;
        case ROOK:   c = 'R'; break;
        case KNIGHT: c = 'N'; break;
        case BISHOP: c = 'B'; break;
        case QUEEN:  c = 'Q'; break;
        case KING:   c = 'K'; break;
        case EMPTY:  c = '.'; break; // case vide
    }
    if (p.color == BLACK) c = tolower(c); // ca c est pour mettre les pieces noires en minscule
    return c ;
}

//une f qui convertit un caractere fen en piece 
Piece char_to_piece(char c ){
    Piece p ;

    if(c=='.'){
        p.type= EMPTY;
        p.color = NONE;
    }
    else{
        p.color = isupper(c) ? WHITE : BLACK ; //maj en blanc /min en noir
        switch(toupper(c)) {
            case 'P': p.type = PAWN; break;
            case 'R': p.type = ROOK; break;
            case 'N': p.type = KNIGHT; break;
            case 'B': p.type = BISHOP; break;
            case 'Q': p.type = QUEEN; break;
            case 'K': p.type = KING; break;
            default: p.type = EMPTY; p.color = NONE; break;
        }
    }
    return p;
}

//une f qui ecrit le plateau en fen dans un fichier
void write_fen(const Game &game , const string &filename){
    ofstream fic(filename);
    if(!fic){
        cout<<"ERREUR : impossible d ouvrir" << filename << "en ecriture " << endl;
        return;
    }// ouvre le fichier en mode ecriture 

    for (int row = 0; row < 8; row++) //lignes
    {
        int empty_count = 0; // compteur de cases vides consecutves 

        for (int col = 0; col < 8; col++)
        {
            Piece p =game.board[row][col];

            if (p.type == EMPTY){
                empty_count++; //si la case est vide on incremente le compteur 
            }
            else{
                if(empty_count>0){  // si on avait des cases vides dans cette piece on ecrit le nombre 
                    fic<<empty_count;
                    empty_count=0;
                }

                fic<< piece_to_char(p);//on acrit ;e caractere representant la piece
            }
        }
        if (empty_count > 0) fic<< empty_count ; // si la ligne se termine par des cases vides on ecrit leur nombre

        //ajoute / sauf pour la derniere ligne
        if (row != 7 ) fic <<"/";
        
    }
    fic.close();

    
} 

//lit un plateau depuis un fichier fen 
void read_fen(Game &game , const string &filename){
    //ouvre le fichier en mode lecture 
    ifstream fic(filename);
    if(!fic){
        cout << "ERREUR : impossible d'ouvrir " << filename << " en lecture." << endl;
        return;
    }

    // lit la ligne entiere contenant la notation fen 
    string line;
    getline(fic , line );
    fic.close();

    int row=0; //ligne du plateau
    int col=0;  // colonne

    for(char c :line){
        //parcours chaque caractere de la chaine fen
        if(c=='/'){ // le/ signifie qu on passe a la ligne suivante 
            row++;
            col=0;
        } 
        else if (isdigit(c)){ // ca veut dire si c est un chiffre il represente des cases vides cosecutives 
            int n = c -'0';
            for (int i=0; i<n;i++){
                game.board[row][col++]={EMPTY , NONE};
            }
        }
        else { // sinon c est une piece on la convertit en struct Piece 
            game.board[row][col++]= char_to_piece(c);
        }
    }
}
