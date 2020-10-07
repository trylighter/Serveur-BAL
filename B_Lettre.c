//
//  B_Lettre.c
//  Project Réseau/Langage_C
//
//  Created by FREGEFOND Théo & Bayle-Sales Axel on 08/02/2017.
//  Copyright © 2017 FREGEFOND Théo. All rights reserved.
//

#include "B_Lettre.h"




/*##############################*/
//                              //
//     Corps des fonctions      //
//                              //
/*##############################*/


struct Liste_Destinataire*Ininialiser_Liste_Dest (void)

{
    struct Liste_Destinataire* Nouvelle_Liste_Dest = malloc(sizeof(struct Liste_Destinataire));
    
    Nouvelle_Liste_Dest->S_Dest_Courant=NULL;
    Nouvelle_Liste_Dest->S_Dest_Premier=NULL;
    Nouvelle_Liste_Dest->S_Dest_Dernier=NULL;
    
    return Nouvelle_Liste_Dest;
}




struct Liste_Lettre*Ininialiser_Liste_Lettre (void)

{
    struct Liste_Lettre* Nouvelle_Liste_Lettre = malloc(sizeof(struct Liste_Destinataire));
    
    Nouvelle_Liste_Lettre->S_Lettre_Courante=NULL;
    Nouvelle_Liste_Lettre->S_Lettre_Premiere=NULL;
    Nouvelle_Liste_Lettre->S_Lettre_Derniere=NULL;
    
    return Nouvelle_Liste_Lettre;
}




int Recuperation_Numero(char*message)
{
    int Un_Num_Dest=-1;
    int i=0;
    char *ptr;  //Ne sert à rien ici
    
    //Utile pour récuperer le numéro de destinataire dans l'entête d'un message
    while ((message[i]=='-')&&(i<4))
    {
        i++;
    }
    
    //strtol revoit 0 si il n'a pas trouvé on le tranforme en -1 pour signifier une erreur
    if ((Un_Num_Dest=(int)strtol(&message[i],&ptr,10))==0)
    {
        Un_Num_Dest=-1;
    }
    
    return Un_Num_Dest;
}





struct Liste_Lettre*Renvoi_Liste_Lettre(struct Liste_Destinataire*Une_Liste_Dest,int Un_num_dest)
{
    //Si la liste de destinataire est vide
    if (Une_Liste_Dest->S_Dest_Premier==NULL)
    {
        return NULL;
    }
    //Si la liste de destinataire est non vide
    else
    {
       Une_Liste_Dest->S_Dest_Courant=Une_Liste_Dest->S_Dest_Premier;
      
        while (((Une_Liste_Dest->S_Dest_Courant)!=NULL)&&((Une_Liste_Dest->S_Dest_Courant->num_destinataire)!=Un_num_dest))
        {
            Une_Liste_Dest->S_Dest_Courant=Une_Liste_Dest->S_Dest_Courant->Destinataire_Suivant;
        }
    
        //Si le destinataire n'est pas présent dans la liste
        if (Une_Liste_Dest->S_Dest_Courant==NULL)
        {
            return NULL;
        }
        //Si le destinataire a été trouvé
        else
        {
            return Une_Liste_Dest->S_Dest_Courant->Lettres_Du_Destinataire;
        }
    }
}





void Ajouter_Destinataire(struct Liste_Destinataire*Une_Liste_Dest,int Un_num_dest)
{
    struct Destinataire*Un_Nouveau_Dest=malloc(sizeof(struct Destinataire));
    
    Un_Nouveau_Dest->num_destinataire=Un_num_dest;
    Un_Nouveau_Dest->Lettres_Du_Destinataire=Ininialiser_Liste_Lettre();
    Un_Nouveau_Dest->Destinataire_Suivant=NULL;
    
    //Si la liste est vide
    if (Une_Liste_Dest->S_Dest_Premier==NULL)
    {
        Une_Liste_Dest->S_Dest_Premier=Un_Nouveau_Dest;
        Une_Liste_Dest->S_Dest_Dernier=Un_Nouveau_Dest;
    }
    //Si la liste est non vide on le rajoute en premier
    else
    {
        Un_Nouveau_Dest->Destinataire_Suivant=Une_Liste_Dest->S_Dest_Premier;
        Une_Liste_Dest->S_Dest_Premier=Un_Nouveau_Dest;
    }
}





void Stockage_Nouveau_Message(struct Liste_Lettre*Une_Liste_Lettre,char*message)
{
    struct Lettre*Nouvelle_Lettre=malloc(sizeof(struct Lettre));
    
    Nouvelle_Lettre->La_Lettre=malloc(strlen(message)*sizeof(char));
    Nouvelle_Lettre->Lettre_Suivante=NULL;
    
    strcpy(Nouvelle_Lettre->La_Lettre,message);
    
    //Cas si il n'y a aucune lettre dans la liste de lettre
    if (Une_Liste_Lettre->S_Lettre_Premiere==NULL)
    {
        
        Une_Liste_Lettre->S_Lettre_Premiere=Nouvelle_Lettre;
        Une_Liste_Lettre->S_Lettre_Derniere=Nouvelle_Lettre;
    }
    //Cas où il y a au moins un lettre dans la liste de lettre
    else
    {
        Nouvelle_Lettre->Lettre_Suivante=Une_Liste_Lettre->S_Lettre_Premiere;
        Une_Liste_Lettre->S_Lettre_Premiere=Nouvelle_Lettre;
    }
}




void Recuperation_Message(struct Liste_Lettre*Une_Liste_Lettre,char*message)
{
    //Cas où il n y a plus de lettre à récupérable
    if ((Une_Liste_Lettre->S_Lettre_Premiere)==NULL) {
        printf("Pas de message à récupérer\n");
        strcpy(message, "ERROR : No message available");
    }
    //Cas où il n y a une unique lettre dans la liste
    else if (Une_Liste_Lettre->S_Lettre_Premiere==Une_Liste_Lettre->S_Lettre_Derniere)
    {
         strcpy(message, Une_Liste_Lettre->S_Lettre_Premiere->La_Lettre);
         free(Une_Liste_Lettre->S_Lettre_Premiere);
         Une_Liste_Lettre->S_Lettre_Premiere=NULL;
         Une_Liste_Lettre->S_Lettre_Derniere=NULL;
    }
    //Cas ou il y a plus d'une lettre dans la liste
    else
    {
        strcpy(message, Une_Liste_Lettre->S_Lettre_Derniere->La_Lettre);
        
        Une_Liste_Lettre->S_Lettre_Courante=Une_Liste_Lettre->S_Lettre_Premiere;
        while ((Une_Liste_Lettre->S_Lettre_Courante->Lettre_Suivante)!=(Une_Liste_Lettre->S_Lettre_Derniere))
        {
            Une_Liste_Lettre->S_Lettre_Courante=Une_Liste_Lettre->S_Lettre_Courante->Lettre_Suivante;
        }
        free(Une_Liste_Lettre->S_Lettre_Derniere);
        Une_Liste_Lettre->S_Lettre_Derniere=Une_Liste_Lettre->S_Lettre_Courante;    
    }
    
}


