//
//  B_Lettre.h
//  Project Réseau/Langage_C
//
//  Created by FREGEFOND Théo & Bayle-Sales Axel on 08/02/2017.
//  Copyright © 2017 FREGEFOND Théo. All rights reserved.
//

#ifndef B_Lettre_h
#define B_Lettre_h


/*##############################*/
//                              //
//  Importation des fichiers    //
//                              //
/*##############################*/

#include "Header.h"


/*##############################*/
//                              //
//  Declaration des structures  //
//                              //
/*##############################*/

//Structure permettant de stocker une lettre et de la chaîner avec d'autres lettres
struct Lettre
{
    char*La_Lettre;                 //Chaine de caractère contenue dans la lettre
    
    struct Lettre*Lettre_Suivante;      
};

//Structure permettant d'identifier la liste de lettre d'un destinataire
struct Liste_Lettre
{
    struct Lettre*S_Lettre_Premiere;
    struct Lettre*S_Lettre_Courante;
    struct Lettre*S_Lettre_Derniere;
};

struct Destinataire
{
    int num_destinataire;                               //Numéro unique attribué à un destinataire du serveur
    struct Liste_Lettre*Lettres_Du_Destinataire;        //Lien vers la liste de lettre du destinataire
    
    struct Destinataire*Destinataire_Suivant;
    
};


//Structure permettant d'identifier une liste de destinataire
struct Liste_Destinataire
{
    struct Destinataire*S_Dest_Premier;
    struct Destinataire*S_Dest_Courant;
    struct Destinataire*S_Dest_Dernier;
};


/*##############################*/
//                              //
//  Declaration des fonctions   //
//                              //
/*##############################*/


//Permet d'initialiser une liste de destinataire
struct Liste_Destinataire*Ininialiser_Liste_Dest (void);


//Permet d'initialiser une liste de Lettre
struct Liste_Lettre*Ininialiser_Liste_Lettre (void);


//Permet de récuperer un nombre dans une châine de caractère donnée
int Recuperation_Numero(char*message);


//Permet d'aller chercher la Liste de Lettre du destinataire selectionner
struct Liste_Lettre*Renvoi_Liste_Lettre(struct Liste_Destinataire*Une_Liste_Dest,int Un_num_dest);


//Permet d'ajouter un destinataire dans une liste
void Ajouter_Destinataire(struct Liste_Destinataire*Une_Liste_Dest,int Un_num_dest);


//Permet d'aller stocker un message en sommet d'une liste de lettre
void Stockage_Nouveau_Message(struct Liste_Lettre*Une_Liste_Lettre,char*message);


//Permet d'aller chercher un message en sommet d'une liste de lettre et de le supprimer de la liste de lettre
void Recuperation_Message(struct Liste_Lettre*Une_Liste_Lettre,char*message);


#endif /* B_Lettre_h */
