#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "function.hpp"
#include "functions_IA.hpp"

using namespace std ;

int get_nb_mot_dico(ifstream &file){
    char buffer[BUFFER_SIZE];
    int count = 0;
    file >> setw(256)>> buffer;
    while(file){
        count ++;
        file >> setw(BUFFER_SIZE) >>buffer;
    }
    return count;
}
bool verif_joueur(int argc , char *argv[]){
    if (argc!=2 ){
        cout << "saisir des joueurs H(humain) ou R(robot)"<< endl;
        return false;
    }
    int nb_joueurs=strlen(argv[argc-1]);

    for (size_t i = 0; i < nb_joueurs; i++)
    {
        if (argv[argc-1][i]!='H' && argv[argc-1][i]!='R'){
            cout << "argument invalide saisir H(humain) et R(robot)"<< endl;
            return false;
        }
    }
    if(nb_joueurs<2){
        cout << "nombre de joueurs insuffisant"<< endl;
        return false;
    }
    return true;

}

void dico_to_2Darray(char **liste_mots,int nb_mots, ifstream &file){
    
    file.clear();
    file.seekg(0,ios_base::beg); // on remet le curseur au début du fichier pour pouvoir reparcourir le fichier 
                                //car int get_nb_mot_dico(ifstream &file) parcours deja le fichier donc le curseur sera à la fin du fichier
    
    
    char buffer[BUFFER_SIZE];
    int longueur_mot;
    int count=0;
    file >> setw(BUFFER_SIZE)>> buffer;
    while(file){
        
        longueur_mot=strlen(buffer)+1;
        liste_mots[count]= new char[longueur_mot];
        
        strncpy(liste_mots[count],buffer,longueur_mot);
        file >> setw(BUFFER_SIZE) >>buffer;
        count++;
    }
}

void clear_2Darray(char **liste_mots , int nb_mots){
    for (size_t i = 0; i < nb_mots; i++)
    {
        delete [] liste_mots[i];
    }
    delete [] liste_mots;
    
}

bool is_in_dico( char **liste_mot ,  char *str, const int NB_MOTS){
    if(strlen(str)<=2){
        return false;
    }
    int min =0 ;
    int max =NB_MOTS;
    int millieu=(min+max)/2;
    while(min<=max){
        if (strcmp(liste_mot[millieu],str)==0 )
        {

            return true;
            
        }
        else if(strcmp(liste_mot[millieu],str)>0){
            max=millieu-1;
        }
        else{
            min=millieu+1;
        }
        millieu=(min+max)/2;
    }
    return false;

}



void create_joueurs(JOUEUR *liste_joueurs,char *str){
    /*
        liste_jouer -> liste en allocation dynamique qui va contenir tout les joueurs 
        str-> chaine qui nous dit quels seront les joueurs de la partie ex: "HRHR"
    */
   JOUEUR mon_joueur;

   for (size_t i = 0; i < strlen(str); i++)
   {
        mon_joueur.type=str[i];
        mon_joueur.nb_quart_singe=0;
        liste_joueurs[i]=mon_joueur;
   }
   
}
//affichage pour ?
void affichage_jeu(JOUEUR *current_player, MANCHE &ma_manche){

    cout << ma_manche.count+1 << current_player->type <<", "<<"("<< ma_manche.current_word<<")"<<" > ";

    
}
void clear_joueur_array(JOUEUR *liste_joueurs){
    delete [] liste_joueurs;
}

bool accepted_char(char &mon_char){
    
    return (isalpha(mon_char) || mon_char=='?' || mon_char=='!');
    
}
void user_input_str(MANCHE &ma_manche){
    
    cin >> setw(MAX_CHAR)>>ma_manche.buffer;
    cin.ignore(INT16_MAX, '\n');
    if (ma_manche.buffer[0]=='?' && strlen(ma_manche.current_word)<2)
    {
        cout << "nombre de lettres insuffisantes\n";
        return;
    }
    
    for (size_t i = 0; i < strlen(ma_manche.buffer); i++)
    {
        ma_manche.buffer[i]=toupper(ma_manche.buffer[i]);
    }
    
}
bool user_input_char(MANCHE &ma_manche){
    
    user_input_str(ma_manche);

    ma_manche.current_char=ma_manche.buffer[0];
    if (!accepted_char(ma_manche.current_char))
    {
        cout << "saisie incorrect veuillez saisir QUE des LETTRES \n";
        return false;
    }
    return true;
    
}


void concat_char(char *str,char letter){
    strncat(str,&letter,1);
    //str[strlen(str)]=letter;
    
}

void init_manche(MANCHE &ma_manche){
   
    ma_manche.count=0;
    ma_manche.current_char=0;
    memset(ma_manche.current_word,0,sizeof(ma_manche.current_word));
    memset(ma_manche.buffer,0,sizeof(ma_manche.buffer));

}
void print_nb_quart_singe(const JOUEUR *liste_joueurs,const int NB_JOUEUR){
    for (size_t i = 0; i < NB_JOUEUR; i++)
    {
        cout << i+1 << liste_joueurs[i].type << " : " <<liste_joueurs[i].nb_quart_singe;
        if (i<NB_JOUEUR-1)
        {
            cout << "; ";
        }
        
    }
    cout << "\n";
}
JOUEUR *get_previous_player( MANCHE &ma_manche, const int NB_JOUEUR , JOUEUR *liste_joueurs){
    ma_manche.count--;
    ma_manche.count+=NB_JOUEUR;
    ma_manche.count%=NB_JOUEUR;
    return &liste_joueurs[ma_manche.count];
    
}
JOUEUR *get_next_player( MANCHE &ma_manche, const int NB_JOUEUR , JOUEUR *liste_joueurs){
    ma_manche.count++;
    ma_manche.count+=NB_JOUEUR;
    ma_manche.count%=NB_JOUEUR;
    return &liste_joueurs[ma_manche.count];
    
}
void abandon(JOUEUR *current_player,bool &run,MANCHE &ma_manche){
    current_player->nb_quart_singe+=0.25;
    run=has_lost(current_player);
    cout<<"le joueur "<< ma_manche.count+1<<current_player->type <<" abandonne la manche et prend un quart de singe\n";
    memset(ma_manche.current_word,0,sizeof(ma_manche.current_word));
    memset(ma_manche.buffer,0,sizeof(ma_manche.buffer));
}
char random_letter(){
    srand(time(NULL));
    return 65 + rand() % (( 90 + 1 ) - 65);
}

bool has_lost(JOUEUR *joueur){
    return joueur->nb_quart_singe!=1.0;
}