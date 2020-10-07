TP_Langage_C : main.o B_Lettre.o Gestion_Clients.o
	gcc -o  tsock main.o B_Lettre.o Gestion_Clients.o



main.o : main.c Header.h B_Lettre.h 
	gcc -std=gnu99 -Wall -c main.c Header.h B_Lettre.h Gestion_Clients.h



B_Lettre.o : B_Lettre.c B_Lettre.h
	gcc -std=gnu99 -Wall -c B_Lettre.c B_Lettre.h



Gestion_Clients.o : Gestion_Clients.c Gestion_Clients.h
	gcc -std=gnu99 -Wall -c Gestion_Clients.c Gestion_Clients.h