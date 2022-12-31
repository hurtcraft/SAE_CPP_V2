#ifndef __FUNCTION_IA_HPP
#define __FUNCTION_IA_HPP

#include <fstream>



bool debut_pareil(const char *mot, const char *current_word);

int premiere_occurence( char **liste_mots, int minimum, int maximum, const char *current_word);
int derniere_occurence( char **liste_mots, int minimum, int maximum, const char *current_word);
void get_solution_viable( char **liste_mots, const int min , const int max ,const int NB_JOUEURS,MANCHE &ma_manche);
bool search_between_range(char **liste_mots, const int min , const int max ,const int NB_JOUEURS,MANCHE &ma_manche);
bool letter_is_safe(char **liste_mots,char letter, MANCHE ma_manche,int min , int max);
char get_letter_of_solution(MANCHE &ma_manche);
char bluff(char **liste_mots,MANCHE ma_manche,int min , int max);



#endif 