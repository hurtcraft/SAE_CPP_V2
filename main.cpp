#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "function.hpp"
#include "functions_IA.hpp"


using namespace std ;

int main(int argc , char *argv[]){
    /*
    if (!verif_joueur(argc,argv)){
        exit(EXIT_FAILURE);
    }
    */
    ifstream file("ods4.txt");
    if (!file.is_open())
    {
        cerr<<"impossible d'ouvrir le fichier";
        exit(EXIT_FAILURE);
    }
    
    const int NB_JOUEUR=strlen(argv[1]);
    const int NB_MOTS=get_nb_mot_dico(file);

    char **liste_mots=NULL;
    //initiation de la liste de mot
    liste_mots=new char*[NB_MOTS];
    if (liste_mots==NULL)
    {
        cerr << "allocation liste_mots echouer";
        exit(EXIT_FAILURE);
    }
    
    dico_to_2Darray(liste_mots,NB_MOTS,file);
    file.close();

    //initiation des joueurs 
    JOUEUR *liste_joueurs=NULL;
    liste_joueurs=new JOUEUR[NB_JOUEUR];
    if (liste_joueurs==NULL)
    {
        cerr << "allocation liste_joueurs echouer";
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    

    create_joueurs(liste_joueurs,argv[1]);
    //bool abandon=false;
    JOUEUR *current_player;
    MANCHE ma_manche;
    init_manche(ma_manche);
    //char current_char;


    bool run=true;
    int min=0;
    int max=NB_MOTS;
    char bot_letter;
    bool solution_exist;
    

    srand(time(NULL));

    
    
    while (run)
    {

        min = premiere_occurence(liste_mots,min,max,ma_manche.current_word);
        max = derniere_occurence(liste_mots,min,max,ma_manche.current_word);
        
        
        //cout <<ma_manche.solution <<" "<<min<<" , "<<max<<endl;
        current_player=&liste_joueurs[ma_manche.count];
        affichage_jeu(current_player,ma_manche);

        if (current_player->type=='H')
        {
            if (!user_input_char(ma_manche.buffer,ma_manche.current_char))
            {
            // si le joueur rentre autre chose qu'une lettre ou un ? ou un ! alors on reviens en début de boucle
            continue;
            }
        }
        else{
            if (liste_joueurs[0].type=='R' && ma_manche.current_word[0]=='\0')
            {
                bot_letter= 65 + rand() % (( 90 + 1 ) - 65);// on choisi une lettre entre A - Z
                ma_manche.current_char=bot_letter;
            }
            else{
                get_solution_viable(liste_mots,min,max,NB_JOUEUR,ma_manche);
                if(strcmp(ma_manche.solution,"NO_SOLUTION")==0){
                    bot_letter='?';
                }
                else{
                    bot_letter=get_letter_of_solution(ma_manche);
                
                }
            
                ma_manche.current_char=bot_letter;
            }

            cout << bot_letter <<endl;
            cout << "\n"<<"solution : " <<ma_manche.solution<<min<<" , "<<max<<endl;

            
        }
        if (min==-1 || max==-1)
        {
            //si min = -1 alors max aussi est égale à -1
            //-1 signifie qu'il n'ya pas doccurence trouvé 
            //par conséquent si on laisse min,max à -1
            // la fonction is_in_dico() va planté , 
            //c'est pourquoi on redonne des valeurs a min,max
            min=0;
            max=NB_MOTS;
        }


        concat_char(ma_manche.current_word,ma_manche.current_char);
        if (is_in_dico(liste_mots,ma_manche.current_word,min,max))
        {
            solution_exist=true;
            current_player->nb_quart_singe+=0.25;
            run=has_lost(current_player);
            cout << "le mot "<<ma_manche.current_word<< " existe, le joueur "<<ma_manche.count+1<<current_player->type<< " prend un quart de singe\n",
            print_nb_quart_singe(liste_joueurs,NB_JOUEUR);
            memset(ma_manche.current_word,0,sizeof(ma_manche.current_word));
            memset(ma_manche.buffer,0,sizeof(ma_manche.buffer));
            continue;
        }
        else{
            solution_exist=false;
        }
        
        if (ma_manche.current_char=='?')
        {
            
            current_player=get_previous_player(ma_manche,NB_JOUEUR,liste_joueurs);
            ma_manche.current_word[strlen(ma_manche.current_word)-1]=0;
            cout << ma_manche.count+1 << current_player->type<< ", saisir le mot > ";
            if (current_player->type=='H'){
                user_input_str(ma_manche.buffer);
            }
            else{
                get_solution_viable(liste_mots,min,max,NB_JOUEUR,ma_manche);
                if (strcmp(ma_manche.solution,"NO_SOLUTION")==0)
                {
                    ma_manche.current_char='!';
                    abandon(current_player,run,ma_manche);
                    print_nb_quart_singe(liste_joueurs,NB_JOUEUR);
                }
                else{
                    strcpy(ma_manche.buffer,ma_manche.solution);
                }
                
            }
            //cout<<ma_manche.buffer<<endl;
            if (debut_pareil(ma_manche.buffer,ma_manche.current_word))
            {
                if (is_in_dico(liste_mots,ma_manche.buffer,min,max))
                {
                current_player=get_next_player(ma_manche,NB_JOUEUR,liste_joueurs);
                cout<< "le mot " << ma_manche.buffer <<" existe, ";
                }
                else{
                cout<< "le mot " << ma_manche.buffer <<" n'existe pas ";
                }
            }
            else{
                cout <<"le mot "<<ma_manche.buffer<<" ne commence pas par les lettres attendues, ";
            }

            cout <<"le joueur " <<ma_manche.count+1<<current_player->type<< " prend un quart de singe\n";
            current_player->nb_quart_singe+=0.25;
            run=has_lost(current_player);
            print_nb_quart_singe(liste_joueurs,NB_JOUEUR);
            memset(ma_manche.current_word,0,sizeof(ma_manche.current_word));
            memset(ma_manche.buffer,0,sizeof(ma_manche.buffer));
            continue;
            
        }
        if (ma_manche.current_char=='!'){
            abandon(current_player,run,ma_manche);
            print_nb_quart_singe(liste_joueurs,NB_JOUEUR);
            
            continue;
        }



        if (strcmp(ma_manche.buffer,"EXIT")==0)
        {
            clear_joueur_array(liste_joueurs);
            clear_2Darray(liste_mots,NB_MOTS);
            return 0;
        }
        else if(strcmp(ma_manche.buffer,"SINGE")==0){
            print_nb_quart_singe(liste_joueurs,NB_JOUEUR);

        }
        

        ma_manche.count++;
        ma_manche.count = ma_manche.count % NB_JOUEUR;

    }

    cout <<"La partie est finie"<<endl;

    

    clear_joueur_array(liste_joueurs);
    clear_2Darray(liste_mots,NB_MOTS);

    
    return 0;
}

