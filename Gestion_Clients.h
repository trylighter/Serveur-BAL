//
//  Gestion_Clients.h
//  Project Réseau/Langage_C
//
//  Created by FREGEFOND Théo & Bayle-Sales Axel on 26/02/2017.
//  Copyright © 2017 FREGEFOND Théo. All rights reserved.
//

#ifndef Gestion_Clients_h
#define Gestion_Clients_h



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


//Structure permettant d'identifier un client et de le chaîner avec les autres clients de la liste
struct Client
{
    int Socket_Client;              //Socket du client
    char Type_Client;               //Soit un client Emetteur "E" soit Recepteur "R"
    
    int longueur_client;            //Pour un client de type "E" c'est la longueur des messages qui vont être envoyés
                                    //Pour un client de type "R" c'est la longueur du message à recevoir
    int destinataire;               //Numéro du destinataire sur lequel le client veut écrire en type "E" ou recevoir en type "R"
    char*Message_A_Ecrire;          //Chaine de caractere à envoyer au client de type "R"
    
    struct Client*Client_Suivant;
};

//Structure permettant d'identifier une liste de client
struct Liste_Client
{
    struct Client*S_Client_Premier;
    struct Client*S_Client_Courant;
    struct Client*S_Client_Dernier;
};


/*##############################*/
//                              //
//  Declaration des fonctions   //
//                              //
/*##############################*/


//Permet d'initialiser une liste de client à gérer par le serveur
struct Liste_Client*Initialiser_Liste_Clients (void);


//Permet d'ajouter un client à une liste de client
struct Client*Ajouter_Client (struct Liste_Client*Une_Liste_Client , int sock_du_client);


//Permet de renvoyer la valeur du plus grand socket d'une liste de client
int Socket_Max (struct Liste_Client*Une_Liste_Client,int Sock_pere);


//Permet de supprimer le client pointer par le Client courant d'une liste de client
void Suppression_Client (struct Liste_Client*Une_Liste_Client,int sock_du_client);


//Fonction de test permettant de donner tous les sockets present dans une liste de client
void Client_Encore_En_Course(struct Liste_Client*Une_Liste_Client);


#endif /* Gestion_Clients_h */
