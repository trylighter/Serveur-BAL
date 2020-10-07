//
//  main.c
//  Project Réseau/Langage_C
//
//  Created by FREGEFOND Théo & Bayle-Sales Axel on 31/01/2017.
//  Copyright © 2017 FREGEFOND Théo. All rights reserved.
//


#include "Header.h"



/*##############################*/
//                              //
//     Corps des fonctions      //
//                              //
/*##############################*/





void Creer_Message (int longueur, int Nombre_en_Entete,char*message,int Primitive)
{
    //Initialisation statique du caractère à envoyer
    static char caractere='a';
    
    //nb chiffres du numéro du destinataire
    int nb;
    
    if (Nombre_en_Entete<10)
    {
        nb=1;
    }
    else if (Nombre_en_Entete<100)
    {
        nb=2;
    }
    else if (Nombre_en_Entete<1000)
    {
        nb=3;
    }
    else if (Nombre_en_Entete<10000)
    {
        nb=4;
    }
    else
    {
        nb=5;
    }
        
    //Cas où le message est une primitive de service
    if (Primitive==1)
    {
        char*tiret=malloc(5*sizeof(char));
        char*mot=malloc(5*sizeof(char));
        
        
        sprintf(mot,"%s%d%s","-",longueur,"-");
        
        //Distinction selon la taille du numero de message
        if(Nombre_en_Entete<10)
        {
            sprintf(tiret,"%s","----");
        }
        else
        {
            for (int k=0; k<(5-nb);k++)
            {
                sprintf(tiret,"%s%c",tiret,'-');
            }
        }
        
        sprintf(message,"%s%d%s",tiret,Nombre_en_Entete,mot);
        
    }
    //Cas où on envoit un message
    else
    {
        char*tiret=malloc(5*sizeof(char));
        char*mot=malloc((longueur-5)*sizeof(char));
        mot[0]='\0';
        
        //Construction du mot de caractere
        for (int j=0; j<longueur-5;j++)
        {
            sprintf(mot,"%s%c",mot,caractere);
        }
        
        //Changement des caracteres
        if (caractere=='z')
        {
            caractere='a';
        }
        else
        {
            caractere++;
        }
        
        //Distinction selon la taille du numero de message
        if(Nombre_en_Entete<10)
        {
            sprintf(tiret,"%s","----");
        }
        else
        {
            for (int k=0; k<(5-nb);k++)
            {
                sprintf(tiret,"%s%c",tiret,'-');
            }
        }
        
        sprintf(message,"%s%d%s",tiret,Nombre_en_Entete,mot);
        
    }
}




/*##############################*/
//                              //
//      Programme principal     //
//                              //
/*##############################*/


int main (int argc, char **argv)
{
    /*##########################################*/
    //    Declaration des variables globales    //
    /*##########################################*/
    
    int c;
    extern char *optarg;
    extern int optind;
    
    int nb_message = -1;        /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
    int source = -1 ;           /* 0=puits, 1=source */
    int protocole=0;            /* Pour TCP protocole=0 par defaut ; Pour UDP protocole=1    */
    int longueur=DEFAULT_SIZE;  /* Longueur des message ici affecté à une valeur par défault  */
    int mode=-1;                /* 0=emission, 1=reception 2=serveur default=services d'envois directs*/
    int num_dest=-1;            /* Variable representant le numéro du destinataire d'un message*/
    
    
    /*###################################*/
    //    Recuperation des options       //
    /*###################################*/
    
    while ((c = getopt(argc, argv, "bpsun:e:r:l:")) != -1) {
        
        switch (c) {
                
            case 'p':
                if (source == 1) {
                    perror("Usage: cmd [-p|-s][-n ##]");
                    exit(1) ;}
                source = 0;
                break;
            case 's':
                if (source == 0)
                {
                    perror("Usage: cmd [-p|-s][-n ##]");
                    exit(1) ;
                }
                source = 1;
                break;
                
            case 'u':
                protocole = 1;
                break;

            case 'n':
                nb_message = atoi(optarg);
            
                if (nb_message>NB_MAX) //Traitement de l'exception : si l'utilisateur rentre un nb de message supérieur à NB_MAX
                {
                    nb_message=NB_MAX;
                }
                break;
                
            case 'l':
                longueur = atoi(optarg);
               
                if (longueur<MINSIZE) //Traitement de l'exception : si l'utilisateur rentre une longueur de message inferieur à la longueur de l'entete
                {
                    longueur=MINSIZE;
                }
                else if (longueur>MAXSIZE) //Traitement de l'exception : si l'utilisateur rentre une longueur de message trop grande
                {
                    longueur=MAXSIZE;
                }
                
                break;
                
            case 'e':
                if ((mode !=0)&&(mode!=(-1)))
                {
                    perror("Usage: cmd [-e|-r|-b][-n ##]");
                    exit(1) ;
                }
                mode = 0;
                num_dest=atoi(optarg);
                
                if (num_dest>NB_MAX) //Traitement de l'exception : si l'utilisateur rentre un num dest trop grand
                {
                    perror("Le destinataire choisi n'est pas disponible");
                    exit(1);
                }
                
                break;
                
            case 'r':
                if ((mode !=1)&&(mode!=(-1)))
                {
                    perror("Usage: cmd [-e|-r|-b][-n ##]");
                    exit(1) ;
                }

                mode = 1;
                num_dest=atoi(optarg);
                if (num_dest>NB_MAX) //Traitement de l'exception : si l'utilisateur rentre un num dest trop grand
                {
                    perror("Le destinataire choisi n'est pas disponible");
                    exit(1);
                }
                break;
                
            case 'b':
                if ((mode !=2)&&(mode!=(-1)))
                {
                    perror("Usage: cmd [-e|-r|-b][-n ##]");
                    exit(1) ;
                }
                mode = 2;
                break;
                
            default:
                perror("Usage: cmd [-p|-s][-n ##]");
                break;
        }
    }
    
    
    
    
    
    /*#########################################################################*/
    //      Choix de la BAL et de ses options ou service d'envoi direct        //
    /*#########################################################################*/
    
    switch (mode)
    {
            
        /*###################################################*/
        //        Execution de la BAL en Emission            //
        /*###################################################*/
        case 0:
        {
            
            //Recuperation des arguments
            
            char*Nom_Hote=argv[argc-2];
            char*Nom_Port=argv[argc-1];
            
            
            //Creation du socket TCP reception/emission
            
            int Socket_TCP=socket(AF_INET,SOCK_STREAM,0);
            
            //Declaration des structures
            
            struct hostent*hp;
            struct sockaddr_in adr_serveur;
            
            //Recuperation de l'adresse distante
            
            memset((char*)& adr_serveur,0,sizeof(adr_serveur));
            
            adr_serveur.sin_family=AF_INET;
            adr_serveur.sin_port=htons(atoi(Nom_Port));
            
            if ((hp=gethostbyname(Nom_Hote))==NULL)
            {
                perror("Erreur de la fonction gethostbyname()");
                exit(1);
            }
            
            memcpy((char*)&(adr_serveur.sin_addr),hp->h_addr,hp->h_length);
            
            
            //Demande de connexion à l'adresse serveur
            
            int connecte=-1;
            while (connecte==-1)
            {
                if ((connecte=connect(Socket_TCP,(struct sockaddr*)&adr_serveur, sizeof(*(struct sockaddr*)&adr_serveur)))==-1)
                {
                    perror("Erreur de la fonction connect()");
                    exit(1);
                }
            }
            
            
            //Emission vers l'adresse distante
            
            
            char*primitive = malloc(PRIMITIVE_SIZE*sizeof(char));
            
            if (nb_message == -1)
            {
                nb_message = DEFAULT_NB_MESSAGE;
            }
            
            printf("SOURCE : lg_mesg_emis=%d, port=%s, nb_envoi=%d, TP=tcp, dest=%s\n",longueur,Nom_Port,nb_message,Nom_Hote);
            
            
            
            //Envoi de la primitive de service
            
            Creer_Message(longueur,num_dest,primitive,1);
            primitive[5]='E';
            
            if (write(Socket_TCP,primitive,PRIMITIVE_SIZE*sizeof(char))==-1)
            {
                perror("Erreur dans l'envoi de message TCP avec la fonction write()");
                exit(1);
            }
            
            char*message=malloc(longueur*sizeof(char));
            
            //Envoi des messages de demande de stockage
            
            for (int i=1;i<nb_message+1;i++)
            {
                Creer_Message(longueur,num_dest,message,0);
                
                if (write(Socket_TCP,message,longueur*sizeof(char))==-1)
                {
                    perror("Erreur dans l'envoi de message TCP avec la fonction write()");
                    exit(1);
                }
                
                printf("SOURCE : Envoi n°%-5d destinataire %d (%lu) [%s]\n",i,num_dest,strlen(message),message);
            }
            
            //Fermeture de la connexion
            
            if (shutdown(Socket_TCP,2)==-1)
            {
                perror("Erreur de fermeture de la connexion TCP");
                exit(1);
            }
            
            //Fermeture du socket reception/emission TCP
            
            if (close(Socket_TCP)==-1)
            {
                perror("Erreur de fermeture du socket TCP");
                exit(1);
            }
            
            printf("SOURCE : fin\n");
        }
            break;
        
        /*###############################################*/
        //      Execution de la BAL en réception         //
        /*###############################################*/
        case 1:
        {
            //Recuperation des arguments
            
            char*Nom_Hote=argv[argc-2];
            char*Nom_Port=argv[argc-1];
            
            
            //Creation du socket TCP reception/emission
            
            int Socket_TCP=socket(AF_INET,SOCK_STREAM,0);
            
            
            
            //Declaration des structures
            
            struct hostent*hp;
            struct sockaddr_in adr_serveur;
            
            //Recuperation de l'adresse distante
            
            memset((char*)& adr_serveur,0,sizeof(adr_serveur));
            
            adr_serveur.sin_family=AF_INET;
            adr_serveur.sin_port=htons(atoi(Nom_Port));
            
            if ((hp=gethostbyname(Nom_Hote))==NULL)
            {
                perror("Erreur de la fonction gethostbyname()");
                exit(1);
            }
            
            memcpy((char*)&(adr_serveur.sin_addr),hp->h_addr,hp->h_length);
            
            
            //Demande de connexion à l'adresse serveur
            
            int connecte=-1;
            while (connecte==-1)
            {
                if ((connecte=connect(Socket_TCP,(struct sockaddr*)&adr_serveur, sizeof(*(struct sockaddr*)&adr_serveur)))==-1)
                {
                    perror("Erreur de la fonction connect()");
                    exit(1);
                }
            }
            
            //Emission vers l'adresse distante
            
            
            char*primitive=malloc((PRIMITIVE_SIZE)*sizeof(char));
            
            printf("RECEPTION : demande message destinataire %d , port=%s, TP=tcp, dest=%s\n",num_dest,Nom_Port,Nom_Hote);
            
            //Primitive
            Creer_Message(longueur,num_dest,primitive,1);
            primitive[5]='R';
                
            if (write(Socket_TCP,primitive,(PRIMITIVE_SIZE)*sizeof(char))==-1)
            {
                perror("Erreur dans l'envoi de message TCP avec la fonction write()");
                exit(1);
            }
            
            
            
            char*message=malloc(longueur*sizeof(char));
            
            
            if(read(Socket_TCP,message,longueur*sizeof(char))==-1)
            {
                perror("Erreur de réception de message BAL");
                exit(1);
            }
            
            
            printf("RECEPTION : destinataire n°%-5d (%lu) [%s]\n",num_dest,strlen(message),message);
            
            free(message);
            
            //Fermeture de la connexion
            
            if (shutdown(Socket_TCP,2)==-1)
            {
                perror("Erreur de fermeture de la connexion TCP");
                exit(1);
            }

            
            
            //Fermeture du socket reception/emission TCP
            
            if (close(Socket_TCP)==-1)
            {
                perror("Erreur de fermeture du socket TCP");
                exit(1);
            }
            
            printf("RECEPTION : fin\n");
            
            
        }
            break;
          
        /*###################################################*/
        //          Execution de la BAL en serveur           //
        /*###################################################*/
        case 2:
        {
            //Recuperation des arguments
            char*Nom_Port=argv[argc-1];
            
            //Affichage du choix
            printf("PUITS : port=%s,TP=tcp\n",Nom_Port);
            
            //Initialisation de la BAL
            struct Liste_Destinataire*Ma_Liste_dest=Ininialiser_Liste_Dest();
            
            //Initialisation du registre de clients
            struct Liste_Client*Ma_Liste_client=Initialiser_Liste_Clients();
            
            
            //Creation du socket TCP reception/emission
            
            int Socket_TCP=socket(AF_INET,SOCK_STREAM,0);
            
            
            //Declaration des structures
            
            struct sockaddr_in adr_local;
            
            
            
            //Creation d'un port local d'écoute
           
            memset((char*)& adr_local,0,sizeof(adr_local));
            adr_local.sin_family=AF_INET;
            adr_local.sin_port=htons(atoi(Nom_Port));
            adr_local.sin_addr.s_addr = INADDR_ANY;
            
            if (bind(Socket_TCP,(struct sockaddr*)&adr_local,sizeof(*(struct sockaddr*)&adr_local))==-1)
            {
                perror("Erreur de la fonction bind()");
                exit(1);
            }
            
            
            //Dimensionnement de l'écoute
            
            if (listen(Socket_TCP,5)==-1)
            {
                perror("Erreur de la fonction listen()");
                exit(1);
            }
            
            
            
            //Declaration des différentes châines de caractères
            
            //Message envoyé à la première connexion
            char*message_primitive=malloc(PRIMITIVE_SIZE*sizeof(char));
            //Message a stocker dans le serveur
            char*message_stockage=malloc(MAXSIZE*sizeof(char));
            //Messages à lire sur le serveur
            char*message_lecture=malloc(MAXSIZE*sizeof(char));
            
            
            //Valeur du plus grand socket à insérer dans les descripteur, ici ce sera le socket père
            int max = Socket_Max(Ma_Liste_client, Socket_TCP);
            
            
            //Initialisation des variables locales
            int Sock_Bis;
            int taille_recu;
            
            
            //Initialisation des ensembles de descripteurs en lecture et en écriture
            //RQ : les ensemble bis sont des ensemble contenant tous les descripteurs utile mais toujours declarés inactif
            fd_set rfds,rfds_bis ;
            FD_ZERO(&rfds_bis);
            
            fd_set wfds,wfds_bis ;
            FD_ZERO(&wfds_bis);
            
            
            //Ajout du descripteur representant le socket du processus père
            FD_SET(Socket_TCP , &rfds_bis);
            
            // Ajout du descipteur d'entée stadard
            FD_SET(STDIN_FILENO,&rfds_bis);
            
            while (1)
            {
                //Remise à zéro des ensembles avant le select
                rfds = rfds_bis;
                wfds = wfds_bis;
                
                //Calcul de la valeur du plus grand socket
                max = Socket_Max(Ma_Liste_client,Socket_TCP);
                
                if(select(max+1,&rfds,&wfds,NULL,NULL) == -1)
                {
                    perror("Erreur de la fonction select()");
                    exit(1);
                }
                
                //Utilisation de l'entrée standard
                if(FD_ISSET(STDIN_FILENO, &rfds))
                {
                    //Fin du programme en cas d'appuie sur la touche entrée
                    break;
                }
                //On est dans le socket père on va ajouter un nouveau client
                else if (FD_ISSET(Socket_TCP,&rfds))
                {
                    struct sockaddr_in adr_client;
                    int lg_adr_client=sizeof(adr_client);
                    
                    if((Sock_Bis=accept(Socket_TCP,(struct sockaddr*)&adr_client,(socklen_t*)&lg_adr_client))==-1)
                    {
                        perror("Erreur de la fonction accept()");
                    }
                    //Creation d'une fiche client
                    Ajouter_Client(Ma_Liste_client, Sock_Bis);
                    
                    //Ajout du descripteur du nouveau client à l'ensemble
                    FD_SET(Sock_Bis,&rfds_bis);
                }
                
                //On interroge les clients déjà existant
                
                Ma_Liste_client->S_Client_Courant=Ma_Liste_client->S_Client_Premier;
                int Sock_Actuel;
                
                while (Ma_Liste_client->S_Client_Courant!=NULL)
                {
                    //Affectation de la valeur du socket actuel
                    Sock_Actuel=Ma_Liste_client->S_Client_Courant->Socket_Client;
                
                    
                    //Traitement si activité detectée en lecture
                    if(FD_ISSET(Sock_Actuel,&rfds))
                    {
                        //On identifie si le message est une primitive de service ou un message
                        if (Ma_Liste_client->S_Client_Courant->Type_Client=='?')
                        {
                            longueur=PRIMITIVE_SIZE;
                            
                            if((taille_recu=(int)read(Sock_Actuel,message_primitive,longueur*sizeof(char)))==-1)
                            {
                                perror("Erreur de réception de message TCP");
                                exit(1);
                            }
                            //On recois la primitive d'un client en lecture ou en écriture
                            if (taille_recu>0)
                            {
                                
                                //On recupere le numero de destinataire sur lequel on va devoir travailler
                                if ((num_dest=Recuperation_Numero(message_primitive))==-1) {
                                    printf("Echec de lecture du numero de destinataire\n");
                                    break;
                                }
                                Ma_Liste_client->S_Client_Courant->destinataire=num_dest;
                                
                                
                                //On recupere la taille sur laquelle on va travailler soit en lecture soit en écriture
                                if ((Ma_Liste_client->S_Client_Courant->longueur_client=Recuperation_Numero(&message_primitive[6]))==-1)
                                {
                                    printf("Echec de lecture de la longueur des messages à traiter\n");
                                    break;
                                }
                                
                                
                                //On lui affecte un type et on traite sa demande si il est de typee Récepteur "R"
                                if ((Ma_Liste_client->S_Client_Courant->Type_Client=message_primitive[5])=='R')
                                {
                                    //Affichage de l'action réalisé sur le serveur
                                    printf("PUITS : Lecture BAL destinataire %-5d\n",num_dest);
                                    
                                    //Initialisation de la liste a recuperer
                                    struct Liste_Lettre*Liste_A_Recupere=NULL;
                                    
                                    
                                    memset(message_lecture,'\0',MAXSIZE*sizeof(char));
                                    
                                    
                                    //Recuperation de la liste de lettre du destinataire
                                    
                                    //Cas où le destinataire n'a pas été encore enregistré sur le serveur
                                    if ((Liste_A_Recupere=(Renvoi_Liste_Lettre(Ma_Liste_dest,num_dest)))==NULL)
                                    {
                                        printf("Aucun destinataire trouvé\n");
                                        strcpy(message_lecture,"ERROR : Recipient not found");
                                    }
                                    //Sinon on tente la récuperation d'un message sur ce destinataire
                                    else
                                    {
                                        Recuperation_Message(Liste_A_Recupere,message_lecture);
                                    }
                                    
                                    //On force la fin de la chaine du message recuperé au cas où celui ci soit plus grand que la taille desirée
                                    longueur=Ma_Liste_client->S_Client_Courant->longueur_client;
                                    message_lecture[longueur]='\0';
                                    longueur=(int)strlen(message_lecture);
                                    
                                   //Le message sera envoyé à posteriori qd les buffers d'écriture seront detectés comme libre
                                    
                                    //Allocation dynamique de la taille du message à envoyer
                                    Ma_Liste_client->S_Client_Courant->Message_A_Ecrire=malloc(longueur*sizeof(char));
                                    
                                    //Recuperation sur le Message a ecrire
                                    strcpy(Ma_Liste_client->S_Client_Courant->Message_A_Ecrire,message_lecture);
                                    
                                    //Activer le socket d'émission concerné pour l'envoi ultérieur
                                    FD_SET(Sock_Actuel,&wfds_bis);
                                }
                            }
                            //Si fermeture juste apres la demande de connexion du client !! Cas improbable normalement !
                            else
                            {
                                if (close(Sock_Actuel)==-1)
                                {
                                    perror("Erreur de fermeture du socket TCP");
                                    exit(1);
                                }
                                Suppression_Client(Ma_Liste_client, Sock_Actuel);
                                
                                FD_CLR(Sock_Actuel,&rfds_bis);
                            }
                        }
                        //Si le message n'est pas une primitive de service
                        else
                        {
                            //Si le client est en écriture et transmet un message à stocker
                            if (Ma_Liste_client->S_Client_Courant->Type_Client=='E')
                            {
                                longueur=Ma_Liste_client->S_Client_Courant->longueur_client;
                                message_stockage=realloc(message_stockage,longueur*sizeof(char));
                                
                                
                                if((taille_recu=(int)read(Sock_Actuel,message_stockage,longueur*sizeof(char)))==-1)
                                {
                                    perror("Erreur de réception de message TCP");
                                    exit(1);
                                }
                                
                                //Permet de forcer la longueur des messages en cas de problème sur le réseau
                                message_stockage[longueur]='\0';
                                
                                //Si le message est non nul c'est une demande d'écriture
                                if (taille_recu>0)
                                {
                                    //Initialisation de la liste a recuperer
                                    struct Liste_Lettre*Liste_A_Recupere=NULL;
                                    
                                    //On recupere le numero sur lequel on va devoir travailler
                                    num_dest=Ma_Liste_client->S_Client_Courant->destinataire;
                                    
                                    printf("PUITS : Reception lettre destinataire n°%-5d [%s]\n",num_dest,message_stockage);
                                    
                                    if ((Liste_A_Recupere=Renvoi_Liste_Lettre(Ma_Liste_dest,num_dest))==NULL)
                                    {
                                        Ajouter_Destinataire(Ma_Liste_dest,num_dest);
                                        Liste_A_Recupere=Renvoi_Liste_Lettre(Ma_Liste_dest,num_dest);
                                    }
                                    
                                    Stockage_Nouveau_Message(Liste_A_Recupere,message_stockage);
                                }
                                //Si la taille est nul, fermeture de la connexion
                                else
                                {
                                    if (close(Sock_Actuel)==-1)
                                    {
                                        perror("Erreur de fermeture du socket TCP");
                                        exit(1);
                                    }
                                    Suppression_Client(Ma_Liste_client, Sock_Actuel);
                                    
                                    FD_CLR(Sock_Actuel,&rfds_bis);
                                }
                            }
                            //Si le client est en lecture encore c'est surement pour averir d'une fermeture de connexion
                            else 
                            {
                                char*message=malloc(PRIMITIVE_SIZE*sizeof(char));
                                
                                
                                if((taille_recu=(int)read(Sock_Actuel,message,PRIMITIVE_SIZE*sizeof(char)))==-1)
                                {
                                    perror("Erreur de réception de message TCP");
                                    exit(1);
                                }
                                
                                if (taille_recu==0)
                                {
                                    if (close(Sock_Actuel)==-1)
                                    {
                                        perror("Erreur de fermeture du socket TCP");
                                        exit(1);
                                    }
                                    Suppression_Client(Ma_Liste_client, Sock_Actuel);
                                    
                                    FD_CLR(Sock_Actuel,&rfds_bis);
                                }
                            }
                        }
                    }
                    
                    //Traitement si les buffer du socket sont libres en écriture, envoi du message demandé par le récepteur
                    if(FD_ISSET(Sock_Actuel,&wfds))
                    {
                        longueur=(int)strlen(Ma_Liste_client->S_Client_Courant->Message_A_Ecrire);
                        
                        if (write(Sock_Actuel,Ma_Liste_client->S_Client_Courant->Message_A_Ecrire,longueur*sizeof(char))==-1)
                        {
                            perror("Erreur dans l'envoi de BAL avec la fonction write()");
                            exit(1);
                        }
                        
                        free(Ma_Liste_client->S_Client_Courant->Message_A_Ecrire);
                        
                        FD_CLR(Sock_Actuel,&wfds_bis);
                    }
                    
                    //Passage au socket suivant en tenant compte que tous les utilisateur auraient pu tous être supprimés
                   
                    if (Ma_Liste_client->S_Client_Premier!=NULL)
                    {
                        Ma_Liste_client->S_Client_Courant=Ma_Liste_client->S_Client_Courant->Client_Suivant;
                    }
                }
            }
            
            //Liberation de la liste de client et de destinataire
        
            free(Ma_Liste_client);
            free(Ma_Liste_dest);
            
            //Fermeture du socket TCP
            if (close(Socket_TCP)==-1)
            {
                perror("Erreur de fermeture du socket TCP");
                exit(1);
            }
            
            printf("PUITS : fin\n");
            
        }
            break;
        
        /*#######################################*/
        //     Execution des envois directs      //
        /*#######################################*/
        default:
        {
            switch (protocole)
            {
                /*########################################*/
                //           Execution de UDP             //
                /*########################################*/
                case 1:
                {
                    //Recuperation des arguments
                    
                    char*Nom_Hote=argv[argc-2];
                    char*Nom_Port=argv[argc-1];
                    
                    
                    //Creation du socket UDP recption/emission
                    
                    int Socket_UDP = socket(AF_INET,SOCK_DGRAM,0);
                    
                    switch (source)
                    {
                            
                        /*########################################*/
                        //           Usage Source en UDP          //
                        /*########################################*/
                        case 1:
                        {
                            
                            //Declaration des structures
                            
                            struct hostent*hp;
                            struct sockaddr_in adr_distant;
                            
                            //Recuperation de l'adresse distante
                            
                            memset((char*)& adr_distant,0,sizeof(adr_distant));
                            
                            adr_distant.sin_family=AF_INET;
                            adr_distant.sin_port=htons(atoi(Nom_Port));
                            
                            if ((hp=gethostbyname(Nom_Hote))==NULL)
                            {
                                perror("Erreur de la fonction gethostbyname()");
                                exit(1);
                            }
                            
                            memcpy((char*)&(adr_distant.sin_addr),hp->h_addr,hp->h_length);
                            
                            
                            //Emission vers l'adresse distante
                            
                            char*message = malloc(longueur*sizeof(char));
                            
                            if (nb_message == -1)
                            {
                                nb_message = DEFAULT_NB_MESSAGE;
                            }
                            
                            printf("SOURCE : lg_mesg_emis=%d, port=%s, nb_envoi=%d, TP=udp, dest=%s\n",longueur,Nom_Port,nb_message,Nom_Hote);
                            
                            for (int i=1;i<nb_message+1;i++)
                            {
                                
                                Creer_Message(longueur,i,message,0);
                                
                                if (sendto(Socket_UDP,message,longueur*sizeof(char),0,(struct sockaddr*)&adr_distant, sizeof(*(struct sockaddr*)&adr_distant))==-1)
                                {
                                    perror("Erreur d'envoi de message UDP avec la fonction sendto()");
                                    exit(1);
                                }
                                
                                printf("SOURCE : Envoi n°%-5d (%lu) [%s]\n",i,strlen(message),message);
                            }
                            
                        }
                            break;
                            
                        /*########################################*/
                        //           Usage Puits en UDP           //
                        /*########################################*/
                        case 0:
                        {
                            //Declaration des structures
                            
                            struct sockaddr_in adr_emetteur;
                            int lg_adr_emetteur;
                            struct sockaddr_in adr_local;
                            
                            //Creation d'un port local d'écoute
                            
                            memset((char*)& adr_local,0,sizeof(adr_local));
                            adr_local.sin_family=AF_INET;
                            adr_local.sin_port=htons(atoi(Nom_Port));
                            adr_local.sin_addr.s_addr = INADDR_ANY;
                            
                            if (bind(Socket_UDP,(struct sockaddr*)&adr_local,sizeof(*(struct sockaddr*)&adr_local))==-1)
                            {
                                perror("Erreur de la fonction bind()");
                                exit(1);
                            }
                            
                            
                            // Reception de message sur ce port
                            
                            char*nb_string_message=malloc(MAXSIZE*sizeof(char));
                            
                            if (nb_message == -1)
                            {
                                nb_message=INT_MAX;
                                strcpy(nb_string_message,"Infini");
                            }
                            else
                            {
                                sprintf(nb_string_message,"%d", nb_message);
                            }
                            
                            int quantite=0;
                            
                            printf("PUITS : lg_mesg_lu=%d, port=%s, nb_reception=%s, TP=udp\n",longueur,Nom_Port,nb_string_message);
                            
                            char*message=malloc(longueur*sizeof(char));
                            
                            while(quantite<nb_message)
                            {
                                memset(message,'\0',longueur*sizeof(char));
                                
                                if(recvfrom(Socket_UDP,message,longueur*sizeof(char),0,(struct sockaddr*)&adr_emetteur,(socklen_t*)&lg_adr_emetteur)==-1)
                                {
                                    perror("Erreur à la réception");
                                    exit(1);
                                }
                                
                                printf("PUITS : Reception n°%-5d (%lu) [%s]\n",quantite+1,strlen(message),message);
                                
                                quantite++;
                                
                            }
                        }
                            break;
                            
                        /*########################################*/
                        //           Aucun usage renseigné        //
                        /*########################################*/
                        default:
                            perror("usage: cmd [][-n ##]");
                            exit(1) ;
                            break;
                    }
                    
                    
                    //Fermeture du socket recption/emission
                    
                    if (close(Socket_UDP)==-1)
                    {
                        perror("Erreur de fermeture du socket");
                        exit(1);
                    }
                    
                    printf("Fin de programme UDP\n");
                }
                    break;
                    
                    
                /*#######################################*/
                //           Execution de TCP            //
                /*#######################################*/
                default:
                {
                    //Recuperation des arguments
                    
                    char*Nom_Hote=argv[argc-2];
                    char*Nom_Port=argv[argc-1];
                    
                    
                    //Creation du socket TCP reception/emission
                    
                    int Socket_TCP=socket(AF_INET,SOCK_STREAM,0);
                    
                    switch (source)
                    {
                        /*########################################*/
                        //           Usage Source en TCP          //
                        /*########################################*/
                        case 1:
                        {
                            //Declaration des structures
                            
                            struct hostent*hp;
                            struct sockaddr_in adr_serveur;
                            
                            //Recuperation de l'adresse distante
                            
                            memset((char*)& adr_serveur,0,sizeof(adr_serveur));
                            
                            adr_serveur.sin_family=AF_INET;
                            adr_serveur.sin_port=htons(atoi(Nom_Port));
                            
                            if ((hp=gethostbyname(Nom_Hote))==NULL)
                            {
                                perror("Erreur de la fonction gethostbyname()");
                                exit(1);
                            }
                            
                            memcpy((char*)&(adr_serveur.sin_addr),hp->h_addr,hp->h_length);
                            
                            
                            //Demande de connexion à l'adresse serveur
                            
                            int connecte=-1;
                            while (connecte==-1)
                            {
                                if ((connecte=connect(Socket_TCP,(struct sockaddr*)&adr_serveur,sizeof(*(struct sockaddr*)&adr_serveur)))==-1)
                                {
                                    perror("Erreur de la fonction connect()");
                                    exit(1);
                                }
                            }
                            
                            //Emission vers l'adresse distante
                            
                            char*message = malloc(longueur*sizeof(char));
                            
                            if (nb_message == -1)
                            {
                                nb_message = DEFAULT_NB_MESSAGE;
                            }
                            
                            printf("SOURCE : lg_mesg_emis=%d, port=%s, nb_envoi=%d, TP=tcp, dest=%s\n",longueur,Nom_Port,nb_message,Nom_Hote);
                            
                            for (int i=1;i<nb_message+1;i++)
                            {
                                Creer_Message(longueur,i,message,0);
                                
                                if (write(Socket_TCP,message,longueur*sizeof(char))==-1)
                                {
                                    perror("Erreur dans l'envoi de message TCP avec la fonction write()");
                                    exit(1);
                                }
                                
                                printf("SOURCE : Envoi n°%-5d (%lu) [%s]\n",i,strlen(message),message);
                            }
                            
                            //Fermeture de la connexion
                            
                            if (shutdown(Socket_TCP,2)==-1)
                            {
                                perror("Erreur de fermeture de la connexion TCP");
                                exit(1);
                            }
                            
                        }
                            break;
                            
                        /*########################################*/
                        //           Usage Puits en TCP           //
                        /*########################################*/
                        case 0:
                        {
                            //Affichage du choix effectué
                            
                            char*nb_string_message=malloc(MAXSIZE*sizeof(char));
                            
                            if (nb_message == -1)
                            {
                                nb_message=INT_MAX;
                                strcpy(nb_string_message,"Infini");
                            }
                            else
                            {
                                sprintf(nb_string_message,"%d",nb_message);
                            }
                            
                            printf("PUITS : lg_mesg_lu=%d,port=%s,nb_reception=%s,TP=tcp\n",longueur,Nom_Port,nb_string_message);
                            
                            //Declaration des structures
                            
                            struct sockaddr_in adr_client;
                            int lg_adr_client=sizeof(adr_client);
                            
                            struct sockaddr_in adr_local;
                            int Sock_Bis;
                            
                            
                            //Creation d'un port local d'écoute
                            
                            memset((char*)& adr_local,0,sizeof(adr_local));
                            adr_local.sin_family=AF_INET;
                            adr_local.sin_port=htons(atoi(Nom_Port));
                            adr_local.sin_addr.s_addr = INADDR_ANY;
                            
                            if (bind(Socket_TCP,(struct sockaddr*)&adr_local,sizeof(*(struct sockaddr*)&adr_local))==-1)
                            {
                                perror("Erreur de la fonction bind()");
                                exit(1);
                            }
                            //Dimensionnement de l'écoute
                            
                            if (listen(Socket_TCP,5)==-1)
                            {
                                perror("Erreur de la fonction listen()");
                                exit(1);
                            }
                            
                            //Mise en état d'acceptation
                            
                            if((Sock_Bis=accept(Socket_TCP,(struct sockaddr*)&adr_client,(socklen_t*)&lg_adr_client))==-1)
                            {
                                perror("Erreur de la fonction accept()");
                            }
                            
                            
                            // Reception de message sur ce port
                            
                            int quantite_recu=0;
                            int taille_recu;
                            
                           char*message=malloc(longueur*sizeof(char));
                            
                            while(quantite_recu<nb_message)
                            {
                                
                                memset(message,'\0',longueur*sizeof(char));
                                
                                if((taille_recu=(int)read(Sock_Bis,message,longueur*sizeof(char)))==-1)
                                {
                                    perror("Erreur de réception de message TCP");
                                    exit(1);
                                }
                                
                                
                                if (taille_recu!=0)
                                {
                                    printf("PUITS : Reception n°%-5d (%lu) [%s]\n",quantite_recu+1,strlen(message),message);
                                    quantite_recu++;
                                }
                                else //Si on recois un message nul on se remet en etat d'acceptation
                                {
                                    if (close(Sock_Bis)==-1)
                                    {
                                        perror("Erreur de fermeture du socket Bis");
                                        exit(1);
                                    }
                                    
                                    if((Sock_Bis=accept(Socket_TCP,(struct sockaddr*)&adr_client,(socklen_t*)&lg_adr_client))==-1)
                                    {
                                        perror("Erreur de la fonction accept()");
                                    }
                                }
                            }
                        }
                            break;
                            
                        /*########################################*/
                        //           Aucun usage renseigné        //
                        /*########################################*/
                        default:
                            perror("usage: cmd [][-n ##]");
                            exit(1) ;
                            break;
                    }
                    
                    //Fermeture du socket reception/emission TCP
                    
                    if (close(Socket_TCP)==-1)
                    {
                        perror("Erreur de fermeture du socket TCP");
                        exit(1);
                    }
                    
                    printf("Fin de programme TCP\n");
                }
                    break;
            }
        }
            break;
    }
    return 0;
}


