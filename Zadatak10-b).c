#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

struct _lista;
typedef struct _lista* Pozicija;

struct _stablo;
typedef struct _stablo* StabloP;

typedef struct _lista {
	char Grad[MAX_SIZE];
	int Stanovnistvo;
	Pozicija Next;

}Lista;

typedef struct _stablo {
	char Drzava[MAX_SIZE];
	Pozicija HeadGrad;
	StabloP Lijevi;
	StabloP Desni;

}Stablo;

StabloP StvoriDrzavu(char* naziv, char* datoteka);
StabloP UnosDrzava(StabloP Trenutni, char* naziv, char* datoteka);
Pozicija StvoriGrad(char* naziv, int br);
Pozicija StvoriHead(Pozicija P);
Pozicija UnosGrada(Pozicija P, char* naziv, int br);
StabloP IspisDrzava(StabloP Trenutni);
int IspisGradova(Pozicija P);
StabloP IspisOdredeneDrzave(StabloP Trenutni, char* naziv, int uvjet);
int IspisOdredenihGradova(Pozicija P, int uvjet);

int main()
{
	StabloP root = NULL;
	FILE* pDat = NULL;
	char drzava[MAX_SIZE] = { 0 };
	char gradovi[MAX_SIZE] = { 0 };
	char odabirD[MAX_SIZE] = { 0 };
	int uvjet = 0;
	int izlaz = 1;

	pDat = fopen("drzave.txt", "r");
	if (!pDat) {
		printf("\nGRESKA!Neuspjelo otvaranje!");
		return -1;
	}

	while (!feof(pDat)) {
		fscanf(pDat, " %s %s", drzava, gradovi);
		root = UnosDrzava(root, drzava, gradovi);
	}

	fclose(pDat);
	IspisDrzava(root);
	puts("");

	printf("\n______________PRETRAGA_______________");
	while (izlaz != 0) {
		printf("\nUnesite zeljenu drzavu(Za izlaz unesite <<kraj>>): ");
		scanf(" %s", odabirD);

		if (strcmp(odabirD, "kraj") == 0)
			izlaz = 0;

		else {

			printf("\nUnesite minimali broj stanovnika gradova drzave %s: ", odabirD);
			scanf("%d", &uvjet);
			IspisOdredeneDrzave(root, odabirD, uvjet);
		}
	}
	puts("");

	return EXIT_SUCCESS;
}

StabloP StvoriDrzavu(char* naziv, char* datotekaGradovi)
{
	StabloP Nova = NULL;
	FILE* pDat = NULL;
	char grad[MAX_SIZE] = { 0 };
	int broj = 0;

	Nova = (StabloP)malloc(sizeof(Stablo));
	if (!Nova) {
		printf("\nGRESKA!Neuspjela alokacija!");
		return NULL;
	}

	strcpy(Nova->Drzava, naziv);
	Nova->Lijevi = NULL;
	Nova->Desni = NULL;
	Nova->HeadGrad = StvoriHead(Nova->HeadGrad);

	pDat = fopen(datotekaGradovi, "r");
	if (!pDat) {
		printf("\nGRESKA!Neuspjelo otvaranje!");
		return NULL;
	}

	while (!feof(pDat)) {
		fscanf(pDat, " %s %d ", grad, &broj);
		 UnosGrada(Nova->HeadGrad, grad, broj);
	}

	fclose(pDat);

	return Nova;
}

StabloP UnosDrzava(StabloP Trenutni, char* naziv, char* datoteka)
{
	if (Trenutni == NULL)
		Trenutni = StvoriDrzavu(naziv, datoteka);

	else {
		if (strcmp(naziv, Trenutni->Drzava) < 1)
			Trenutni->Lijevi = UnosDrzava(Trenutni->Lijevi, naziv, datoteka);

		else
			Trenutni->Desni = UnosDrzava(Trenutni->Desni, naziv, datoteka);

	}

	return Trenutni;
}

Pozicija StvoriHead(Pozicija P)
{
	Pozicija Novi = NULL;

	Novi = (Pozicija)malloc(sizeof(Lista));
	if (!Novi) {
		printf("\nGRESKA!Neuspjela alokacija!");
		return NULL;
	}

	strcpy(Novi->Grad," ");
	Novi->Stanovnistvo = 0;
	Novi->Next = NULL;


	return Novi;
}

Pozicija StvoriGrad(char* naziv, int br)
{
	Pozicija Novi = NULL;

	Novi = (Pozicija)malloc(sizeof(Lista));
	if(!Novi){
		printf("\nGRESKA!Neuspjela alokacija!");
		return NULL;
	}

	strcpy(Novi->Grad, naziv);
	Novi->Stanovnistvo = br;
	Novi->Next = NULL;


	return Novi;
}

Pozicija UnosGrada(Pozicija P, char* naziv, int br)
{
	Pozicija Novi = StvoriGrad(naziv, br);

	while (P->Next != NULL) {

		if (br < P->Next->Stanovnistvo) {
			Novi->Next = P->Next;
			P->Next = Novi;
			return P;
		}

		else
			P = P->Next;

	}

	if (P->Next == NULL) {
		P->Next = Novi;
		P = P->Next;
	}

	return P;

}

StabloP IspisDrzava(StabloP Trenutni)
{
	if (Trenutni == NULL)
		return Trenutni;

	IspisDrzava(Trenutni->Lijevi);
	printf("\nDrzava: %s", Trenutni->Drzava);
	printf("\n\tGradovi:");
	IspisGradova(Trenutni->HeadGrad->Next);
	IspisDrzava(Trenutni->Desni);

	return Trenutni;
}

int IspisGradova(Pozicija P)
{
	if (P == NULL) {
		printf("\nLista je prazna...");
		return EXIT_SUCCESS;
	}

	while (P != NULL) {
		printf("\n\t\t %s", P->Grad);
		printf("\n\t\t\tBroja stanovnika: %d", P->Stanovnistvo);
		
		P = P->Next;

	}



	return EXIT_SUCCESS;
}

StabloP IspisOdredeneDrzave(StabloP Trenutni, char* naziv, int uvjet)
{
	if (Trenutni == NULL)
		return Trenutni;

	else if (strcmp(naziv, Trenutni->Drzava) == 0) {
		printf("\nDrzava: %s", Trenutni->Drzava);
		printf("\n\tGradovi s vise od %d stanovnika: ", uvjet);
		IspisOdredenihGradova(Trenutni->HeadGrad->Next, uvjet);
		return Trenutni;
	}
	else if (strcmp(naziv, Trenutni->Drzava) < 1)
		IspisOdredeneDrzave(Trenutni->Lijevi, naziv, uvjet);
	else 
		IspisOdredeneDrzave(Trenutni->Desni, naziv, uvjet);
	
	


	return Trenutni;
}

int IspisOdredenihGradova(Pozicija P, int uvjet)
{
	while (P != NULL) {
		if (P->Stanovnistvo > uvjet) {
			printf("\n\t\t%s ", P->Grad);
			printf("\n\t\t\tBroja stanovnika: %d", P->Stanovnistvo);
		}
		P = P->Next;
	}


	return EXIT_SUCCESS;
}