#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

struct _stablo;
typedef struct _stablo* StabloP;

typedef struct _stablo {
	char Naziv[MAX_SIZE];
	StabloP Dijete;
	StabloP Brat;

}stablo;

struct _stog;
typedef struct _stog* Pozicija;

typedef struct _stog {
	StabloP Direktorij;
	Pozicija Next;

}stog;


StabloP IspisZaCMD(StabloP Pomoc, StabloP trenutni, Pozicija P);
StabloP MD(StabloP trenutni, char* naziv);
int DIR(StabloP trenutni);
int Push(StabloP temp, Pozicija P);
StabloP CD(StabloP trenutni, Pozicija P, char* naziv);
StabloP Pop(Pozicija P);
//StabloP EXIT( StabloP trenutni);


int main()
{
	stablo root = { .Naziv = "C:", .Brat = NULL, .Dijete = NULL };
	StabloP trenutni = &root;
	stog Head = { .Direktorij = NULL, .Next = NULL };
	int odabir = 7;
	char naziv[MAX_SIZE] = { 0 };


	printf("Microsoft Windows [Version 10.0.18363.1916]\n(c)2019. Microsoft Corporation.Sva prava pridrzana.\n"); 
	while (odabir != 6) {
		printf("\nPrirucnik: 1) md 2) dir 3) cd 4) cd.. 5) exit\n");

		IspisZaCMD(&root, trenutni, &Head); //ispisuje put do trenutnog direktorija

		printf("%s> ", trenutni->Naziv); //ispisuje trenutni direktorij
		scanf("%d", &odabir);


		if (odabir == 1) {

			printf("\nmd ");
			scanf(" %s", naziv);
			MD(trenutni, naziv);
		}

		else if (odabir == 2) {

			printf("\ndir ");
			printf("\nDirectory of ");
			IspisZaCMD(&root, trenutni,&Head);
			printf("%s\n\n", trenutni->Naziv);

			DIR(trenutni);

		}

		else if (odabir == 3) {
			printf("\ncd ");
			scanf(" %s", naziv);
			trenutni = CD(trenutni, &Head, naziv);

		}

		else if (odabir == 4) 
			trenutni = Pop(&Head);

		else if (odabir == 5) {
			//EXIT(&root);
			odabir = 6;
		}
		
	}


	return EXIT_SUCCESS;
}


StabloP IspisZaCMD(StabloP Pomoc, StabloP trenutni, Pozicija P)
{

	P = P->Next;
	while (P != NULL && P->Direktorij != trenutni) {
		printf("%s/", P->Direktorij);
		P = P->Next;
	}
	return NULL;
}


StabloP MD(StabloP trenutni, char* naziv)
{
	StabloP novi = NULL;

	novi = (StabloP)malloc(sizeof(stablo));

	if (!novi) {
		printf("\nGRESKA!!Neuspjela alokacija memorije!");
		return NULL;
	};
	strcpy(novi->Naziv, naziv);
	novi->Dijete = NULL;
	novi->Brat = NULL;


	if (trenutni->Dijete == NULL) {
		trenutni->Dijete = novi;
	}
	else {
		trenutni = trenutni->Dijete;
		
		while (trenutni->Brat != NULL) {
				trenutni = trenutni->Brat;
		}
		novi->Brat = trenutni->Brat;
		trenutni->Brat = novi;
	}

	return novi;
}

int DIR(StabloP trenutni)
{
	int brojac = 2;
	trenutni = trenutni->Dijete;

	if (trenutni == NULL) {
		printf("\n%d File(s)\t%d bytes", brojac, brojac);
	}

	else {
		printf("<DIR>\t.\n<DIR>\t..\n");
		printf("<DIR>\t%s\n", trenutni->Naziv);
		brojac++;
		
		while (trenutni->Brat != NULL) {
			printf("<DIR>\t%s\n", trenutni->Brat->Naziv);
			trenutni = trenutni->Brat;
			brojac++;
		}
		printf("\n%d Dir(s)\t%d bytes free", brojac, 214748364-56*brojac); // ovaj broja sam eto tako neki random stavio
	}
	return EXIT_SUCCESS;
}

int Push(StabloP temp, Pozicija P)
{
	Pozicija novi = NULL;

	novi = (Pozicija)malloc(sizeof(stog));
	
	if (!novi) {
		printf("\nGRESKA!!Neuspjela alokacija memorije!");
		return -1;
	};
	
	novi->Direktorij = NULL;
	novi->Next = NULL;

	
	if (P->Next == NULL)
	{
		novi->Direktorij = temp;
		P->Next = novi;
	}
	else
	{
		while (P->Next != NULL)
		{
			P = P->Next;
		}


		novi->Direktorij = temp;
		P->Next = novi;
	}
	return EXIT_SUCCESS;
}

StabloP CD(StabloP trenutni, Pozicija P, char* naziv)
{
	StabloP temp = trenutni;
	Push(trenutni, P);

	trenutni = trenutni->Dijete;

	while (trenutni != NULL && strcmp(trenutni->Naziv, naziv) != 0)
		trenutni = trenutni->Brat;

	if (trenutni == NULL) {
		printf("\nNe postoji trazeni direktorij!");
		return temp;
	}
	else
		return trenutni;
}

StabloP Pop(Pozicija P)
{
	StabloP prev;
	Pozicija temp;

	while (P->Next->Next != NULL)
	{
		P = P->Next;
	}
	prev = P->Next->Direktorij;
	temp = P->Next;
	P->Next = temp->Next;
	free(temp);

	return prev;
}
/*
StabloP EXIT(StabloP trenutni)
{
	StabloP prev = trenutni;
	
	
	if (trenutni == NULL)
		return NULL;

	else if (trenutni->Dijete != NULL)
		trenutni = EXIT(trenutni->Dijete);

	else if (trenutni->Brat != NULL)
		trenutni = EXIT(trenutni->Brat);


	
		free(trenutni);


	return prev;
}
*/