//
//  Header.h
//  Project Réseau/Langage_C
//
//  Created by FREGEFOND Théo & Bayle-Sales Axel on 31/01/2017.
//  Copyright © 2017 FREGEFOND Théo. All rights reserved.
//

#ifndef Header_h
#define Header_h

/*####################################*/
//                                    //
//   Declaration des modifications    //
//                                    //
/*####################################*/

#define MAXSIZE 100             //Taille maximale des chaines de caractère                              /*Modfiable*/
#define MINSIZE 5               //Taille minimale des chaines de caractères
#define DEFAULT_SIZE 30         //Taille par défaut des chaines de caractères
#define PRIMITIVE_SIZE 10       //Taille du premier message envoyé par un client

#define DEFAULT_NB_MESSAGE 10   //Nombre de message par défaut en émission
#define NB_MAX 99999            //Nb de message maximale en émission et numero max du destinataire (Nombre max tenant sur 5 chiffres)

#define h_addr h_addr_list[0]   //Permet la compatibilité de l'application sur les systèmes linux


/*##############################*/
//                              //
//  Importation des librairies  //
//                              //
/*##############################*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>


/*##############################*/
//                              //
//  Importation des fichiers    //
//                              //
/*##############################*/

#include "B_Lettre.h"
#include "Gestion_Clients.h"


/*##############################*/
//                              //
//  Declaration des fonctions   //
//                              //
/*##############################*/


//Fonction renvoyant un message à partir d'une longueur donnée, d'un numéro de destinataire, d'un message à affecter et d'une option de primitive
void Creer_Message (int longueur, int Nombre_en_Entete,char*message, int Primitive);


#endif /* Header_h */
