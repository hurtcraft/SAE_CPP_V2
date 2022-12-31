#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include "function.hpp"
#include "functions_IA.hpp"
#include <time.h>



using namespace std;


bool debut_pareil(const char *mot, const char *current_word){

    int len_current_word = strlen(current_word);
    for (int i = 0; i < len_current_word; ++i){
        
        if (mot[i] != current_word[i])
            return false;
    }
    return true;


}

int premiere_occurence( char **liste_mots, int minimum, int maximum, const char *current_word){
    int min = minimum;
    int max =maximum - 1;
    int indice = -1;
    while(min <= max){
        int milieu = (min + max) / 2;
        if (debut_pareil(liste_mots[milieu], current_word)){
            indice = milieu;
            max = milieu -1;
        }
        else if(strcmp(liste_mots[milieu], current_word) > 0)
            max = milieu -1;
        else
            min = milieu +1;
    }
    return indice;
}

int derniere_occurence( char **liste_mots, int minimum, int maximum, const char *current_word){
    int min = minimum;
    int max = maximum - 1;
    int indice = -1;
    while(min <= max){
        int milieu = (min + max) / 2;
        if (debut_pareil(liste_mots[milieu], current_word)){
            indice = milieu;
            min = milieu +1;
        }
        else if(strcmp(liste_mots[milieu], current_word) > 0)
            max = milieu -1;
        else
            min = milieu +1;
    }
    return indice;
}

void get_solution_viable(char **liste_mots, const int min , const int max ,const int NB_JOUEURS,MANCHE &ma_manche){
    strcpy(ma_manche.solution,"NO_SOLUTION");
    if (min==-1 && max==-1)
    {
        return;
    }
    
    srand(time(NULL));
    int nombre_aleatoire;
    nombre_aleatoire=min + rand() % (( max + 1 ) - min);
    cout << "\ntest : " <<min <<" , "<< max <<" , "<< nombre_aleatoire<<"\n";
    
    //parcours les solutions entre un nombre aleatoire et max

    if (search_between_range(liste_mots,nombre_aleatoire-1,max,NB_JOUEURS,ma_manche))
    {
        return;
    }
    else{
        // parcours dans l'autre sens si il ne trouve pas de solution entre le nombre aleatoir et max
        search_between_range(liste_mots,min,nombre_aleatoire,NB_JOUEURS,ma_manche);
    }



}
bool search_between_range(char **liste_mots, const int min , const int max ,const int NB_JOUEURS,MANCHE &ma_manche){
    int longueur_mot;
    int len_current_word=strlen(ma_manche.current_word);
    char letter;
    char copie_current_word[MAX_CHAR];
    cout << ma_manche.current_word;
    strcpy(copie_current_word,ma_manche.current_word);
    for (size_t i = min; i <= max; i++)
    {
        longueur_mot=strlen(liste_mots[i]);
        if(longueur_mot<=2){
            continue;
        }
        if ((longueur_mot-len_current_word)>1 && (longueur_mot-len_current_word)<NB_JOUEURS ){
            strcpy(ma_manche.solution,liste_mots[i]);
            letter = ma_manche.solution[len_current_word];
            copie_current_word[len_current_word]=letter;
            if(is_in_dico(liste_mots,copie_current_word,min,max)){
                cout << "\n"<<i;
                i=derniere_occurence(liste_mots,i,max,copie_current_word);
                continue;
            }
            return true;
        }
    }
    return false;
}
char get_letter_of_solution(MANCHE &ma_manche){
    return ma_manche.solution[strlen(ma_manche.current_word)];
}
































