#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_SIZE 1024

struct _stablo;
typedef struct _stablo* StabloP;
typedef struct _stablo {

	int Element;
	StabloP Lijevi;
	StabloP Desni;

}stablo;

struct _stog;
typedef struct _stog* Pozicija;
typedef struct _stog {

	int Broj;
	Pozicija Next;

}stog;


StabloP Insert(StabloP trenutni, int broj);
StabloP StvoriNovi(int broj);
int Replace(StabloP trenutni);
int Push(Pozicija P, int Broj);
int Pop(Pozicija P);
int Inorder(StabloP trenutni);
int DodajNaStog(Pozicija P, StabloP trenutni);
int UpisiUDatoteku(Pozicija P, StabloP trenutni, char* imedatoteke);
int ObrisiStablo(StabloP trenutni);


int main()
{

	StabloP root = NULL;
	stog head = { .Broj = 0, .Next = NULL };
	int i = 0;
	int broj = 0;
	int Niz[10] = { 2,5,7,8,11,1,4,2,3,7 };
	char imedatoteke[MAX_SIZE] = { 0 };
	srand((unsigned)time(NULL));


	for (i = 0; i < 10; i++)
		root = Insert(root, Niz[i]);

	printf("\nUnesite naziv datoteke(NAPOMENA: na kraj dodajte .txt): ");
	scanf(" %s", imedatoteke);

	Inorder(root);
	puts(" ");

	DodajNaStog(&head, root);
	UpisiUDatoteku(&head, root, imedatoteke);

	Replace(root);
	Inorder(root);
	DodajNaStog(&head, root);
	UpisiUDatoteku(&head, root, imedatoteke);
	ObrisiStablo(root);

	// dio pod c)
	root = NULL;
	printf("\nUnesite broj elemenata stabla: ");
	scanf("%d", &broj);

	for (i = 0; i < broj; i++)
		root = Insert(root, (rand() % 81 + 10));
	Inorder(root);
	puts(" ");

	DodajNaStog(&head, root);
	UpisiUDatoteku(&head, root, imedatoteke);

	Replace(root);
	Inorder(root);
	DodajNaStog(&head, root);
	UpisiUDatoteku(&head, root, imedatoteke);
	ObrisiStablo(root);
	
	return EXIT_SUCCESS;

}

StabloP Insert(StabloP trenutni, int broj) 
{
	if (trenutni == NULL) {
		trenutni = StvoriNovi(broj);
		return trenutni;
	}

	else if (trenutni->Element > broj)
		trenutni->Desni = Insert(trenutni->Desni, broj);

	else if (trenutni->Element <= broj)
		trenutni->Lijevi = Insert(trenutni->Lijevi, broj);

	return trenutni;
}

StabloP StvoriNovi(int broj)
{
	StabloP novi = NULL;

	novi = (StabloP)malloc(sizeof(stablo));

	if (!novi){
		printf("\nGRESKA!!Neuspjela alokacija memorije!");
		return NULL;

	}

	novi->Element = broj;
	novi->Lijevi = NULL;
	novi->Desni = NULL;


	return novi;
}




int Replace(StabloP trenutni)
{
	int zbroj = 0;
	int tempbr = 0;

	if (trenutni != NULL){
		zbroj = Replace(trenutni->Lijevi);
		zbroj = zbroj + Replace(trenutni->Desni);

		tempbr = trenutni->Element;
		trenutni->Element = zbroj;
		zbroj = zbroj + tempbr;
	}
	return zbroj;
}

int Push(Pozicija P, int Broj)
{
	Pozicija NoviElement = NULL;

	NoviElement = (Pozicija)malloc(sizeof(stog));
	if (!NoviElement){
		printf("\nGreska!Nemoguca alokacija memorije");
		return -1;
	}

	NoviElement->Broj = Broj;
	NoviElement->Next = P->Next;
	P->Next = NoviElement;


	return EXIT_SUCCESS;
}

int Pop( Pozicija P)
{
	Pozicija Prvi = P->Next;
	Pozicija temp = NULL;
	int Broj = Prvi->Broj;

	temp = Prvi;
	if (!temp)
		return EXIT_SUCCESS;

	P->Next = temp->Next;
	free(temp);
	
	return EXIT_SUCCESS;

}

int Inorder(StabloP trenutni)
{
	if (trenutni == NULL)
		return EXIT_SUCCESS;

	Inorder(trenutni->Lijevi);
	printf(" %d ", trenutni->Element);
	Inorder(trenutni->Desni);

	return EXIT_SUCCESS;
}

int DodajNaStog(Pozicija P, StabloP trenutni)
{
	if (trenutni == NULL)
		return EXIT_SUCCESS;
	

	DodajNaStog(P, trenutni->Desni);
	Push(P, trenutni->Element);
	DodajNaStog(P, trenutni->Lijevi);

	return EXIT_SUCCESS;
}

int UpisiUDatoteku(Pozicija P, StabloP trenutni, char* imedatoteke)
{
	FILE* pDat = NULL;

	pDat = fopen(imedatoteke, "a");
	if (!pDat){
		printf("\nGreska pri otvaranju datoteke!");
		return -1;
	}

	while (P->Next != NULL)
	{
		fprintf(pDat, "%d ", P->Next->Broj);
		Pop(P);
	}

	fprintf(pDat, "\n");

	fclose(pDat);

	return EXIT_SUCCESS;
}

int ObrisiStablo(StabloP trenutni)
{
	if (trenutni == NULL)
		return EXIT_SUCCESS;

	ObrisiStablo(trenutni->Lijevi);
	ObrisiStablo(trenutni->Desni);

	free(trenutni);

	return EXIT_SUCCESS;
}