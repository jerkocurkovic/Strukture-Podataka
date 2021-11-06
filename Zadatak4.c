#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 25

struct _polinom;
typedef struct _polinom* Pozicija;

typedef struct _polinom {
	int Koef;
	int Exp;
	Pozicija Next;
} Polinom;


int OtvaranjeDatoteke(Pozicija P, char* datoteka);
int UnosPolinoma(Pozicija P, int Koef, int Exp);
int IspisPolinoma(Pozicija Prvi);
int ZbrajanjePolinoma(Pozicija Zbroj, Pozicija P1, Pozicija P2);
int ProduktPolinoma(Pozicija Produkt, Pozicija P1, Pozicija P2);


int main()
{
	Polinom p1 = { .Koef = 0, .Exp = 0, .Next = NULL };
	Polinom p2 = { .Koef = 0, .Exp = 0, .Next = NULL };
	Polinom zbroj = { .Koef = 0, .Exp = 0, .Next = NULL }; 
	Polinom produkt = { .Koef = 0, .Exp = 0, .Next = NULL };


	char datoteka1[MAX_SIZE] = { 0 };
	char datoteka2[MAX_SIZE] = { 0 };
	
	

	printf("\nUnesite naziv datoteke za polinom p1(NAPOMENA: na kraj dodajte .txt): ");
	scanf(" %s", datoteka1);

	printf("\nUnesite naziv datoteke za polinom p2(NAPOMENA: na kraj dodajte .txt): ");
	scanf(" %s", datoteka2);
		
		
	OtvaranjeDatoteke(&p1, datoteka1);
	printf("\nPolinom p1: ");
	IspisPolinoma(p1.Next);
	puts("");

	OtvaranjeDatoteke(&p2, datoteka2);
	printf("\nPolinom p2: ");
	IspisPolinoma(p2.Next);
	puts("");

	ZbrajanjePolinoma(&zbroj, &p1, &p2);
	printf("\np1+p2= ");
	IspisPolinoma(zbroj.Next);
	puts("");

	ProduktPolinoma(&produkt, &p1, &p2);
	printf("\np1*p2= ");
	IspisPolinoma(produkt.Next);
	puts("");
	


	return EXIT_SUCCESS;
}

int OtvaranjeDatoteke(Pozicija P, char* datoteka)
{
	FILE* pDat = NULL;
	int tempKoef = 0, tempExp = 0;


	pDat = fopen(datoteka, "r");

	if (!pDat) {
		printf("\nGRESKA!Neuspjelo otvaranje");
		return -1;
	}

	while (!feof(pDat)) {
		fscanf(pDat, " %d %d", &tempKoef, &tempExp);
		UnosPolinoma(P, tempKoef, tempExp);

	}

	return EXIT_SUCCESS;
}




int UnosPolinoma(Pozicija P, int Koef, int Exp)
{
	Pozicija NoviPolinom = NULL;
	Pozicija prethodnik = P;

	P = P->Next;
	

	while (P != NULL && P->Exp > Exp) {
		prethodnik = P;
		P=P->Next;
	}

	if (P != NULL && P->Exp == Exp)
		P->Koef += Koef;

		else {
			NoviPolinom = (Pozicija)malloc(sizeof(Polinom));

			if (!NoviPolinom) {
				printf("\nGRESKA!Nemoguca alokacija memorije");
				return -1;
			}

			NoviPolinom->Exp = Exp;
			NoviPolinom->Koef = Koef;
			NoviPolinom->Next = P;
			prethodnik->Next = NoviPolinom;

		}
	

	return EXIT_SUCCESS;
}

int IspisPolinoma(Pozicija Prvi) {

	Pozicija temp = Prvi;


	while (temp->Next != NULL) {	

		if (temp->Koef < 0) 
			printf("(%d)x^(%d)", temp->Koef, temp->Exp);
		else
			printf("%dx^(%d)", temp->Koef, temp->Exp);
		printf("+");

		temp = temp->Next;
	}

	if (temp->Koef < 0)
		printf("(%d)x^(%d)", temp->Koef, temp->Exp);
	else
		printf("%dx^(%d)", temp->Koef, temp->Exp);

	return EXIT_SUCCESS;
}

int ZbrajanjePolinoma(Pozicija Zbroj, Pozicija P1, Pozicija P2)
{
	Pozicija temp = NULL;

	while (P1!=NULL && P2!=NULL){
		if (P1->Exp == P2->Exp) {
			UnosPolinoma(Zbroj, P1->Koef + P2->Koef, P1->Exp);

			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->Exp > P2->Exp) {
			UnosPolinoma(Zbroj, P1->Koef, P1->Exp);

			P1 = P1->Next;
		}

		else {
			UnosPolinoma(Zbroj, P2->Koef, P2->Exp);

			P2 = P2->Next;
		}

	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL) {

		UnosPolinoma(Zbroj, temp->Koef, temp->Exp);
		temp = temp->Next;
	}


	return EXIT_SUCCESS;
}

int ProduktPolinoma(Pozicija Produkt, Pozicija P1, Pozicija P2)
{
	Pozicija Pocetak = P2;
	while (P1 != NULL) {
		P2 = Pocetak;
		while (P2 != NULL) {
			UnosPolinoma(Produkt, P1->Koef * P2->Koef, P1->Exp + P2->Exp);
			P2 = P2->Next;
		}
		P1 = P1->Next;

	}


	return EXIT_SUCCESS;
}