//
//  Gestion_Clients.c
//  Project Réseau/Langage_C
//
//  Created by FREGEFOND Théo & Bayle-Sales Axel on 26/02/2017.
//  Copyright © 2017 FREGEFOND Théo. All rights reserved.
//

#include "Gestion_Clients.h"




/*##############################*/
//                              //
//     Corps des fonctions      //
//                              //
/*##############################*/


struct Liste_Client*Initialiser_Liste_Clients (void)

{
    struct Liste_Client* Nouvelle_Liste_Client = malloc(sizeof(struct Liste_Client));
    
    Nouvelle_Liste_Client->S_Client_Premier=NULL;
    Nouvelle_Liste_Client->S_Client_Courant=NULL;
    Nouvelle_Liste_Client->S_Client_Dernier=NULL;
    
    return Nouvelle_Liste_Client;
}




struct Client*Ajouter_Client (struct Liste_Client*Une_Liste_Client , int sock_du_client)
{
    //Initialisation de la nouvelle fiche client avec la valeur de son socket
    
    struct Client*Nouveau_Client = malloc(sizeof(struct Client));
    
    Nouveau_Client->Message_A_Ecrire=NULL;
    Nouveau_Client->Socket_Client=sock_du_client;
    Nouveau_Client->Client_Suivant=NULL;
    Nouveau_Client->Type_Client='?';
    Nouveau_Client->longueur_client=-1;
    Nouveau_Client->destinataire=-1;
    
    //Chaînage du nouveau client dans la liste
    
    //Si la liste est vide
    if (Une_Liste_Client->S_Client_Premier==NULL)
    {
        Une_Liste_Client->S_Client_Premier=Nouveau_Client;
        Une_Liste_Client->S_Client_Dernier=Nouveau_Client;
    }
    //Si la Liste de client n'est pas vide
    else
    {
        Une_Liste_Client->S_Client_Dernier->Client_Suivant=Nouveau_Client;
        Une_Liste_Client->S_Client_Dernier=Nouveau_Client;
    }
    
    return Nouveau_Client;
}




void Suppression_Client (struct Liste_Client*Une_Liste_Client,int sock_du_client)
{
    
    //Verification supplémentaire si le client a le bon socket
    if (Une_Liste_Client->S_Client_Courant->Socket_Client!=sock_du_client)
    {
        printf("Mauvais socket supression non autorisé\n");
        exit(1);
    }
    
    
    //Verification si la liste est non vide
    if (Une_Liste_Client->S_Client_Courant!=NULL)
    {
        //Si il y a qu'un seul client dans la liste
        if (Une_Liste_Client->S_Client_Dernier==Une_Liste_Client->S_Client_Premier) {
            free(Une_Liste_Client->S_Client_Courant);
            Une_Liste_Client->S_Client_Premier=Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Dernier=NULL;
            
        }
        //Si c'est le premier client de la liste mais pas le seul
        else if(Une_Liste_Client->S_Client_Courant==Une_Liste_Client->S_Client_Premier)
        {
            Une_Liste_Client->S_Client_Premier=Une_Liste_Client->S_Client_Premier->Client_Suivant;
            free(Une_Liste_Client->S_Client_Courant);
            Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Premier;
        }
        //Si il n'est pas le premier client de la liste
        else
        {
            struct Client*Client_A_Supprime=Une_Liste_Client->S_Client_Courant;
            
            Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Premier;
            while(Une_Liste_Client->S_Client_Courant->Client_Suivant!=Client_A_Supprime)
            {
                Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Courant->Client_Suivant;
            }
            
            //Si c'est le dernier client de la liste
            if (Une_Liste_Client->S_Client_Courant->Client_Suivant==Une_Liste_Client->S_Client_Dernier)
            {
                Une_Liste_Client->S_Client_Dernier=Une_Liste_Client->S_Client_Courant;
                Une_Liste_Client->S_Client_Dernier->Client_Suivant=NULL;
            }
            //Partout ailleurs
            else
            {
                Une_Liste_Client->S_Client_Courant->Client_Suivant=Client_A_Supprime->Client_Suivant;
            }
            
            free(Client_A_Supprime);
        }
    }
}




int Socket_Max (struct Liste_Client*Une_Liste_Client,int Sock_pere)
{
    //Max prendra par défaut la valeur du Socket du processus père et non celui de STDIN_FILENO qui est de valeur 0
    int Max=Sock_pere;
    
    //Si la liste est non vide
    if (Une_Liste_Client->S_Client_Premier!=NULL) {
        
        Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Premier;
        
        while ((Une_Liste_Client->S_Client_Courant!=NULL))
        {
            if ((Une_Liste_Client->S_Client_Courant->Socket_Client)>Max)
            {
                Max=Une_Liste_Client->S_Client_Courant->Socket_Client;
            }
            
            Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Courant->Client_Suivant;
        }
    }
    return Max;
}




//Programme de test pour verifier la création de nouveau client et leur suppresion en cas d'inactivité
void Client_Encore_En_Course(struct Liste_Client*Une_Liste_Client)
{Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Premier;
    
    printf("Client encore en course : ");
    
    while (Une_Liste_Client->S_Client_Courant!=NULL)
    {
        printf("%d ",Une_Liste_Client->S_Client_Courant->Socket_Client);
        Une_Liste_Client->S_Client_Courant=Une_Liste_Client->S_Client_Courant->Client_Suivant;
    }
    
    printf("\n");
}

