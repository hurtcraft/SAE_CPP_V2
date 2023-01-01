#ifndef __FUNCTION_HPP
#define __FUNCCTION_HPP

#include <fstream>

enum {
    BUFFER_SIZE=256,
    MAX_CHAR=26,
    
};
typedef struct JOUEUR{
    char type;
    float nb_quart_singe;
}JOUEUR;
typedef struct MANCHE{
    char current_word[MAX_CHAR];
    char buffer[MAX_CHAR];
    int count;
    char current_char;
    char solution[MAX_CHAR];
}MANCHE;
int get_nb_mot_dico(std::ifstream &file);
bool verif_joueur(int argc , char *argv[]);
void dico_to_2Darray(char **liste_mots,int nb_mots, std::ifstream &file);
void clear_2Darray(char **liste_mots , int nb_mots);

void init_manche(MANCHE &ma_manche);
bool is_in_dico( char **liste_mot ,  char *str, int min,int max);
void create_joueurs(JOUEUR *liste_joueurs,char *str);
void clear_joueur_array(JOUEUR *liste_joueurs);
void affichage_jeu(JOUEUR *current_player, MANCHE &ma_manche);
void user_input_str(MANCHE &ma_manche);
bool accepted_char(char &mon_char);
bool user_input_char(MANCHE &ma_manche);
void print_nb_quart_singe(const JOUEUR *liste_joueurs,const int NB_JOUEUR);
void concat_char(char *str,char letter);

JOUEUR *get_previous_player( MANCHE &ma_manche, const int NB_JOUEUR , JOUEUR *liste_joueurs);
JOUEUR *get_next_player(MANCHE &ma_manche, const int NB_JOUEUR , JOUEUR *liste_joueurs);
char random_letter();
void abandon(JOUEUR *current_player,bool &run,MANCHE &ma_manche);
bool has_lost(JOUEUR *joueur);





#endif 