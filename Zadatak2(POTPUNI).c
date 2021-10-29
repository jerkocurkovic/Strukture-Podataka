#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

struct _osoba;
typedef struct _osoba* Pozicija;

typedef struct _osoba {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godinarodenja;
	Pozicija next;
}osoba;

Pozicija StvoriOsobu();
int DodajNaPocetak(Pozicija Head);
int Ispisi(Pozicija Prvi);
Pozicija PronadiZadnjeg(Pozicija Head);
int DodajNaKraj(Pozicija Head);
Pozicija PronadiOsobuPoPrezimenu(Pozicija Prvi, char* prezime);
Pozicija PronadiOdredenuOsobu(Pozicija Prvi, char* ime, char* prezime, int godinarodenja);
Pozicija PronadiPrethodnika(Pozicija Head, Pozicija Clan);
int BrisiOdredenuOsobu(Pozicija Head, char* ime, char* prezime, int godinarodenja);

int main()
{
	osoba Head = { .ime = {0}, .prezime = {0}, .godinarodenja = 0, .next = NULL };
	Pozicija temp=NULL;
	char ime[MAX_SIZE] = { 0 };
	char prezime[MAX_SIZE] = { 0 };
	int godinarodenja = 0;
	int brelemenata=0;
	int i = 0;
	int odabir = 5;

	printf("\nUnesite broj elemenata vezane liste: ");
	scanf(" %d", &brelemenata);
	puts("");

	for (i = 0; i < brelemenata; i++) {

		DodajNaPocetak(&Head);
	}

	while (odabir != 0) {
		printf("\n1 - Dodaj novu osobu na pocetak liste");
		printf("\n2 - Ispisi listu");
		printf("\n3 - Dodaj novu osobu na kraj liste");
		printf("\n4 - Pronadi osobu u listi(po prezimenu)");
		printf("\n5 - Obrisi odredenu osobu iz liste");
		printf("\n0 - Kraj");
		puts("");
		scanf(" %d", &odabir);

		if (odabir == 1)
				DodajNaPocetak(&Head);

		else if (odabir == 2)
				Ispisi(Head.next);

		else if (odabir == 3)
				DodajNaKraj(&Head);

		else if (odabir == 4) {
				printf("\nUnesite prezime trazene osobe: ");
				scanf(" %s", prezime);
				temp = PronadiOsobuPoPrezimenu(Head.next, prezime);
				printf("\nIme: %s\tPrezime: %s\tGodina rodenja: %d", temp->ime, temp->prezime, temp->godinarodenja);
				puts("");

				temp = NULL;
				memset(prezime, 0, MAX_SIZE);
			}

		else if (odabir == 5) {
				printf("\nUnesite ime osobe: ");
				scanf(" %s", ime);
				printf("\nUnesite prezime osobe: ");
				scanf(" %s", prezime);
				printf("\nUnesite godinu rodenja osobe: ");
				scanf(" %d", &godinarodenja);

				BrisiOdredenuOsobu(&Head, ime, prezime, godinarodenja);

				memset(ime, 0, MAX_SIZE);
				memset(prezime, 0, MAX_SIZE);
				godinarodenja = 0;
			}

		}

		

	

	return EXIT_SUCCESS;

}

Pozicija StvoriOsobu()
{

	Pozicija NovaOsoba = NULL;
	char ime[MAX_SIZE] = { 0 };
	char prezime[MAX_SIZE] = { 0 };
	int godinarodenja = 0;

	NovaOsoba = (Pozicija)malloc(sizeof(osoba));
	if (!NovaOsoba) {
		printf("\nGRESKA!!!NEMOGUCA ALOKACIJA MEMORIJE\n");
		return NULL;
	}

	printf("\nUnesite ime osobe: ");
	scanf(" %s", ime);
	printf("\nUnesite prezime osobe: ");
	scanf(" %s", prezime);
	printf("\nUnesite godinu rodenja osobe: ");
	scanf(" %d", &godinarodenja);

	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godinarodenja = godinarodenja;

	NovaOsoba->next = NULL;

	return NovaOsoba;
}

int DodajNaPocetak(Pozicija Head)
{
	Pozicija NovaOsoba = StvoriOsobu();
	NovaOsoba->next = Head->next;
	Head->next = NovaOsoba;

	return EXIT_SUCCESS;
}

int Ispisi(Pozicija Prvi)
{
	Pozicija temp = Prvi;
	int brojac = 0;

	while (temp) {
		printf("\n%d. osoba: ", brojac + 1);
		printf("\nIme: %s\tPrezime: %s\tGodina rodenja: %d", temp->ime, temp->prezime, temp->godinarodenja);

		temp = temp->next;
		brojac++;
	}
	puts("");

	return EXIT_SUCCESS;
}

Pozicija PronadiZadnjeg(Pozicija Head)
{
	Pozicija temp = Head;
	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}

int DodajNaKraj(Pozicija Head)
{
	Pozicija NovaOsoba = NULL;
	Pozicija temp = NULL;

	temp = PronadiZadnjeg(Head);
	NovaOsoba = StvoriOsobu();

	NovaOsoba->next = temp->next;
	temp->next = NovaOsoba;


	return EXIT_SUCCESS;
}

Pozicija PronadiOsobuPoPrezimenu(Pozicija Prvi, char* prezime)
{
	Pozicija temp = Prvi;
	while (temp) {

		if (strcmp(temp->prezime, prezime) == 0) {
			return temp;
		}
		temp = temp->next;

	}

	return NULL;
}

Pozicija PronadiOdredenuOsobu(Pozicija Prvi, char* ime, char* prezime, int godinarodenja)
{
	Pozicija temp = Prvi;
	while (temp) {

		if ((strcmp(temp->prezime, prezime) == 0) && (strcmp(temp->ime, ime) == 0) && (temp->godinarodenja == godinarodenja))
		{
			return temp;
		}
		temp = temp->next;

	}

	return NULL;
}

Pozicija PronadiPrethodnika(Pozicija Head, Pozicija Clan)
{
	Pozicija prethodnik = NULL;
	prethodnik = Head;
	Head = Head->next;

	while (Head != NULL && Head != Clan)
	{
		prethodnik = Head;
		Head = Head->next;
	}

	if (Head == NULL)
		return NULL;
	else
		return prethodnik;


}

int BrisiOdredenuOsobu(Pozicija Head, char* ime, char* prezime, int godinarodenja)
{

	Pozicija prethodnik = NULL;
	Pozicija temp = NULL;

	temp = PronadiOdredenuOsobu(Head->next, ime, prezime, godinarodenja);
	prethodnik = PronadiPrethodnika(Head, temp);

	if (prethodnik == NULL)
		printf("\nGRESKA!!\n");
	else {
		temp = prethodnik->next;
		prethodnik->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}