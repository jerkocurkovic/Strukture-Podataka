#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 1024

struct _lista;
typedef struct _lista* Pozicija;

struct _stablo;
typedef struct _stablo* StabloP;

typedef struct _lista {
	char Drzava[MAX_SIZE];
	StabloP Gradovi;
	Pozicija Next;

}Lista;

typedef struct _stablo {
	char Grad[MAX_SIZE];
	int Stanovnistvo;
	StabloP Lijevi;
	StabloP Desni;

}Stablo;

Pozicija StvoriDrzavu(char* naziv, char* datoteka);
Pozicija UnosDrzava(Pozicija P, char* naziv, char* datoteka);
StabloP StvoriGrad(char* naziv, int br);
StabloP UnosGrada(StabloP Trenutni, char* naziv, int br);
int IspisDrzava(Pozicija P);
StabloP IspisGradova(StabloP Trenutni);
int IspisOdredeneDrzave(Pozicija P, char* naziv, int uvjet);
StabloP IspisOdredenihGradova(StabloP Trenutni, int uvjet);



int main()
{
	Lista Head = { .Drzava = { 0 }, .Gradovi = NULL, .Next = NULL };
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
		UnosDrzava(&Head, drzava, gradovi);
	}

	fclose(pDat);
	IspisDrzava(Head.Next);
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
			IspisOdredeneDrzave(Head.Next, odabirD, uvjet);
		}
	}
	puts("");

	return EXIT_SUCCESS;
}

Pozicija StvoriDrzavu(char* naziv, char* datotekaGradovi)
{
	Pozicija Nova = NULL;
	FILE* pDat = NULL;
	char grad[MAX_SIZE] = { 0 };
	int broj = 0;

	Nova = (Pozicija)malloc(sizeof(Lista));
	if (!Nova) {
		printf("\nGRESKA!Neuspjela alokacija!");
		return NULL;
	}

	strcpy(Nova->Drzava, naziv);
	Nova->Gradovi = NULL; //
	Nova->Next = NULL;

	pDat = fopen(datotekaGradovi, "r");
	if (!pDat) {
		printf("\nGRESKA!Neuspjelo otvaranje!");
		return NULL;
	}

	while (!feof(pDat)) {
		fscanf(pDat, " %s %d ", grad, &broj);
		Nova->Gradovi = UnosGrada(Nova->Gradovi, grad, broj);
	}

	fclose(pDat);

	return Nova;
}

Pozicija UnosDrzava(Pozicija P, char* naziv, char* datoteka)
{
	Pozicija Nova = StvoriDrzavu(naziv, datoteka);

	while(P->Next != NULL) {
		
		if (strcmp(naziv, P->Next->Drzava) < 1) {
			Nova->Next = P->Next;
			P->Next = Nova;
			return P;
		}

		else
			P = P->Next;

	}
	
	if (P->Next == NULL) {
		P->Next = Nova;
		P = P->Next;
	}
	


	return P;
}

StabloP StvoriGrad(char* naziv, int br)
{
	StabloP Novi = NULL;

	Novi = (StabloP)malloc(sizeof(Stablo));
	if (!Novi) {
		printf("\nGreska!Neuspjela alokacija!");
		return NULL;
	}

	strcpy(Novi->Grad, naziv);
	Novi->Stanovnistvo = br;
	Novi->Desni = NULL;
	Novi->Lijevi = NULL;

	return Novi;
}

StabloP UnosGrada(StabloP Trenutni, char* naziv, int br)
{
	if (Trenutni == NULL)
		Trenutni = StvoriGrad(naziv, br);

	else if (br < Trenutni->Stanovnistvo)
		Trenutni->Lijevi = UnosGrada(Trenutni->Lijevi, naziv, br);

	else if (br > Trenutni->Stanovnistvo)
		Trenutni->Desni = UnosGrada(Trenutni->Desni, naziv, br);

	else {
		if (strcmp(naziv, Trenutni->Grad) < 1)
			Trenutni->Lijevi = UnosGrada(Trenutni->Lijevi, naziv, br);
		else
			Trenutni->Desni = UnosGrada(Trenutni->Desni, naziv, br);
	}


	return Trenutni;
}

int IspisDrzava(Pozicija P)
{
	
	if (P == NULL) {
		printf("\nLista je prazna...");
		return EXIT_SUCCESS;
	}

	while (P != NULL) {
		printf("\nDrzava: %s", P->Drzava);
		printf("\n\tGradovi:");
		IspisGradova(P->Gradovi);
		P = P->Next;

	}



	return EXIT_SUCCESS;
}

StabloP IspisGradova(StabloP Trenutni)
{
	if (Trenutni == NULL)
		return Trenutni;

	IspisGradova(Trenutni->Lijevi);
	printf("\n\t\t%s ", Trenutni->Grad);
	printf("\n\t\t\tBroja stanovnika: %d", Trenutni->Stanovnistvo);
	IspisGradova(Trenutni->Desni);

	return Trenutni;
}

int IspisOdredeneDrzave(Pozicija P, char* naziv, int uvjet)
{
	while (P != NULL) {
		if (strcmp(P->Drzava, naziv) == 0) {
			printf("\nDrzava: %s", P->Drzava);
			printf("\n\tGradovi s vise od %d stanovnika: ", uvjet);
			IspisOdredenihGradova(P->Gradovi, uvjet);
			return EXIT_SUCCESS;
		}
		P = P->Next;
	}

		
	if (P == NULL) {
		printf("\nTrazena drzava ne postoji...");
		return EXIT_SUCCESS;
	}
	

	return EXIT_SUCCESS;
}

StabloP IspisOdredenihGradova(StabloP Trenutni, int uvjet)
{
	if (Trenutni == NULL)
		return Trenutni;
	

	IspisOdredenihGradova(Trenutni->Lijevi, uvjet);
	if (Trenutni->Stanovnistvo >= uvjet) {
		printf("\n\t\t%s ", Trenutni->Grad);
		printf("\n\t\t\tBroja stanovnika: %d", Trenutni->Stanovnistvo);
	}
	IspisOdredenihGradova(Trenutni->Desni, uvjet);


	return Trenutni;
}

